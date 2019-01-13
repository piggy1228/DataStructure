//
//  main.cpp
//  hw1 maincode
//
//  Created by KEXIN ZHU on 9/1/16.
//  Copyright 2016 KEXIN ZHU. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdio>


using namespace std;

//to rearrange the word structure, make it the exact word number in each line.
//Put each line in a vector,and put each word in each line.
//line_text vector just put each line's string in each position for the purpose
//in the flush right and left.
//word_in_line vector means first push back each word as a position in
//vector to consist of a vector contains word in each line, then push back the
//line vector into the bigger vector
int count_line(int width, vector<string> &text, vector<string> &lined_text,
               vector<vector<string> > &word_in_line){
    int line_num = 1;
    vector<string> word_each_line;
    unsigned long accumulated_num = 0;
    //accumulated_num is to count the length of the character to make sure it
    //does not excced the width
    string line_string="";
    //initialize the line_string
    int i;
    for (i=0; i<text.size(); i++) {
    //ignore the corner case.just structure the word arrangement in the vector.
        if (text[i].size()<=width) {
            accumulated_num += text[i].size()+1;
            //to put each line in the vector which contains a vector
            //,and push back into the bigger vector when it exceeds its width.
            if (accumulated_num-1< width) {
                line_string += text[i]+" ";
                //line_sring is for the lined_text vector
                word_each_line.push_back(text[i]);
                //word_each_line vector is for the word_in_line
            }
            else{
                // when the character numbers exceed the number of width,clear
                //the previous vector(vector_each_line),and start a new line.
                accumulated_num = text[i].size();
                line_num +=1;
                lined_text.push_back(line_string);
                //finish this line,and add it to the vector lined_text
                word_in_line.push_back(word_each_line);
                //finish this line's vector, and add it to the vector
                //word_in_line
                line_string = text[i]+" ";
                //start the new line to add the line_string
                word_each_line.clear();
                //clear each line.and start a new line.
                word_each_line.push_back(text[i]);
                //to put the first word in the next line.
            }
        }
        // for the special corner case:long word
        if(text[i].size() > width){
            // if the word itself exceeds the line width.first out the previous
            //vector into the bigger vector.
            int round = int(text[i].size())/(width-1);
            //round means how many lines the word occupy from begin to end
            // if before the long word, there is some word in the line, then
            //push back the previous string into the vector for both lined_text
            //vector and the word_in_line vector.
            if (accumulated_num>0) {
        //clear the previous line and start a new line in both two vectors.
                lined_text.push_back(line_string);
                word_in_line.push_back(word_each_line);
                word_each_line.clear();
            }
            line_string ="";
            //start a new line_string for the long word no matter there is
            //a word before or not since the long word must in another line
            
            // if the word occuopy from begin to end and not finished, it need
            //to add a hypen
            //ignore the corner case that the last letter just arrive the length
            //width-1 or width
            if (int(text[i].size())%(width-1)!=0 &&
                int(text[i].size())%(width-1)!=1) {
                for (int j=0; j<round; j++) {
                    for (int k=0; k<(width-1); k++) {
                        int string_num;
                        string_num = k+j*(width-1);
                        //the index of the string character
                        line_string += text[i][string_num];
                    }
                    line_string += "-";
                    //add a hypen at the end of the line and start a new line,
                    //continue the long word left
                    word_each_line.push_back(line_string);
                    line_string +=" ";
                    lined_text.push_back(line_string);
                    word_in_line.push_back(word_each_line);
                    word_each_line.clear();
                    line_string = "";
                    //clear the line_string before start a new line
                }
                //continue the long word with the left character
                for (int m=0; m<(int(text[i].size())-round*(width-1)); m++) {
                    line_string += text[i][m+round*(width-1)];
                }
                //this is the final part of the word, just check if the next
                //word can fit in the width,and back to the short word loop.
                word_each_line.push_back(line_string);
                line_string +=" ";
                accumulated_num = int(text[i].size())-round*(width-1)+1;



            }
        
            //the corner case the last letter just arrive the length
            //width-1 or width

            else{
                for (int j=0; j<round-1; j++) {
                    for (int k=0; k<(width-1); k++) {
                        int string_num;
                        string_num = k+j*(width-1);
                        //the index of the string character
                        line_string += text[i][string_num];
                    }
                    line_string += "-";
                    //add a hypen at the end of the line and start a new line,
                    //continue the long word left
                    word_each_line.push_back(line_string);
                    line_string +=" ";
                    lined_text.push_back(line_string);
                    word_in_line.push_back(word_each_line);
                    word_each_line.clear();
                    line_string = "";
                    //clear the line_string before start a new line
                    
                }
                //the corner case the last letter arrive the length width-1
                if (int(text[i].size())%(width-1)==0) {
                    for (int m=0; m<(int(text[i].size())-(round-1)*(width-1));
                         m++) {
                        line_string += text[i][m+(round-1)*(width-1)];
                    }
                    //this is the final part of the word, just check if the next
                    //word can fit in the width,and back to the short word loop.
                    word_each_line.push_back(line_string);
                    line_string +=" ";
                    accumulated_num = width-2;


                }
                else{
                    for (int m=(round-1)*(width-1); m<int(text[i].size()); m++)
                    {
                        line_string += text[i][m];
                    }
                    word_each_line.push_back(line_string);
                    line_string +=" ";
                    accumulated_num = width - 1 ;


                }
            }
    
        }
        
    }
    // push back the last line into the vector because it is out of the loop.
    lined_text.push_back(line_string);
    word_in_line.push_back(word_each_line);
    return line_num;
}


//the flush left function put all the word in the left and blank in the right.
void flush_left(vector<string> &lined_text,int line_num,int width,
                string &out_string){
    out_string = "";
    for (int i=0; i<lined_text.size(); i++) {
        out_string+=  "|" ;
        //output the frame at the start of each line
        out_string+=" ";
        out_string+=lined_text[i];
        //output each line per time
        unsigned long blank_num;
        //count the blank number to add at the end of the string
        blank_num=width+1-lined_text[i].size();
        for (int j = 0; j<blank_num; j++) {
            out_string += ' ';
        }
        out_string+="|\n";
        //finish each line
    }
}


// the word all in the right,and put the blank in the left
void flush_right(vector<string> &lined_text, int line_num,
                 int width,string &out_string){
    out_string ="";
    for (int i=0; i<lined_text.size(); i++) {
        //output the frame at the start of each line
        out_string+= "| ";
        unsigned long blank_num;
        //count the blank number it should add before words
        blank_num=width+1-lined_text[i].size();
        for (int j = 0; j<blank_num; j++) {
            out_string += ' ';
        }
        //first print the blank then print the word
        out_string += lined_text[i];
        out_string += "|\n";
        //finish each line
    }
}


//count the number of word in each line string
int count_word(string count_string){
    int num_of_word = 0;
    char nextChar;
    // checks each character in the string
    for (int i=0; i<int(count_string.length()); i++)
    {
        nextChar = count_string.at(i); // gets a character
        if (isspace(count_string[i]))
            num_of_word++;
        //if find out a space, then there is a word
    }
    return num_of_word;
    
}

//full justify the line, put the blank average between the string.
void full_justify(vector<string> &lined_text,
vector<vector<string> > &word_in_line,
int line_num, int width,string &out_string)
{
    unsigned long blank_num;
    int total_word;
    vector<unsigned long> blank_num_in_line;
    vector<int> word_num_in_line;
    vector<int> vector_blank_for_all;
    vector<int> vector_blank_left;
    int accumulated_blank_left=0;
    out_string="";
    //count the total blank and the total word in the line,and push back them
    // into two different vector
    for (int i=0; i<lined_text.size(); i++) {
        string word;
        blank_num = width+1-lined_text[i].size();
        //count the total blank number in each line.
        blank_num_in_line.push_back(blank_num);
        //push back it into a the blank_num_in_line vector for future use
        total_word = count_word(lined_text[i]);
        //use the count word function to count the number of word in each line
        word_num_in_line.push_back(total_word);
    }
    //to calculate the blank
    for (int j=0; j<lined_text.size(); j++) {
        int blank_for_all;
        int blank_left;
        //ignore the specific case that one line only have a word.
        //calculate the number of blank after each word
        //blank left means after the same number of blank each line was added
        //then added one word by one word from the left word
        if (word_num_in_line[j]>1) {
            blank_for_all = int (blank_num_in_line[j])/(word_num_in_line[j]-1);
            vector_blank_for_all.push_back(blank_for_all);
            blank_left =int (blank_num_in_line[j])% (word_num_in_line[j]-1);
            vector_blank_left.push_back(blank_left);
        }
        else{
            //if there is one word in the line, just calculate the blank number
            //and put blank number into the two vectors
            blank_for_all = 0;
        //blank_for_all is 0, because there is no need to calculate seperately
            vector_blank_for_all.push_back(blank_for_all);
            blank_left = int(blank_num_in_line[j]);
            vector_blank_left.push_back(blank_left);

            
        }
    }

    //this for loop start to consist of the output of the string
    for (int i=0; i<word_in_line.size()-1; i++) {
        out_string += "| ";
        //count the word number in each line
        int count_word_in_line = int(word_in_line[i].size());
        for (int j=0; j<count_word_in_line; j++) {
            // if the word is not the last word in the line,then output it
            // output the exact number of blank
            if (j != count_word_in_line-1) {
                out_string += word_in_line[i][j];
                //output word by word
                out_string +=" ";
                //add the blank to seperate two words
                string type_blank(vector_blank_for_all[i],' ');
                //the number of blank should be added after each word
                //so when output the word.just output the blank for all
                out_string += type_blank;
                if (accumulated_blank_left<vector_blank_left[i]) {
                    out_string += " ";
                    accumulated_blank_left++;
                }
            }
            //if it is the last word in the line and it is not the only word in
            //line,just add the word and finish the line
            if(j == count_word_in_line-1 && count_word_in_line !=1){
                out_string+= word_in_line[i][count_word_in_line-1];
                out_string+=" |\n";
                accumulated_blank_left=0;
                //clear the accumulated blank for the next line to accumulate
            }
        }
        //if it is the only word in line,then count the blank it should be added
        if (count_word_in_line == 1) {
            out_string += word_in_line[i][0];
            out_string +=" ";
            // when the word length does not equal to the width, print blank
            if (blank_num_in_line[i] !=0) {
                string type_last_blank(int(blank_num_in_line[i]),' ');
                out_string += type_last_blank;
            }
             out_string +="|\n";
        }
    }
    // the last line should all be flushed left, so it is out of the loop
    int last_line_index = int(word_in_line[lined_text.size()-1].size());
    out_string += "| ";
    //output all the word then calculate all the blank it should be added.
    for (int j=0; j<last_line_index; j++) {
        
        out_string += word_in_line[lined_text.size()-1][j];
        out_string += " ";
        int blank_num = width - int(lined_text[lined_text.size()-1].size());
        // if the last line only have one word, then just add the blank number
        //until the width length.
        if (j == last_line_index-1) {
            string type_blank(blank_num,' ');
            out_string += type_blank;
            out_string += " |\n";
        }
    }
}



int main(int argc, const char * argv[]) {
    
    ifstream fn(argv[1]);
    ofstream out_str(argv[2]);
    string width_str(argv[3]);
    string function_type(argv[4]);
    string Out_string;
    //Out_string means all the string should be put into the output file
    string out_string;
    //out_string is in the function, which is part of Our_stringlong_word.txt
    vector<string> text;
    vector<vector<string> > word_in_line;
    int width;
    vector<string> lined_text;
    
    //check of the third argument is digit.or it is invalid input.
    for (int i=0; i<width_str.size(); i++) {
        if (!isdigit(width_str[i])) {
            cerr <<"the third argument is invalid input"<<endl;
            exit(1);
            
        }
    }
    
    
    width = atoi(width_str.c_str());//to find out the width of the rectangle
    const string top_bottom_line(width+4,'-');
    //get the top and the bottom line if the rectangle.
    string word;
    //check the number of argument
    if (argc != 5) {
        cerr<<"wrong number of statement.\n";
        exit(1);
    }
    //check the output file
    
    if (!fn.good()) {
        cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }
    
    //check if the forth argument is valid
    if (function_type != "flush_left" && function_type !="flush_right"&&
        function_type != "full_justify") {
        cerr<<"the forth argumemt is invalid"<<endl;
        exit(1);
    }
    

    
    //output each word to the text vector
    //each  word in text vector occupied a position
    while (fn>>word) {
        text.push_back(word);
    }
    int line_num = count_line(width, text, lined_text, word_in_line);
    
    Out_string = top_bottom_line;
    //the first string to out put is the top line
    Out_string += "\n";
    // to find out which type the instruction and run.
    //if its instruction is flush_left, then run the function
    if (function_type == "flush_left") {
        flush_left(lined_text, line_num, width,out_string);
        Out_string += out_string;
        //add the content in the output file
        Out_string +=top_bottom_line;
        //add the  bottom line in the output file
        Out_string +="\n";
        out_str << Out_string;
        //output all the content to the txt file
        
    }
    
    //if its instruction is flush_right, then run the flush right function
    else if (function_type == "flush_right"){
        flush_right(lined_text, line_num, width,out_string);
        Out_string += out_string;
        //add the content in the output file
        Out_string +=top_bottom_line;
        //add the  bottom line in the output file
        Out_string +="\n";
        out_str << Out_string;
        //output all the content to the txt file
    }
    
    //if its instruction is full_justify, then run the full justify function
    else{
        full_justify(lined_text, word_in_line, line_num, width,out_string);
        Out_string += out_string;
        //add the content in the output file
        Out_string +=top_bottom_line;
        //add the  bottom line in the output file
        Out_string +="\n";
        out_str << Out_string;
        //output all the content to the txt file
    }
    if (!out_str.good()) {
        cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }
    //error message if the output file is wring.
    
    
    return 0;
}
