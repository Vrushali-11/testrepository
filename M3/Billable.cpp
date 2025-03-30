#include "Billable.h"
#include "Utils.h"
namespace seneca {
   void Billable::price(double value){
      m_price = value;
   }
   void Billable::name(const char* name){ 
      ut.alocpy(m_name, name);
   }
   Billable::Billable(const Billable& other) :m_name{ut.alocpy(other)} {
      m_price = other.m_price;
   }
   Billable& Billable::operator=(const Billable& other){
      if (this != &other) {
         ut.alocpy(m_name, other);
         m_price = other.m_price;
      }
      return *this;
   }
   Billable::~Billable(){
      delete[] m_name;
   }
   Billable::operator const char* () const{
      return m_name;
   }
   double Billable::price() const{
      return m_price;
   }
   double operator+(double money, const Billable& B) {
      return money + B.price();
   }
   double& operator+=(double& money, const Billable& B){
      return money += B.price();
   }

}
