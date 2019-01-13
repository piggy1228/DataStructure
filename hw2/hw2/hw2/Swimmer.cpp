//
//  Swimmer.cpp
//  hw2
//
//  Created by KEXIN ZHU on 9/10/16.
//  Copyright  2016 KEXIN ZHU. All rights reserved.
//

#include "Swimmer.h"
#include <iostream>
#include <string>
#include <vector>

//construct the class in the file
//two bool function to compare to swimmers
using namespace std;
Swimmer::Swimmer(){
    first_name_ = "";
    last_name_ = "";
    round_ = "";
    number_="";
    lane_number_ = "";
    country_ = "";
    event_ = "";
    game_len_=0;
    medals_ = "";
    relay_team_ = "";
    
}

Swimmer::Swimmer(string first_name,string last_name,string round,string number, string lane_number,string country,vector<float> time,string event,float final_time,int game_len,string final_time_str,string medals,string relay_team){
    first_name_ = first_name;
    last_name_ = last_name;
    round_ = round;
    number_=number;
    lane_number_ = lane_number;
    country_ = country;
    time_ = time;
    event_ = event;
    final_time_=final_time;
    game_len_ = game_len;
    final_time_str_=final_time_str;
    medals_ = medals;
    relay_team_=relay_team;
}

//to compare the 2 swimmers their final time for sorting
 bool less_final_time(const Swimmer& swim1,const Swimmer& swim2){
     if (swim1.final_time()<swim2.final_time()){
         return true;
     }
     else if(swim1.final_time() == swim2.final_time()&& swim1.last_name()<swim2.last_name()){
         return true;
     }
    else if(swim1.final_time() == swim2.final_time()&&
            swim1.last_name() == swim2.last_name()&&swim1.first_name()<swim2.first_name()){
        return true;
    }
    else if (swim1.first_name() == swim2.first_name() && swim1.last_name() == swim2.last_name()&&swim1.final_time()<swim2.final_time()){
        return true;
    }
    else{
        return false;
    }
 }

//to modify the medals, when the swimmers are fastest in the final, give it a medal
void Swimmer::set_medals(string m){
    medals_ = m;
}


void Swimmer::set_last_name(string l_n){
    last_name_ = l_n;
}

//is used for the order of participants, compare by the country
bool alphabetical_less_than(const Swimmer& swim1, const Swimmer& swim2){
    if (swim1.country() < swim2.country()) {
        return true;
    }
    else if (swim1.country() == swim2.country() && swim1.last_name() <swim2.last_name()){
        return  true;
    }
    else if (swim1.country() == swim2.country() && swim1.last_name() == swim2.last_name() &&swim1.first_name()<swim2.first_name()){
        return true;
    }
    else{
        return false;
    }
                                                
}

