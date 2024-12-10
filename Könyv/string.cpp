#include "string.h"
#include <cstring>

///konstruktorok
String::String(char s){
    len = 1;
    pData = new char[len + 1];
    pData[0] = s;
    pData[1] = '\0';
}

String::String(const char* s){
    len = strlen(s);
    pData = new char[len + 1];
    strcpy(pData, s);
}

///masolo konstruktor
String::String(const String& s){
    len = s.len;
    if(s.pData == NULL)
        pData = NULL;
    else{
        pData = new char[len + 1];
        strcpy(pData, s.pData);
    }
}

///ertekado operator
String& String::operator=(const String& s){
    if(this != &s){
        delete [] pData;
        len = s.len;
        pData = new char[len+1];
        strcpy(pData, s.pData);
    }
    return *this;
}

///osszehasonlito operator
bool String::operator==(const String& s){
    bool jolesz = false;
    for(size_t i = 0; i<len; i++){
        if(pData[i] == s.pData[i])
            jolesz = true;
        else
            jolesz = false;
    }
    return (len == s.len && jolesz);
}


///indexelo operatorok
char& String::operator[](size_t idx){
    if(idx >= len || idx < 0)
        throw std::invalid_argument("Hibas index!");
    return pData[idx];
}

char String::operator[](size_t idx) const{
    if(idx >= len || idx <0)
        throw std::invalid_argument("Hibas index!");
    return pData[idx];
}


