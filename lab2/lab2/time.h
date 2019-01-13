//
//  time.h
//  lab2
//
//  Created by KEXIN ZHU on 9/6/16.
//  Copyright  2016 KEXIN ZHU. All rights reserved.
//


#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <vector>
#include <iomanip>
#include <string>
#include <cmath>

class Time{
public:
    Time();

    Time(uintptr_t aHour,uintptr_t aMinute, uintptr_t aSecond);

    //Accessor
    uintptr_t getHour() const;
    uintptr_t getMinute() const;
    const uintptr_t& getSecond() const;
    
    //Modifier
    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);
    
    void PrintAmPm() const;
    
    //other member functions
    bool IsEarlierThan(const Time&t1, const Time& t2);
    
private:
    uintptr_t hour;
    uintptr_t minute;
    uintptr_t second;
};
bool IsEarlierThan(const Time&t1, const Time& t2);
