/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

int main(int argc, char *argv[])
{

    if ( argc < 3 or argc > 4){
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]";
        cerr << endl;
        return 1;
    }
        
    string command_file;

    if (argc == 3){
        command_file = "user_input";
    }

    if (argc == 4){
        command_file = argv[3];
    }


    MetroSim files(argc, argv[1], argv[2], command_file);

    //files.station_test();
   // files.command_test();

    files.main_metro();
    // files.station_test();
    // files.command_test();


        return 0;
}
