#include "kmk.h"

///kiiro fuggveny
void KMK::kiir(std::ostream& os) const{
    Konyv::kiir(os);
    os << ", " << szin.c_str();
}

///kiiro fuggveny fajlhoz
void KMK::fajlbair(std::ostream& os, std::string elv) const{
    os << cim.c_str() << elv << szerzo.c_str() << elv << mufaj.c_str() << elv << kiado.c_str() << elv
    << ev << elv << szin.c_str() << std::endl;
}

///kiiro fuggveny
void KMKsorozat::kiir(std::ostream& os) const{
    KMK::kiir(os);
    os << ", " << Sorozat::nev.c_str() << ", " << Sorozat::hanyadik << ". resz";
}

///kiiro fuggveny fajlba
void KMKsorozat::fajlbair(std::ostream& os, std::string elv) const{
    os << cim.c_str() << elv << szerzo.c_str() << elv << mufaj.c_str() << elv << kiado.c_str() << elv
    << ev << elv << szin.c_str() << elv << nev.c_str() << elv << hanyadik << std::endl;
}
