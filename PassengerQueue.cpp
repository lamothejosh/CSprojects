/*
 *
 *  COMP 15 Proj1 Metro Sim
 *
 *  PassengerQueue.cpp
 *
 *  PURPOSE implementation of the passenger queue class
 *
 *  Modified by: Josh Lamothe   
 *           On: 6/18/2022
 *
 */

#include "PassengerQueue.h"
#include "Passenger.h"

#include <iostream>
#include <vector>

using namespace std;

/*
Name: front
Purpose:returns the passenger at the front of the queue
Parameters:none
Return Values:Passenger at the front
*/
Passenger PassengerQueue::front()
{
       if (pass_queue.empty())
    {
       throw runtime_error("cannot get first of empty queue");
    }
    
    return pass_queue.front();
}

/*
Name: Dequeue
Purpose:  removes a passenger from the front of the queue
Parameters:none
Return Values: none (void) 
*/
void PassengerQueue::dequeue()
{
    if (pass_queue.empty())
    {
       throw runtime_error("cannot remove from empty queue");
    }
    
    pass_queue.erase(pass_queue.begin());
}

/*
Name: enqueue
Purpose: adds a passenger to the end of the queue
Parameters:the address of the passenger
Return Values: none (void)
*/
void PassengerQueue::enqueue(const Passenger &Passenger)
{
    pass_queue.push_back(Passenger);
}

/*
Name: size
Purpose: returns the size of the queue
Parameters:none
Return Values: int holding the size of the queue
*/
int PassengerQueue::size()
{
    return pass_queue.size();
}

/*
Name: print 
Purpose: prints the passenger queue
Parameters:an output stream 
Return Values: none (void)
*/
void PassengerQueue::print(ostream &output)
{
    for (int i = 0; i < pass_queue.size(); i++)
    {
        output << "[";
        output <<  pass_queue[i].id;
        output << ", ";
        output << pass_queue[i].from;
        output << "->";
        output << pass_queue[i].to;
        output << "]";
    }
    
}