/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  Passenger.h
 *
 *  PURPOSE interface of the passenger struct 
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/17/2022
 *
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        void print(std::ostream &output);

};

#endif
