//
//  time.cpp
//  lab2
//
//  Created by KEXIN ZHU on 9/6/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
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
#include "time.h"



Time::Time(){
    hour =0;
    minute =0;
    second =0;
    
}
Time::Time(uintptr_t aHour,uintptr_t aMinute, uintptr_t aSecond){
    hour = aHour;
    minute = aMinute;
    second = aSecond;
    
}
uintptr_t Time::getHour() const{
    return hour;
}

uintptr_t Time::getMinute() const{
    return minute;
}

const uintptr_t& Time::getSecond() const{
    return second;
}

void Time::setHour(int h){
 hour = h;
}

void Time::setMinute(int m){
    minute = m;
}

void Time::setSecond(int s){
    second = s;
}

void Time::PrintAmPm() const{

    if (getHour()<12 && getHour()!=0) {
        std::cout<<std::setw(2)<<std::setfill('0')<<hour<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<second<<" am"<<std::endl;
    }
    else if (getHour() >12){
        std::cout<<std::setw(2)<<std::setfill('0')<<hour-12<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<second<<" pm"<<std::endl;
    }
    else if(getHour() == 0){
        std::cout<<std::setw(2)<<std::setfill('0')<<"12"<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<second<<" am"<<std::endl;
    }
    else if(getHour() == 12){
        std::cout<<std::setw(2)<<std::setfill('0')<<"12"<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<second<<" pm"<<std::endl;
    }
}


bool IsEarlierThan(const Time&t1, const Time& t2){
    return ((t1.getHour()<t2.getHour()) || (t1.getHour() == t2.getHour() && t1.getMinute() < t2.getMinute())
                                      || (t1.getHour()==t2.getHour() && t1.getMinute() == t2.getMinute()
                                          &&t1.getSecond() ==t2.getSecond()));
}






