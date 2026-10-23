// making sure that duplicate and sick animals are removed from all enclosures in a zoo 
// demonstrates the usage of STL algorithms adapted from Pro C++ 
// Alex
// 10/21/2026
#include <algorithm>  
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>  
using namespace std; 

// this is similar to typedef 
using ZooMap = map<string, list<string>>; 
using EnclosurePair = ZooMap::value_type; 

// removes duplicate and sick animals form ZooMap 
void auditEnclosures(ZooMap& animalsByEnclosure, const list<string>& sickAnimals); 

int main() 
{ 
	// initialize map ZooMap 
	ZooMap animals = { { "Orange", { "aardvark", "lion", "buffalo", "wildcat", "lion", "eagle" } }, 
				{ "Green", { "elephant", "zebra", "aardvark", "bear", "alligator"} }, 
				{ "Yellow", { "goose", "alligator", "flamingo", "goose", } }, 
                { "Blue", { "shark", "dolphin", "alligator", "turtle", "eagle", "penguin"} }, 
                { "Red", { "deer", "duck", "wildcat", "lion" } } }; 
	
	list<string> sickAnimals = { "buffalo", "wildcat", "eagle"}; 
	
	// local lambda expression to print a enclosure 
	auto printEnclosure = [](const EnclosurePair& enclosure) 
	{ 
		cout << enclosure.first << ":"; 
		for (auto& str : enclosure.second) 
		{ 
			cout << ' ' << str; 
		} 
		cout << endl; 
	}; 
	cout << "Before audit:" << endl; 
	for_each(animals.cbegin(), animals.cend(), printEnclosure); 
	cout << endl; 
	auditEnclosures(animals, sickAnimals); 
	cout << "After audit:" << endl; for_each(animals.cbegin(), animals.cend(), printEnclosure); 
	cout << endl; 
} 

// expects a map of string/list pairs keyed on enclosure names 
// and containing lists of all the animals in those enclosures 
// 
// removes from each list any name on the sickAnimals list and 
// any name that is found in any other enclosure 
void auditEnclosures(ZooMap& animalsByEnclosure, const list<string>& sickAnimals) 
{ 
	set<string> sick(sickAnimals.begin(), sickAnimals.end());
    set<string> seen;

    for (auto& enclosure : animalsByEnclosure)
    {
        auto& animals = enclosure.second;
        auto newEnd = remove_if(animals.begin(), animals.end(),
            [&sick, &seen](const string& name)
            {
                if (sick.find(name) != sick.end())
                {
                    return true; 
                }
                // First occurrence: remember it.
                seen.insert(name); 
                return false;  
            });

        animals.erase(newEnd, animals.end());
    }
} 
