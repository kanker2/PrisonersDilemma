#ifndef PRISONER_H
#define PRISONERH
#include <cmath>
#include <iostream>
using namespace std;
class Prisoner{
private:
    const static int POSSIBLE_SITUATIONS_PLAYING = 4;
    inline const static bool points[2][2] = {{2, 3}, 
                                             {0, 5}};
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

    void display(){
        cout << "Decisions" << endl;
        for(int i = 0; i < NUM_POSSIBLE_DECISIONS; i++)
            cout << decisions[i] << " ";
        cout << endl;
        cout << "Initial assumptions" << endl;
        for(int i = 0; i < MEMORY * 2; i++)
            cout << initialAssumption[i] << " ";
        cout << endl;
    }

    const static int DEFAULT_MEMORY = 3;
    inline static int MEMORY = DEFAULT_MEMORY;
    inline static int NUM_POSSIBLE_DECISIONS = pow(POSSIBLE_SITUATIONS_PLAYING, MEMORY);

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

    void initialize();
    /*
        Initializes the decisions with which the prisoner is going to decide his next movement
    */
    void startGame();
    void play();
    bool getDecision();
    void seeOpponent(bool oppsDecision);
    void endGame();

    int getPunctuation(){return punctuation;};

    static void recombinate(Prisoner& p1, Prisoner& p2);
    static void mutate(Prisoner& p, float mutationRate);

    static int getMemory(){return MEMORY;};
    static void setMemory(int mem){
        MEMORY = mem;
        NUM_POSSIBLE_DECISIONS = pow(POSSIBLE_SITUATIONS_PLAYING, MEMORY);
    };
private:
    int obtainedPunctuation(bool oppsDecision);
};
#endif