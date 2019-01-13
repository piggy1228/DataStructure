#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//============================================================================
//version 1
//============================================================================
//first string store the costume name,in the pair, first int store the number
//of the costume numbers left the vector store the name customers who rent it
typedef map<string,pair<int,vector<string> > >  COSTUME_SHOP_TYPE;
//in the first pair first store last name,second store the first name
//the value type store the costume name
typedef map<pair<string,string>, string> PEOPLE_TYPE;

//============================================================================
//version 2
//============================================================================
//the int store the number of the costume left, the first object in the vector
//is the name of the costume, and other strings are the name of who rent the
//the int store the number of the costume left, the first object in the vector
//is the name of the costume, and other strings are the name of who rent the
//costume
typedef vector<vector<pair<int, vector<string> > > > COSTUME_SHOP_TYPE_nonmap;

//string store the last_name,first name and costume_name
typedef vector<vector<string> > PEOPLE_TYPE_nonmap;

//============================================================================
//version 1
//============================================================================

// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(PEOPLE_TYPE& people);

//============================================================================
//version 2
//============================================================================
// prototypes for the helper functions
void addCostume_nonmap(COSTUME_SHOP_TYPE_nonmap &costume_shop_nonmap);
void rentCostume_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap,
                        PEOPLE_TYPE_nonmap& people_nonmap);
void lookup_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap);
void printPeople_nonmap(PEOPLE_TYPE_nonmap& people_nonmap);





//============================================================================
//version 1
//============================================================================
int main(int argc,char* argv[]) {
    if (argc == 1) {
        //in Xcode only
        //ifstream arq(getenv("SSSSS"));
        //cin.rdbuf(arq.rdbuf());
        // two data structures store all of the information for efficiency
        COSTUME_SHOP_TYPE costume_shop;
        PEOPLE_TYPE people;
        char c;
        
        while (std::cin >> c) {
            if (c == 'a') {
                addCostume(costume_shop);
            } else if (c == 'r') {
                rentCostume(costume_shop,people);
            } else if (c == 'l') {
                lookup(costume_shop);
            } else if (c == 'p') {
                printPeople(people);
            } else {
                std::cerr << "error unknown char " << c << std::endl;
                exit(0);
            }
        }
    }
    //for the extra part
    //============================================================================
    //version 2
    //============================================================================

    else{
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
    

}





//============================================================================
//version 1
//============================================================================
/**
 when add inventory, ingorning the customers' requirments, make the numbers of
 inventory and costume name match, with a empty vector for later storing names
 */
void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    vector<string> name;//a empty vector for later use
    int original_num = 0;//original number initialize
    map<string,pair<int,vector<string> > >::iterator c_itr;
    c_itr = costume_shop.find(costume_name);//find the costume_name
    //if the inventory already exists before
    if (c_itr!=costume_shop.end()) {
        original_num = c_itr->second.first;
        //find out the original numbers
    }
    pair<int, vector<string> > p1 = make_pair(num+original_num, name);
    //make the number of inventory and customer's name a pair, their(vector size)
    //sum should always be the same
    
    costume_shop[costume_name] = p1;//the value type of the costume_shop is the pair
    cout<<"Added "<<num<<" "<<costume_name;
    if (num == 1) {
        cout<<" costume.\n";
    }
    else{
        cout<<" costumes.\n";
    }
    
}

/**
 first find out if the shop has this costume and does the shop has any costume left
 if the costumer already has one,need to first return then rent the new costume
 */
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    string full_name = first_name+" "+last_name;
    map<string,string>::iterator itr;
    map<string,pair<int,vector<string> > >::iterator c_itr;
    pair<string, string> p(last_name,first_name);//make last name and first name a pair
    string original_costume=people[p];//if the people already have a costume
    //record all the people who come to the shop
    c_itr = costume_shop.find(costume_name);
    //if there cannot find the costume name, there is no inventory
    if (c_itr == costume_shop.end()) {
        cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }
    //if the velue type showed the number of inventory is 0
    else if (c_itr->second.first == 0){
        cout<<"No "<<costume_name<<" costumes available.\n";
    }
    //if the customers already have a costume
    else if (original_costume.size() != 0 ) {
        //if people wants to rent a same one
        if (original_costume == costume_name) {
            cout<<first_name<<" "<<last_name<<" already has a "<<original_costume
            <<" costume.\n";
        }
        //if not the same one
        else{
            costume_shop[original_costume].first++;//increment the returning costume
            vector<string>::iterator v_itr;
            for (v_itr = costume_shop[original_costume].second.begin();
                 v_itr!=costume_shop[original_costume].second.end(); v_itr++) {
                if (*v_itr == full_name) {
                    costume_shop[original_costume].second.erase(v_itr);
                    //erase the name from the name vector when returning
                    break;
                }
            }
            people[p] = costume_name;
            costume_shop[costume_name].first--;//decrement when it was rent out
            costume_shop[costume_name].second.push_back(full_name);
            //add the customer name in the vector of name matched the costume name
            cout<<first_name<<" "<<last_name<<" returns a "<<original_costume
            <<" costume before renting a "<<costume_name<<" costume.\n";
        }
    }
    //if the customer is the first time appear and there is inventory for costume
    else{
        people[p] = costume_name;
        costume_shop[costume_name].first--;//decrement inventory number
        costume_shop[costume_name].second.push_back(full_name);//add name
        cout<<first_name<<" "<<last_name<<" rents a "<<costume_name<<" costume.\n";
    }
    
}

/**
 to look up if the shop has this inventory and print out the name in order
 in the vector
 */
void lookup(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    std::cin >> costume_name;
    //iterator to look for the specific costume
    map<string,pair<int,vector<string> > >::iterator c_itr;
    c_itr = costume_shop.find(costume_name);
    //if does not find the costume
    if (c_itr == costume_shop.end()) {
        cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }
    else{
        cout<<"Shop info for "<<costume_name<<" costumes:\n";
        int num =c_itr->second.first;
        //print the integers that the inventory left
        if (num >0) {
            if (num >1) {
                cout<<"  "<<num<<" copies available\n";
            }
            else{
                cout<<"  "<<num<<" copy available\n";
            }
            
        }
        //if anyone rented it print out their name
        if (c_itr->second.second.size()>0) {
            int p_num = c_itr->second.second.size();
            if (p_num>1) {
                cout<<"  "<<p_num<<" copies rented by:\n";
            }
            else{
                cout<<"  "<<p_num<<" copy rented by:\n";
            }
            for (int i=0; i<p_num; i++) {
                cout<<"    "<<c_itr->second.second[i]<<endl;
            }
        }
    }
}


/**
 print all the people who appeared before and what they are wearing
 the map has already sorted by last name
 */
void printPeople(PEOPLE_TYPE& people) {
    map<pair<string,string>, string>::iterator itr;
    //print the person number come to the shop
    if (people.size()>1) {
        cout<<"Costume info for the "<<people.size()<<" party attendees:\n";
    }
    else{
        cout<<"Costume info for the "<<people.size()<<" party attendee:\n";
    }
    for (itr = people.begin(); itr != people.end(); itr++) {
        //if the costume does not available
        if (itr->second.size() == 0) {
            cout<<"  "<<itr->first.second<<" "<<itr->first.first
            <<" does not have a costume.\n";
            
        }
        //print the information in the map
        else{
            cout<<"  "<<itr->first.second<<" "<<itr->first.first<<" is wearing a "
            <<itr->second<<" costume.\n";
        }
        
    }
    
}

//============================================================================
//version 2
//============================================================================

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
void rentCostume_nonmap(COSTUME_SHOP_TYPE_nonmap& costume_shop_nonmap,
                        PEOPLE_TYPE_nonmap& people_nonmap) {
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
            if (last_name == people_nonmap[i][0] && first_name ==
                people_nonmap[i][1]) {
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
                        cout<<"  "<<costume_shop_nonmap[i][j].first<<
                        " copies available\n";
                    }
                    else{
                        cout<<"  "<<costume_shop_nonmap[i][j].first<<
                        " copy available\n";
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
    //get the object one by one from the people vectors,then find a place to
    //insert in the sorted vector
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




