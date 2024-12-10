#include <iostream>
#include <string>
#include "gtest_lite.h"
#include "konyv.h"
#include "sorozat.h"
#include "kmk.h"
#include "nyilvantartas.h"
#include "string.h"
#include "memtrace.h"

//#define CPORTA

#ifndef CPORTA
void menu(){
    std::cout << "Valaszd ki a szam beirasaval, hogy mit szeretnel csinalni:" << std::endl;
    std::cout << "|0. Kilepes" << std::endl << "|1. Konyv hozzaadasa" << std::endl;
    std::cout << "|2. Konyv torlese" << std::endl << "|3. Konyv keresese" << std::endl;
    std::cout << "|4. Sorozat listazasa" << std::endl << "|5. Konyvek listazasa" << std::endl;
    std::cout << "|6. Mentes" << std::endl;
    std::cout << std::endl;
    std::cout << "Valasztott szam: ";
}
#endif // CPORTA

int main(){

#ifdef CPORTA
    Nyilvantartas lista;
    lista.beolvas(lista, "konyvek.txt");

    GTINIT(std::cin);

    ///fajlbeolvasas tesztjei
    TEST(Teszt1, Fajlbeolvasas: ha nem tudja beolvasni kivetelt dob){
        Nyilvantartas proba;
        EXPECT_THROW(proba.beolvas(proba, "konyvek.t"), std::invalid_argument);
    }
    END

    TEST(Teszt2, Fajlbeolvasas: elso sor adatainak tesztelese){
        EXPECT_STREQ("Csontvaros", lista[0].getcim().c_str());
    }
    END

    TEST(Teszt3, Fajlbeolvasas: beolvasott adatok szama){
        EXPECT_EQ(13, lista.getmeret());
    }
    END

    ///konstruktorok tesztjei
    TEST(Teszt4, Default konstruktor tesztje){
        Konyv* uj = new Konyv();
        EXPECT_STREQ("-", uj->getcim().c_str());
        EXPECT_STREQ("-", uj->getszerzo().c_str());
        delete uj;
    }
    END

    TEST(Teszt 5, Sorozat: konstruktor teszt){
        Sorozat* sorozat = new Sorozat("Az ejszaka kiralya", "Laura Thalassa", "fantasy", "Anassa Konyvek", 2022, "Az Alkusz", 1);
        EXPECT_STREQ("Az Alkusz", sorozat->getnev().c_str());
        EXPECT_EQ(1, sorozat->gethanyadik());
        delete sorozat;
    }
    END

    ///bool tesztje
    TEST(Teszt 6, Bool teszt){
        KMKsorozat* boolteszt1 = new KMKsorozat("Arnyek es csont", "Leigh Bardugo", "fantasy", "Konyvmolykepzo", 2014, "Voros pottyos", "Grisa trilogia", 1);
        Konyv* boolteszt2 = new Konyv("Buszkeseg es balitelet", "Jane Austen", "klasszikus", "Meno Konyvek", 2022);
        EXPECT_TRUE(lista.bennevan(boolteszt1));
        EXPECT_FALSE(lista.bennevan(boolteszt2));
        delete boolteszt1;
        delete boolteszt2;
    }
    END

    ///hozzaadas tesztje
    TEST(Teszt 7, Nem letezo uj konyv hozzaadasa){
        Sorozat* hozzaadteszt = new Sorozat("Szeretlek, Hawaii!", "Tomor Anita", "kortars", "Pyrius", 2022, "Hollywood", 4);
        lista.hozzaad(hozzaadteszt);
        EXPECT_EQ(14, lista.getmeret());
        EXPECT_STREQ("Szeretlek, Hawaii!", lista[13].getcim().c_str());
        EXPECT_STREQ("kortars", lista[13].getmufaj().c_str());
    }
    END

    TEST(Teszt 8, Letezo uj konyv hozzaadasa){
        Konyv* hozzaadteszt = new Konyv("Akkor szakitsunk", "Leiner Laura", "ifjusagi", "L&L", 2014);
        EXPECT_THROW(lista.hozzaad(hozzaadteszt), std::invalid_argument);
    }
    END

    ///torles tesztje
    TEST(Teszt 8, Elso elem torlese){
        EXPECT_NO_THROW(lista.torol(0));
        EXPECT_EQ(13, lista.getmeret());
    }
    END

    TEST(Teszt 9, Letezo konyv torlese index alapjan){
        EXPECT_NO_THROW(lista.torol(5));
        EXPECT_EQ(12, lista.getmeret());
    }
    END

    TEST(Teszt 10, Torles hibas index-el){
        EXPECT_THROW(lista.torol(-10), std::invalid_argument);
    }
    END

    TEST(Teszt 11, Adott konyv torlese){
        EXPECT_NO_THROW(lista.torol("Uvegtron"));
        EXPECT_THROW(lista.torol("Jok es Rosszak Iskolaja"), std::invalid_argument);
        EXPECT_EQ(11, lista.getmeret());
    }
    END

    ///kereses tesztje
    TEST(Teszt 12, Kereses adott konyvek){
        KMKsorozat* keresteszt1 = new KMKsorozat("Arnyek es csont", "Leigh Bardugo", "fantasy", "Konyvmolykepzo", 2014, "Voros pottyos", "Grisa trilogia", 1);
        Konyv* keresteszt2 = new Konyv("Jane Austen", "Buszkeseg es balitelet", "klasszikus", "Meno Konyvek", 2022);
        EXPECT_NO_THROW(lista.keres(keresteszt1));
        std::cout << std::endl;
        EXPECT_ANY_THROW(lista.keres(keresteszt2));
        delete keresteszt1;
        delete keresteszt2;
    }
    END

    ///Index teszt
    TEST(Teszt 13, Jo index eseten){
        EXPECT_NO_THROW(lista[0]);
        EXPECT_STREQ("Kincsem", lista[0].getcim().c_str());
        EXPECT_STREQ("Szelesi Sandor", lista[0].getszerzo().c_str());
    }
    END

    TEST(Teszt 14, Rossz index eseten){
        EXPECT_THROW(lista[-10], std::invalid_argument);
        EXPECT_THROW(lista[100], std::invalid_argument);
    }
    END

    ///sorozat kivalogat
    TEST(Teszt 15, Adott sorozat reszeinek kiirasa){
        EXPECT_NO_THROW(lista.valogat("Uvegtron"));
    }
    END

    TEST(Teszt 16, Fajlbairas){
        EXPECT_NO_THROW(lista.mentes(lista, "konyvek1.txt"));
    }
    END

    if (!gtest_lite::test.fail())
        std::cout << std::endl << "Szuper! Minden teszteset jol lefutott!" << std::endl;

    GTEND(std::cerr);

#endif //CPORTA

#ifndef CPORTA

    try{
    Nyilvantartas lista;
    lista.beolvas(lista, "konyvek1.txt");


    menu();

    std::string input;
    while(std::cin >> input){
        try{
            int i;
            try{
                i = stoi(input);
            }catch(std::exception& e){
                i = 100;
            }
            if(i==0) { break; }
            switch(i){
                default:
                        std::cout << "Hibas szam, vagy ervenytelen formatum! Kerlek probald meg ujra: ";
                        break;
                case 1:{
                    std::cout << "------------------------------" << std::endl;
                    std::cout << "Add meg az uj konyv adatait:" << std::endl;
                    std::string cim, szerzo, mufaj, kiado, ev, szin, nev, hanyadik;
                    std::cout << "Cim: ";
                    getchar();
                    std::getline(std::cin, cim);
                    std::cout << "Szerzo: ";
                    std::getline(std::cin, szerzo);
                    std::cout << "Mufaj: ";
                    std::getline(std::cin, mufaj);
                    std::cout << "Kiado: ";
                    std::getline(std::cin, kiado);
                    std::cout << "Kiadasi ev: ";
                    int kilep2;
                    int ellenoriz;
                    while(kilep2 != 0){
                        std::getline(std::cin, ev);
                        try{
                            ellenoriz = stoi(ev);
                            kilep2 = 0;
                        }catch(std::exception& e){
                            std::cout << "Hibas formatum! Kerlek probald meg ujra: ";
                        }
                    }
                    std::string sorozate;
                    std::cout << "|Sorozat resze? " << std::endl << "1: Igen / 2: Nem : ";
                    int valasz;
                    int kilep = 0;
                    while(kilep != -2){
                        std::cin >> sorozate;
                        try{
                            valasz = stoi(sorozate);
                        }catch(std::exception& e){
                            kilep = 0;
                        }
                        switch(valasz){
                            case 1:{
                                if(kiado == "Konyvmolykepzo"){
                                std::cout << "Konyvmolykepzo tipus: ";
                                getchar();
                                std::getline(std::cin, szin);
                                std::cout << "Sorozat cime: ";
                                std::getline(std::cin, nev);
                                std::cout << "Hanyadik resze: ";
                                int kilep3 = -2;
                                double ellenoriz2;
                                while(kilep3 != 0){
                                    std::getline(std::cin, hanyadik);
                                    try{
                                        ellenoriz2 = stod(hanyadik);
                                        kilep3 = 0;
                                    }catch(std::exception& e){
                                        std::cout << "Hibas formatum! Kerlek probald meg ujra: ";
                                    }
                                }
                                lista.hozzaad(new KMKsorozat(cim, szerzo, mufaj, kiado, ev, szin, nev, hanyadik));
                                std::cout << "|Az uj konyv rogzitesre kerult!" << std::endl;
                                std::cout << "------------------------------" << std::endl;
                                kilep = -2;
                                std::cout << std::endl;
                                menu();
                                break;
                            }
                            else{
                                std::cout << "Sorozat cime: ";
                                getchar();
                                std::getline(std::cin, nev);
                                std::cout << "Hanyadik resze: ";
                                int kilep3 = -2;
                                double ellenoriz2;
                                while(kilep3 != 0){
                                    std::getline(std::cin, hanyadik);
                                    try{
                                        ellenoriz2 = stod(hanyadik);
                                        kilep3 = 0;
                                    }catch(std::exception& e){
                                        std::cout << "Hibas formatum! Kerlek probald meg ujra: ";
                                    }
                                }
                                lista.hozzaad(new Sorozat(cim, szerzo, mufaj, kiado, ev, nev, hanyadik));
                                std::cout << "|Az uj konyv rogzitesre kerult!" << std::endl;
                                std::cout << "------------------------------" << std::endl;
                                kilep = -2;
                                std::cout << std::endl;
                                menu();
                                break;
                            }
                            break;

                            }

                          case 2:{
                            if(kiado == "Konyvmolykepzo"){
                                std::cout << "Konyvmolykepzo tipus: ";
                                getchar();
                                std::getline(std::cin, szin);
                                lista.hozzaad(new KMK(cim, szerzo, mufaj, kiado, ev, szin));
                                std::cout << "|Az uj konyv rogzitesre kerult!" << std::endl;
                                std::cout << "------------------------------" << std::endl;
                                kilep = -2;
                                std::cout << std::endl;
                                menu();
                                break;
                            }
                            else{
                                lista.hozzaad(new Konyv(cim, szerzo, mufaj, kiado, ev));
                                std::cout << "|Az uj konyv rogzitesre kerult!" << std::endl;
                                std::cout << "------------------------------" << std::endl;
                                kilep = -2;
                                std::cout << std::endl;
                                menu();
                                break;
                            }
                            break;
                            }

                            default:{
                                std::cout << "Hibas szam, vagy ervenytelen formatum! Kerlek probald meg ujra: ";
                                break;
                            }
                        } //belso switch
                    } //belso while
                    break;
                } //nagy case 1


                case 2:{
                    std::string torles;
                    int egesz;
                    int valasz2 = 0;
                    std::cout << "------------------------------" << std::endl;
                    std::cout << "Mi alapjan szeretnel torolni: " << std::endl;
                    std::cout << "1: index / 2: konyv megadas: ";
                    while(valasz2 != -2){
                        std::cin >> torles;
                        try{
                            egesz = stoi(torles);
                        }catch(std::exception& e){
                            valasz2 = 0;
                        }
                        switch(egesz){
                            default:{
                                std::cout << "Hibas szam, vagy ervenytelen formatum! Kerlek probald meg ujra: ";
                                break;
                            }

                            case 1:{
                                int idx;
                                std::cout << "Index alapjan torles: ";
                                std::cin >> idx;
                                lista.torol(idx);
                                std::cout << "|A konyv torolve lett!" << std::endl;
                                std::cout << "------------------------------" << std::endl;
                                valasz2 = -2;
                                std::cout << std::endl;
                                menu();
                                break;
                            }
                        case 2:{
                            std::cout << "Torolni kivant konyv adatai: " << std::endl;
                            std::string cim, szerzo, mufaj, kiado, ev, szin, nev, hanyadik;
                            std::cout << "Cim: ";
                            getchar();
                            std::getline(std::cin, cim);
                            lista.torol(cim);
                            std::cout << "|A konyv torolve lett!" << std::endl;
                            std::cout << "------------------------------" << std::endl;
                            valasz2 = -2;
                            std::cout << std::endl;
                            menu();
                            break;
                        }
                    }
                    }
                    break;
                }

                case 3:{
                    std::string keresoszo;
                    std::cout << "------------------------------" << std::endl;
                    std::cout << "Ird be amit keresel, a program kilistazza a talalatokat (cim, szerzo): ";
                    getchar();
                    std::getline(std::cin, keresoszo);
                    std::cout << "------------------------------" << std::endl;
                    lista.keres(String(keresoszo));
                    std::cout << "------------------------------" << std::endl;
                    std::cout << std::endl;
                    menu();
                    break;
                }

                case 4:{
                    std::cout << "------------------------------" << std::endl;
                    std::cout << "Melyik sorozat reszeire vagy kivancsi: ";
                    std::string sorozat;
                    getchar();
                    std::getline(std::cin, sorozat);
                    std::cout << "------------------------------" << std::endl;
                    lista.valogat(String(sorozat));
                    std::cout << "------------------------------" << std::endl;
                    std::cout << std::endl;
                    menu();
                    break;
                }

                case 5:{
                    std::cout << "------------------------------" << std::endl;
                    std ::cout << "Nyilvantartasban levo konyvek: " << std::endl;
                    lista.kilistaz();
                    std::cout << "------------------------------" << std::endl;
                    std::cout << std::endl;
                    menu();
                    break;
                }

                case 6:{
                    lista.mentes(lista, "konyvek1.txt");
                    std::cout << "Valtoztatasok elmentve!" << std::endl;
                    std::cout << std::endl;
                    menu();
                    break;
                }

            }
        }catch (std::exception& e){
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
            menu();
        }
    }

    }catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }
#endif //CPORTA


    return 0;
}
