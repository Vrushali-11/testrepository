#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
namespace seneca {
   class Food:public Billable {
      bool m_ordered{};
      bool m_child{};
      char* m_customize{};
      void customize();
   public:
      Food() = default;
      Food(const Food& other);
      virtual ~Food();
      Food& operator=(const Food& other);
      virtual std::ostream& print(std::ostream& ostr = std::cout)const;
      virtual bool order();
      virtual bool ordered()const;
      virtual std::ifstream& read(std::ifstream& file);
      virtual double price()const;
   };
}
#endif // !SENECA_FOOD_H


