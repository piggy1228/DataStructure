//
//  main.cpp
//  lab8
//
//  Created by KEXIN ZHU on 10/19/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

//===========================================
//check1
//===========================================
int back_to_original(int x, int y){
    if (x==0 and y == 0) {
        return 1;
    }
    else if (x==0){
        return back_to_original(0, y-1);
    }
    else if (y==0){
        return back_to_original(x-1, 0);
    }
    else{

        return back_to_original(x-1, y)+back_to_original(x, y-1);

    }
}




#include <iostream>

int main(int argc, const char * argv[]) {
    int a=back_to_original(3, 3);
    std::cout<<"num: "<<a<<std::endl;
    return 0;
}
