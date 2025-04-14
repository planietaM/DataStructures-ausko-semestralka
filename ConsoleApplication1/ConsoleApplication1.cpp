#include <libds/amt/explicit_hierarchy.h>

#include "Uzemie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Nacitaj.h"
#include <Windows.h>
//pre citanie klavesnice
#include <conio.h>
#include "Algoritmus.h"

int main()
{
    SetConsoleOutputCP(1252);
    Nacitaj nacitaj;
    std::vector<Obec> obce;
    obce = nacitaj.NacitajObce();
   
    std::ifstream citac("C://Users//marpl//OneDrive - Žilinská univerzita v Žiline//4-semester//Ausko//Semestralka Ausko//uzemie.csv");
    std::ifstream citacObci("C://Users//marpl//OneDrive - Žilinská univerzita v Žiline//4-semester//Ausko//Semestralka Ausko//obce.csv");
    if (!citac.is_open() || !citacObci.is_open()) {
        std::cerr << "Subor sa nepodarilo otvorit" << std::endl;
        return 1;
    }

    ds::amt::MultiWayExplicitHierarchy<Uzemie> hierarchia;
	const ds::amt::MultiWayExplicitHierarchy<Uzemie>* hierarchiaPtr = &hierarchia;

    // Create root
    ds::amt::MultiWayExplicitHierarchyBlock<Uzemie>& root = hierarchia.emplaceRoot();
    root.data_ = Uzemie("Austria", 0);

    std::string riadok;
    while (std::getline(citac, riadok)) {
        std::istringstream stream(riadok);
        std::string nazov;
        std::string kod;
        int cislo = 0;
        std::getline(stream, nazov, ';');
        std::getline(stream, kod);

        if (kod.size() > 4 && kod.substr(0, 3) == "<AT" && kod.back() == '>') {
            std::string cisloText = kod.substr(3, kod.size() - 4);
            cislo = std::stoi(cisloText);
        }

        if (cislo < 10) {
           
            size_t index1 = (std::to_string(cislo)[0] - '0') - 1; 
            auto& child = hierarchia.emplaceSon(root, index1);
            child.data_ = Uzemie(nazov, cislo);

            //std::cout << "Main region added at index " << index1 << ": " << nazov << std::endl;
        }
        else if (cislo < 100) {
            // Two-digit code: sub-region under a main region
            std::string cisloStr = std::to_string(cislo);
            size_t index1 = (cisloStr[0] - '0') - 1; // Parent index (0-based)
            size_t index2 = (cisloStr[1] - '0') - 1; // Child index (0-based)

            auto* parent = hierarchia.accessSon(root, index1);
            if (parent == nullptr) {
                //std::cerr << "Chyba: Rodicovsky region pre " << nazov << " nebol najdeny (index " << index1 << ")" << std::endl;
            }
            else {
                auto& child = hierarchia.emplaceSon(*parent, index2);
                child.data_ = Uzemie(nazov, cislo);
                //std::cout << "Subregion " << nazov << " pridany pod " << parent->data_.getNazov() << " na indexe2 " << index2 << std::endl;
            }
        }
        else if (cislo < 1000) {

            std::string cisloStr = std::to_string(cislo);
            size_t index1 = (cisloStr[0] - '0') - 1; // Parent index (0-based)
            size_t index2 = (cisloStr[1] - '0') - 1; // Child index (0-based)
            size_t index3 = (cisloStr[2] > '0') ? (cisloStr[2] - '0') - 1 : 0;
            if (index3 <= 0) {
                index3 = 0;
            }

            auto* parent = hierarchia.accessSon(root, index1);
			auto* parent2 = hierarchia.accessSon(*parent, index2);
            
            auto& child = hierarchia.emplaceSon(*parent2, index3);
            child.data_ = Uzemie(nazov, cislo);
            //std::cout << "Subregion " << nazov << " pridany pod " << parent->data_.getNazov() << " na indexe2 " << index2 << " na indexe3 " << index3 << std::endl;
        } 
    }
    
    int posledne_ulozene = 0;
    int indexer = -1;
	int indexObce = 0;
        while (std::getline(citacObci, riadok)) {
        std::istringstream stream(riadok);
        std::string nazov;
        std::string pscRaw;
        std::string kodRaw;
        
        std::getline(stream, nazov, ';');
        std::getline(stream, pscRaw, ';');
        std::getline(stream, kodRaw);

        std::string psc = pscRaw.substr(1, pscRaw.size() - 2); // odstráni < a >
        std::string kod = kodRaw.substr(2); // odstráni "AT" a nechá "111"

        int index1 = (kod[0] - '0') - 1; // Parent index (0-based)
        int index2 = (kod[1] - '0') - 1; // Child index (0-based)
        int index3 = (kod[2] > '0') ? (kod[2] - '0') - 1 : 0;
        if (index3 <= 0) {
            index3 = 0;
        }
        
        if (posledne_ulozene == index3) {
			indexer++;
		}
		else {
			posledne_ulozene = index3;
			indexer = 0;
        }

        Obec potrebnaObec = obce[indexObce];
        indexObce += 1;

        auto* parent = hierarchia.accessSon(root, index1);        
        parent->data_.setUzemie(2020, potrebnaObec.getPocetPohlavie("male", 2020), potrebnaObec.getPocetPohlavie("female", 2020));
        parent->data_.setUzemie(2021, potrebnaObec.getPocetPohlavie("male", 2021), potrebnaObec.getPocetPohlavie("female", 2021));
        parent->data_.setUzemie(2022, potrebnaObec.getPocetPohlavie("male", 2022), potrebnaObec.getPocetPohlavie("female", 2022));
        parent->data_.setUzemie(2023, potrebnaObec.getPocetPohlavie("male", 2023), potrebnaObec.getPocetPohlavie("female", 2023));
        parent->data_.setUzemie(2024, potrebnaObec.getPocetPohlavie("male", 2024), potrebnaObec.getPocetPohlavie("female", 2024));

        auto* parent2 = hierarchia.accessSon(*parent, index2);
        parent2->data_.setUzemie(2020, potrebnaObec.getPocetPohlavie("male", 2020), potrebnaObec.getPocetPohlavie("female", 2020));
        parent2->data_.setUzemie(2021, potrebnaObec.getPocetPohlavie("male", 2021), potrebnaObec.getPocetPohlavie("female", 2021));
        parent2->data_.setUzemie(2022, potrebnaObec.getPocetPohlavie("male", 2022), potrebnaObec.getPocetPohlavie("female", 2022));
        parent2->data_.setUzemie(2023, potrebnaObec.getPocetPohlavie("male", 2023), potrebnaObec.getPocetPohlavie("female", 2023));
        parent2->data_.setUzemie(2024, potrebnaObec.getPocetPohlavie("male", 2024), potrebnaObec.getPocetPohlavie("female", 2024));

        auto* parent3 = hierarchia.accessSon(*parent2, index3);
        parent3->data_.setUzemie(2020, potrebnaObec.getPocetPohlavie("male", 2020), potrebnaObec.getPocetPohlavie("female", 2020));
        parent3->data_.setUzemie(2021, potrebnaObec.getPocetPohlavie("male", 2021), potrebnaObec.getPocetPohlavie("female", 2021));
        parent3->data_.setUzemie(2022, potrebnaObec.getPocetPohlavie("male", 2022), potrebnaObec.getPocetPohlavie("female", 2022));
        parent3->data_.setUzemie(2023, potrebnaObec.getPocetPohlavie("male", 2023), potrebnaObec.getPocetPohlavie("female", 2023));
        parent3->data_.setUzemie(2024, potrebnaObec.getPocetPohlavie("male", 2024), potrebnaObec.getPocetPohlavie("female", 2024));

        auto& child = hierarchia.emplaceSon(*parent3, indexer);
        child.data_ = Uzemie(nazov, atoi(psc.c_str()));
        child.data_.setUzemie(2020, potrebnaObec.getPocetPohlavie("male", 2020), potrebnaObec.getPocetPohlavie("female", 2020));
        child.data_.setUzemie(2021, potrebnaObec.getPocetPohlavie("male", 2021), potrebnaObec.getPocetPohlavie("female", 2021));
        child.data_.setUzemie(2022, potrebnaObec.getPocetPohlavie("male", 2022), potrebnaObec.getPocetPohlavie("female", 2022));
        child.data_.setUzemie(2023, potrebnaObec.getPocetPohlavie("male", 2023), potrebnaObec.getPocetPohlavie("female", 2023));
        child.data_.setUzemie(2024, potrebnaObec.getPocetPohlavie("male", 2024), potrebnaObec.getPocetPohlavie("female", 2024));
		
		std::cout << "Obec " << nazov << " pridana pod " << parent->data_.getNazov() << " na indexe " << indexer << "  " << kodRaw << std::endl;
    }


    

    citac.close();
    std::cout << "Hierarchia uspesne nacitana! " << hierarchia.accessRoot()->data_.getPocetVRoku(2020)  << std::endl;

    
    const ds::amt::MultiWayExplicitHierarchyBlock<Uzemie>* vracajuciObjekt = hierarchia.accessRoot();

    std::cout << "Si na rodicovi " << vracajuciObjekt->data_.getNazov() << " -vyzsie nevies ist" << std::endl;
   
    std::cout << "Zadaj prikaz (hore, dole, vlavo, vpravo, dalej, spat):\n";

    bool running = true;
    int kolkoSynov = 0;
    Algoritmus algoritmus;

    while (running) {
        std::vector<Uzemie> uzemieVypis;
        int kolkoSynov = 0;

        std::string prikaz;
        std::cout << "> ";
        std::cin >> prikaz;

        if (prikaz == "hore") {
            if (vracajuciObjekt == hierarchia.accessRoot()) {
                std::cout << "Si na rodicovi " << vracajuciObjekt->data_.getNazov() << " -vyzsie nevies ist" << std::endl;
            }
            else {
                vracajuciObjekt = hierarchia.accessParent(*vracajuciObjekt);
                std::cout << "Si na rodicovi " << vracajuciObjekt->data_.getNazov() << std::endl;
            }
        }
        else if (prikaz == "dole") {
            if (std::to_string(vracajuciObjekt->data_.getCisloUzemia()).size() >= 5) {
                std::cout << "Si liste (Posledny syn Bez deti ) " << vracajuciObjekt->data_.getNazov() << " -nizsie nevies ist" << std::endl;
            }
            else {
                vracajuciObjekt = hierarchia.accessSon(*vracajuciObjekt, 0);
                std::cout << "Si na rodicovi " << vracajuciObjekt->data_.getNazov() << std::endl;
            }
        }
        else if (prikaz == "vlavo") {
            if (vracajuciObjekt == hierarchia.accessRoot()) {
                std::cout << "Si na synovi vlavo " << vracajuciObjekt->data_.getNazov() << std::endl;
            }
            else {
                kolkoSynov = hierarchia.accessParent(*vracajuciObjekt)->sons_->size();

                if (hierarchia.isNthSon(*vracajuciObjekt, 0)) {
                    std::cout << "Viac synov vlavo ako " << vracajuciObjekt->data_.getNazov() << " nie je" << std::endl;
                }
                else {
                    int index = 0;
                    for (int i = 0; i < kolkoSynov; i++) {
                        if (hierarchia.isNthSon(*vracajuciObjekt, i)) break;
                        index++;
                    }
                    vracajuciObjekt = hierarchia.accessSon(*hierarchia.accessParent(*vracajuciObjekt), index - 1);
                    std::cout << "Si na synovi vlavo " << vracajuciObjekt->data_.getNazov() << std::endl;
                }
            }
        }
        else if (prikaz == "vpravo") {
            if (vracajuciObjekt == hierarchia.accessRoot()) {
                std::cout << "Si na synovi vpravo " << vracajuciObjekt->data_.getNazov() << std::endl;
            }
            else {
                kolkoSynov = hierarchia.accessParent(*vracajuciObjekt)->sons_->size();

                if (hierarchia.isNthSon(*vracajuciObjekt, kolkoSynov - 1)) {
                    std::cout << "Viac synov vpravo ako " << vracajuciObjekt->data_.getNazov() << " nie je" << std::endl;
                }
                else {
                    int index = 0;
                    for (int i = 0; i < kolkoSynov; i++) {
                        if (hierarchia.isNthSon(*vracajuciObjekt, i)) break;
                        index++;
                    }
                    vracajuciObjekt = hierarchia.accessSon(*hierarchia.accessParent(*vracajuciObjekt), index + 1);
                    std::cout << "Si na synovi vpravo " << vracajuciObjekt->data_.getNazov() << std::endl;
                }
            }
        }
        else if (prikaz == "dalej") {
            std::cout << "Vyber si cislo od 1-4: (1=min, 2=max, 3=str, 4=hasType): ";
            int option;
            std::cin >> option;
            int rok=0;
            int pocet=0;
            std::string obsahuje = " ";
			std::string typUzemia = " ";

            
            ds::amt::MultiWayExplicitHierarchyBlock<Uzemie> pomocnyBegin = (*vracajuciObjekt);

            ds::amt::MultiWayExplicitHierarchy<Uzemie>::PreOrderHierarchyIterator beginHierar(&hierarchia, &pomocnyBegin);
            ds::amt::MultiWayExplicitHierarchy<Uzemie>::PreOrderHierarchyIterator endHierar(&hierarchia, nullptr);

            switch (option) {
            case 1:
				
                std::cout << " Vyber si rok pre minimum :" << std::endl;
                std::cin >> rok;
                std::cout << " Vyber si rok pre minimum " << std::endl;
                std::cin >> pocet;
				uzemieVypis = algoritmus.filter(beginHierar, endHierar, algoritmus.filterMinResidencePredicate(rok, pocet));
                break;
            case 2:
                
                std::cout << " Vyber si rok pre maximum :" << std::endl;
                std::cin >> rok;
                std::cout << " Vyber si rok pre maximum " << std::endl;
                std::cin >> pocet;
                uzemieVypis = algoritmus.filter(beginHierar, endHierar, algoritmus.filterMaxResidencePredicate(rok, pocet));
                break;
            case 3:

                std::cout << " Vyber string ktory obsahuje nazov :" << std::endl;
                std::cin >> obsahuje;
				uzemieVypis = algoritmus.filter(beginHierar, endHierar, algoritmus.filterContainsStrPredicate(obsahuje));
                break;
            case 4:
                std::cout << " Vyber typ ktoreho uzemie hladas : () pk , gd , sr , r , o " << std::endl;
                std::cin >> typUzemia;
				uzemieVypis = algoritmus.filter(beginHierar, endHierar, algoritmus.filterTypObce(typUzemia));
                break;
            default:
                std::cout << "Neplatna volba\n";
            }
        }
        else if (prikaz == "spat") {
            std::cout << "Koniec\n";
            running = false;
        }
        else {
            std::cout << "Neznamy prikaz: " << prikaz << std::endl;
        }

        for (const auto& uzemie : uzemieVypis) {
            std::cout << uzemie.getNazov() << " | " << uzemie.getCisloUzemia() << " | " << uzemie.getPocetVRoku(2021) << std::endl;
        }
    }
    
    return 0;
}