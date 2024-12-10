#ifndef KMK_H_INCLUDED
#define KMK_H_INCLUDED
#include "memtrace.h"
#include "string.h"
#include "konyv.h"
#include "sorozat.h"

class KMK : public virtual Konyv{
protected:
    String szin;
public:
    ///konstruktorok
    KMK (const String& c="-", const String& s="-", const String& m="-", const String& k="-", int e=0, const String& sz="-")
        : Konyv(c, s, m, k, e), szin(sz) {};

    KMK(std::string c, std::string s, std::string m, std::string k, std::string e, std::string sz)
        :Konyv(c, s, m, k, e), szin(sz.c_str()) {}

    ///kiiro fuggveny
    void kiir(std::ostream& os = std::cout) const;

    ///kiiro fuggveny fajlhoz
    void fajlbair(std::ostream& os, std::string elv) const;

    ///get-ter
    String getszin() const { return szin; }

    ~KMK() {}

};

class KMKsorozat : public KMK, public Sorozat{
public:
    ///konstruktorok
    KMKsorozat(const String& c="-", const String& s="-", const String& m="-", const String& k="-", int e=0, const String& sz="-", String nev ="-", double hanyadik = 0){
        Konyv::cim = c;
        Konyv::szerzo = s;
        Konyv::mufaj = m;
        Konyv::kiado = k;
        Konyv::ev = e;
        KMK::szin = sz;
        Sorozat::nev = nev;
        Sorozat::hanyadik = hanyadik;
    }

    KMKsorozat(std::string c, std::string s, std::string m, std::string k, std::string e, std::string sz, std::string nev, std::string h)
        :Konyv(c, s, m, k, e), KMK(c, s, m, k, e, sz), Sorozat(c, s, m, k, e, nev, h) {};


    ///kiiro fuggveny
    void kiir(std::ostream& os = std::cout) const;

    ///kiiro fuggveny fajlba
    void fajlbair(std::ostream& os, std::string elv) const;

    ~KMKsorozat() {}

};

#endif // KMK_H_INCLUDED
