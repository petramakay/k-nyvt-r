#include "sorozat.h"

///kiiro fuggveny
void Sorozat::kiir(std::ostream& os) const{
    Konyv::kiir(os);
    os << ", " << nev.c_str() << ", " << hanyadik << ". resz";
}

///kiiro fuggveny fajlhoz
void Sorozat::fajlbair(std::ostream& os, std::string elv) const{
    os << cim.c_str() << elv << szerzo.c_str() << elv << mufaj.c_str() << elv << kiado.c_str() << elv << ev
    << elv  << nev.c_str() << elv << hanyadik << std::endl;
}
