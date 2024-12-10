#ifndef SOROZAT_H_INCLUDED
#define SOROZAT_H_INCLUDED
#include"konyv.h"
#include "string.h"
#include "memtrace.h"

class Sorozat : virtual public Konyv {
protected:
    String nev;
    double hanyadik;
public:
    ///konstruktorok
    Sorozat(const String& c="-", const String& s="-", const String& m="-", const String& k="-", int e=0, const String& n="-", double h=0)
        : Konyv(c,s,m,k,e), nev(n), hanyadik(h) {};

    Sorozat(std::string c, std::string s, std::string m, std::string k, std::string e, std::string n, std::string h)
        :Konyv(c, s, m, k, e){
        nev = n.c_str();
        hanyadik = std::stod(h);
    }

    ///get-terek
    String getnev() const { return nev; }
    double gethanyadik() const { return hanyadik; }

    ///kiiro fuggveny
    void kiir(std::ostream& os = std::cout) const;

    ///kiiro fuggveny fajlhoz
    void fajlbair(std::ostream& os, std::string elv) const;

    ~Sorozat() {}

};

#endif // SOROZAT_H_INCLUDED
