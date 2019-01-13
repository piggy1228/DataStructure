//
//  main.cpp
//  lab chk3
//
//  Created by KEXIN ZHU on 8/31/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    int n;
    double data;
    double total=0, avg;
    cout << "how many data would you like to input =>"<<endl;
    cin >> n;
    double array_data[n];
    for (int i=0; i<n; i++) {
        cout << "input the data you need"<<endl;
        cin>> data;
        array_data[i] = data;
        total = total+data;
    }
    avg = total/n;
    cout << "the average is " << avg<< endl;
    int val=0;
    for (int j=0; j<n; j++) {
        if (array_data[j]<avg) {
            val ++;
            }
    }
    cout << val<<" value(s) less than the average is"<< endl;
    for (int q=0; q<n; q++) {
        if (array_data[q]<avg) {
            cout<< array_data[q]<<" \n";
        }
    }
    

    return 0;
}
