/***********************************************************************
// OOP244 Project, Utils Module
//
// File  Utils.h
// started by Fardad
// Description
// utility function to be used in the project
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
using namespace std;
#include "Utils.h"
namespace seneca {
   Utils ut;
   bool debug = false;
   const size_t AllocationBlockSize = 128;

   int Utils::getInt(int returnValue) const {
      if (cin.peek() != '\n') {
         returnValue = getInt();
      }
      return returnValue;
   }

   int Utils::getInt(int min, int max) const
   {
      int ret{};
      do {
         ret = getInt();
      } while ((ret < min || ret > max) &&
         cout << "Invalid value: [" << min << "<= value <=" << max << "], try again: ");
      return ret;
   }

   int Utils::getInt()const {
      int num{ };
      bool done = false;
      while (!done) {
         if (cin.peek() == '\n') {
            cin.ignore();
            cout << "You must enter a value: ";
         }
         else {
            cin >> num;
            if (cin.fail()) {
               cout << "Invalid integer: ";
               cin.clear();
            }
            else {
               if (cin.peek() != '\n') {
                  cout << "Only an integer please: ";
               }
               else {
                  done = true;
               }
            }
            cin.ignore(100000, '\n');
         }
      }
      return num;
   }



   char* Utils::alocpy(const char* src) const {
      char* des{};
      return alocpy(des, src);
   }

   char* Utils::alocpy(char*& des, const char* src)const {
      delete[] des;
      des = nullptr;
      if (src) {
         des = new char[strlen(src) + 1];
         strcpy(des, src);
      }
      return des;
   }


   char* Utils::strcpy(char* des, const char* src)const {
      int i;
      for (i = 0; src[i]; i++) des[i] = src[i];
      des[i] = char(0);
      return des;
   }
   char* Utils::strcpy(char* des, const char* src, int len)const {
      int i;
      for (i = 0; i < len && src[i]; i++) des[i] = src[i];
      des[i] = 0; // unlike strncpy, this function null terminates the des cstring
      return des;
   }
   char* Utils::strncpy(char* des, const char* src, int len)const {
      int i = 0;
      while (i < len - 1 && src[i]) {
         des[i] = src[i];
         i++;
      }
      des[i] = src[i];
      return des;
   }
  
   int Utils::strlen(const char* str)const {
      int len;
      for (len = 0; str[len]; len++);
      return len;
   }

   // Dynamically reads a cstring from istream
   char* Utils::read(char*& toRet, istream& istr, char delimiter)const {
      bool done = false;
      char* cstr = new char[AllocationBlockSize];
      toRet = cstr;
      int size = AllocationBlockSize;
      int nullindex = 1;
      do {
         istr.getline(cstr, AllocationBlockSize, delimiter);
         if (istr.fail()) {
            char* temp = new char[size + AllocationBlockSize];
            strcpy(temp, toRet);
            delete[] toRet;
            toRet = temp;
            cstr = &toRet[size - nullindex++];
            size += AllocationBlockSize;
            istr.clear();
         }
         else {
            done = true;
         }
      } while (!done);
      char* temp = new char[strlen(toRet) + 1];
      strcpy(temp, toRet);
      delete[] toRet;
      toRet = temp;
      return toRet;
   }
   ostream& Utils::print(ostream& ostr, const char* cstring, size_t maxlen) const {
      for (int i = 0; cstring && i < 30 && cstring[i]; ostr << cstring[i++]);
      return ostr;
   }

   bool Utils::isspace(char ch)const {
      return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
   }

   bool Utils::isspace(const char* cstring) const {
      while (cstring && isspace(*cstring)) {
         cstring++;
      }
      return cstring && *cstring == 0;
   }

}