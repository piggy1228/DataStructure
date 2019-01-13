//
//  phonebook_map.cpp
//  Lab9
//
//  Created by GuanChendi on 3/30/16.
//  Copyright © 2016 GuanChendi. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

// add a number, name pair to the phonebook
void add(map<int,string> &phonebook, int number, string const& name) {
    phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const map<int,string> & phonebook, int number) {
    map<int,string>::const_iterator ITR = phonebook.find(number);
    if (ITR != phonebook.end() ) {
        cout << ITR->second << " is calling!" << endl;
    }else{
        cout << "unknown caller!" << endl;
    }
}


int main() {
    // create the phonebook; initially all numbers are unassigned
    map<int,string> phonebook;
    
    // add several names to the phonebook
    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");
    //////////////O(1)for construting
    //////////////memory O(n)
    //////////////still work
    //////////////vector can be faster when searching，but maps take less memory
    
    // test the phonebook
    identify(phonebook, 2222);
    identify(phonebook, 4444);
}