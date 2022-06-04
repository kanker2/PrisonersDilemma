#ifndef POBLATION_H
#define POBLATION_H
#include "prisoner.h"
#include <vector>

using namespace std;

class Poblation{
private:
    int size, mutRate, recombRate, nPlaysPerGame;
    vector<Prisoner> prisoners;
    int punctuation;
public:
    Poblation(int size, int mutationRate, int recombinationRate, int numPlays) : 
    size(size), mutRate(mutationRate), recombRate(recombinationRate), nPlaysPerGame(numPlays), punctuation(0){
        prisoners.resize(size);
    };

    //Initilizates all the prisoners
    void init();
    //Makes a simulation of the current poblation making them play against each other and stablishes the punctuation of each individual
    void simulate();
    //based on the current poblation generates the next poblation
    Poblation getNextGen() const;
    int getPunctuation() const;
    //Returns the best prisoner of the poblation
    Prisoner const& bestPrisoner() const;

private:
    //Gives back the pair of indexes of Prisoners which will be faced
    unordered_map<int, int> makeMatches() const;
    //Makes them play a match and gives back the punctuation obtained by each
    pair<int, int> playAMatch(Prisoner& p1, Prisoner& p2);
    pair<int, int> getPoints(pair<bool, bool> const& decisions){
        if(decisions.first && decisions.second)         return {5, 5};
        else if(decisions.first && !decisions.second)   return {0, 3};
        else if(!decisions.first && decisions.second)   return {3, 0};
        else                                            return {2, 2};
    };
};

#endif