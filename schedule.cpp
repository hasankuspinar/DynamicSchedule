// Hasan Kuspinar
#include "schedule.h"
#include <iostream>
#include <string>
using namespace std;

Schedule::Schedule() // default constructor
{
    data = new string * [7];
    time_slots = 0;
    for(int i = 0; i < 7; i++) // assigning all to pointers of the data array to NULL since it is empty
    {
        data[i] = NULL;
    }
}

Schedule::Schedule(int c) // parametric constructor
{
    data = new string * [7];
    time_slots = c;
    for(int i = 0; i < 7; i++)
    {
        data[i] = new string[time_slots];
        for(int j = 0; j < time_slots; j++) // initializing all the column elements to free
        {
            data[i][j] = "free";
        }
    }
}

string ** Schedule::createClone() const
{
    string ** Clone;
    Clone = new string * [7];
    if(time_slots == 0) // assigning all the clone pointers to NULL if there are no columns
    {
        for(int a = 0; a < 7; a++)
        {
            Clone[a] = NULL;
        }
    }
    else // assigning all the columns of data to the clone
    {
        for(int i = 0; i < 7; i++)
        {
            Clone[i] = new string[time_slots];
            for(int a = 0; a < time_slots; a++)
            {
                Clone[i][a] = data[i][a];
            }
        }
    }
    return Clone;
}

Schedule::Schedule(const Schedule & copy) // Deep copy constructor that creates a same schedule as the copy schedule (inspired from lecture slides 4.1)
{
    data = copy.createClone();
    time_slots = copy.time_slots;
}

Schedule::~Schedule()
{
    for(int i = 0; i < 7; i++)
    {
        delete [] data[i];
    }
    delete [] data;
}

int Schedule::getSlots() const // getter function for timeslots
{
    return time_slots;
}

string ** Schedule::getData() const // getter function for data pointer
{
    return data;
}

const Schedule & Schedule::operator= (const Schedule& rhs) // inspired from lecture notes 4.1
{
    if(this != &rhs)
    {
        for(int i = 0; i < 7; i++) // deallocating the memory of the lhs
        {
            delete [] data[i];
        }
        delete [] data;
        data = rhs.createClone();
        time_slots = rhs.time_slots;
    }
    return *this;
}

ostream & operator << (ostream & os, Days day)
{
    string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    os << days[day];
    return os;
}

ostream & operator << (ostream & os, const Schedule & sch)
{
    string days[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for(int i = 0; i < 7; i++)
    {
        os << days[i].substr(0,2) << ": ";
        for(int j = 0; j < sch.getSlots(); j++)
        {
            os << sch.getData()[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

string * Schedule::operator[] (Days day) const
{
    return data[day];
}

Schedule operator * (const Schedule & lhs, const Schedule & rhs)
{
    Schedule clone(lhs); // creating a clone of the lhs
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < clone.getSlots(); j++)
        {
            if (lhs.getData()[i][j] == "busy" && rhs.getData()[i][j] == "busy") // if both of them are busy making the slot of clone busy
            {
                clone.getData()[i][j] = "busy";
            }
            else // if either of them are not busy making the slot of clone free
            {
                clone.getData()[i][j] = "free";
            }
        }
    }
    return clone; // returning the clone
}

bool operator < (const Schedule & lhs, const Schedule & rhs) // returns true if lhs has less busy slots, false otherwise
{
    int count1 = 0, count2 = 0;
    for(int a = 0; a < 7; a++)
    {
        for(int b = 0; b < lhs.getSlots(); b++)
        {
            if(lhs.getData()[a][b] == "busy") // incrementing count 1 if the corresponding slot of lhs has busy
            {
                count1++;
            }
        }
    }
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < rhs.getSlots(); j++) // incrementing count 2 if the corresponding slot of rhs has busy
        {
            if(rhs.getData()[i][j] == "busy")
            {
                count2++;
            }
        }
    }
    if(count1 < count2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Schedule Schedule::operator + (Days day) const
{
    Schedule clone(*this); // creating a deep copy of our object
    for(int i = 0; i < clone.time_slots; i++)
    {
        clone.data[day][i] = "busy"; // making all the columns in the given day busy
    }
    return clone; // returning the clone
}

Schedule Schedule::operator + (int idx) const
{
    Schedule clone(*this); // creating a deep copy of our object
    if(clone.time_slots == 0)
    {
        return clone;
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            clone.data[i][idx] = "busy"; // making all the days in the given column busy
        }
        return clone;
    }
}

Schedule Schedule::operator + (const Schedule & rhs) const
{
    Schedule clone(*this); // creating a deep copy of our object
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < clone.time_slots; j++)
        {
            if(data[i][j] == "free" && rhs.data[i][j] == "free") // checking if both of the schedules have free in the slot
            {
                clone.data[i][j] = "free"; // making it free if it is so
            }
            else
            {
                clone.data[i][j] = "busy"; // making it busy if it is not
            }
        }
    }
    return clone;
}