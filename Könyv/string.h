#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <iostream>
#include "memtrace.h"

class String{
    char *pData;
    size_t len;
public:
    ///parameter nelkuli konstruktor
    String() :pData(NULL), len(0) {}

    ///konstruktorok
    String(char s);
    String(const char *s);
    String(const std::string& s){
        len = s.size();
        pData = new char[len + 1];
        for(size_t i = 0; i<len; i++)
            pData[i] = s[i];
    }

    ///masolo konstruktor
    String(const String& s);

    ///ertekado operator
    String& operator=(const String& s);

    ///osszehasonlito operator
    bool operator==(const String& s);

    ///sztring hossza
    size_t size() const { return len; }

    ///sztringet ad vissza
    const char* c_str() const {
        if(pData == NULL)
            return "";
        else
            return pData;
    }

    ///indexelo operatorok
    char& operator[](size_t idx);
    char operator[](size_t idx) const;


    ///destruktor
    virtual ~String() {
        delete[] pData; }


};


#endif // STRING_H_INCLUDED
