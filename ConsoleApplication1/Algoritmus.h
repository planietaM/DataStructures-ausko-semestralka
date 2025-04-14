#pragma once

#include <vector>
#include <string>
#include "Obec.h"

class Algoritmus {
private:
    
    static bool checkMaxResidence(const Uzemie& uzemie, int year, int maxResidents) {
        if (uzemie.getPocetVRoku(year) <= maxResidents) {
            return true;
        }
        else {
            return false;
        }
    }

    static bool checkMinResidence(const Uzemie& uzemie, int year, int minResidents) {
        if (uzemie.getPocetVRoku(year) >= minResidents) {
            return true;
        }
        else {
            return false;
        }
    }

    static bool containsSubstring(const Uzemie& uzemie, const std::string& hladanyText) {
        if (uzemie.getNazov().find(hladanyText) != std::string::npos) {
            return true;
        }
        else {
            return false;
        }
    }

    // Opravil som názov parametra na 'typObce', aby sedel s použitím vo funkcii.
    static bool typUzemia(const Uzemie& uzemie, const std::string& typObce) {
        if (typObce == "pk") {
            if (uzemie.getCisloUzemia() == 0) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (typObce == "gd") {
            if (uzemie.getCisloUzemia()  >= 0 && uzemie.getCisloUzemia() <10) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (typObce == "sr") {

            if (uzemie.getCisloUzemia() > 9 && uzemie.getCisloUzemia() < 100) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (typObce == "r") {
            if (uzemie.getCisloUzemia() > 99 && uzemie.getCisloUzemia() < 1000) {
                return true;
            }
            else {
                return false;
            }
        }
        else if (typObce == "o") {
            if (std::to_string(uzemie.getCisloUzemia()).length() == 5 ) {
                return true;
            }
            else {
                return false;
            }
        }
        else{
            return false;
        }
    }



public:
    // Šablónová funkcia pre generické filtrovanie kolekcie na základe predikátu.
    template <typename Iterator, typename Predicate>
    std::vector<Uzemie> filter(Iterator begin, Iterator end, Predicate pred) {
        std::vector<Uzemie> result;
        for (auto it = begin; it != end; ++it) {
            if (pred(*it)) {
                result.push_back(*it);
            }
        }
        return result;
    }

    // Vráti lambda funkciu, ktorá overí, èi má obec maximálne maxResidents obyvate¾ov v danom roku.
    auto filterMaxResidencePredicate(int year, int maxResidents) {
        return [year, maxResidents](const Uzemie& uzemie) -> bool {
            return checkMaxResidence(uzemie, year, maxResidents);
            };
    }

    // Vráti lambda funkciu, ktorá overí, èi má obec aspoò minResidents obyvate¾ov v danom roku.
    auto filterMinResidencePredicate(int year, int minResidents) {
        return [year, minResidents](const Uzemie& uzemie) -> bool {
            return checkMinResidence(uzemie, year, minResidents);
            };
    }

    // Vráti lambda funkciu, ktorá overí, èi názov obce obsahuje zadaný reazec.
    auto filterContainsStrPredicate(const std::string& hladanyText) {
        return [hladanyText](const Uzemie& uzemie) -> bool {
            return containsSubstring(uzemie, hladanyText);
            };
    }
	// Vráti lambda funkciu, ktorá overí, èi je to typ obce.
    auto filterTypObce(const std::string& typObce) {
        return [typObce](const Uzemie& uzemie) -> bool {
            return typUzemia(uzemie, typObce);
            };
    }
};