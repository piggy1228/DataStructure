#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <assert.h>
#include <fstream>
#include <sstream>
using namespace std;
//the int store the number of the costume left, the first object in the vector
//is the name of the costume, and other strings are the name of who rent the
//costume
typedef vector<vector<pair<int, vector<string> > > > COSTUME_SHOP_TYPE_nonmap;

//string store the last_name,first name and costume_name
typedef vector<vector<string> > PEOPLE_TYPE_nonmap;

// prototypes for the helper functions
void addCostume_nonmap(COSTUME_SHOP_TYPE_nonmap &costume_shop_nonmap);
void rentCostume_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap, PEOPLE_TYPE_nonmap& people_nonmap);
void lookup_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap);
void printPeople_nonmap(PEOPLE_TYPE_nonmap& people_nonmap);

int main(int argc, char* argv[]) {

    ifstream arq(getenv("SSSSS"));
    cin.rdbuf(arq.rdbuf());
    //if (argc != 2) {
        //exit(1);
   // }
   // assert(argc == 2);
  // two data structures store all of the information for efficiency
  COSTUME_SHOP_TYPE_nonmap costume_shop_nonmap;
  PEOPLE_TYPE_nonmap people_nonmap;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addCostume_nonmap(costume_shop_nonmap);
    } else if (c == 'r') {
      rentCostume_nonmap(costume_shop_nonmap,people_nonmap);
    } else if (c == 'l') {
      lookup_nonmap(costume_shop_nonmap);
    } else if (c == 'p') {
      printPeople_nonmap(people_nonmap);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addCostume_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap) {
  std::string costume_name;
  int num;
  std::cin >> costume_name >> num;
    vector<pair<int, vector<string> > > one_costume;
    vector<string> names;
    names.clear();
    one_costume.clear();
    bool found = false;
    //to find if the inventory is already in the vector
    for (int i=0; i<costume_shop_nonmap.size(); i++) {
        for (int j=0; j<costume_shop_nonmap[i].size(); j++) {
            if (costume_name == costume_shop_nonmap[i][j].second[0]) {
                //to add on the inventory numbers
                costume_shop_nonmap[i][j].first = num+ costume_shop_nonmap[i][j].first;
                found = true;
                break;
            }
        }
    }
    //if cannot find the same name of costume_name,make a new vector to store
    //the costume and the names vector is empty since which store the name who
    //rent the costume
    if (!found) {
        names.push_back(costume_name);
        one_costume.push_back(make_pair(num, names));
        costume_shop_nonmap.push_back(one_costume);
    }

    //print out output
    cout<<"Added "<<num<<" "<<costume_name;
    if (num == 1) {
        cout<<" costume.\n";
    }
    else{
        cout<<" costumes.\n";
    }
}

/*
 need to consider several cases.there is no costume_name;considering have rent before,
 and available and found,not rent before, and not available;
 considering the number is 0.not available;
 not rent before, but available;not rent before, and not available.
 use the for loop to find the name are the same to get the exact position
 */
void rentCostume_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap, PEOPLE_TYPE_nonmap& people_nonmap) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    string full_name = first_name + " "+last_name;
    vector<string> people_custome;
    string original_custome = "";

    
    bool rented = false;
    //find the info for the costumer first
    for (int i=0; i<people_nonmap.size(); i++) {
        if (last_name == people_nonmap[i][0] && first_name == people_nonmap[i][1]) {
            rented = true;
            original_custome = people_nonmap[i][2];
        }
    }
    
    
    
    
    //get the info of the costume
    bool found = false;
    bool available = false;
    bool same = false;
    for (int i=0; i<costume_shop_nonmap.size(); i++) {
        for (int j=0; j<costume_shop_nonmap[i].size(); j++) {
            if (costume_shop_nonmap[i][j].second[0] == costume_name) {
                found = true;
                //not available
                if(costume_shop_nonmap[i][j].first == 0){
                    cout<<"No "<<costume_name<<" costumes available.\n";
                }
                else{
                    available = true;
                    //find if the two costumes are the same
                    if (original_custome == costume_name) {
                        same = true;
                        cout<<full_name<<" already has a "<<costume_name
                        <<" costume.\n";
                    }
                    else{
                        //if rented before
                        if (rented && original_custome.size() > 1) {
                            cout<<full_name<<" returns a "<<original_custome
                            <<" costume before renting a "<<costume_name
                            <<" costume.\n";
                            //undo the former info later
                        }
                        else{
                            cout<<full_name<<" rents a "<<costume_name<<" costume.\n";
                        }
                    //change the vector
                    costume_shop_nonmap[i][j].first--;
                    costume_shop_nonmap[i][j].second.push_back(full_name);
                    }
                }
            }
        }
    }
    if (!found) {
        cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }
    
    //undo the info if rented before
    if (rented && !same && available) {
        for (int i=0; i<people_nonmap.size(); i++) {
            if (last_name == people_nonmap[i][0] && first_name == people_nonmap[i][1]) {
                people_nonmap[i][2] = costume_name;
            }
        }
        //delete the name in the vector for the original costumes
        for (int i=0; i<costume_shop_nonmap.size(); i++) {
            for (int j=0; j<costume_shop_nonmap[i].size(); j++) {
                if (costume_shop_nonmap[i][j].second[0] == original_custome) {
                    costume_shop_nonmap[i][j].first++;
                    vector<string>::iterator itr;
                    for (itr =costume_shop_nonmap[i][j].second.begin() ;
                         itr != costume_shop_nonmap[i][j].second.end(); itr++) {
                        if ((*itr) == full_name) {
                            costume_shop_nonmap[i][j].second.erase(itr);
                            break;
                        }
                    }
                }
            }
        }
        
    }
    //modify the people info if not rented before
    if (!rented && found &&available) {
        vector<string> one_person;
        one_person.push_back(last_name);
        one_person.push_back(first_name);
        one_person.push_back(costume_name);
        people_nonmap.push_back(one_person);
    }
    //if not rented and the costume not available
    if (!rented && (!found || !available)) {
        vector<string> one_person;
        one_person.push_back(last_name);
        one_person.push_back(first_name);
        one_person.push_back("");
        people_nonmap.push_back(one_person);
    }
}

/**
 have a specfic name and find the infomation, just need to use the for loop
 to locate the position and print all the information out
 */

void lookup_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap) {
  std::string costume_name;
  std::cin >> costume_name;
 
    bool found = false;
    //get to the object have the same name of the costume_name
    for (int i=0; i<costume_shop_nonmap.size(); i++) {
        for (int j=0; j<costume_shop_nonmap[i].size(); j++) {
            if (costume_shop_nonmap[i][j].second[0] == costume_name) {
                found = true;
                cout<<"Shop info for "<<costume_name<<" costumes:\n";
                if (costume_shop_nonmap[i][j].first > 0) {
                    if (costume_shop_nonmap[i][j].first > 1) {
                        cout<<"  "<<costume_shop_nonmap[i][j].first<<" copies available\n";
                    }
                    else{
                        cout<<"  "<<costume_shop_nonmap[i][j].first<<" copy available\n";
                    }
                }
                //print put the customer name for the costume name
                if (costume_shop_nonmap[i][j].second.size()==2) {
                    cout<< "  "<<costume_shop_nonmap[i][j].second.size()-1
                    <<" copy rented by:\n";
                    cout<<"    "<<costume_shop_nonmap[i][j].second[1]<<endl;
                }
                else if(costume_shop_nonmap[i][j].second.size()>2){
                    cout<<"  "<<costume_shop_nonmap[i][j].second.size()-1
                    <<" copies rented by:\n";
                    for (int k=1; k<costume_shop_nonmap[i][j].second.size(); k++) {
                        cout<<"    "<<costume_shop_nonmap[i][j].second[k]<<"\n";
                    }
                }
                
            }
        }
    }
    //if cannot find the costume in the shop
    if (!found) {
         cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }

}
/**
 print all the people information
 push back them into a sorted vector first
 */

void printPeople_nonmap(PEOPLE_TYPE_nonmap& people_nonmap) {
    if (people_nonmap.size() == 1) {
        cout<<"Costume info for the 1 party attendee:\n";
    }
    else{
        cout<<"Costume info for the "<<people_nonmap.size()<<" party attendees:\n";
    }
    vector<vector<string> > sorted;//a tmp vector to store the sorted info
    sorted.push_back(people_nonmap[0]);
    //get the object one by one from the people vectors,then find a place to insert
    //in the sorted vector
    for (int i=1; i<people_nonmap.size(); i++) {
        bool inserted = false;
        for (vector<vector<string> >::iterator itr = sorted.begin();
             itr!=sorted.end(); itr++) {
            //find a place to insert
            if (people_nonmap[i][0]<(*itr)[0]) {
                sorted.insert(itr, people_nonmap[i]);
                inserted = true;
                break;
            }
            //if the last name are the same, compare the first name
            else if (people_nonmap[i][0]==(*itr)[0])
                if (people_nonmap[i][1]<(*itr)[1]) {
                    sorted.insert(itr, people_nonmap[i]);
                    inserted = true;
                    break;
                }
        }
        //if not find a place to insert, inster it at the last
        if (!inserted) {
            sorted.push_back(people_nonmap[i]);
        }
    }

    //ptint the sorted people info
    //first object is last name, second object is first name and third object is
    //the costume name
    for (int i=0; i<sorted.size(); i++) {
        if (sorted[i][2].size()>0) {
            cout<<"  "<<sorted[i][1]<<" "<<sorted[i][0]<<" is wearing a "<<
            sorted[i][2]<<" costume.\n";
        }
        else{
            cout<<"  "<<sorted[i][1]<<" "<<sorted[i][0]<<
            " does not have a costume.\n";
        }
    }
}
