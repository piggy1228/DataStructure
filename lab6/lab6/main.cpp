//
//  main.cpp
//  lab6
//
//  Created by KEXIN ZHU on 10/4/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;
void reverse_vector(vector<int> &v1){
    for (int i=0; i<(v1.size()+1)/2; i++) {
        int temp;
        int j = v1.size()-i-1;
        temp = v1[j];
        v1[j] = v1[i];
        v1[i] = temp;
        //cout<<"i: "<<i <<"  j: "<<j<<endl;
        //cout<<"v1[i]:   "<<v1[i]<<"   v1[j]: "<<v1[j]<<endl;
    }
}


void reverse_list (list<int> &l){
    list<int>::iterator itr;
    list<int>::reverse_iterator ri;
    int count=0;
    int temp;
    itr = l.begin();
    for (ri = l.rbegin(); count<(l.size()+1)/2; ++ri) {
        temp = *itr;
        *itr = *ri;
        *ri = temp;
        count++;
        itr++;
    }
    cout<<"count: "<<count<<endl;
    
}




void print_v (vector<int > &v){
    cout<<"size:"<<v.size()<<endl;
    for (int i=0; i<v.size(); i++) {
        cout<<v[i]<<" "<<endl;
    }
}

void print_l (list<int> &l){
    cout<<"size:"<<l.size()<<endl;
    for (list<int>::iterator itr=l.begin(); itr!=l.end(); itr++) {
        cout<<*itr<<" "<<endl;
    }
}

int main(int argc, const char * argv[]) {
    //=====================================================
    //check point 1
    //=====================================================
    //Case: 2 vector of 2 values
    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    print_v(v);
    reverse_vector(v);
    print_v(v);
    
    //Case: 1 value
    vector<int> v1;
    v1.push_back(2);
    print_v(v1);
    reverse_vector(v1);
    print_v(v1);
    
    //case empty
    vector<int> v2;
    print_v(v2);
    reverse_vector(v2);
    print_v(v2);
    //=====================================================
    //check point 2
    //=====================================================
    std::list<int> l;
    for (int i=0; i<10; i++){
        l.push_back(i);
    }
    print_l(l);
    reverse_list(l);
    print_l(l);
    
    //case empty
    std::list<int> l1;
    print_l(l1);
    reverse_list(l1);
    print_l(l1);
    
    //Case: 1 value
    std::list<int> l2;
    l2.push_back(10);
    print_l(l2);
    reverse_list(l2);
    print_l(l2);
    
    //Case: 2 vector of 2 values
    std::list<int> l3;
    l3.push_back(10);
    l3.push_back(7);
    print_l(l3);
    reverse_list(l3);
    print_l(l3);
    return 0;
}
