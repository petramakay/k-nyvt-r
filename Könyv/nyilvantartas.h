#ifndef NYILVANTARTAS_H_INCLUDED
#define NYILVANTARTAS_H_INCLUDED

#include <fstream>
#include <iostream>
#include "memtrace.h"
#include "string.h"
#include "konyv.h"
#include "sorozat.h"
#include "kmk.h"

class Nyilvantartas{
    Konyv** adat;
    size_t meret;
public:
    ///konstruktor
    Nyilvantartas() :adat(NULL), meret(0) {};

    ///masolo konstruktor
    Nyilvantartas(const Nyilvantartas& n){
        delete[] adat;
        meret = n.meret;
        for(size_t i = 0; i<meret; i++)
            adat[i] = n.adat[i];
    }

    ///get-ter
    size_t getmeret() const { return meret; }

    ///eldonti, hogy egy konyv benne van-e a nyilvantartasban
    bool bennevan(Konyv* keres) const;
    bool bennevan(String cim) const;

    ///indexoperator
    Konyv& operator[](size_t idx);

    ///hozzaado fuggveny
    void hozzaad(Konyv* ujelem);

    ///torlo fuggveny index alapjan
    void torol(size_t idx);

    ///torlo fuggveny cim alapjan
    void torol(String cim);

    ///kereso fuggveny
    void keres(Konyv* k) const;
    void keres(String keres) const;

    ///listazo fuggveny
    void kilistaz(std::ostream& os = std::cout) const;

    ///sorozat kereso
    void valogat(String nev);

    ///fajlbeolvasas
    void beolvas(Nyilvantartas& konyvek, const std::string fajlnev) const;

    ///fajlkiiras
    void mentes(Nyilvantartas& konyvek, const std::string fajlnev);

    ///destruktor
    virtual ~Nyilvantartas(){
        for(size_t i = 0; i<meret; i++){
            delete adat[i];
        }
        delete[] adat;
    }
};


#endif // NYILVANTARTAS_H_INCLUDED
