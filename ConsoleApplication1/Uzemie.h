/*
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
class Uzemie
{
private:
	std::string nazovUzemia;
	int cisloUzemia;
	int male20 = 0;
	int female20 = 0;
	int male21 = 0;
	int female21 = 0;
	int male22 = 0;
	int female22 = 0;
	int male23 = 0;
	int female23 = 0;
	int male24 = 0;
	int female24 = 0;
public:
	Uzemie(std::string nazovUzemie, int cisloUzemia);
	Uzemie(const Uzemie& zdroj);
	Uzemie& operator=(Uzemie& zdroj);
	Uzemie& operator == ( Uzemie& zdroj);
	~Uzemie();

	int getPocetPohlavie(std::string pohlavie, int rok);
	int getPocetVRoku(int rok) const;
	void set(int rok, int muzi, int zeny);
	std::string getNazov() const;
	int getCisloUzemia() const;

};*/

#pragma once
#include <string>

class Uzemie {
public:
    // Verejné premenné a/alebo metódy pod¾a potreby
    std::string nazovUzemia;
    int cisloUzemia;
    int male20;
    int female20;
    int male21;
    int female21;
    int male22;
    int female22;
    int male23;
    int female23;
    int male24;
    int female24;

    Uzemie();
    // Konstruktor s parametrami
    Uzemie(std::string nazovUzemia, int cisloUzemia);

    // Kopírovací konštruktor
    Uzemie(const Uzemie& zdroj);

    // Operátor priradenia – opravenej signatúry (prijíma const referenciu)
    Uzemie& operator=(const Uzemie& zdroj);

    // Operátor porovnania – vracia bool
    bool operator==(const Uzemie& zdroj) const;

    // Destruktor
    ~Uzemie();

    // Príklad metód, ak potrebuješ ïalšie getter-y (napr. getCisloUzemia)
   

    int getPocetPohlavie(std::string pohlavie, int rok);
    int getPocetVRoku(int rok) const;
    void setUzemie(int rok, int muzi, int zeny);
    std::string getNazov() const;
    int getCisloUzemia() const;
};
