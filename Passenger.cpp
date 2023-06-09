/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  Passenger.cpp
 *
 *  PURPOSE implementation of the passenger struct 
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/17/2022
 *
 */
#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

/*
Name: print
Purpose: prints the passenger's ID, start and end station
Parameters:
Return Values:none 
*/
void Passenger::print(std::ostream &output)
{
   
   output <<  "[";
   output << this->id; 
   output <<  ", ";
   output << this->from;
   output << "->"; 
   output << this->to;
   output << "]";

}
