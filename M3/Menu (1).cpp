#include <iostream>
#include "Menu.h"
#include  "Utils.h"
#include "constants.h"
using namespace std;
namespace seneca {
   MenuItem::MenuItem(const char* content, size_t no_of_indentations, size_t indentation_size, int row=-1) :
      m_content{ ut.alocpy(content) },
      m_indentNo{ no_of_indentations },
      m_indentSize{ indentation_size },
      m_row{ row } {
      if ( row > static_cast<int>(MaximumNumberOfMenuItems) || m_indentNo > 4 || m_indentSize > 4 || ut.isspace(m_content)) {
         delete[] m_content;
         m_content = nullptr;
      }
   }
   std::ostream& MenuItem::display(std::ostream& ostr) const{
      if (m_content) {
         ostr.fill(' ');
         ostr.width(m_indentNo * m_indentSize);
         ostr << "";
         if (m_row >= 0) {
            ostr.width(2);
            ostr.setf(ios::right);
            ostr << m_row << "- ";
            ostr.unsetf(ios::right);
         }
         char* c = m_content;
         while (ut.isspace(*c)) {
            c++;
         }
         ostr << c;
      }
      else {
         ostr << "??????????";
      }
      return ostr;
   }
   MenuItem::~MenuItem(){
      delete[] m_content;
   }
   MenuItem::operator bool() const{
      return m_content != nullptr;
   }
 

   size_t operator<<(std::ostream& ostr, const Menu& m){
      size_t selection = 0;
      if (&ostr == &cout) {
         selection = m.select();
      }
      return selection;
   }

   Menu::Menu(const char* title, const char* exitText,size_t indentation, size_t indentationSize):
      m_indentation{ indentation }, 
      m_indentation_size{ indentationSize },
      m_title{ title, indentation, indentationSize },
      m_exit{ exitText,indentation, indentationSize,0 },
      m_prompt{ "> ", indentation, indentationSize } {}

   Menu& Menu::operator<<(const char* menuItem){
      if (m_noOfItems < MaximumNumberOfMenuItems) {
         m_items[m_noOfItems] = new MenuItem(menuItem, m_indentation, m_indentation_size, static_cast<int>(m_noOfItems)+1);
         m_noOfItems++;
      }
      return *this;
   }

   size_t Menu::select() const{
      if (m_title) m_title.display() << endl;
      for (size_t i = 0; i < m_noOfItems; i++) {
         m_items[i]->display() << endl;
      }
      m_exit.display() << endl;
      m_prompt.display();
      return ut.getInt(0, static_cast<int>(m_noOfItems));
   }

   Menu::~Menu(){
      for (size_t i = 0; i < m_noOfItems; delete m_items[i++]);
   }

}