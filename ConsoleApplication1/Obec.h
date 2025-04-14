#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
class Obec
{
private:
	std::string nazovObce;
	int aggregation;
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
public:
	Obec(std::string nazovObce, int aggregation, int male20, int female20, int male21, int female21, int male22, int female22, int male23, int female23, int male24, int female24);
	Obec(const Obec& zdroj);
	Obec& operator=(Obec&& zdroj);
	~Obec();
	int getPocetPohlavie(std::string pohlavie, int rok);
	int getPocetVRoku(int rok) const;
	std::string getNazov() const;
	int getKod() const;
};
