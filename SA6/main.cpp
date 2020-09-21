#include <iostream>
#include "voiture.h"
#include "parking.h"
#include <fstream>
#include <string.h>
#include <thread>
using namespace std;

int main (void){
    Parking P(0, 2, 10, "parking.csv");
    P.AfficherInfo();
    return 0;
}