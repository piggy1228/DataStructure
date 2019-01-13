//
//  main.cpp
//  lab2
//
//  Created by KEXIN ZHU on 9/6/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include "time.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, const char * argv[]) {
    vector<Time> times;
    
    Time t1(0,3,5);
    Time t2(23,2,3);
    Time t3;
    cout<< t1.getHour()<<endl;
    cout<<t1.getMinute()<<endl;
    cout<<t1.getSecond()<<endl;
    cout<<t2.getHour()<<endl;
    cout<<t2.getMinute()<<endl;
    cout<<t2.getSecond()<<endl;
    cout<<t3.getHour()<<endl;
    cout<<t3.getMinute()<<endl;
    cout<<t3.getSecond()<<endl;
    t2.setHour(23);
    t2.PrintAmPm();
    if (IsEarlierThan(t1, t2)){
        cout<<"is earlier than"<<endl;
    };
    
    times.push_back(t1);
    times.push_back(t2);
    times.push_back(t3);
    
    sort(times.begin(),times.end(),IsEarlierThan);
    for (int i=0; i<times.size(); i++) {
        times[i].PrintAmPm();
        
    }
    
    return 0;
}
