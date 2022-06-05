#include "poblation.h"
#include <time.h>

using namespace std;

int main(){

    srand(time(NULL));

    int n = 100000;
    Poblation pob;
    pob.init();
    pob.simulate();
    cout << pob.getScore() << endl;
    while(n--){
        pob = pob.getNextGen();
        pob.simulate();
    }
    cout << pob.getScore() << endl;
        
    return 0;
}