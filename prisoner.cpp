#include "prisoner.h"

void Prisoner::initialize(){
    for(int i = 0; i < NUM_POSSIBLE_DECISIONS; i++)
        decisions[i] = (float) rand() / RAND_MAX < 0.5;
    for(int i = 0; i < MEMORY * 2; i++)
        initialAssumption[i] = (float) rand() / RAND_MAX < 0.5;
}

void Prisoner::startGame(){
    for(int i = 0; i < MEMORY * 2; i++)
        madeDecisions[i] = initialAssumption[i];
}

void Prisoner::play(){
    int situation = 0;
    for(int i = 0; i < MEMORY * 2; i++)
        situation = situation * 2 + madeDecisions[i];

    currDecision = decisions[situation];
}

bool Prisoner::getDecision() const{
    return currDecision;
}

void Prisoner::seeOpponent(bool oppsDecision){
    for(int i = MEMORY - 1; i > 0; i--){
        madeDecisions[i * 2] = madeDecisions[(i - 1) * 2];
        madeDecisions[i * 2 + 1] = madeDecisions[i * 2 - 1];
    }
    madeDecisions[0] = currDecision;
    madeDecisions[1] = oppsDecision;
}

void Prisoner::endGame(){
    for(int i = 0; i < MEMORY * 2; i++)
        madeDecisions[i] = initialAssumption[i];
}

void Prisoner::recombinate(Prisoner& p1, Prisoner& p2){
    int crossPos = rand() % NUM_POSSIBLE_DECISIONS;
    for(int i = crossPos; i < NUM_POSSIBLE_DECISIONS; i++){
        bool aux = p1.decisions[i];
        p1.decisions[i] = p2.decisions[i];
        p2.decisions[i] = aux;
    }

    crossPos = rand() % MEMORY * 2;
    for(int i = 0; i < MEMORY * 2; i++){
        bool aux = p1.initialAssumption[i];
        p1.initialAssumption[i] = p2.initialAssumption[i];
        p2.initialAssumption[i] = aux;
    }
}

void Prisoner::mutate(Prisoner& p, float mutationRate){
    for(int i = 0; i < NUM_POSSIBLE_DECISIONS; i++)
        if((float) rand() / RAND_MAX < mutationRate)
            p.decisions[i] = !p.decisions[i];
    for(int i = 0; i < MEMORY * 2; i++)
        if((float) rand() / RAND_MAX < mutationRate)
            p.initialAssumption[i] = !p.initialAssumption[i];
}

ostream& operator<<(ostream& out, Prisoner const& p){
    p.display(out);
    return out;
}