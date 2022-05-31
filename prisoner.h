#ifndef PRISONER_H
#define PRISONERH
#include <cmath>

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

    int getPunctuation(){return punctuation;};

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
private:
    int obtainedPunctuation(bool oppsDecision) const;
};
#endif