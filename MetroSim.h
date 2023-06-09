/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  MetroSim.h
 *
 *  PURPOSE interface of the metro sim class
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/25/2022
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class MetroSim
{
public:

     MetroSim(int argc, string stations, string output, string comm);
 
    void main_metro(); // runs the metro sim program

    void user_version(); //if there is no command file this is used
    void command_version(); // version for a program with command file

    void move_train(string line); // moves the train for the commmand version

    void station_read(); //reads in the stations
    void command_read(); //reads in the commands

    void queue_creator(); // initalizes the train and station queue

    void station_test(); // testing functions for the stations vector
    void command_test(); // testing function for the command vector 

    void train_print(); //prints the train
    void train_actions(string user_input); // moves the train for user version
    void station_add(int start, int finish); // adds passengers to the station
    
    void station_to_train(); //moves passengers from station to train
    void off_the_train(); // removes pass. at their stop 

private:

    //all the files that are inputted
    string file_command, file_station, file_output;
    //output stream
    ofstream outputs;
    // number of commands, stations and files passed in
    int num_arg, num_stations, num_commands;
    //holds location of the train
    int train_location = 0;
    // holds id of the passengers
    int pass_id = 1; 
    // holds which line of the command file we are at
    int command_line = 0;


    //creates a vector of passenger queues (one queue per station)
    // one vector for the stations and one vector for the train
    vector<PassengerQueue> station_line;
    vector<PassengerQueue> train_line;

    // creates a vector of strings for the name of the stations
    vector<string> station_names;
    
    //vector that holds each line of the command file
    vector<string> train_commands;

};

#endif
