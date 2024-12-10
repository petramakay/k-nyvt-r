#include "nyilvantartas.h"

///eldonti, hogy egy konyv benne van-e a nyilvantartasban
bool Nyilvantartas::bennevan(Konyv* keres) const{
    for(size_t i = 0; i<meret; i++){
        if(keres->getcim() == adat[i]->getcim() && keres->getszerzo() == adat[i]->getszerzo()){
            return true;
        }
    }
    return false;
}

bool Nyilvantartas::bennevan(String keres) const{
    for(size_t i = 0; i<meret; i++){
        if(keres == adat[i]->getcim()){
            return true;
        }
        else if(keres == adat[i]->getszerzo()){
            return true;
        }
    }
    return false;
}

///indexoperatorok
Konyv& Nyilvantartas::operator[](size_t idx){
    if(idx >= meret || idx < 0)
        throw std::invalid_argument("Ervenytelen index!");
    return *adat[idx];
}


///hozzaado fuggveny
void Nyilvantartas::hozzaad(Konyv* ujelem){
    if(bennevan(ujelem)){
        delete ujelem;
        throw std::invalid_argument("Ez a konyv mar szerepel a nyilvantartasban!");
    }
    meret++;
    Konyv** tmp = new Konyv*[meret];
    for(size_t i = 0; i<meret-1; i++)
        tmp[i] = adat[i];
    tmp[meret-1] = ujelem;
    delete[] adat;
    adat = tmp;
}


///torlo fuggveny index alapjan
void Nyilvantartas::torol(size_t idx){
    if(idx >= meret || idx < 0)
        throw std::invalid_argument("Hibas index!");
    if(idx == 0){
        Konyv** uj = new Konyv*[meret-1];
        for(size_t i = 0; i<meret; i++)
            uj[i] = adat[i+1];
        delete adat[idx];
        delete[] adat;
        adat = uj;
        meret--;
    }
    else{
        --meret;
        Konyv** uj = new Konyv*[meret];
        size_t i;
        for(i = 0; i<idx; ++i)
            uj[i] = adat[i];

        delete adat[idx];

        for(i += 1; i<meret+1; i++)
            uj[i-1] = adat[i];

        delete[]adat;
        adat = uj;
    }
}


///torlo fuggveny cim alapjan
void Nyilvantartas::torol(String cim){
    if(!bennevan(cim))
        throw std::invalid_argument("Nem letezo konyv torlese!");
    else{
        size_t idx;
        for(size_t i = 0; i<meret; i++){
            if(adat[i]->getcim() == cim)
                idx = i;
        }
        --meret;
        Konyv** uj = new Konyv*[meret];
        size_t i;

        for(i = 0; i<idx; i++)
            uj[i] = adat[i];

        delete adat[idx];

        for(i += 1; i<meret+1; i++)
            uj[i-1] = adat[i];

        delete[] adat;
        adat = uj;
    }
}


///kereso fuggveny
void Nyilvantartas::keres(Konyv* k) const{
    if(bennevan(k)){
        k->kiir();
    }
    else{
        throw std::invalid_argument("|Nincs talalat! Esetleg nezd meg, hogy jol irtad-e be!");
    }
}

void Nyilvantartas::keres(String keres) const{
    if(!bennevan(keres)) throw std::invalid_argument("|Nincs talalat! Esetleg nezd meg, hogy jol irtad-e be!");
    for(size_t i = 0; i<meret; i++){
        if(adat[i]->getcim() == keres){
            adat[i]->kiir();
            std::cout << std::endl;
        }
        else if(adat[i]->getszerzo() == keres){
            adat[i]->kiir();
            std::cout << std::endl;
        }
    }
}

///listazo fuggveny
void Nyilvantartas::kilistaz(std::ostream& os) const{
    for(size_t i = 0; i<meret; i++){
        os << i << ": ";
        adat[i]->kiir(os);
        os << std::endl;
    }
}

///sorozat kereso
void Nyilvantartas::valogat(String nev){
    int szamol;
    for(size_t i = 0; i<meret; i++){
        Sorozat* proba = dynamic_cast<Sorozat*>(adat[i]);
        if(proba != NULL){
            if(proba->getnev() == nev){
                proba->kiir();
                std::cout << std::endl;
                szamol++;
            }
        }
    }
    if(szamol == 0) throw std::invalid_argument("Nincs ilyen sorozat a nyilvantartasban!");
}

///fajlbeolvasas
void Nyilvantartas::beolvas(Nyilvantartas& konyvek, const std::string fajlnev) const{
    std::ifstream fajlolvaso;
    fajlolvaso.open(fajlnev.c_str());
    std::string beolvasottsor;

    if(fajlolvaso.is_open()){
        while(getline(fajlolvaso, beolvasottsor)){
            std::string darabok[8];
            size_t szamlalo = 0;
            size_t elso = 0;
            size_t utolso = beolvasottsor.find(";");

            while (utolso != std::string::npos){
                darabok[szamlalo++] = beolvasottsor.substr(elso, utolso-elso);
                elso = utolso + 1;
                utolso = beolvasottsor.find(";", elso);
            }
            darabok[szamlalo++] = beolvasottsor.substr(elso, utolso-elso);

            if(szamlalo == 5)
                konyvek.hozzaad(new Konyv(darabok[0], darabok[1], darabok[2], darabok[3], darabok[4]));
            if(szamlalo == 7)
                konyvek.hozzaad(new Sorozat(darabok[0], darabok[1], darabok[2], darabok[3], darabok[4], darabok[5], darabok[6]));
            if(szamlalo == 6)
                konyvek.hozzaad(new KMK(darabok[0], darabok[1], darabok[2], darabok[3], darabok[4], darabok[5]));
            if(szamlalo == 8)
                konyvek.hozzaad(new KMKsorozat(darabok[0], darabok[1], darabok[2], darabok[3], darabok[4], darabok[5], darabok[6], darabok[7]));

        }
    } else { throw std::invalid_argument("Nem tudtam betolteni a fajlt!"); }
}


void Nyilvantartas::mentes(Nyilvantartas& konyvek, const std::string fajlnev){
    std::ofstream fajliro;
    fajliro.open(fajlnev.c_str());
    if(fajliro.is_open()){
        for(size_t i = 0; i<konyvek.getmeret(); ++i)
            konyvek[i].fajlbair(fajliro, ";");
    } else { throw std::invalid_argument("Nem tudtam kimenteni a fajlt!"); }
}

