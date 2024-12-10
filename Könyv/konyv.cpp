#include "konyv.h"

///kiiro fuggveny
void Konyv::kiir(std::ostream& os) const{
    os << cim.c_str() << ", " << szerzo.c_str() << ", " << mufaj.c_str() << ", " <<
    kiado.c_str() << ", " << ev;
}

///kiiro fuggveny fajlhoz
void Konyv::fajlbair(std::ostream& os, std::string elv) const{
    os << cim.c_str() << elv << szerzo.c_str() << elv << mufaj.c_str() << elv << kiado.c_str() << elv << ev << std::endl;
}
