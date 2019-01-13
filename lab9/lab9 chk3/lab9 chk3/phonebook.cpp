//
//  phonebook.cpp
//  Lab9
//
//  Created by GuanChendi on 3/30/16.
//  Copyright © 2016 GuanChendi. All rights reserved.
//

// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
    phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
    if (phonebook[number] == "UNASSIGNED")
        cout << "unknown caller!" << endl;
    else
        cout << phonebook[number] << " is calling!" << endl;
}

/*
int main() {
    // create the phonebook; initially all numbers are unassigned
    vector<string> phonebook(10000, "UNASSIGNED");
    
    // add several names to the phonebook
    add(phonebook, 1111, "fred");
    add(phonebook, 2222, "sally");
    add(phonebook, 3333, "george");
    ////////O(N) to construct the phonebook
    ////////memory O(N)
    ////////still O(N), yes it will work on cellphone
    
    // test the phonebook
    identify(phonebook, 2222);
    identify(phonebook, 4444);
}
*/