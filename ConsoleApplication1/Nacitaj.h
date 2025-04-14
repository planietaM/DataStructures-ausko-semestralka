#pragma once
#include <string>
#include <vector>
#include "Obec.h"
#include <fstream>
#include <sstream>
#include <iostream>

class Nacitaj
{
private:
    std::ifstream citac1;
    std::ifstream citac2;
    std::ifstream citac3;
    std::ifstream citac4;
    std::ifstream citac5;


public:
    Nacitaj();
    ~Nacitaj();
    std::vector<Obec> NacitajObce();

};

