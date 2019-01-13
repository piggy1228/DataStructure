#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


typedef map<string,pair<int,vector<string> > >  COSTUME_SHOP_TYPE;
typedef map<pair<string,string>, string> PEOPLE_TYPE;


// prototypes for the helper functions
void addCostume(COSTUME_SHOP_TYPE &costume_shop);
void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people);
void lookup(COSTUME_SHOP_TYPE& costume_shop);
void printPeople(PEOPLE_TYPE& people);
int main() {
    //in Xcode only
    ifstream arq(getenv("SSSSS"));
    cin.rdbuf(arq.rdbuf());
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


void addCostume(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    int num;
    std::cin >> costume_name >> num;
    vector<string> name;
    int original_num = 0;
    map<string,pair<int,vector<string> > >::iterator c_itr;
    c_itr = costume_shop.find(costume_name);
    if (c_itr!=costume_shop.end()) {
        original_num = c_itr->second.first;
    }

    pair<int, vector<string> > p1 = make_pair(num+original_num, name);

    
    costume_shop[costume_name] = p1;
    cout<<"Added "<<num<<" "<<costume_name;
    if (num == 1) {
        cout<<" costume.\n";
    }
    else{
        cout<<" costumes.\n";
    }
    
}


void rentCostume(COSTUME_SHOP_TYPE& costume_shop, PEOPLE_TYPE& people) {
    std::string first_name;
    std::string last_name;
    std::string costume_name;
    std::cin >> first_name >> last_name >> costume_name;
    string full_name2 = first_name+" "+last_name;
    map<string,string>::iterator itr;
    map<string,pair<int,vector<string> > >::iterator c_itr;
    pair<string, string> p(last_name,first_name);
    string original_costume=people[p];
    c_itr = costume_shop.find(costume_name);
    if (c_itr == costume_shop.end()) {
        cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }
    
    else if (c_itr->second.first == 0){
        cout<<"No "<<costume_name<<" costumes available.\n";
 
    }
    
    else if (original_costume.size() != 0 ) {
        if (original_costume == costume_name) {
            cout<<first_name<<" "<<last_name<<" already has a "<<original_costume<<" costume.\n";
        }
        else{
            costume_shop[original_costume].first++;
            vector<string>::iterator v_itr;
            for (v_itr = costume_shop[original_costume].second.begin(); v_itr!=costume_shop[original_costume].second.end(); v_itr++) {
                if (*v_itr == full_name2) {
                    costume_shop[original_costume].second.erase(v_itr);
                    break;
                }
            }
            people[p] = costume_name;
            costume_shop[costume_name].first--;
            costume_shop[costume_name].second.push_back(full_name2);
            cout<<first_name<<" "<<last_name<<" returns a "<<original_costume<<" costume before renting a "<<costume_name<<" costume.\n";
        }
    }
    
    else{
        people[p] = costume_name;
        costume_shop[costume_name].first--;
        costume_shop[costume_name].second.push_back(full_name2);
        cout<<first_name<<" "<<last_name<<" rents a "<<costume_name<<" costume.\n";
    }
    
}


void lookup(COSTUME_SHOP_TYPE& costume_shop) {
    std::string costume_name;
    std::cin >> costume_name;
    
    map<string,pair<int,vector<string> > >::iterator c_itr;
    c_itr = costume_shop.find(costume_name);
    if (c_itr == costume_shop.end()) {
        cout<<"The shop doesn't carry "<<costume_name<<" costumes.\n";
    }
    else{
        cout<<"Shop info for "<<costume_name<<" costumes:\n";
        int num =c_itr->second.first;
        if (num >0) {
            if (num >1) {
                cout<<"  "<<num<<" copies available\n";
            }
            else{
                cout<<"  "<<num<<" copy available\n";
            }
            
        }
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


void printPeople(PEOPLE_TYPE& people) {
    map<pair<string,string>, string>::iterator itr;
    string first_name;
    string last_name;
    if (people.size()>1) {
        cout<<"Costume info for the "<<people.size()<<" party attendees:\n";
        
    }
    else{
        cout<<"Costume info for the "<<people.size()<<" party attendee:\n";
    }
    for (itr = people.begin(); itr != people.end(); itr++) {
        if (itr->second.size() == 0) {
            cout<<"  "<<itr->first.second<<" "<<itr->first.first<<" does not have a costume.\n";

        }
        else{
            cout<<"  "<<itr->first.second<<" "<<itr->first.first<<" is wearing a "<<itr->second<<" costume.\n";
        }
        
    }
    
}
