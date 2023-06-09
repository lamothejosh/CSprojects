/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  MetroSim.cpp
 *
 *  PURPOSE implementation of the metro sim class
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/25/2022
 *
 */

#include "MetroSim.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
Name: constructor
Purpose: creates an instance of Metro Sim to be ran
Parameters: and int with the number of arguments, and strings holding
            each file that's passed in 
Return Values:none 
*/
MetroSim::MetroSim(int argc, string stations, string output, string com)
{
    file_command = com;
    file_station = stations;
    file_output = output;
    num_arg = argc;

    outputs.open(file_output);

    if (not outputs.is_open())
    {
        cerr << "could not open file " << file_output << endl;
        exit(1);
    }

}

/*
Name: main_metro
Purpose: runs the metro sim program
Parameters: none
Return Values:none 
*/
void MetroSim::main_metro()
{
    station_read();
    queue_creator();
    command_read();

    if (num_arg == 3)
    {
        user_version();
    }
    else
       command_version();
}

/*
Name: user_version
Purpose: runs the metro sim version where the user inputs commands
Parameters:none
Return Values:none 
*/
void MetroSim::user_version()
{
    train_print();
    
    string uc; // string that holds users input 
    string uc2; // string that holds second letter
    int start, destination;
    
    cout << "Command? ";
    cin >> uc;

    if (uc.at(0) == 'p')
    {
        cin >> start;
        cin >> destination;
        station_add(start, destination);
    }
    if (uc.at(0) == 'm' and uc.size() == 1)
    {
        cin >> uc2;
        uc = uc + uc2;
    }
    if (uc.at(0) == 'm')
    {
        train_actions(uc);
    }
        user_version();
    
}
/*
Name: command_version()
Purpose: runs the metro sim version with command file
Parameters: none
Return Values:none 
*/
void MetroSim::command_version()
{   
        while (command_line <= train_commands.size()) {
        train_print();

        if (train_commands[command_line][0] == 'm' ){
            string line = train_commands[command_line];
            cout << "Command? ";
            move_train(line);
        }if (train_commands[command_line][0] == 'p'){
            string line = train_commands[command_line];
            size_t space_spot, space_spot2;
            space_spot = line.find('p ', 0);
            space_spot2 = line.find(" ", space_spot + 1); 

            int start = stoi(line.substr(space_spot,space_spot2));
            int goal = stoi(line.substr(space_spot2, line.back()));

            cout << "Command? ";
            station_add(start, goal);
        }
        command_line++;
        num_commands--;
        if (num_commands == 0){
        train_print();
        cout << "Command? ";
        move_train("m f");
        }
    }
}

/*
Name: move train
Purpose: moves the train
Parameters: a string holding the command
Return Values:none 
*/
void MetroSim::move_train(string line)
{
    if (line == "m f" )
    {
        cout << "Thanks for playing MetroSim. Have a nice day!";
        cout << endl;
        outputs.close();
        exit(0);
    }
    if (line == "m m")
    {
        if (train_location == station_names.size() - 1)
        {
            station_to_train();
            train_location = 0;
        }       
        else{   
        station_to_train();
        train_location++;
        }
        off_the_train();
    }    
}

/*
Name: station_add
Purpose: adds a passenger to the station they start at
Parameters: integers holding starting and ending locations for passengers
Return Values:none 
*/
void MetroSim::station_add(int start, int destination)
{
    if (start and destination >= station_names.size()){
        cerr << "No stations in that range" << endl;
        return;
    }
    Passenger station_joiner = Passenger(pass_id, start, destination);
    station_line[start].enqueue(station_joiner);
    pass_id++;
}

/*
Name: train_action
Purpose:moves the train or ends the program in the user version
Parameters: none
Return Values:none 
*/
void MetroSim::train_actions(string user_input)
{
    if (user_input == "mf" )
    {
        cout << "Thanks for playing MetroSim. Have a nice day!";
        cout << endl;
        exit(0);
    }
    if (user_input == "mm")
    {
        if (train_location == train_line.size() - 1)
        {
            station_to_train();
            train_location = 0;
            off_the_train();
        }
        else{   
        station_to_train();
        train_location++;
        off_the_train();
        }
        user_version();
    }  
}

/*
Name: station_to_train
Purpose: moves passengersfrom the station to the train
Parameters: none
Return Values:none 
*/
void MetroSim::station_to_train()
{
    int size = station_line.at(train_location).size();
    for (int i = 0; i < size; i++)
    {
        Passenger train_joiner = station_line[train_location].front();
        int goal_station = train_joiner.to;
        train_line[goal_station].enqueue(train_joiner);
        station_line[train_location].dequeue();
    }
}

/*
Name: off_the_train
Purpose: takes passengers off at their stops
Parameters: none
Return Values:none 
*/
void MetroSim::off_the_train()
{
    int size = train_line.at(train_location).size();

    for (int i = 0; i < size; i++)
    {
        Passenger train_leaver;
        train_leaver = train_line[train_location].front();
        outputs << "Passenger " << train_leaver.id; 
        outputs << " left train at station ";
        outputs << station_names[train_leaver.to] << endl;

        train_line[train_location].dequeue();
    }
    
}

/*
Name: queue creator
Purpose: initializes the stations and train's passenger queues
Parameters: none
Return Values:none 
*/
void MetroSim::queue_creator()
{
    for (int i = 0; i < station_names.size(); i++)
    {
        PassengerQueue station_spot;
        station_line.push_back(station_spot);
        train_line.push_back(station_spot);
    }
    
}

/*
Name: train print
Purpose: prints the train and the stations along with their passenger lines
Parameters: none
Return Values:none 
*/
void MetroSim::train_print()
{
    cout << "Passengers on the train: " << "{";
    
    for (int i = 0; i < train_line.size(); i++)
    {
        train_line[i].print(cout);
    }

    cout << "}" << endl;

    for (int i = 0; i < station_names.size(); i++)
    {
        if (train_location == i)
        {
            cout << "TRAIN: ";
            cout << "[" << i << "] ";
            cout << station_names[i];
            cout << " {";
            station_line[i].print(cout);
            cout << "}" << endl;
        }
        else{
            cout << "       ";
            cout << "[" << i << "] ";
            cout << station_names[i];
            cout << " {";
            station_line[i].print(cout);
            cout << "}" << endl;
        }
    }
}

/*
Name: station_read
Purpose: reads in the file containing stations and places each
         one in a vector containing station names
Parameters: none
Return Values:none 
*/
void MetroSim::station_read()
{
    ifstream file;
    file.open(file_station);
    if (not file.is_open()){
         cerr << "could not open file " << file_station << endl;
        exit(1);
    }

    int station_counter = 0;
    string line_holder;
    int i = 0;

    while (file.peek() != EOF){
        getline(file, line_holder);
        station_names.push_back(line_holder);
        station_counter++;
        i++;
    }

    num_stations = station_counter;
    file.close();
    
}

/*
Name: station_test
Purpose: prints the vector of station names (function used to test)
        this function tests whether the file opens correctly and
        whether it was inputted into the vector correctly
Parameters: none
Return Values:none 
*/
void MetroSim::station_test()
{
    for (int i = 0; i < station_names.size(); i++)
    {
        outputs << station_names[i] << endl;
    }
    
}

/*
Name: command_read
Purpose: reads in the file containing commands and places each
         one in a vector containing station names
Parameters: none
Return Values:none 
*/
void MetroSim::command_read()
{
    if (num_arg == 4){
        ifstream file;
        file.open(file_command);

        if (not file.is_open()){
            cerr << "could not open file " << file_command << endl;
            exit(1);
        }

        string line_holder;
        int count = 0;        

        while (file.peek() != EOF){
             getline(file, line_holder);
             train_commands.push_back(line_holder);
             count++;
        }
        
        if (count == 0 and file.peek() == EOF)
             {
                train_print();
                cout << "Command? ";
                move_train("m f");
             }

        num_commands = count;
        file.close();
    }
    
    
}

/*
Name: command_test
Purpose: prints the vector of commands (function used to test)
        this function tests whether the file opens correctly and
        whether it was inputted into the vector correctly
Parameters: none
Return Values:none 
*/
void MetroSim::command_test()
{
    for (int i = 0; i < train_commands.size(); i++)
    {
        outputs << train_commands[i] << endl;
    }
}




