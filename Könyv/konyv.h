#ifndef KONYV_H_INCLUDED
#define KONYV_H_INCLUDED

#include "string.h"
#include "memtrace.h"

class Konyv{
protected:
    String cim;
    String szerzo;
    String mufaj;
    String kiado;
    int ev;
public:
    ///konstruktorok
    Konyv(const String& c="-", const String& s="-", const String& m="-", const String& k="-", int e=0)
        :cim(c), szerzo(s), mufaj(m), kiado(k), ev(e) {}

    Konyv(std::string c, std::string s, std::string m, std::string k, std::string e){
        cim = c.c_str();
        szerzo = s.c_str();
        mufaj = m.c_str();
        kiado = k.c_str();
        ev = std::stoi(e);
    }

    ///kiiro fuggveny
    virtual void kiir(std::ostream& os = std::cout) const;

    ///kiiro fuggveny fajlhoz
    virtual void fajlbair(std::ostream& os, std::string elv) const;

    ///get-terek
    String getcim() const { return cim; }
    String getszerzo() const { return szerzo; }
    String getmufaj() const { return mufaj; }
    String getkiado() const { return kiado; }
    int getev() const { return ev; }

    ///virtualis destruktor az orokles miatt
    virtual~Konyv() {};

};




#endif // KONYV_H_INCLUDED
