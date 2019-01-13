#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "board.h"
#include <time.h>
using namespace std;

//creat a class called cell to store the point
class Cell{
public:
    Cell(int w0,int h0) : w(w0), h(h0) {}
    const int get_w() const {return w;}
    const int get_h() const{return h;}
private:
    int w;
    int h;
};



/**
 sort the Cell by value,to make sure the values later use in the board recursion
 will start from the small number so it will faster.
 create a new tmp vector to store the sorted live cells, each time choose one
 Cell in live cells, then to find a position in tmp to store
 */
void sort_the_live_cells(const vector<Cell> &live_cells,const Board &board,vector<Cell>& tmp){
    tmp.push_back(live_cells[0]);
    //bool is to find out if it is inserted into tmp, if not,it need to push at back
    bool inserted = false;
    for (int i = 1; i<live_cells.size(); i++) {
        vector<Cell>::iterator itr;
        inserted = false;
        //choose all the cells in the for loop
        for (itr = tmp.begin(); itr != tmp.end(); itr++) {
            //if find out the right place push back the vector
            if (board.get(live_cells[i].get_h(),live_cells[i].get_w()) <
                board.get((*itr).get_h(),((*itr).get_w()))) {
                itr =  tmp.insert(itr, live_cells[i]);
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            tmp.push_back(live_cells[i]);
        }
        
    }
}



/**
 print solved board
 use the solution to set all the path to 'X'
 */
void print_solved_board(Board  board, vector<vector<Cell> > one_solution){
    for (int i=0; i<one_solution.size(); i++) {
        for (int j=0; j<one_solution[i].size(); j++) {
            board.solved(one_solution[i][j].get_w(), one_solution[i][j].get_h());
        }
    }
    cout<<board;
}




/**
 convert letter to number
 */
int conver_letter_num(char w){
    if (w == ' ') {
        return ' ';
    }
    if (w=='A'){
        return 10;
    }
    else if (w == 'B') return 11;
    else if (w == 'C') return 12;
    else if (w=='D') return 13;
    else if (w=='E') return 14;
    else if (w=='F') return 15;
    else if (w == 'G') return 16;
    else if (w == 'H') return 17;
    else if (w == 'I') return  18;
    else if (w == 'J') return 19;
    else if (w == 'K') return 20;
    else if (w=='L') return 21;
    else if (w=='M') return 22;
    else if (w=='N') return 23;
    else if (w == 'O') return 24;
    else if (w == 'P') return 25;
    else if (w == 'Q') return  26;
    else if (w == 'R') return 27;
    else if (w == 'S') return 28;
    else if (w=='T') return 29;
    else if (w=='U') return 30;
    else if (w=='V') return 31;
    else if (w == 'W') return 32;
    else if (w == 'X') return 33;
    else if (w == 'Y') return  34;
    else if (w=='Z') return 35;
    else return int(w)-'0';
    
}



/**
 print all_point_all_paths for the final answer
 the vector store the point, the larger one store the way it pass, the largest
 is the whole path
 */
void print_all_points_all_paths(vector<vector<vector<Cell> > > &all_points_all_paths,Board board,int argc){
    if (argc == 3) {
        for (int i=0; i<all_points_all_paths.size(); i++) {
            cout<<"\nSolution:\n";
            for (int j=0; j<all_points_all_paths[i].size(); j++) {
                //each pair
                for (int k=0; k<all_points_all_paths[i][j].size(); k++) {
                    //each point
                    cout<<"("<<all_points_all_paths[i][j][k].get_w()<<","<<
                    all_points_all_paths[i][j][k].get_h()<<")  ";
                }
                cout<<endl;
            }
            //print solved board
            print_solved_board(board, all_points_all_paths[i]);
        }
        if (all_points_all_paths.size()>0) {
            cout<<"\nFound "<<all_points_all_paths.size()<<" solution(s)\n";
        }

    }
    else{
        cout<<"\nSolution:\n";
        for (int j=0; j<all_points_all_paths[0].size(); j++) {
            for (int k=0; k<all_points_all_paths[0][j].size(); k++) {
                cout<<"("<<all_points_all_paths[0][j][k].get_w()<<","<<
                all_points_all_paths[0][j][k].get_h()<<")  ";
            }
            cout<<endl;
        }
        print_solved_board(board, all_points_all_paths[0]);
        
    }
    
}




/**
 to find out if the cell is dead, the path has already been passed
 para@ board_w,board_h: the coordinate of the point is looking for if it is already
 passed in the way the starting point find the pair
 */
bool is_dead(const vector<Cell> &died_cells,int board_w, int board_h){
    for (int i=0; i<died_cells.size(); i++) {
        if (died_cells[i].get_w() == board_w && died_cells[i].get_h()==board_h){
            return true;
        }
    }
    return false;
}

/**
 to find out if the point that other pairs pass previous before the point
 find the other point
 */
bool is_dead_for_all_paths( const vector<vector<Cell> > &died_cells,const int &board_w, const int& board_h){
    for (int i=0; i<died_cells.size(); i++) {
        for (int j=0; j<died_cells[i].size(); j++) {
            if (died_cells[i][j].get_w() == board_w && died_cells[i][j].get_h()==board_h){
                return true;
            }
        }
    }
    return false;
}


/**
 remove all the cells get paired from the live cells
 so numbers on the board will be smaller
 para@ live_cells: all the point on the board need to be paired
 */
void remove_from_live_cells(const vector<Cell>& pairs, vector<Cell>& live_cells){
    vector<Cell>::iterator itr = live_cells.begin();
    //if the point has same coordinate, erase it from the live_cells
    while (itr != live_cells.end()) {
        //when the point have value 1
        if (pairs.size() == 1) {
            if ((*itr).get_w() == pairs[0].get_w() && (*itr).get_h() ==
                pairs[0].get_h()) {
                itr = live_cells.erase(itr);
                return;
            }
        }
        // when it has another point
        else {
            if ((*itr).get_w() == pairs[1].get_w() && (*itr).get_h() ==
                pairs[1].get_h()) {
                itr = live_cells.erase(itr);
                itr--;
            }
            else if ((*itr).get_w() == pairs[0].get_w() &&
                     (*itr).get_h() == pairs[0].get_h()) {
                itr = live_cells.erase(itr);
                itr--;
            }
        }
        ++itr;
    }
}



/**
 recurssive function
 this function let one point to find another point based on the way it passed
 para@ died_cell_in_all_solution: all path the single point can find another point
 @ original_died_cell :the path that already passed before it get to the point
 @ died_cell the path : the path it passed during the process the point find the way
 @ w,h the coordinate for the point
 @pair: the point and its pair on the board
 @ count: the point number the path already passed
 @ num: the value of the starting point
 @ start_w,start_h: the coordinate of the starting point
 */

int one_pair(vector<vector<Cell> > &died_cell_in_all_solution,const vector<vector<Cell> >
    & original_died_cell,vector<Cell> &died_cell,const Board &board,const int &w,
    const int &h ,vector<Cell>& pair,int count,const int& num,
    const int &start_w,const int &start_h){
    //if the path is  not valid, return 0

    if (is_dead_for_all_paths(original_died_cell, w, h)||w<0||h<0||
        h>=board.height()||w>=board.width()||(board.get(h, w) != ' '&&
num != count && !(start_w == w && start_h == h) )||is_dead(died_cell, w, h)) {

        return 0;
    }
    died_cell.push_back(Cell(w, h));

    //when it get to the number they have
    if (count == num) {
        //special case, value 1 is itself
        if (count == 1) {
            died_cell_in_all_solution.push_back(died_cell);
            pair.push_back(Cell(start_w,start_h));
            return 1;
        }
        //if the ending point value = starting point value
        if (board.get(h,w) != ' ' && conver_letter_num(board.get(h,w)) == num) {
            pair.push_back(Cell(start_w,start_h));
            pair.push_back(Cell(w,h));
            died_cell_in_all_solution.push_back(died_cell);
            died_cell.pop_back();
            return 1;
        }
        //if not, wrong path
            died_cell.pop_back();

        return 0;
    }

    else{
        //if does not get to the steps they have, go to the next point
        //they will go to the four direction
        count++;//incrememt the steps
        int result = one_pair(died_cell_in_all_solution,original_died_cell,died_cell,
                               board, w+1, h, pair, count, num,start_w,start_h)+
        one_pair(died_cell_in_all_solution,original_died_cell,died_cell, board,
                 w-1, h, pair, count, num,start_w,start_h)+
        one_pair(died_cell_in_all_solution,original_died_cell,died_cell, board,
                 w, h-1, pair, count, num,start_w,start_h)+
        one_pair(died_cell_in_all_solution,original_died_cell,died_cell, board,
                 w, h+1, pair, count, num,start_w,start_h);
        died_cell.pop_back();
        
        return result;

    }
}


/**
 find one way to get rid of a pair number
 driver function
 to initialize the function
 */
int one_pair(vector<vector<Cell> > &died_cell_in_all_solution,const
vector <vector<Cell> > &original_died_cell,vector<Cell>& died_cell,const Board& board,
             const int& w,const int& h,vector<Cell>& pair){
    pair.clear();
    died_cell.clear();
    died_cell_in_all_solution.clear();
    char num = board.get(h,w);
    int n = 0;
    n = conver_letter_num(num);//let the char in the file convert to the int number
    return one_pair(died_cell_in_all_solution,original_died_cell,died_cell,
                    board, w, h, pair, 1, n, w, h);
    
}





/**
 find all the paths in the whole board
 first to find out the live cells in the board to get them pairs,then store the path
 into the vector,then find the second pair, if the way is dead, return to the previous
 one.
 para @one path: all the point it passed before
 para @ argc: the number of argc
 para@ found: if the function found the solution
 */
void find_all_paths(vector<Cell> &live_cells,vector<vector<Cell> > &
    died_cell_in_all_solution,vector<vector <vector<Cell> > > &all_points_all_paths,
    vector<Cell> & died_cell,const Board & board, vector<Cell>& pair,const int& argc
    ,vector<vector<Cell> >& one_path,bool &found){
    //base case,find the solution
    //when there is no points on the board needs to be paired
    if (live_cells.size() == 0) {
        all_points_all_paths.push_back(one_path);
        found = true;
        if (argc == 2) {
            print_all_points_all_paths(all_points_all_paths, board, argc);
            //if find one solution,exit from the whole program
            exit(0);
        }
        return;
    }
    //if not find the solution
    else{
        int path_num = 0;
        //initialize the function, when there is no point in the one path
        if (one_path.size() == 0) {
            //put a empth one_path into the function to find the pair
            vector<vector<Cell> > empty;
            path_num = one_pair(died_cell_in_all_solution, empty, died_cell, board,
                        live_cells[0].get_w(), live_cells[0].get_h(), pair);
        }
        //if is alread initialized,put the passed way in the funtion
        //the starting_point is the first point in the live_cells,since it
        //will be removed when it was passed, so the first point is always new
        else{
            path_num = one_pair(died_cell_in_all_solution, one_path, died_cell,
                    board, live_cells[0].get_w(), live_cells[0].get_h(), pair);
        }
        //if there is no way to go based on the previous path, return, back
        //to the former path to find another path
        if (path_num == 0) {
            return;
        }
        //remove the point in the live_cells when it was already paired
        remove_from_live_cells(pair, live_cells);
        //make sure the vector died_cell_in_all_solution will not change after
        // it call the recurssive function
        vector<vector<Cell> > current_died_cells = died_cell_in_all_solution;
        //put all the way the new pair found into the one_path and try one by one
        //if it does not work, it will return to the previous path
        for (int i = 0; i<died_cell_in_all_solution.size(); i++) {
            vector<Cell> path_end;
            //find the start point
            path_end.push_back(died_cell_in_all_solution[i][0]);
            if (died_cell_in_all_solution[i].size() > 1){
                //find the ending point
                path_end.push_back
        (died_cell_in_all_solution[i][died_cell_in_all_solution[i].size()- 1]);
            }
            //remove the starting point and the ending point
            remove_from_live_cells(path_end, live_cells);
            one_path.push_back(died_cell_in_all_solution[i]);
            find_all_paths(live_cells, current_died_cells, all_points_all_paths,
                           died_cell, board, pair, argc, one_path,found);
            //insert back all the way that was removed before,so it can find another
            //way
            for (int j=0; j<path_end.size(); j++) {
                live_cells.insert(live_cells.begin(), path_end[j]);
            }
            //pop back the path it already in,so it can find another way
            one_path.pop_back();
            vector<Cell> tmp;
            //make sure the points at the original position
            sort_the_live_cells(live_cells, board, tmp);
            live_cells = tmp;

        }
    }
}



int main(int argc, char* argv[]) {
    /*///////////////////Timing part
    clock_t start, end;
    start = clock();
    ///////////////////*/
    
    // parse the arguments
    if (argc < 2) {
        std::cerr << "USAGE:  " << argv[0] << " <puzzlefile>" << std::endl;
        std::cerr << "        " << argv[0] << " <puzzlefile> find_all_solutions" << std::endl;
        exit(0);
    }
    bool all_solutions = false;
    if (argc > 2) {
        assert (argc == 3);
        assert (std::string(argv[2]) == std::string("find_all_solutions"));
        all_solutions = true;
    }
    
    // open the file
    std::ifstream istr(argv[1]);
    if (!istr.good()) {
        std::cerr << "ERROR!  cannot open " << argv[1] << std::endl;
        exit(0);
    }
    
    // read the file
    std::string token;
    istr >> token;
    assert (token == "width");
    int width,height;
    istr >> width;
    istr >> token;
    assert (token == "height");
    istr >> height;
    assert (width > 0);
    assert (height > 0);
    int x,y,v;
    
    // create the board
    vector<Cell> live_cells;
    //create a vector to store all the numbers need to be paired
    Board board(width,height);
    while (istr >> x >> y >> v) {
        assert (x >= 0 && x < width);
        assert (y >= 0 && y < height);
        board.set(x,y,v);
        live_cells.push_back(Cell(x,y));
    }
    
    // print the original puzzle board
    std::cout << board;
    
    // Now...  solve it!
    //initialize the vectors
    vector<vector<Cell> > all_dead_cell;
    vector<vector<Cell> > original_died_cells;
    vector<Cell> died_cell;
    vector<Cell> pairs;
    vector<vector<Cell> > died_cell_in_all_solution;
    vector<vector<Cell> > all_pair;
    vector< vector<vector<Cell> > > all_points_all_paths;
    vector<Cell> tmp;
    sort_the_live_cells(live_cells, board,tmp);
    bool found = false;
    vector<vector<Cell> > one_path;
    //find the answer
    
    find_all_paths(tmp, died_cell_in_all_solution, all_points_all_paths, died_cell,
        board, pairs, argc, one_path,found);
    if (argc == 3) {
        print_all_points_all_paths(all_points_all_paths, board, argc);
    }
    
    //if there is no answer
    if (!found ) {
        cout<<"No solutions\n";
    }

    /*////////////////////////////////////////////////////////////////////Timing
    end = clock();
    static double time_consumed = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time: " << time_consumed << " s" <<endl;
    ////////////////////////////////////////////////////////////////////*/

}


