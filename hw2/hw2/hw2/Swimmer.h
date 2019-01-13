//
//  Swimmer.h
//  hw2
//
//  Created by KEXIN ZHU on 9/10/16.
//  Copyright  2016 KEXIN ZHU. All rights reserved.
//

#ifndef Swimmer_h
#define Swimmer_h
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//in the class I have the relay team, which means the country if it is in a relay competition


class Swimmer{
public:
    //Constructor
    Swimmer();
    Swimmer(string first_name,string last_name,string round,string number, string lane_number,string country,vector<float> time,string event, float final_time, int game_len,string final_time_str,string medals,string relay_team);
    
    //Accesors
    const string& first_name() const {return first_name_;}
    const string& last_name() const {return last_name_;}
    const string& round() const {return round_;}
    const string& number() const{return number_;}
    const string& lane_number() const{return lane_number_;}
    const string& country() const{return country_;}
    const vector<float>& time() const{return time_;}
    const string& event() const{return event_;}
    const float& final_time() const{return final_time_;}
    const int& game_len() const{return game_len_;}
    const string& final_time_str() const{return final_time_str_;}
    const string& medals() const{return medals_;}
    const string& relay_team() const{return relay_team_;}
    
    
    
    //Modifiers
    void set_last_name(string last_name_);
    void set_medals(string medals_);
    
    
private://member variables
    string first_name_;
    string last_name_;
    string round_;
    string number_;
    string lane_number_;
    string country_;
    vector<float> time_;
    float final_time_;
    string event_;
    int game_len_;
    string final_time_str_;
    string medals_;
    string relay_team_;
};

bool less_final_time(const Swimmer& swim1,const Swimmer& swim2);
bool alphabetical_less_than(const Swimmer& swim1, const Swimmer& swim2);




#endif /* Swimmer_h */
