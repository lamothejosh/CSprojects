/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  PassengerQueue.h
 *
 *  PURPOSE interface of the passenger queue
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/18/2022
 *
 */

#ifndef PASSENGERQUEUE_H
#define PASSENGERQUEUE_H
#include "Passenger.h"
#include <iostream>
#include <vector>

using namespace std;


class PassengerQueue {

    public:

        Passenger front();
        void  dequeue();
        void enqueue(const Passenger &Passenger);
        int size();
        void print(ostream &output);

    private:
    
    vector<Passenger> pass_queue;

};
#endif