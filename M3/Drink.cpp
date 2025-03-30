#include <iostream>
#include <fstream>
#include "Drink.h"
#include "Utils.h"
#include "Menu.h"
using namespace std;
namespace seneca {
   std::ostream& Drink::print(std::ostream& ostr) const{
      char name[26];
      ut.strcpy(name, *this, 25);
      ostr.width(28);
      ostr.fill('.');
      ostr.setf(ios::left);
      ostr << name;
      ostr.unsetf(ios::left);
      switch (m_size) {
      case 'S':
         ostr << "SML..";
         break;
      case 'M':
         ostr << "MID..";
         break;
      case 'L':
         ostr << "LRG..";
         break;
      case 'X':
         ostr << "XLR..";
         break;
      default: 
         ostr << ".....";
      }
      ostr.width(7);
      ostr.fill(' ');
      ostr.setf(ios::right);
      ostr.setf(ios::fixed);
      ostr.precision(2);
      ostr << price();
      ostr.unsetf(ios::right);
      return ostr;
   }
   bool Drink::order(){
      Menu order("Drink Size Selection", "Back", 3);
      order << "Small" << "Medium" << "Larg" << "Extra Large";
      switch (order.select()){
      case 1:
         m_size = 'S';
         break;
      case 2:
         m_size = 'M';
         break;
      case 3:
         m_size = 'L';
         break;
      case 4:
         m_size = 'X';
         break;
      default:
         m_size = char(0);
      }
      return ordered();
   }

   bool Drink::ordered() const{
      return static_cast<bool>(m_size);
   }

   std::ifstream& Drink::read(std::ifstream& file)   {
      char buffer[71];
      double thePrice;
      file.getline(buffer, 71, ',');
      file >> thePrice;
      file.ignore(10000, '\n');
      if (file) {
         Billable::name(buffer);
         Billable::price(thePrice);
         m_size = char(0);
      }
      return file;
   }
   double Drink::price() const{
      double thePrice = Billable::price();
      if (ordered()) {
         if (m_size == 'S') thePrice *= 0.5;
         else if (m_size == 'M') thePrice *= 0.75;
         else if (m_size == 'X') thePrice *= 1.5;
      }
      return thePrice;
   }
}