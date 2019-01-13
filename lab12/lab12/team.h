#ifndef _TEAM_H_
#define _TEAM_H_

#include <string>
#include <iostream>
#include <list>

#include "superhero.h"

class Team {

public:
    Team(){
        std::list<Superhero> heros;
        superheroes = heros;
    }
  // accessor function
  std::string getName() const;

  // adding and removing a single superhero
    void operator+=(const Superhero &a){
        superheroes.push_back(a);
    }
    void operator-=(const Superhero &a){
        list<Superhero>::iterator itr;
        for (itr = superheroes.begin(); itr != superheroes.end(); itr++) {
            if ((*itr).getName() == a.getName()) {
                superheroes.erase(itr);
            }
        }
    }

  // adding two teams together or a team and a superhero together
  // makes a team.  these functions must be member functions to allow
  // access to the list of superheroes.
    friend Team operator+(const Team &a, const Team &b){
        Team t;
        t.superheroes = a.superheroes;
        for (list<Superhero>::const_iterator itr = b.superheroes.begin(); itr != b.superheroes.end(); itr++) {
            t.superheroes.push_back(*itr);
        }
   
        return t;
    }
  friend Team operator+(const Team &a, const Superhero &b){
      Team t;
      t.superheroes = a.superheroes;
      t.superheroes.push_back(b);
      return t;
    }
  
private:
  // REPRESENATION
  std::list<Superhero> superheroes;
};

// non-member function because it doesn't need access to any Team variables
inline Team operator+(const Superhero &a, const Superhero &b){
    Team t;
    t += a;
    t += b;
    return t;
}

#endif
