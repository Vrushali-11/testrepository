#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"
namespace seneca {
   class Menu;
   class MenuItem {
      char* m_content{};
      size_t m_indentNo{ };
      size_t m_indentSize{  };
      int m_row{-1};
      MenuItem(const char* content, size_t no_of_indentations, size_t indentation_size, int row);
      MenuItem(const MenuItem&) = delete;
      MenuItem& operator=(const MenuItem&) = delete;
      virtual ~MenuItem();
      operator bool() const;
      friend class Menu;
      std::ostream& display(std::ostream& ostr = std::cout)const;
   };
   class Menu {
      size_t m_noOfItems{};
      size_t m_indentation{};
      size_t m_indentation_size{};
      MenuItem m_title;
      MenuItem m_exit;
      MenuItem m_prompt;
      MenuItem* m_items[MaximumNumberOfMenuItems]{};
   public:
      Menu(const Menu&) = delete;
      Menu& operator=(const Menu&) = delete;
      Menu(const char* title , const char* exitText = "Exit", size_t indentation = 0, size_t indentationSize = 3);
      Menu& operator<<(const char* menuItem);
      size_t select()const;
      virtual ~Menu();
   };
   size_t operator<<(std::ostream& ostr, const Menu& m);
}
#endif // !SENECA_MENU_H


