//
//  main.cpp
//  Lab9
//
//  Created by GuanChendi on 3/29/16.
//  Copyright © 2016 GuanChendi. All rights reserved.
//

#include <iostream>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    std::ifstream istr(argv[1]);
    if (!istr) {
        std::cerr << "Could not open " << argv[1] << " to read\n";
        return 1;
    }
    map<int,int> Integer;
    int TmpNum;
    /*//////////////////////////////check 1
    while (istr >> TmpNum) {
        Integer[TmpNum] += 1;
    }
    ///////////////////////////////////////*/
    
    ////////////////////////////////check 2
    while (istr >> TmpNum) {
        pair< map<int,int>::iterator,bool > pair_tmp;
        
        pair_tmp = Integer.insert( make_pair(TmpNum,1) );
        if ( !(pair_tmp.second) ) { // pair_tmp.second == false
            Integer[TmpNum] += 1;
        }
    }
    ////////////////////////////////////////
    
    map<int,int>::const_iterator ITR;
    int MaxCount = 0;
    vector<int> modes;
    for (ITR = Integer.begin(); ITR != Integer.end(); ++ITR) {
        if (ITR->second > MaxCount) {
            MaxCount = ITR->second;
            modes.clear();
            modes.push_back(ITR->first);
        }else if (ITR->second == MaxCount){
            modes.push_back(ITR->first);
        }
    }
    cout << "modes: " << endl;
    for (int i=0; i<modes.size(); i++) {
        cout << modes[i] << ' ';
    }
    cout << endl;
    return 0;
}
