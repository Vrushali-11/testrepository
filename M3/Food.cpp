#include <iostream>
#include <fstream>
#include "Food.h"
#include "Utils.h"
#include "Menu.h"
using namespace std;
namespace seneca {
   Food::Food(const Food& other):Billable(other),m_customize(ut.alocpy(other.m_customize)) {
      m_ordered = other.m_ordered;
      m_child = other.m_child;
   }
   Food::~Food(){
      delete[] m_customize;
   }
   Food& Food::operator=(const Food& other){
      if (this != &other) {
         Billable::operator=(other);
         ut.alocpy(m_customize, other.m_customize);
         m_ordered = other.m_ordered;
         m_child = other.m_child;
      }
      return *this;
   }
   std::ostream& Food::print(std::ostream& ostr) const{
      char name[26];
      ut.strcpy(name, *this, 25);
      ostr.width(28);
      ostr.fill('.');
      ostr.setf(ios::left);
      ostr << name;
      ostr.unsetf(ios::left);
      ostr << (m_ordered ? (m_child ? "Child" : "Adult") : ".....");
      ostr.width(7);
      ostr.fill(' ');
      ostr.setf(ios::right);
      ostr.setf(ios::fixed);
      ostr.precision(2);
      ostr << price();
      ostr.unsetf(ios::right);
      if (&ostr == &cout && m_customize) {
         ostr << " >> ";
         ut.print(ostr, m_customize, 30);
      }
      return ostr;
   }
   bool Food::order(){
      m_ordered = false;
      Menu order("Food Size Selection", "Back",3);
      order << "Adult" << "Child";
      switch (order.select()) {
      case 1:
         m_ordered = true;
         m_child = false;
         break;
      case 2:
         m_ordered = true;
         m_child = true;
         break;
      default:
         m_ordered = false;
         delete[] m_customize;
         m_customize = nullptr;
      }
      if (ordered()) customize();
      return ordered();
   }
   bool Food::ordered() const{
      return m_ordered;
   }
   std::ifstream& Food::read(std::ifstream& file)   {
      char buffer[71];
      double thePrice;
      file.getline(buffer, 71, ',');
      file >> thePrice;
      file.ignore(10000, '\n');
      if (file) {
         Billable::name(buffer);
         Billable::price(thePrice);
         m_child = false;
         m_ordered = false;
         delete[] m_customize;
         m_customize = nullptr;
      }
      return file;
   }
   void Food::customize(){
      cout << "Special instructions\n> ";
      if (cin.peek() == '\n') {
         cin.ignore();
         delete[] m_customize;
         m_customize = nullptr;
      }
      else {
         ut.read(m_customize, cin);
      }
   }
   double Food::price() const{
      double thePrice = Billable::price();
      if (ordered() && m_child) {
         thePrice /= 2;
      }
      return thePrice;
   }
}