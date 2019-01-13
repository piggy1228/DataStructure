//
//  main.cpp
//  lab9
//
//  Created by KEXIN ZHU on 10/26/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " grid-file\n";
        return 1;
    }
    ifstream istr(argv[1]);
    if (!istr) {
        cerr << "Could not open " << argv[1] << endl;
        return 1;
    }
    string num;
    map<string,int> counters;
    while (istr >> num) {
        ++counters[num];
    }
    
    vector<string> max_num;
    int max = 0;
    map<string, int>::const_iterator itr;
    for (itr = counters.begin(); itr != counters.end(); itr++) {
        //cout<<itr->first<<"\t"<<itr->second<<endl;
        if (itr ->second > max) {
            max = itr ->second;
            max_num.clear();
            max_num.push_back(itr->first);
        }
        else if (itr->second == max){
            max_num.push_back(itr->first);
        }

    }
    for (int i=0; i<max_num.size(); i++) {
        cout<<"chk1\n";
        cout<<max_num[i]<<endl;
    }
    
//=======================================================================
    //find
//=======================================================================
    ifstream istr1(argv[1]);
    map<string,int> counters1;

    while (istr1 >>num) {
        map<string,int>::iterator tmp = counters1.find(num);
        if (tmp == counters1.end()) {
            counters1.insert(make_pair(num, 1));
        }
        else{
            tmp->second++;
        }
    }
    vector<string> max_num1;
    int max1 = 0;
    map<string, int>::const_iterator itr1;
    for (itr1 = counters1.begin(); itr1 != counters1.end(); itr1++) {
        //cout<<itr->first<<"\t"<<itr->second<<endl;
        if (itr1 ->second > max1) {
            max1 = itr1 ->second;
            max_num1.clear();
            max_num1.push_back(itr1->first);
        }
        else if (itr1->second == max1){
            max_num1.push_back(itr1->first);
        }
        
    }
    for (int i=0; i<max_num1.size(); i++) {
        cout<<"chk2\n";
        cout<<max_num1[i]<<endl;
    }
//=======================================================================
//insert
//=======================================================================
    ifstream istr2(argv[1]);
    map<string,int> counters2;
    while (istr2>>num) {
        pair<map<string,int>::iterator, bool> tmp2 = counters2.insert(make_pair(num,0));
        tmp2.first->second ++;
    }
    vector<string> max_num2;
    int max2 = 0;
    map<string, int>::const_iterator itr2;
    for (itr2 = counters2.begin(); itr2 != counters2.end(); itr2++) {
        //cout<<itr->first<<"\t"<<itr->second<<endl;
        if (itr2 ->second > max2) {
            max2 = itr2 ->second;
            max_num2.clear();
            max_num2.push_back(itr2->first);
        }
        else if (itr2->second == max2){
            max_num2.push_back(itr2->first);
        }
        
    }
    for (int i=0; i<max_num2.size(); i++) {
        cout<<"chk2.1\n";
        cout<<max_num2[i]<<endl;
    }
    
    
    
    
    
    return 0;
}
