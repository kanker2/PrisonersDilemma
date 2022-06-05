#include "poblation.h"
#include <time.h>

using namespace std;

int main(){

    srand(time(NULL));

    Poblation pob;

    pob.init();
    pob.simulate();
    
    return 0;
}