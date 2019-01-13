//
//  main.cpp
//  lab3
//
//  Created by KEXIN ZHU on 9/13/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;
void compare_squares(unsigned int* a,unsigned int* b,unsigned int n){
    for (unsigned int *q=a; q<a+n; q++) {
        *b= pow(*q, 2);
        b++;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    unsigned int a[3]={1,2,3};
    unsigned int b[3]={4,5,6};
    
    compare_squares(a, b, 3);
    for (unsigned int* i=b; i<b + 3; i++) {
        cout<<*i<<endl;
    }
    
    return 0;
}
