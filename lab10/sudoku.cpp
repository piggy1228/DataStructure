#include <vector>
#include <set>
#include <iostream>
#include <math.h>
#include <cassert>
#include "sudoku.h"

using std::set;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using namespace std;
// ======================================================
// A program to solve very simple Sudoku puzzles
// ======================================================

int main() {

  int size;
  while (cin >> size) {
    // Read in the board size and create an empty board
    Sudoku board(size);

    // Read in and set the known positions in the board
    char c;
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {      
        cin >> c;
        if (c != '.') {
          board.Set(i,j,c-'0');
        }
      }
    }
    
    // The iterative solving routine 
    while (1) {
      
      // Is the puzzle is already solved?
      if (board.IsSolved()) {
        cout << "\nPuzzle is solved:" << endl;
        board.Print();
        break;
      }
      
      // Is the puzzle impossible?
      if (board.Impossible()) {
        cout << "\nCannot solve this puzzle:" << endl;
        board.Print();
        break;
      }
      
      // Try to reduce the number of choices in one or more board cells
      // by propagating known values within each row, column, and quadrant
      int changed = 0;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (board.KnownValue(i,j))
            changed += board.Propagate(i,j);
        }
      }
      
      // If nothing changed this iteration, give up
      if (changed == 0) {
        cout << "\nPuzzle is too difficult for this solver!" << endl;
        board.Print();
        break;      
      }
    }
  }
}

// ======================================================

// Construct an empty board
Sudoku::Sudoku(int s) {
  // set the size
  size = s;
  quadrant_size = (int)sqrt(size);
  assert (quadrant_size*quadrant_size == s);
    set<int> num;
    for (int i=0; i<size; i++) {
        num.insert(i+1);
    }
    vector<set<int> > board_row;
    for (int i=0; i<size; i++) {
        board_row.push_back(num);
    }
    
    for (int i=0; i<size; i++) {
        board.push_back(board_row);
    }
  // You need to finish this function!


}

// To construct the puzzle, set the value of a particular cell
void Sudoku::Set(int i, int j, int value) {
    
  // make sure the value is one of the legal values
  assert (board[i][j].find(value) != board[i][j].end());
  board[i][j].clear();
  board[i][j].insert(value);
}

// Does the cell have exactly one legal value?
bool Sudoku::KnownValue(int i, int j) const {
  return (board[i][j].size() == 1);
}

// If there is exactly one number in each cell of the grid, the puzzle is solved!
bool Sudoku::IsSolved() const {
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            if (!KnownValue(i, j)) {
                return false;
            }
        }
    }
     return true;

}

// If there are no legal choices in one or more cells of the grid, the puzzle is impossible
bool Sudoku::Impossible() const {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j].size() == 0)
        return true;
    }
  }
  return false;
}

// print out the solution
void Sudoku::Print() const {
  int solved = IsSolved();
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int count = size+1;
      for (set<int>::iterator itr = board[i][j].begin(); itr != board[i][j].end(); itr++) {
        count--;
        cout << *itr;
      }
      if (!solved) {
        // if it's not solved, print out spaces to separate the values
        for (int k = 0; k < count; k++) {
          cout << " ";
        }
      }
    }
    cout << endl;
  }
}


// Propagate information from this cell along columns & rows &
// within quadrant. Return the number of cells that changed.
int Sudoku::Propagate(int i, int j) {
    set<int>::iterator itr = board[i][j].begin();
    int num = *itr;
    int count =0;
    set<int>::iterator c_itr;
    //same column
    for (int m=0; m<size; m++) {
        if (m == j) {
            continue;
        }
        c_itr = board[i][m].find(num);
        if (c_itr != board[i][m].end()) {
            board[i][m].erase(c_itr);
            count++;
        }
    }
    //same row
    for (int m = 0; m<size; m++) {
        if (m == i) {
            continue;
        }
        c_itr = board[m][j].find(num);
        if (c_itr !=board[m][j].end()) {
            board[m][j].erase(c_itr);
            count++;
        }
    }
    //same quadrant
    for (unsigned int m = i / quadrant_size * quadrant_size; m < i / quadrant_size * quadrant_size + quadrant_size; m++) {
        if (m == i) continue;
        for (unsigned int n = j / quadrant_size * quadrant_size; n < j / quadrant_size * quadrant_size + quadrant_size; n++) {
            if (n == j) continue;
            itr = board[m][n].find(num);
            if (itr != board[m][n].end()) {
                board[m][n].erase(itr);
                count++;
            }
        }
    }
  return count;

}
