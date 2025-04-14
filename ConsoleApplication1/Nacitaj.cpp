
#include "Nacitaj.h"

Nacitaj::Nacitaj()
{
}

Nacitaj::~Nacitaj()
{
    if (this->citac1.is_open())
    {
        this->citac1.close();
    }
    else if (this->citac2.is_open())
    {
        this->citac2.close();
    }
    else if (this->citac3.is_open())
    {
        this->citac3.close();
    }
    else if (this->citac4.is_open())
    {
        this->citac4.close();
    }
    else if (this->citac5.is_open())
    {
        this->citac5.close();
    }
}

std::vector<Obec> Nacitaj::NacitajObce() {
    std::vector<Obec> obce;
    
    std::string cesta = "C://Users//marpl//OneDrive - Žilinská univerzita v Žiline//4-semester//Ausko//SemestralnaPraca1Cast//SemestralnaPraca1Cast//";

    citac1.open(cesta + "2020.csv");
    citac2.open(cesta + "2021.csv");
    citac3.open(cesta + "2022.csv");
    citac4.open(cesta + "2023.csv");
    citac5.open(cesta + "2024.csv");

    if (!citac1.is_open() || !citac2.is_open() || !citac3.is_open() || !citac4.is_open() || !citac5.is_open()) {
        std::cerr << "Subor sa nepodarilo otvorit" << std::endl;
        exit(1);
    }

    std::string riadok1, riadok2, riadok3, riadok4, riadok5;

    // Funkcia na spracovanie jedn�ho riadku CSV
    auto parseLine = [](const std::string& riadok, std::string& nazov, int& agg, int& male, int& female) {
        std::istringstream stream(riadok);
        std::string temp;
        getline(stream, nazov, ';');  // Nazov obce

        getline(stream, temp, ';');   // Aggregation
        temp.erase(std::remove(temp.begin(), temp.end(), '<'), temp.end());
        temp.erase(std::remove(temp.begin(), temp.end(), '>'), temp.end());
        agg = temp.empty() ? 0 : std::stoi(temp);

        getline(stream, temp, ';');   // Pocet muzov
        male = temp.empty() ? 0 : std::stoi(temp);

        getline(stream, temp, ';');   // Pocet zien
        female = temp.empty() ? 0 : std::stoi(temp);
        };

    // Nacitanie platnych riadkov zo vsetkych suborov
    while (getline(citac1, riadok1) && getline(citac2, riadok2) &&
        getline(citac3, riadok3) && getline(citac4, riadok4) &&
        getline(citac5, riadok5)) {

        // Ak sa v ktoromko�vek zo s�borov objav� "Nicht klassifizierbar", ukon��me ��tanie
        if (riadok1.find("Nicht klassifizierbar") != std::string::npos ||
            riadok2.find("Nicht klassifizierbar") != std::string::npos ||
            riadok3.find("Nicht klassifizierbar") != std::string::npos ||
            riadok4.find("Nicht klassifizierbar") != std::string::npos ||
            riadok5.find("Nicht klassifizierbar") != std::string::npos) {
            break;  // Ukon��me cyklus
        }

        std::string nazov;
        int aggregation = 0, male20 = 0, female20 = 0, male21 = 0, female21 = 0;
        int male22 = 0, female22 = 0, male23 = 0, female23 = 0, male24 = 0, female24 = 0;

        std::string tempNazov;

        // Spracovanie jednotliv�ch riadkov
        parseLine(riadok1, tempNazov, aggregation, male20, female20);
        parseLine(riadok2, tempNazov, aggregation, male21, female21);
        parseLine(riadok3, tempNazov, aggregation, male22, female22);
        parseLine(riadok4, tempNazov, aggregation, male23, female23);
        parseLine(riadok5, tempNazov, aggregation, male24, female24);

        // Ulo�enie obce do vektora
        obce.emplace_back(tempNazov, aggregation, male20, female20, male21, female21,
            male22, female22, male23, female23, male24, female24);
    }

    return obce;
}
