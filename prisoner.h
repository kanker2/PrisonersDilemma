#pragma once
#include <cmath>
#include <iostream>

using namespace std;

class Prisoner{
private:
    /*
        odd positions represents the decisions made by the opponent
        even positions represents own decisions
    */
    bool* decisions;
    bool* initialAssumption;

    //true means that collaborating is the decision
    bool currDecision;
    bool* madeDecisions;

    int punctuation = 0;

public:

    Prisoner(){
        decisions = new bool[NUM_POSSIBLE_DECISIONS];
        initialAssumption = new bool[MEMORY * 2];
        madeDecisions = new bool[MEMORY * 2];
    };
    ~Prisoner(){
        delete[] decisions;
        delete[] initialAssumption;
        delete[] madeDecisions;
    };

    /*
        randomizes the decisions and initialAssumptions
    */
    void initialize();
    /*
        initializes the decisions with which the prisoner is going to decide his first movement
    */
    void startGame();
    /*
        based on the initialAssumptions and the decisions the currDecision will be taken
    */
    void play();
    bool getDecision() const;
    /*
        based on the currDecision and the opponents decision the player modifies his current punctuation
        and also edits properly his memories about the last MEMORY games played
    */
    void seeOpponent(bool oppsDecision);
    /*
        does the same as startGame, currently this doesnt have any effect
    */
    void endGame();

    int getPunctuation() const{return punctuation;};
    void setPunctuation(int punct) {punctuation = punct;};
    /*
        the procedure is the following, this is applied into decisions and initialAssumptions data:
        we take a random position in the array from which we will swap the values in p1/p2 arrays

        this intends to mix the information between p1 and p2 with the intention of discovering better strategies
    */
    static void recombinate(Prisoner& p1, Prisoner& p2);

    /*
        goes throw decisiones and initialAssumptions bits and changes them with a probability of mutationRate
    */
    static void mutate(Prisoner& p, float mutationRate);

    static int getMemory(){return MEMORY;};
    static void setMemory(int mem){
        MEMORY = mem;
        NUM_POSSIBLE_DECISIONS = pow(POSSIBLE_SITUATIONS_PLAYING, MEMORY);
    };

    void display(ostream& out) const{
        cout << "Punctuation: " << punctuation << endl;
        for(int i = 0; i < NUM_POSSIBLE_DECISIONS; i++)
            cout << decisions[i] << " ";
        cout << endl;
        for(int i = 0; i < MEMORY * 2; i++)
            cout << initialAssumption[i] << " ";
        cout << endl;
    };
private:
    const static int POSSIBLE_SITUATIONS_PLAYING = 4;
    const static int DEFAULT_MEMORY = 3;
    inline static int MEMORY = DEFAULT_MEMORY;
    inline static int NUM_POSSIBLE_DECISIONS = pow(POSSIBLE_SITUATIONS_PLAYING, MEMORY);
};
ostream& operator<<(ostream& out, Prisoner const& p);