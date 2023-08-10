#include <string>
using namespace std;

#ifndef THE4_SCHEDULE_H
#define THE4_SCHEDULE_H

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
private:
    int time_slots;
    string ** data;
public:
    Schedule(); // default constructor
    Schedule(int); // parametric constructor
    Schedule(const Schedule&); // deep copy
    ~Schedule(); // destructor
    string ** createClone() const;
    const Schedule & operator=(const Schedule &);
    string ** getData() const;
    int getSlots() const;
    string * operator[] (Days) const;
    Schedule operator+ (Days) const;
    Schedule operator+ (int) const;
    Schedule operator+ (const Schedule &) const;
};

ostream & operator << (ostream & os, const Schedule & sch);
ostream & operator << (ostream & os, Days day);
Schedule operator * (const Schedule & sch1, const Schedule & sch2);
bool operator < (const Schedule & sch1, const Schedule & sch2);

#endif //THE4_SCHEDULE_H
