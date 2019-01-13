//
//  main.cpp
//  hw2
//
//  Created by KEXIN ZHU on 9/10/16.
//  Copyright  2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "Swimmer.h"
#include <sstream>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;


//I create a class called swimmer to store all the info about the person.
//there are 4 functions for event,2 functions for participants, 2 modified
//function to modify the class
//because relay has its own structure, so I seperate them to the different functions
//I only construct one class so it will convenience to get and store info
//functions here for the tool function for further use
//to compare which event string is smaller to decide the sequence of print event
//table
//participants just add all the swimmers in the same vectors. when count the heat
//numbers, just find out the same last name and first name
//the whole program are built on the swimmering event,some output or time are
//based on my common sense, so there maybe some misunderstanding

//decide the event table order
bool less_than_event(const string &out_string1,const string &out_string2){
    return  out_string1 < out_string2;
}

//convert float to string
string float_to_str(float flt){
    ostringstream temp;
    temp<<flt;
    return temp.str();
}


/**
    compute the average in a vector
    this is for the custom commands
    
    @param lane average lap time for one swimmer in one event
    @return total lap time for one line in string format
 */
string compute_avg(vector<float>& lane){
    float total_time=0;
    for (int i=0; i<int(lane.size()); i++) {
        total_time += lane[i];
        //the sum of all the time
    }
    float avg;
    avg = total_time/(lane.size());//avg time for each lap in one event
    string avg_str0 = float_to_str(avg);
    string avg_str;
    avg_str = avg_str0.substr(0, 5);//make sure that only out put to 2 decimal
    return avg_str;
}

//convert the string time to float with second unit
//to make it all to the second float for the convenience of calculation
float time_str_to_float(string s){
    string letter;
    string minute="";
    string second="";
    int min=0;
    float sec=0;
    for (int i=0; i<int(s.size()); i++) {
        letter = s[i];
        if (letter == ":") {
            min = atoi(minute.c_str());//get the minute
            for (int j=i+1; j<s.size(); j++) {
                second+=s[j];//get the seconds
            }
            //make the string to the
            sec = atof(second.c_str());
            break;
        }
        else{
            minute += letter;
        }
    }
    return min*60+sec;
}
// end of the tool function


//modify the swimmers
//set the medals
//to modify the swimmer class, to give them the medals
//just give the first 3 swimmers in final set medals;
//if there is a tie then give them medals together
//if their final time are the same, then it is a tie
void set_the_medals(vector<vector<Swimmer> > &swimmers_in_each_event,
                    int num_of_event){
    vector<Swimmer> swimmers_in_final;
    //sort the final round of the swimmers
    int j = num_of_event;
    swimmers_in_final.clear();
    for (int i=0; i< swimmers_in_each_event[j].size();i++) {
        if (swimmers_in_each_event[j][i].round() == "FINAL") {
            swimmers_in_final.push_back(swimmers_in_each_event[j][i]);
        }
    }
    sort(swimmers_in_final.begin(), swimmers_in_final.end(), less_final_time);
    // modify the swimmer information, give the top swimmers medals
    //find the same person in the whole vectos one by one

    for (int i=0; i<swimmers_in_each_event[j].size(); i++) {
        //if find out the this is the same person who get the medals, modify it
        //in the original vectors
        if (swimmers_in_final[0].first_name()==
            swimmers_in_each_event[j][i].first_name() &&
            swimmers_in_final[0].last_name()==
            swimmers_in_each_event[j][i].last_name()&&
            swimmers_in_final[0].round()==swimmers_in_each_event[j][i].round()) {
            swimmers_in_each_event[j][i].set_medals("GOLD");
        }

        else if (swimmers_in_final[1].first_name()==
                 swimmers_in_each_event[j][i].first_name() &&
            swimmers_in_final[1].last_name()==
            swimmers_in_each_event[j][i].last_name()&&
            swimmers_in_final[1].round()==swimmers_in_each_event[j][i].round()){
            if (swimmers_in_final[0].final_time() !=
                swimmers_in_final[1].final_time()) {
                swimmers_in_each_event[j][i].set_medals("SILVER");
            }
            //the tie case: 2 swimmers are both first
            else if (swimmers_in_final[0].final_time() ==
                     swimmers_in_final[1].final_time()) {
                swimmers_in_each_event[j][i].set_medals("GOLD");
            }
        }
        else if (swimmers_in_final[2].first_name()==
                 swimmers_in_each_event[j][i].first_name() &&
                 swimmers_in_final[2].last_name()==
                 swimmers_in_each_event[j][i].last_name()&&
                 swimmers_in_final[2].round()==
                 swimmers_in_each_event[j][i].round()){
            if (swimmers_in_final[1].final_time() !=
                swimmers_in_final[2].final_time()) {
                swimmers_in_each_event[j][i].set_medals("BRONZE");
            }
            else if (swimmers_in_final[1].final_time() ==
                     
                     swimmers_in_final[2].final_time()){
                swimmers_in_each_event[j][i].set_medals("SILVER");
            }
        }
        
        //for the medals number exceed 3. 2 people are tie in bronze
        if (swimmers_in_final[2].final_time()==swimmers_in_final[3].final_time()
            && swimmers_in_final[2].final_time()!=
            swimmers_in_final[1].final_time()) {
            if (swimmers_in_final[3].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[3].last_name()==
                swimmers_in_each_event[j][i].last_name()
                &&swimmers_in_final[3].round()==
                swimmers_in_each_event[j][i].round()) {
                swimmers_in_each_event[j][i].set_medals("BRONZE");
            }
        }
        
        //for the 3 person tie in bronze
        else if (swimmers_in_final[3].final_time()==
                 swimmers_in_final[4].final_time()  &&
                 swimmers_in_final[3].final_time() ==
                 swimmers_in_final[2].final_time()) {
        //find the person in the vectors including all the swimmers and modify the medals
            if (swimmers_in_final[4].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[4].last_name()==
                swimmers_in_each_event[j][i].last_name()&&
                swimmers_in_final[3].round()==
                swimmers_in_each_event[j][i].round()) {
                swimmers_in_each_event[j][i].set_medals("BRONZE");
            }
        }
        
        // for the 3 person tie in the silver
        else if (swimmers_in_final[2].final_time()==
                 swimmers_in_final[3].final_time()&&
                 swimmers_in_final[2].final_time()==
                 swimmers_in_final[1].final_time()) {
            if (swimmers_in_final[3].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[3].last_name()==
                swimmers_in_each_event[j][i].last_name()&&
                swimmers_in_final[3].round()==
                swimmers_in_each_event[j][i].round()) {
                swimmers_in_each_event[j][i].set_medals("SILVER");
            }
            
        }
    }
    
}

//set the medals for relay swimmers
//to modify the swimmer class, to give them the medals
//it is similar with swimmers not relay
void set_the_medals_for_relay(vector<vector<Swimmer> > &swimmers_in_each_event,
                              int num_of_event){
    vector<Swimmer> swimmers_in_final;
    //sort the final round of the swimmers
    int j=num_of_event;
    swimmers_in_final.clear();
    for (int i=0; i< swimmers_in_each_event[j].size();i++) {
        if (swimmers_in_each_event[j][i].round() == "FINAL") {
            swimmers_in_final.push_back(swimmers_in_each_event[j][i]);
        }
    }
    sort(swimmers_in_final.begin(), swimmers_in_final.end(), less_final_time);
    
    
    //find the person who win the medals and set medals in the vector
    //because its relay, so the four people in a team both get a medal
    //just check the first person in a relay team of their time info
    //the method is same, both find out the same perison and modify the info
    for (int i=0; i<swimmers_in_each_event[j].size(); i++) {
        for (int k=0; k<4; k++) {
            //put all the info in the new vectors,
            //through the for loop to find exact the same person
            if (swimmers_in_final[k].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[k].last_name()==
                swimmers_in_each_event[j][i].last_name()&&
                swimmers_in_final[k].round()==
                swimmers_in_each_event[j][i].round()) {
                swimmers_in_each_event[j][i].set_medals("GOLD");
                
            }
        }
        for (int k=4; k<8; k++) {
            if (swimmers_in_final[k].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[k].last_name()==
                swimmers_in_each_event[j][i].last_name()&&
                swimmers_in_final[k].round()==
                swimmers_in_each_event[j][i].round()){
                if (swimmers_in_final[0].final_time() !=
                    swimmers_in_final[4].final_time()) {
                    swimmers_in_each_event[j][i].set_medals("SILVER");
                }
                else if (swimmers_in_final[0].final_time() ==
                         swimmers_in_final[4].final_time()) {
                    swimmers_in_each_event[j][i].set_medals("GOLD");
                }
            }
            
        }
        
        for (int k=8; k<12; k++) {
            if (swimmers_in_final[k].first_name()==
                swimmers_in_each_event[j][i].first_name() &&
                swimmers_in_final[k].last_name()==
                swimmers_in_each_event[j][i].last_name()&&
                swimmers_in_final[k].round()
                ==swimmers_in_each_event[j][i].round()){
                if (swimmers_in_final[4].final_time() !=
                    swimmers_in_final[8].final_time()) {
                    swimmers_in_each_event[j][i].set_medals("BRONZE");
                    
                }
                else if (swimmers_in_final[4].final_time() ==
                         swimmers_in_final[8].final_time()){
                    swimmers_in_each_event[j][i].set_medals("SILVER");
                    
                }
            }
        }
        for (int k = 12; k<16; k++) {
            //for the medals number exceed 3. 2 people are tie in bronze
            if (swimmers_in_final[8].final_time()==
                swimmers_in_final[12].final_time() &&
                swimmers_in_final[8].final_time()!=
                swimmers_in_final[4].final_time()) {
                if (swimmers_in_final[k].first_name()==
                    swimmers_in_each_event[j][i].first_name() &&
                    swimmers_in_final[k].last_name()==
                    swimmers_in_each_event[j][i].last_name()&&
                    swimmers_in_final[3].round()==
                    swimmers_in_each_event[j][i].round()) {
                    swimmers_in_each_event[j][i].set_medals("BRONZE");
                }
            }
            
            
            // for the 3 person tie in the silver
            if (swimmers_in_final[8].final_time()==
                swimmers_in_final[12].final_time()&&
                swimmers_in_final[8].final_time()==
                swimmers_in_final[4].final_time()) {
                if (swimmers_in_final[k].first_name()==
                    swimmers_in_each_event[j][i].first_name() &&
                    swimmers_in_final[k].last_name()==
                    swimmers_in_each_event[j][i].last_name()&&
                    swimmers_in_final[3].round()==
                    swimmers_in_each_event[j][i].round()) {
                    swimmers_in_each_event[j][i].set_medals("SILVER");
                }
                
            }
            
        }
        
        for (int k=16; k<20; k++) {
            //for the 3 person tie in bronze
            if (swimmers_in_final[12].final_time()==
                swimmers_in_final[16].final_time()
                && swimmers_in_final[12].final_time() ==
                swimmers_in_final[8].final_time()) {
                //find the person in the vectors including all the swimmers and modify the medals
                if (swimmers_in_final[4].first_name()==
                    swimmers_in_each_event[j][i].first_name() &&
                    swimmers_in_final[4].last_name()==
                    swimmers_in_each_event[j][i].last_name()
                    &&swimmers_in_final[3].round()==
                    swimmers_in_each_event[j][i].round()) {
                    swimmers_in_each_event[j][i].set_medals("BRONZE");
                }
            }
        }
    }
}


//
//
//4 kind of event table




//print the event table
//just sort all the swimmers final time
//find out the first 5
// print put the info in order
void event_table(string &out_string,int len,vector<string> &event_type,
                 vector<vector<Swimmer> > &swimmer_in_each_event,int num_of_event){
    string swimmer_name;
    string first_line;
    int count_words = 0;
    //title print out the
    out_string = event_type[num_of_event];
    count_words = int(event_type[num_of_event].size());
    //count the blank
    string type_blank0(39-count_words,' ');
    //set width should be 39 blanks
    out_string += type_blank0;
    //print the title of the table
    
    //output the title,
    for (int i=0; i<swimmer_in_each_event[num_of_event][0].game_len()/50; i++) {
        int integer = (i+1)*50;//find out the total lap number
        string int_str = float_to_str(integer);//convert
        first_line += int_str;
        first_line += "m     ";
    }
    first_line+="  FINAL\n";
    //this calculate the line number of to print the cut off line
    const string cut_off(first_line.size()+38,'-');
    out_string += first_line;
    out_string +=cut_off;
    out_string+="\n";
    //from the whole table, sort the first 5 swimmers
    sort(swimmer_in_each_event[num_of_event].begin(),
         swimmer_in_each_event[num_of_event].end(),less_final_time);
    
    //print the 5 swimmers' information
    //blanks are all for the set width
    
    for (int i=0; i<5; i++) {
        swimmer_name =swimmer_in_each_event[num_of_event][i].first_name()+" "
        +swimmer_in_each_event[num_of_event][i].last_name();
        out_string += swimmer_name;
        count_words = int(swimmer_name.size());
        //to set width
        const string type_blank(37-count_words,' ');//37 width
        out_string += type_blank;
        for (int j=0; j<int(swimmer_in_each_event[num_of_event][i].time().size()); j++) {
            string time_string = float_to_str( swimmer_in_each_event[num_of_event][i].time()[j]);
            //to make sure strings show the precisions
            if (time_string.size()==2) {
                time_string += ".00";
            }
            
            if (time_string.size()==4) {
                time_string += "0";
            }
            //print out the time step by step
            out_string += time_string;
            out_string +="    ";
        }
        
        out_string +=" ";
        if (swimmer_in_each_event[num_of_event][i].final_time_str().size() == 5) {
            out_string +="  ";//it will need 2 more blanks with the minutes
        }
        out_string += swimmer_in_each_event[num_of_event][i].final_time_str();
        out_string += "\n";
    }
}


//print events with medals, the top non medalist must exists
//I merge two vector together
//first one from the first swimmers to the first non medalist in final
//second in the total round with 10 swimmers so I will not forget to print
//thoses swimmers faster than the non medalists in the final
void event_medal_table(string &out_string,int len,vector<string> &event_type,
                       vector<vector<Swimmer> > &swimmer_in_each_event,int num_of_event){
    string swimmer_name;
    string first_line;
    vector<Swimmer> swimmers_in_final;
    vector<Swimmer> first_4_final;
    vector<Swimmer> swimmers_event_medals_table;
    first_4_final.clear();
    swimmers_in_final.clear();
    //sort the final round of the swimmers
    for (int i=0; i< swimmer_in_each_event[num_of_event].size();i++) {
        if (swimmer_in_each_event[num_of_event][i].round() == "FINAL") {
            swimmers_in_final.push_back(swimmer_in_each_event[num_of_event][i]);
        }
    }
    sort(swimmers_in_final.begin(), swimmers_in_final.end(), less_final_time);
    float stop_time;
    //to put the first three swimmers in final and non_medalist in final in a vector
    for (int i=0; i<4; i++) {
        first_4_final.push_back(swimmers_in_final[i]);
    }

    //consider the tie case,5 person get the medals
    if (int(swimmers_in_final[3].medals().size())>0) {
        first_4_final.push_back(swimmers_in_final[4]);
    }

    //consider the 5 person get the medals;then the non medalist will be the 5th in the final
    if (int(swimmers_in_final[4].medals().size())>0) {
        first_4_final.push_back(swimmers_in_final[5]);
    }
    stop_time = first_4_final[first_4_final.size()-1].final_time();
    //knows who is the last ont to print out
    //if others are faster than the first non medalist in final
    //print the title of the table
    out_string = event_type[num_of_event];
    int count_words = int(event_type[num_of_event].size());//count the size
    string type_blank(39-count_words,' ');//set the width
    out_string += type_blank;//set the width
    for (int i=0; i<swimmer_in_each_event[num_of_event][0].game_len()/50; i++) {
        int integer = (i+1)*50;
        //print each lap number
        //convert from integer to string so that it can be output to the txt file
        string int_str = float_to_str(integer);
        first_line += int_str;
        first_line += "m     ";
    }
    first_line+="  FINAL    MEDALS";
    string cut_off(first_line.size()+39,'-');
    out_string += first_line; out_string += "\n";
    out_string += cut_off; out_string += "\n";
    //from the whole table, sort the first 5 swimmers
    sort(swimmer_in_each_event[num_of_event].begin(),
         swimmer_in_each_event[num_of_event].end(),less_final_time);
    
    //to merge two top swimmers info together
    //sort swimmers in all rounds
    //i<10 to make sure that will not miss the person who are faster than
    //first non_medalist
    for (int i=0; i<10; i++) {
        if (swimmer_in_each_event[num_of_event][i].final_time()>stop_time && i>=5) {
            break;
        }

        first_4_final.push_back(swimmer_in_each_event[num_of_event][i]);
    }
    sort(first_4_final.begin(),first_4_final.end(),less_final_time);
    //order the sequence of the final time for all swimmers togeteher
    swimmers_event_medals_table.push_back(first_4_final[0]);
    int j=0;
    for (int i=1; i<first_4_final.size(); i++) {
        if (first_4_final[i].first_name()!=
            swimmers_event_medals_table[j].first_name() ||
            first_4_final[i].last_name() !=
            swimmers_event_medals_table[j].last_name() ||
            first_4_final[i].round() !=
            swimmers_event_medals_table[j].round()) {
            swimmers_event_medals_table.push_back(first_4_final[i]);
            j++;
        }
    }
    //print the top swimmers' information
    //set the width 37
    for (int i=0; i<swimmers_event_medals_table.size(); i++) {
        swimmer_name =swimmers_event_medals_table[i].first_name()+" "+
        swimmers_event_medals_table[i].last_name();
        if (swimmers_event_medals_table[i].round()!="FINAL") {
            swimmer_name += " (";//add the name with the round
            swimmer_name += swimmers_event_medals_table[i].round();
            swimmer_name +=")";
            
        }
        out_string += swimmer_name;
        count_words = int(swimmer_name.size());
        string type_blank1(37-count_words,' ');
        out_string += type_blank1;
        for (int j=0; j<int(swimmers_event_medals_table[i].time().size()); j++) {
            string time_string = float_to_str( swimmers_event_medals_table[i].time()[j]);
            if (time_string.size()==2) {
                time_string += ".00";//set the precision
            }
            
            if (time_string.size()==4) {
                time_string += "0";
            }
            out_string += time_string;
            out_string +="    ";
            
        }
        out_string+=" ";
        if (swimmers_event_medals_table[i].final_time_str().size() == 5) {
            out_string += "  ";
        }
        out_string += swimmers_event_medals_table[i].final_time_str();
        count_words =int(swimmers_event_medals_table[i].medals().size());
        string type_blank2(10-count_words,' ');
        out_string+=type_blank2;
        out_string += swimmers_event_medals_table[i].medals();out_string+="\n";
        
    }
}


//very similar with event table, just different when then output the country name
//instead of own name
//print the event table for relay
void event_table_for_relay(string &out_string,int len,vector<string> &event_type,
                 vector<vector<Swimmer> > &swimmer_in_each_event,
                           int num_of_event){
    string swimmer_name;
    string first_line;
    out_string = event_type[num_of_event];
    string type_blank((39-event_type[num_of_event].size()),' ');//set 39 width
    out_string += type_blank;
    //print the title of the table
    
    for (int i=0; i<swimmer_in_each_event[num_of_event][0].game_len()/50; i++) {
        int integer = (i+1)*50;//print the title, the lap name
        string int_str = float_to_str(integer);
        first_line += int_str;
        first_line += "m     ";
    }
    first_line+="  FINAL\n";
    string cut_off(first_line.size()+38,'-');
    out_string += first_line;
    out_string += cut_off;out_string+="\n";
    //from the whole table, sort the first 5 swimmers
    sort(swimmer_in_each_event[num_of_event].begin(),
         swimmer_in_each_event[num_of_event].end(),less_final_time);
    
    //print the 5 swimmers' information
    //37 width
    //will not repeat the country
    for (int i=0; i<20; i=i+4) {
        swimmer_name =swimmer_in_each_event[num_of_event][i].relay_team();
        out_string += swimmer_name;
        string type_blank1(int(37-swimmer_name.size()),' ');
        out_string += type_blank1;
        for (int j=0; j<int(swimmer_in_each_event[num_of_event][i].time().size());
             j++) {
            string time_string = float_to_str(
                swimmer_in_each_event[num_of_event][i].time()[j]);
            if (time_string.size()==2) {
                time_string += ".00";// make sure 2 precisions
            }
            
            if (time_string.size()==4) {
                time_string += "0";
            }
            out_string += time_string;//print out the time in the time vector
            out_string +="    ";
        }
        out_string +=" ";
        out_string += swimmer_in_each_event[num_of_event][i].final_time_str();
        out_string += "\n";
        }
    }

//print the event medal table for relay
void event_medal_table_for_relay(string &out_string,int len,vector<string> &event_type,
        vector<vector<Swimmer> > &swimmer_in_each_event,int num_of_event){
    string swimmer_name;
    string first_line;
    vector<Swimmer> swimmers_in_final;//put all the swimmers in final rounds
    vector<Swimmer> first_4_final;//put the faster swimmers together in all rounds
    vector<Swimmer> swimmers_event_medals_table;//the standard medal table
    float stop_time;//when the first_4_final stop to output
    first_4_final.clear();
    swimmers_in_final.clear();
    //sort the final round of the swimmers
    for (int i=0; i< swimmer_in_each_event[num_of_event].size();i++) {
        if (swimmer_in_each_event[num_of_event][i].round() == "FINAL") {
            swimmers_in_final.push_back(swimmer_in_each_event[num_of_event][i]);
        }
    }
    sort(swimmers_in_final.begin(), swimmers_in_final.end(), less_final_time);
    //to put the first three swimmers in final and non_medalist in final in a vector
    for (int i=0; i<16; i=i+4) {
        first_4_final.push_back(swimmers_in_final[i]);
    }
    //consider the tie case,4 person get the medals
    if (int(swimmers_in_final[12].medals().size()>0)) {
        first_4_final.push_back(swimmers_in_final[16]);
    }
    //consider the 5 person get the medals;then the non medalist will be the 5th in the final
    if (int(swimmers_in_final[12].medals().size()>0)) {
        first_4_final.push_back(swimmers_in_final[20]);
    }

    stop_time = first_4_final[first_4_final.size()-1].final_time();
    // find out the first non-medalist final time
    //stop print it in the event medal table
    
    //print the title of the table
    int count_words =0;
    count_words = int(event_type[num_of_event].size());
    string type_blank(39-count_words,' ');//39 width
    out_string = event_type[num_of_event];
    out_string += type_blank;
    // these are all the same with above
    for (int i=0; i<swimmer_in_each_event[num_of_event][0].game_len()/50; i++) {
        int integer = (i+1)*50;
        string int_str = float_to_str(integer);
        first_line += int_str;
        first_line += "m     ";
    }
    first_line+="  FINAL    MEDALS\n";
    out_string += first_line;
    string cut_off(first_line.size()+38,'-');
    out_string += cut_off;out_string +="\n";
    //from the whole table, sort the first  swimmers
    sort(swimmer_in_each_event[num_of_event].begin(),
         swimmer_in_each_event[num_of_event].end(),less_final_time);
    
    //to merge two top swimmers info together
    for (int i=0; i<40; i=i+4) {
        if (swimmer_in_each_event[num_of_event][i].final_time()> stop_time && i>16) {
            break;
        }
        first_4_final.push_back(swimmer_in_each_event[num_of_event][i]);
    }

    sort(first_4_final.begin(),first_4_final.end(),less_final_time);
    //sort all the swimmers before the stop time
    swimmers_event_medals_table.push_back(first_4_final[0]);
    int j=0;
    //get rid of the repeated name
    for (int i=1; i<first_4_final.size(); i++) {
        if (first_4_final[i].relay_team()!=
            swimmers_event_medals_table[j].relay_team() || first_4_final[i].round() !=
            swimmers_event_medals_table[j].round()) {
            swimmers_event_medals_table.push_back(first_4_final[i]);
            j++;
        }
    }
    
    //print the 5 swimmers' information
    for (int i=0; i<swimmers_event_medals_table.size(); i++) {
        
        swimmer_name =swimmers_event_medals_table[i].relay_team();
        if (swimmers_event_medals_table[i].round()!="FINAL") {
            swimmer_name += " (";
            swimmer_name += swimmers_event_medals_table[i].round();
            swimmer_name +=")";
            
        }
        
        out_string += swimmer_name;
        count_words = int(swimmer_name.size());//width 37
        string type_blank1(37-count_words,' ');
        out_string += type_blank1;
        //output the tame make sure the 2 precision
        for (int j=0; j<int(swimmers_event_medals_table[i].time().size()); j++) {
            string time_string = float_to_str(swimmers_event_medals_table[i].time()[j]);
            if (time_string.size()==2) {
                time_string += ".00";
            }
            if (time_string.size()==4) {
                time_string += "0";
            }
            out_string += time_string;
            out_string +="    ";
        }
        out_string +=" ";
        if (swimmers_event_medals_table[i].final_time_str().size() == 5) {
            out_string +="  ";
        }
        //outout the final time
        out_string += swimmers_event_medals_table[i].final_time_str();
        count_words = int(swimmers_event_medals_table[i].medals().size());
        string type_blank2(10-count_words,' ');//10 width
        out_string += type_blank2;
        out_string += swimmers_event_medals_table[i].medals(); out_string +="\n";
    }
}


//end of event table
//the participants table

//print the participants table
//put all the swimmers in a big loop
//if they are the same person, add on their heat semi and final number
//create 6 vectors to make the index are the same
// in order to output their info at the end
//I construct vectors for each info we need to print, so they are corresponding
//when i finish one person, i store the info
void print_the_participants(string &out_string, vector<vector<Swimmer> >
                            &swimmer_in_each_event){
    vector<int> heat_num, semi_num,final_num;
    vector<string> swimmer_first_name,swimmer_last_name, swimmer_country;
    vector<Swimmer> all_swimmers;
    int heats=0,semis=0,finals=0;
    
    //put all the participants together
    for (int i=0; i<swimmer_in_each_event.size(); i++) {
        for (int j=0; j<swimmer_in_each_event[i].size(); j++) {
            all_swimmers.push_back(swimmer_in_each_event[i][j]);
        }
    }
    sort(all_swimmers.begin(),all_swimmers.end(),alphabetical_less_than);
    //sort them in order
    
    // count the number of heat, semi and final that each swimmers are in
    int num_of_swimmers=0;
    //first push back the first name in the vector
    swimmer_first_name.push_back(all_swimmers[0].first_name());
    swimmer_last_name.push_back(all_swimmers[0].last_name());
    swimmer_country.push_back(all_swimmers[0].country());
    //add on their rounds number
    //if their round is heat,semi or final
    //increment and push back the final to the corresponding vectors
    if (all_swimmers[0].round() == "HEAT") {
        heats++;
    }
    else if (all_swimmers[0].round() == "SEMI"){
        semis++;
    }
    else{
        finals++;
    }
    for (int i=1; i<all_swimmers.size(); i++) {
        //to check if it is the same person
        //if its the same person
        //add on their rounds numbers
        //or push back to the next position in vector
        if (all_swimmers[i].first_name() == swimmer_first_name[num_of_swimmers]
            && all_swimmers[i].last_name()
            ==swimmer_last_name[num_of_swimmers]) {
            if (all_swimmers[i].round() == "HEAT") {
                heats++;
            }
            else if (all_swimmers[i].round() == "SEMI"){
                semis++;
            }
            else{
                finals++;
            }
        }
        else{
            //if it is not the same person, get the new name
            //add the rounds num for the first time see the name
            heat_num.push_back(heats);
            semi_num.push_back(semis);
            final_num.push_back(finals);
            swimmer_first_name.push_back(all_swimmers[i].first_name());
            swimmer_last_name.push_back(all_swimmers[i].last_name());
            swimmer_country.push_back(all_swimmers[i].country());
            if (all_swimmers[i].round() == "HEAT") {
                heats = 1;
                semis = 0;
                finals =0;//reset a new swimmer
            }
            else if (all_swimmers[i].round() == "SEMI"){
                semis = 1;
                heats = 0;
                finals = 0;
            }
            else{
                finals = 1;
                semis = 0;
                heats = 0;
            }
            num_of_swimmers++;
            
        }
    }
    //for the last person whose round numbers have not be put inside the vectors
    heat_num.push_back(heats);
    semi_num.push_back(semis);
    final_num.push_back(finals);
    //begin to print out the info
    out_string ="COUNTRY  PARTICIPANT                HEATS  SEMIS  FINALS\n";
    out_string += "--------------------------------------------------------\n";
    string full_name;// the name will add on the round(not final)
    for(int i=0; i < swimmer_first_name.size();i++){
        string heat_num_str = float_to_str(heat_num[i]);
        string semi_num_str = float_to_str(semi_num[i]);
        string final_num_str = float_to_str(final_num[i]);
        out_string += swimmer_country[i];out_string += "      ";
        full_name = swimmer_first_name[i]+" "+swimmer_last_name[i];
        out_string += full_name;
        
        int count_words = int(full_name.size());
        //30 blanks total
        //output the round numbers
        string type_blank(30 - count_words,' ');
        if (heat_num_str.size() <=1) {
            out_string +=" ";
        }
        out_string += type_blank;
        out_string += heat_num_str;
        out_string += "     ";
        if (semi_num_str.size()<=1) {//control the width if the number is larger
            //then 9
            out_string += " ";
        }
        out_string += semi_num_str;
        out_string += "      ";
        if (final_num_str.size()<=1) {
            out_string += " ";
        }
        out_string += final_num_str;out_string +="\n";
        
    }
    
}
//2nd participants table
//print the participants with medals table
//similar with above
//add the number of medals
void print_the_participants_medals(string &out_string, vector<vector<Swimmer> >
                                   &swimmer_in_each_event){
    vector<int> heat_num, semi_num,final_num, gold_num ,silver_num, bronze_num;
    vector<string> swimmer_first_name,swimmer_last_name, swimmer_country;
    vector<Swimmer> all_swimmers;
    int heats=0,semis=0,finals=0,golds =0,silvers = 0,bronze = 0;
    //put all the participants together
    for (int i=0; i<swimmer_in_each_event.size(); i++) {
        for (int j=0; j<swimmer_in_each_event[i].size(); j++) {
            all_swimmers.push_back(swimmer_in_each_event[i][j]);
        }
    }
    sort(all_swimmers.begin(),all_swimmers.end(),alphabetical_less_than);
    
    // count the number of heat, semi and final that each swimmers are in
    int num_of_swimmers=0;
    swimmer_first_name.push_back(all_swimmers[0].first_name());
    swimmer_last_name.push_back(all_swimmers[0].last_name());
    swimmer_country.push_back(all_swimmers[0].country());
    if (all_swimmers[0].round() == "HEAT") {
        heats++;
    }
    else if (all_swimmers[0].round() == "SEMI"){
        semis++;
    }
    else{
        //if in the final round, find out if the swimmer get the medal
        finals++;
        if (all_swimmers[0].medals() == "GOLD") {
            golds++;
        }
        else if(all_swimmers[0].medals() == "SILVER"){
            silvers++;
        }
        else if (all_swimmers[0].medals() == "BRONZE"){
            bronze++;
        }
    }
    //if find out the swimmers info, then get out all its info about the
    //participants table;count the number of the rounds and medals' occur
    //time, and then store to the corresponding vector
    for (int i=1; i<all_swimmers.size(); i++) {

        if (all_swimmers[i].first_name() == swimmer_first_name[num_of_swimmers]
            && all_swimmers[i].last_name()
            ==swimmer_last_name[num_of_swimmers]) {
            
            if (all_swimmers[i].round() == "HEAT") {
                heats++;
            }
            else if (all_swimmers[i].round() == "SEMI"){
                semis++;
            }
            else{
                finals++;//only in the round final, the swimmers may get medals
                if (all_swimmers[i].medals() == "GOLD") {

                    golds++;

                }
                else if(all_swimmers[i].medals() == "SILVER"){
                    silvers++;
                    
                }
                else if (all_swimmers[i].medals() == "BRONZE"){
  
                    bronze++;
                    
                }

            }
        }
        else{
            heat_num.push_back(heats);//store all the info in one person
            semi_num.push_back(semis);//start a new person
            final_num.push_back(finals);
            gold_num.push_back(golds);
            silver_num.push_back(silvers);
            bronze_num.push_back(bronze);
            swimmer_first_name.push_back(all_swimmers[i].first_name());
            swimmer_last_name.push_back(all_swimmers[i].last_name());
            swimmer_country.push_back(all_swimmers[i].country());
            //store the info when the name first occur
            if (all_swimmers[i].round() == "HEAT") {
                heats = 1;
                semis = 0;
                finals =0;
                golds = 0;
                silvers = 0;
                bronze = 0;
            }
            else if (all_swimmers[i].round() == "SEMI"){
                semis = 1;
                heats = 0;
                finals = 0;
                golds = 0;
                silvers = 0;
                bronze = 0;
            }
            else{
                finals = 1;
                semis = 0;
                heats = 0;
                if (all_swimmers[i].medals() == "GOLD") {
                    golds = 1;
                    silvers = 0;
                    bronze =0;

                }
                else if(all_swimmers[i].medals() == "SILVER"){

                    golds = 0;
                    silvers = 1;
                    bronze =0;

                }
                else if (all_swimmers[i].medals() == "BRONZE"){

                    golds = 0;
                    silvers = 0;
                    bronze =1;
                    
                }
                
                else{

                    bronze = 0;
                    silvers = 0;
                    golds = 0;

                }
                
            }
            num_of_swimmers++;
        }
    }

    //for the last person whose round numbers have not be put inside the vectors
    heat_num.push_back(heats);
    semi_num.push_back(semis);
    final_num.push_back(finals);
    gold_num.push_back(golds);
    silver_num.push_back(silvers);
    bronze_num.push_back(bronze);
    out_string = "COUNTRY  PARTICIPANT                HEATS  SEMIS  FINALS    GOLD  SILVER  BRONZE\n";
    out_string +="--------------------------------------------------------------------------------\n";
    string full_name;
    //calculate the blank to set the blanks and output the info one by one
    for(int i=0; i < swimmer_first_name.size();i++){
        out_string += swimmer_country[i]; out_string += "      ";
        full_name = swimmer_first_name[i]+" "+swimmer_last_name[i];
        int count_words=int(full_name.size());
        out_string += full_name;
        //blank and full name,totally 30 size
        string type_blank(30 - count_words,' ');
        out_string += type_blank;
        //if it larger than 9, the blank will less than one
        if (heat_num[i]<=10) {
            out_string += " ";
        }
        if (heat_num[i]==0) {
            out_string+=" ";
        }

        else{
            string heat_num_str = float_to_str(heat_num[i]);
            out_string += heat_num_str;}
            out_string += "     ";
        
        if (semi_num[i]<=10) {
            out_string += " ";
        }
        if (semi_num[i]==0) {
            out_string += " ";
        }

        else{
            string semi_num_str = float_to_str(semi_num[i]);
            out_string += semi_num_str; }
            out_string += "      ";
        
        if (final_num[i]<=10) {
            out_string +=" ";
        }
        if (final_num[i]==0) {
            out_string += " ";
        }

        else{
            string final_num_str = float_to_str(final_num[i]);
            out_string += final_num_str;} out_string += "      ";
        if (gold_num[i]<=10) {
            out_string +=" ";
        }
        if (gold_num[i]  == 0) {
            out_string += "       ";
        }

        else{
            string gold_num_str = float_to_str(gold_num[i]);
            out_string += gold_num_str; out_string += "      ";
        }
        if (silver_num[i] <=10) {
            out_string +=" ";
        }
        if (silver_num[i] == 0) {
            out_string += "        ";
        }

        else{
            string silver_num_str = float_to_str(silver_num[i]);
            out_string += silver_num_str;out_string +="       ";
        }
        if (bronze_num[i]==0) {
            out_string+=" \n";
        }
        else{
            string bronze_num_str = float_to_str(bronze_num[i]);
            out_string += bronze_num_str; out_string += "\n";
        }
    }
    
}

/**
    compute the average final time for each lane
    average time is already the average time each lap in one event
 
    @param avg_each_lane average time for one lap in each lane
    @param swimmers_in_each_event all swimmers
 */

//comupte the average final time for each lane
// average time is already the average time each lap in one event
void custom_table(vector<string> &avg_each_lane, vector<vector<Swimmer> >
                  swimmers_in_each_event){
    vector<float> lane1, lane2, lane3, lane4,lane5,lane6, lane7, lane8;
    string l1,l2,l3,l4,l5,l6,l7,l8;
    for (int i=0; i<swimmers_in_each_event.size(); i++) {
        for (int j=0; j < swimmers_in_each_event[i].size(); j++) {
            if (swimmers_in_each_event[i][j].lane_number() == "1") {
                lane1.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
                //totoal number divides the lap numbers
            }
            if (swimmers_in_each_event[i][j].lane_number() == "2") {
                lane2.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "3") {
                lane3.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "4") {
                lane4.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "5") {
                lane5.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "6") {
                lane6.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "7") {
                lane7.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
            if (swimmers_in_each_event[i][j].lane_number() == "8") {
                lane8.push_back(swimmers_in_each_event[i][j].final_time()
                                /(swimmers_in_each_event[i][j].game_len()/50));
            }
        }
    }
    //use the function to calculate each lane's average
    l1 = compute_avg(lane1);l2 = compute_avg(lane2);
    l3 = compute_avg(lane3);l4 = compute_avg(lane4);
    l5 = compute_avg(lane5);l6 = compute_avg(lane6);
    l7 = compute_avg(lane7);l8 = compute_avg(lane8);
    //push back their average time to output in the main
    avg_each_lane.push_back(l1);avg_each_lane.push_back(l2);
    avg_each_lane.push_back(l3);avg_each_lane.push_back(l4);
    avg_each_lane.push_back(l5);avg_each_lane.push_back(l6);
    avg_each_lane.push_back(l7);avg_each_lane.push_back(l8);
    
}




//in the main function, I input the info from the dataset
//construct a class and print the function
//swimmers in one event will be push back into a vector, then the whole data
//will be push back into the large swimmers_in_each_event
int main(int argc, const char * argv[]) {
    string event,title,word,gender,length,type;
    string round,number,lane_number,first_name,last_name, country,final_time_str,
    relay_team;
    float sec=0,sec0=0,sec1=0;
    vector<float> time;
    float float_final_time = 0,final_time= 0;
    vector<string> event_type;
    int len=0,game_len=0;
    vector<vector<Swimmer> > swimmers_in_each_event;//swimmers in each event in
    //one vector
    vector<Swimmer> swimmers_in_one_event;
    Swimmer one_swimmer;
    string out_string;
    bool isRelay = false;//used for the input data set
    //if it is relay read another way
    
    //use the argument to get the info
    ifstream in_str(argv[1]);
    ofstream out_str(argv[2]);
    string basic_type(argv[3]);
    string extended_type = "";
    if (argc == 5) {
        extended_type = "MEDALS";
      
    }
    
    //check the argument
    if (!in_str.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    if (argc != 4 && argc!=5) {
        cerr << "wrong number of argument.\n";
    }

    if (basic_type != "events" && basic_type != "participants" && basic_type !=
        "custom") {
        cerr << "Invalid input.\n";
        exit(1);
    }
    
    
    //begin to read input data
    while (in_str >> word) {
        if (word == "EVENT") {
            isRelay = false;
            if (swimmers_in_one_event.size()>0) {
                //put all the swimmers in the same event in one vector
                swimmers_in_each_event.push_back(swimmers_in_one_event);
                swimmers_in_one_event.clear();

            }
            in_str >> gender >> length >> type;
            // TODO write to competition info
            if (length[1]=='x') {
                //if it is a relay, read it by the sub string way to change it
                //to the integer
                string firstNumber = length.substr(0, 1);
                string secondNumber = length.substr(2, length.size() - 1);
                int multi = atoi(firstNumber.c_str());//the person number
                int multi2 = atoi(secondNumber.c_str());//swimming length
                len = multi * multi2;
                game_len = len;
            }
            else{
                //to calculate the numbers of laps
            len = atoi(length.c_str());
            game_len = len;
                
            }
            event = gender + " " + length +" "+type;//event name
            //to create the event vector, to count the event number and types
            event_type.push_back(event);
        }
        //to store the info in the class
        else if (word == "HEAT" || word == "SEMI" || word == "FINAL")
        {
            if (isRelay){//read it as a relay
                round = word;//it is the word already be read by input file
                if (word == "FINAL") {
                    number = "0";
                    in_str >> lane_number >> relay_team>>country;
                }
                else{
                    in_str >> number >> lane_number >> relay_team >>country;
                }
                time.clear();//push the float time to the time vector in the class
                for (int i=0; i < len/50; i++) {
                    in_str >> word;
                    if (word.size()==5) {//only the second be stored in time
                        sec1 = atof(word.c_str());
                    }
                    else{
                        sec1 = time_str_to_float(word);//if it is a minute standard
                        //transfer it to the second float standard
                    }
                    sec = sec1-sec0;//get the difference between the lap time
                    sec0 = sec1;
                    float_final_time += sec;
                    time.push_back(sec);
                    final_time_str = word;
                }
                final_time = float_final_time;
                sec0 = 0;
                float_final_time = 0;
                string medals="";
                for (int k=0; k<4; k++) {
                    in_str>>first_name >> last_name;
                    Swimmer one_swimmer(first_name, last_name,round, number,
                    lane_number,country,time, event,final_time,game_len,
                                        final_time_str,medals,relay_team);
                    swimmers_in_one_event.push_back(one_swimmer);
                    //store the swimmer info
                }
            }
            else {
            // TODO read swimmer info from in_str
            round = word;
            if (word == "FINAL") {//if its final, there are no round number
                number = "0";
                in_str >> lane_number >> first_name >> last_name >> country;
            }
            else{
                in_str>> number >> lane_number >> first_name >> last_name
                >> country;
            }
            //put all the time into the time vector.First to calculate each 50m lap
            //then put the final time in it.
            time.clear();
            for (int i=0; i < len/50; i++) {
                in_str >> word;
                if (word.size()==5) {
                    sec1 = atof(word.c_str());
                }
                else{
                    sec1 = time_str_to_float(word);//convert to the float to calculate
                }
                sec = sec1-sec0;
                sec0 = sec1;
                float_final_time += sec;
                time.push_back(sec);
                final_time_str = word;
            }
            
            final_time = float_final_time;
            sec0 = 0;
            float_final_time = 0;
            string medals="";
            string relay_team="";
            // TODO construct swimmer info
            Swimmer one_swimmer (first_name, last_name,round, number,lane_number,
        country,time, event,final_time,game_len,final_time_str,medals,relay_team);
            swimmers_in_one_event.push_back(one_swimmer);}
        }
        else if (word=="Relay"){
            //make the flag on, and read another way
            isRelay = true;
            event +=" Relay";
            event_type.pop_back();//then before the event is not complete
            event_type.push_back(event);//change it to the correct one
        }
        
    
        // when the competition has 4th argument
        else
        {
            isRelay = false;
            // TODO competition info add extra detail
            event+=" ";
            event += word;
            //to delete the wrong event name and change it to the new event name
            event_type.pop_back();
            event_type.push_back(event);//change the event name to the complete one
        }
        
    }
    swimmers_in_each_event.push_back(swimmers_in_one_event);
    // finish to arrange the input data.
    // begin to call for the output data
  
    vector<string> ordered_event_table;
    vector<string> ordered_event_medal_table;
    //output the data into the output txt
    //push back all the event in a new vector for the later sort use
    for (int num_of_event=0; num_of_event<int(event_type.size()); num_of_event++) {
        if (swimmers_in_each_event[num_of_event][0].relay_team() =="") {
            //for the not relay event
            set_the_medals(swimmers_in_each_event,num_of_event);
            event_table(out_string, len,event_type,
                        swimmers_in_each_event,num_of_event);
            ordered_event_table.push_back(out_string);
            event_medal_table(out_string, len,event_type,
                              swimmers_in_each_event,num_of_event);
            ordered_event_medal_table.push_back(out_string);

        }
        
        else{//go the relay event table
            set_the_medals_for_relay(swimmers_in_each_event,num_of_event);
            event_table_for_relay(out_string, len, event_type,
                                  swimmers_in_each_event, num_of_event);
            ordered_event_table.push_back(out_string);
            event_medal_table_for_relay(out_string, len, event_type,
                                        swimmers_in_each_event, num_of_event);
            ordered_event_medal_table.push_back(out_string);
        }
            }
    
    //if its ask for the events
    //order the event table first, then output
    
    if (basic_type == "events" && extended_type =="") {
        sort(ordered_event_table.begin(), ordered_event_table.end(),
             less_than_event);
        for (int i=0; i<ordered_event_table.size(); i++) {
            out_str << ordered_event_table[i];
            out_str << "\n";
        }
    }
    //order the event medal first, then print out
    else if (basic_type == "events" && extended_type == "MEDALS") {
        sort(ordered_event_medal_table.begin(),ordered_event_medal_table.end(),
             less_than_event);
        for (int i=0 ; i<ordered_event_medal_table.size(); i++) {
            out_str << ordered_event_medal_table[i];
            out_str << "\n";
        }

    }
    
    else if (basic_type == "participants" && extended_type == "") {
        print_the_participants(out_string, swimmers_in_each_event);
        out_str << out_string;
    }
    
    else if (basic_type == "participants" && extended_type == "MEDALS"){
        print_the_participants_medals(out_string, swimmers_in_each_event);
        out_str << out_string;
    }
    
    //output the custom table and get a conclusion
    else if (basic_type == "custom"){
    vector<string> avg_lane;
    float min_lane = 100;
    int num_lane_min=0;
    custom_table(avg_lane,swimmers_in_each_event);
    // find out the min average lane and output the lane number
    for (int j=0; j<avg_lane.size(); j++) {
        if (min_lane > atof(avg_lane[j].c_str())) {
            min_lane = atof(avg_lane[j].c_str());
            num_lane_min = j;
            }
        out_str <<"the lane number is "<<j+1<<"its average time is " <<
        avg_lane[j] << " \n";
        }
        out_str<<"the fastest lane is "<<num_lane_min+1<<endl;
    }
    
    return 0;
}
