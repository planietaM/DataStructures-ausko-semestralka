#include "Obec.h"

Obec::Obec(std::string nazovObce, int aggregation, int male20, int female20, int male21, int female21, int male22, int female22, int male23, int female23, int male24, int female24)
{
	this->nazovObce = nazovObce;
	this->aggregation = aggregation;
	this->male20 = male20;
	this->female20 = female20;
	this->male21 = male21;
	this->female21 = female21;
	this->male22 = male22;
	this->female22 = female22;
	this->male23 = male23;
	this->female23 = female23;
	this->male24 = male24;
	this->female24 = female24;


}

Obec::Obec(const Obec& zdroj)
{
	this->nazovObce = zdroj.nazovObce;
	this->aggregation = zdroj.aggregation;
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

Obec& Obec::operator=(Obec&& zdroj)
{
	if (this != &zdroj)
	{
		this->nazovObce = zdroj.nazovObce;
		this->aggregation = zdroj.aggregation;
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

Obec::~Obec()
{
}

int Obec::getPocetPohlavie(std::string pohlavie, int rok)
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

	// Ak neexistuje zhodn� pohlavie alebo rok
	return 0;
}

int Obec::getPocetVRoku(int rok) const
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

std::string Obec::getNazov() const
{
	return this->nazovObce;
}

int Obec::getKod() const
{
	return this->aggregation;
}

