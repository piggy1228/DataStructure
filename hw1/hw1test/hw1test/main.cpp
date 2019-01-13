//
//  main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

int count_line(int width, vector<string> &text, vector<string> &lined_text, vector<vector<string> > &word_in_line){
    
    int line_num = 1;
    vector<string> word_each_line;
    int accumulated_num = 0;
    string line_string="";
    
    int i;
    for (i=0; i<text.size(); i++) {
        if (text[i].size()<=width) {
            accumulated_num += text[i].size()+1;
            if (accumulated_num-1< width) {
                line_string += text[i]+" ";
                word_each_line.push_back(text[i]);
            }
            else{
                accumulated_num = int(text[i].size());
                line_num +=1;
                lined_text.push_back(line_string);
                word_in_line.push_back(word_each_line);
                line_string = text[i]+" ";
                word_each_line.clear();
                word_each_line.push_back(text[i]);
            }
        }
        if(text[i].size() > width){
            
            int round = int(text[i].size())/(width-1);
            if (accumulated_num>0) {
                lined_text.push_back(line_string);
                word_in_line.push_back(word_each_line);
                word_each_line.clear();
            }
            line_string ="";
            for (int j=0; j<round; j++) {
                for (int k=0; k<(width-1); k++) {
                    int string_num;
                    string_num = k+j*(width-1);
                    line_string += text[i][string_num];
                }
                line_string += "-";
                word_each_line.push_back(line_string);
                line_string +=" ";
                lined_text.push_back(line_string);
                word_in_line.push_back(word_each_line);
                word_each_line.clear();
                line_string = "";
            }
            line_string = "";
            for (int m=0; m<(int(text[i].size())-round*(width-1)); m++) {
                line_string += text[i][m+round*(width-1)];
            }
            word_each_line.push_back(line_string);
            line_string +=" ";
            accumulated_num = int(text[i].size())-round*(width-1)+1;
        }
        
    }
    //string temp = line_string.substr(0,text[i].size());
    //cout << "temp: " <<temp << endl;
    lined_text.push_back(line_string);
    /*
     for (int t = 0; t < lined_text.size(); t++) {
     cout << "lined_text[" << t << "]: " << lined_text[t] << endl;
     }
     */
    word_in_line.push_back(word_each_line);
    /*
     for (int t = 0; t < word_in_line.size(); t++) {
     for (int v = 0; v < word_in_line[t].size(); v++) {
     cout << "WordInLine[" << t << "]["<< v << "]: "<< word_in_line[t][v] << endl;
     }
     }
     */
    
    return line_num;
}



void flush_left(vector<string> &lined_text,int line_num,int width,string &out_string){
    out_string = "";
    for (int i=0; i<lined_text.size(); i++) {
        out_string+=  "|" ;
        out_string+=" ";
        out_string+=lined_text[i];
        unsigned long blank_num;
        blank_num=width+1-lined_text[i].size();
        for (int j = 0; j<blank_num; j++) {
            out_string += ' ';
        }
        out_string+="|\n";
    }
}

void flush_right(vector<string> &lined_text, int line_num, int width,string &out_string){
    out_string ="";
    for (int i=0; i<lined_text.size(); i++) {
        out_string+= "| ";
        unsigned long blank_num;
        blank_num=width+1-lined_text[i].size();
        for (int j = 0; j<blank_num; j++) {
            out_string += ' ';
        }
        out_string += lined_text[i];
        out_string += "|\n";
    }
}

int count_word(string count_string){
    int num_of_word = 0;
    char nextChar;
    // checks each character in the string
    for (int i=0; i<int(count_string.length()); i++)
    {
        nextChar = count_string.at(i); // gets a character
        if (isspace(count_string[i]))
            num_of_word++;
    }
    return num_of_word;
    
}

void full_justify(vector<string> &lined_text,vector<vector<string> > &word_in_line,
                  int line_num, int width,string &out_string){
    unsigned long blank_num;
    int total_word;
    vector<unsigned long> blank_num_in_line;
    vector<int> word_num_in_line;
    vector<int> vector_blank_for_all;
    vector<int> vector_blank_left;
    int accumulated_blank_left=0;
    out_string="";
    for (int i=0; i<lined_text.size(); i++) {
        string word;
        blank_num = width+1-lined_text[i].size();
        blank_num_in_line.push_back(blank_num);
        total_word = count_word(lined_text[i]);
        word_num_in_line.push_back(total_word);
    }
    for (int j=0; j<lined_text.size(); j++) {
        int blank_for_all;
        int blank_left;
        if (word_num_in_line[j]>1) {
            blank_for_all = int (blank_num_in_line[j])/(word_num_in_line[j]-1);
            vector_blank_for_all.push_back(blank_for_all);
            blank_left =int (blank_num_in_line[j])% (word_num_in_line[j]-1);
            vector_blank_left.push_back(blank_left);
        }
        else{
            blank_for_all = 0;
            vector_blank_for_all.push_back(blank_for_all);
            blank_left = int(blank_num_in_line[j]);
            vector_blank_left.push_back(blank_left);
            
        }
    }
    for (int i=0; i<word_in_line.size()-1; i++) {
        out_string += "| ";
        int last = int(word_in_line[i].size());
        for (int j=0; j<last; j++) {
            if (j != last-1) {
                out_string += word_in_line[i][j];
                out_string +=" ";
                string type_blank(vector_blank_for_all[i],' ');
                out_string += type_blank;
                //cout<<type_blank<<endl;
                if (accumulated_blank_left<vector_blank_left[i]) {
                    out_string += " ";
                    accumulated_blank_left++;
                }
            }
            if(j == last-1 && last !=1){
                out_string+= word_in_line[i][last-1];
                out_string+=" |\n";
                accumulated_blank_left=0;
            }
        }
        
        if (last == 1) {
            out_string += word_in_line[i][0];
            out_string +=" ";
            if (blank_num_in_line[i] !=0) {
                string type_last_blank(int(blank_num_in_line[i]),' ');
                out_string += type_last_blank;
            }
            out_string +="|\n";
        }
    }
    int last_line_index = int(word_in_line[lined_text.size()-1].size());
    out_string += "| ";
    for (int j=0; j<last_line_index; j++) {
        
        out_string += word_in_line[lined_text.size()-1][j];
        out_string += " ";
        int blank_num = width - int(lined_text[lined_text.size()-1].size());
        if (j == last_line_index-1) {
            string type_blank(blank_num,' ');
            out_string += type_blank;
            out_string += " |\n";
        }
    }
}



int main(int argc, const char * argv[]) {
    string width_str(argv[3]);
    ifstream fn(argv[1]);
    ofstream out_str(argv[2]);
    string function_type(argv[4]);
    string Out_string;
    string out_string;
    vector<string> text;
    vector<vector<string> > word_in_line;
    int width;
    vector<string> lined_text;
    width = atoi(width_str.c_str());//to find out the width of the rectangle
    const string top_bottom_line(width+4,'-');
    string word;
    if (argc != 5) {
        cerr<<"wrong number of statement.\n";
        exit(1);
    }
    if (!fn.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    
    while (fn>>word) {
        text.push_back(word);
    }
    int line_num = count_line(width, text, lined_text, word_in_line);
    Out_string = top_bottom_line;
    Out_string += "\n";
    if (function_type == "flush_left") {
        flush_left(lined_text, line_num, width,out_string);
        Out_string += out_string;
        Out_string +=top_bottom_line;
        Out_string +="\n";
        out_str << Out_string;
    }
    else if (function_type == "flush_right"){
        flush_right(lined_text, line_num, width,out_string);
        Out_string += out_string;
        Out_string +=top_bottom_line;
        Out_string +="\n";
        out_str << Out_string;
    }
    else{
        full_justify(lined_text, word_in_line, line_num, width,out_string);
        Out_string += out_string;
        Out_string +=top_bottom_line;
        Out_string +="\n";
        out_str << Out_string;
    }
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    
    
    return 0;
}
