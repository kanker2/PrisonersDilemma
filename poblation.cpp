#include "poblation.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>

void Poblation::init(){
    for(auto& p : prisoners)
        p.initialize();
    if(debugMode)
        display();
}

void Poblation::simulate(){
    unordered_map<int, int> matches = makeMatches(prisoners.size());

    for(auto const& p : matches){
        Prisoner& p1 = prisoners[p.first],
                & p2 = prisoners[p.second];
        auto const& prisonersPunctuation = playAMatch(p1, p2);
        pobScore += prisonersPunctuation.first + prisonersPunctuation.second;
        p1.setScore(prisonersPunctuation.first);
        p2.setScore(prisonersPunctuation.second);
    }

    if(debugMode)
        display();
}



Poblation Poblation::getNextGen() const{
    Poblation pob(pobSize, mutRate, recombRate, nPlaysPerGame);

    vector<double> fits, sums;
    double sum = 0;
    //TODO pasar este proceso de generar la rueda de la fortuna a una funcion a parte
    for(int i = 0; i < pobSize; i++){
        fits[i] = fitnessFunction(prisoners[i]);
        sum += fits[i];
        sums[i] = sum;
    }

    return pob;
}

int getNextFreeInt(int maxInt, unordered_set<int> & alreadyMatched){
    int nextFree = rand() % maxInt;
    while(alreadyMatched.count(nextFree))
        nextFree = rand() % maxInt;
    alreadyMatched.insert(nextFree);
    return nextFree;
}

unordered_map<int, int> Poblation::makeMatches(int maxIndex) const{
    unordered_map<int, int> matches;
    unordered_set<int> alreadyMatched;

    while(alreadyMatched.size() + 1 < maxIndex){
        int first = getNextFreeInt(maxIndex, alreadyMatched),
            second = getNextFreeInt(maxIndex, alreadyMatched);
        matches.insert({first, second});
    }

    return matches;
}

pair<int, int> Poblation::playAMatch(Prisoner& p1, Prisoner& p2){
    p1.startGame();
    p2.startGame();

    int gamesPlayed = 0;
    pair<int, int> punctuations = {0, 0};

    while(gamesPlayed++ < nPlaysPerGame){
        p1.play();
        p2.play();

        pair<bool, bool> decisions = {p1.getDecision(), p2.getDecision()};
        punctuations.first += getPoints(decisions).first;
        punctuations.second += getPoints(decisions).second;

        p1.seeOpponent(decisions.second);
        p2.seeOpponent(decisions.first);
    }

    p1.endGame();
    p2.endGame();

    return punctuations;
}
