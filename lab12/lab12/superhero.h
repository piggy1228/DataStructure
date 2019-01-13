//
//  superhero.h
//  lab12
//
//  Created by KEXIN ZHU on 11/15/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#ifndef superhero_h
#define superhero_h

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;
class Superhero{
public:
    //CONSTRUCTOR
    Superhero(std::string name, std::string trueIdentity, std::string power)
    {
        name_ = name;
        trueIdentity_ = trueIdentity;
        power_ = power;
        isGood_ = true;
    }
    
    //ACCESSOR
    const std::string getName() const
    {
        return name_;
    }
    
    const std::string getPower() const
    {
        return power_;
    }
    
    const string getTrueIdentity() const {return trueIdentity_;}
    //OPERATOR
    friend ostream& operator<< (ostream& ostr,Superhero& s){
        if (s.isGood_ ==true) {
            ostr<<"Superhero ";
        }
        else{
            ostr<<"Supervillain ";
        }
        ostr<<s.name_<<" has power "<<s.power_<<endl;
        return ostr;
    }
    
    bool operator== (const string& rhs){
        return trueIdentity_ == rhs;
    }
    
    bool operator!= (const string& rhs){
        return trueIdentity_ != rhs;
    }
    
    //GOOD OR NOT
    bool isGood(){
        return isGood_;
    }
    
    void operator- (){
        if (isGood_ == true) {
            isGood_ = false;
        }else{
            isGood_ = true;
        }
    }
    bool operator> (const Superhero& rhs){
        string powerA = power_;
        string powerB = rhs.power_;
        if (powerA == "Wood" && powerB == "Water" ) {
            return true;
        }
        else if (powerA == "Fire" && powerB == "Wood"){
            return true;
        }
        else if (powerA == "Water" && powerB == "Fire"){
            return true;
        }
        return false;
    }
private:
    string trueIdentity_;
    string power_;
    string name_;
    bool isGood_;
};

#endif /* superhero_h */
