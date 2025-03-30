#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H
#include "Billable.h"
namespace seneca {
   class Drink:public Billable {
      char m_size{};
   public:
      virtual std::ostream& print(std::ostream& ostr = std::cout)const;
      virtual bool order();
      virtual bool ordered()const;
      virtual std::ifstream& read(std::ifstream& file);
      virtual double price()const;
   };
}
#endif // !SENECA_DRINK_H


