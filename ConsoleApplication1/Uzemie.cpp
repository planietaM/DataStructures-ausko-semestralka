#include "Uzemie.h"

// Konstruktor
Uzemie::Uzemie(std::string nazovUzemia, int cisloUzemia)
{
	this->nazovUzemia = nazovUzemia;
	this->cisloUzemia = cisloUzemia;

	// Inicializácia ostatných premenných na 0
	this->male20 = 0;
	this->female20 = 0;
	this->male21 = 0;
	this->female21 = 0;
	this->male22 = 0;
	this->female22 = 0;
	this->male23 = 0;
	this->female23 = 0;
	this->male24 = 0;
	this->female24 = 0;
}

// 
Uzemie::Uzemie() = default;

// Kopírovací konštruktor
Uzemie::Uzemie(const Uzemie& zdroj)
{
	this->nazovUzemia = zdroj.nazovUzemia;
	this->cisloUzemia = zdroj.cisloUzemia;
	this->male20 = zdroj.male20;
	this->female20 = zdroj.female20;
	this->male21 = zdroj.male21;
	this->female21 = zdroj.female21;
	this->male22 = zdroj.male22;
	this->female22 = zdroj.female22;
	this->male23 = zdroj.male23;
	this->female23 = zdroj.female23;
	this->male24 = zdroj.male24;
	this->female24 = zdroj.female24;
}

// Operátor priradenia
Uzemie& Uzemie::operator=(const Uzemie& zdroj)
{
	if (this != &zdroj)
	{
		this->nazovUzemia = zdroj.nazovUzemia;
		this->cisloUzemia = zdroj.cisloUzemia;
		this->male20 = zdroj.male20;
		this->female20 = zdroj.female20;
		this->male21 = zdroj.male21;
		this->female21 = zdroj.female21;
		this->male22 = zdroj.male22;
		this->female22 = zdroj.female22;
		this->male23 = zdroj.male23;
		this->female23 = zdroj.female23;
		this->male24 = zdroj.male24;
		this->female24 = zdroj.female24;
	}
	return *this;
}

// Operátor porovnania

bool Uzemie::operator == (const Uzemie& zdroj) const
{
	return (this->nazovUzemia == zdroj.nazovUzemia) &&
		(this->cisloUzemia == zdroj.cisloUzemia) &&
		(this->male20 == zdroj.male20) &&
		(this->female20 == zdroj.female20) &&
		(this->male21 == zdroj.male21) &&
		(this->female21 == zdroj.female21) &&
		(this->male22 == zdroj.male22) &&
		(this->female22 == zdroj.female22) &&
		(this->male23 == zdroj.male23) &&
		(this->female23 == zdroj.female23) &&
		(this->male24 == zdroj.male24) &&
		(this->female24 == zdroj.female24);
}

// Destruktor
Uzemie::~Uzemie()
{
	// Tu niè nemusíš robi, ak nemáš dynamicky alokované zdroje
}

int Uzemie::getPocetPohlavie(std::string pohlavie, int rok)
{
	if (pohlavie == "male") {
		switch (rok) {
		case 2020: return this->male20;
		case 2021: return this->male21;
		case 2022: return this->male22;
		case 2023: return this->male23;
		case 2024: return this->male24;
		}
	}
	else if (pohlavie == "female") {
		switch (rok) {
		case 2020: return this->female20;
		case 2021: return this->female21;
		case 2022: return this->female22;
		case 2023: return this->female23;
		case 2024: return this->female24;
		}
	}

	// Ak neexistuje zhodné pohlavie alebo rok
	return 0;
}

int Uzemie::getPocetVRoku(int rok) const
{
	switch (rok) {
	case 2020: return (this->male20 + this->female20);
	case 2021: return (this->male21 + this->female21);
	case 2022: return (this->male22 + this->female22);
	case 2023: return (this->male23 + this->female23);
	case 2024: return (this->male24 + this->female24);
	};
	return 0;
}

void Uzemie::setUzemie(int rok, int muzi, int zeny)
{
	switch (rok) {
	case 2020:
		this->male20 += muzi;
		this->female20 += zeny;
		break;
	case 2021:
		this->male21 += muzi;
		this->female21 += zeny;
		break;
	case 2022:
		this->male22 += muzi;
		this->female22 += zeny;
		break;
	case 2023:
		this->male23 += muzi;
		this->female23 += zeny;
		break;
	case 2024:
		this->male24 += muzi;
		this->female24 += zeny;
		break;
	}
}

std::string Uzemie::getNazov() const
{
	return this->nazovUzemia;
}

int Uzemie::getCisloUzemia() const
{
	return this->cisloUzemia;
}