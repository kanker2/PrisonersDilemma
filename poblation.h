#ifndef POBLATION_H
#define POBLATION_H
#include "prisoner.h"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Poblation{
private:
    const static int DEF_SIZE = 20, DEF_NUM_PLAYS = 10;
    constexpr static double DEF_MUT_RATE = 0.05, DEF_RECOMB_RATE = 0.25;

    int pobSize, nPlaysPerGame;
    double  mutRate, recombRate;
    vector<Prisoner> prisoners;
    int pobScore;

    inline static bool debugMode = true;
public:
    Poblation() : Poblation(DEF_SIZE, DEF_MUT_RATE, DEF_RECOMB_RATE, DEF_NUM_PLAYS){};

    Poblation(int size, double mutationRate, double recombinationRate, int numPlays) : 
    pobSize(size), mutRate(mutationRate), recombRate(recombinationRate), nPlaysPerGame(numPlays), pobScore(0){
        prisoners.resize(size);
    };
    //Initilizates all the prisoners
    void init();
    //Makes a simulation of the current poblation making them play against each other and stablishes the punctuation of each individual taking from here the punctuation of the population
    void simulate();
    //based on the current poblation generates the next poblation
    Poblation getNextGen() const;
    int getScore() const;
    //Returns the best prisoner of the poblation
    Prisoner const& bestPrisoner() const;

private:
    //Receives the indexes of the prisoners with which the pairs should be made
    //Gives back the pair of indexes of Prisoners which will be faced
    unordered_map<int, int> makeMatches(int maxIndex) const;
    //Makes them play a match and gives back the punctuation obtained by each
    pair<int, int> playAMatch(Prisoner& p1, Prisoner& p2);
    pair<int, int> getPoints(pair<bool, bool> const& decisions){
        if(decisions.first && decisions.second)         return {5, 5};
        else if(decisions.first && !decisions.second)   return {0, 3};
        else if(!decisions.first && decisions.second)   return {3, 0};
        else                                            return {2, 2};
    };
    void display() const{
        displayParametersInfo();
        displayIndividualsInfo();
    };
    void displayParametersInfo() const{
        printf("Poblation size: %d\nMutation rate: %f\nRecombination rate: %f\nNumber of games per match: %d\nCurrent score of the poblation: %d\n", 
                pobSize, mutRate, recombRate, nPlaysPerGame, pobScore);
    };
    void displayIndividualsInfo() const{
        cout << "Individuals memory: " << Prisoner::getMemory() << endl;
        for(int i = 0; i < pobSize; i++)
            cout << "Ind " << i << endl << prisoners[i] << endl;
    };  
    double fitnessFunction(Prisoner const& p) const{
        return (double) p.getScore() / pobScore;
    }
};

#endif