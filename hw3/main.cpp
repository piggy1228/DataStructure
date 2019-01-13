// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <string>
#include "undoarray.h"



// helper testing function
void SimpleTests();
void StudentTests();
void BatchTest(const char* filename, int num);


int main(int argc, char* argv[]) {
    if (argc == 1) {
        SimpleTests();
        std::cout << "Simple tests completed." << std::endl;
        StudentTests();
        std::cout << "Student tests completed." << std::endl;
    } else {
        assert (argc == 3);
        BatchTest(argv[1],atoi(argv[2]));
        std::cout << "Batch test completed." << std::endl;
    }
}


void SimpleTests() {
    // create an undo array of chars of length 7
    
    // Note: The ua UndoArray object is stored on the stack.
    //   The dynamically-allocated substructures of ua are stored
    //   on the heap.
    
    UndoArray<char> ua(7);
    
    // confirm that an empty structure of the specified length was created
    assert (ua.size() == 7);
    for (unsigned int i = 0; i < ua.size(); i++) {
        assert (ua.initialized(i) == false);
    }
    
    std::cout << "constructor test completed" << std::endl;
    
    // some set & get operations
    ua.set(2,'a');
    assert (ua.initialized(2) == true);
    assert (ua.get(2) == 'a');
    ua.set(2,'b');
    assert (ua.initialized(2) == true);
    assert (ua.get(2) == 'b');
    ua.set(4,'c');
    assert (ua.initialized(4) == true);
    assert (ua.get(4) == 'c');
    ua.set(6,'d');
    ua.set(1,'e');
    ua.set(6,'f');
    ua.set(6,'g');
    

    std::cout << "set & get tests completed" << std::endl;
    
    // =======================================================
    //
    //     UNCOMMENT THE SECTIONS BELOW AS YOU
    //        COMPLETE THE IMPLEMENTATION
    //
    // =======================================================
    
    
    // print the structure (to help in debugging)
    

    
    std::cout << "print test completed" << std::endl;
    
    
    // some undo operations
    ua.undo(2);

    assert (ua.get(2) == 'a');
    assert (ua.get(4) == 'c');
    ua.undo(4);
    assert (ua.initialized(4) == false);
    assert (ua.initialized(2) == true);
    assert (ua.get(2) == 'a');
    ua.print();
    std::cout << "undo tests completed" << std::endl;
    
    // example of the copy constructor
    UndoArray<char> another(ua);
    
    // the structures initially look the same
    assert (another.size() == ua.size());
    for (int i = 0; i < another.size(); i++) {
        assert (another.initialized(i) == ua.initialized(i));
        if (another.initialized(i))
            assert (another.get(i) == ua.get(i));
    }
    // but future edits show they are different!
    another.undo(6);
    assert (another.get(6) == 'f');
    assert (ua.get(6) == 'g');
    ua.set(4,'h');
    assert (another.initialized(4) != ua.initialized(4));
    std::cout << "copy constructor test completed" << std::endl;



 // example of the assignment operator
 ua = another;
 // again the structures look the same
 for (int i = 0; i < another.size(); i++) {
 assert (another.initialized(i) == ua.initialized(i));
 if (another.initialized(i))
 assert (another.get(i) == ua.get(i));
 }
 std::cout << "assignment operator test completed" << std::endl;

// Note: The UndoArray destructor is implicitly called for the
//   stack-allocated variables 'ua' and 'another' when we leave the
//   function and it goes out of scope.

}


 void StudentTests() {
 
 // =======================================================
 //
 // YOU SHOULD ADD YOUR OWN TEST CASES HERE
 //
 // be sure to rigorously test:
 //   * undo arrays that store types other than char
 //   * copy constructor
 //   * assignment operator
 //   * destructor
 //   * invalid requests (comment out for final submission)
 //
 // =======================================================
     //create a size of 5 array, and store int inside
     UndoArray<int> ua(5);
     assert(ua.size() == 5);
     
     // confirm that an empty structure of the specified length was created
     for (unsigned int i = 0; i < ua.size(); i++) {
         assert (ua.initialized(i) == false);
     }
     //some get and set operations
     ua.set(2, 28);
     assert (ua.initialized(2) == true);
     assert (ua.get(2) == 28);
     ua.set(2,3);
     assert (ua.initialized(2) == true);
     assert (ua.get(2) == 3);
     ua.set(4,10);
     assert (ua.initialized(4) == true);
     assert (ua.get(4) == 10);
     ua.set(3,7);
     ua.set(3,2);
     ua.set(1,7);
     ua.set(0,9);
     ua.set(3,5);
     std::cout << "set & get tests completed" << std::endl;
     
     
     // some undo operations
     ua.undo(3);

     assert (ua.initialized(3) == true);
     assert(ua.get(3)==2);
     ua.undo(2);
     assert (ua.initialized(2) == true);
     assert (ua.get(2) == 28);
     std::cout << "int undo and set tests completed" << std::endl;
     
     
     
     // example of the copy constructor
     UndoArray<int> another(ua);
     
     // the structures initially look the same
     assert (another.size() == ua.size());
     for (int i = 0; i < another.size(); i++) {
         assert (another.initialized(i) == ua.initialized(i));
         if (another.initialized(i))
             assert (another.get(i) == ua.get(i));
     }
     // but future edits show they are different!
     another.undo(3);
     assert (another.get(3) == 7);
     assert (ua.get(3) == 2);
     ua.set(4,8);
     std::cout << "copy constructor test completed" << std::endl;
     std::cout << "int test completed" << std::endl;
     
     //=======================================================
     //short strings
     UndoArray<std::string> ua1(6);
     ua1.set(0, "hi");
     assert(ua1.get(0)=="hi");
     ua1.set(0,"cs");
     ua1.set(4,"hw3");
     ua1.set(3, "pointer");
     ua1.undo(0);
     assert(ua1.get(0)=="hi");
     UndoArray<std::string> ua2(6);
     // example of the assignment operator
     ua2 = ua1;
     
     // again the structures look the same
     for (int i = 0; i < ua1.size(); i++) {
         assert (ua1.initialized(i) == ua2.initialized(i));
         if (ua2.initialized(i))
             assert (ua2.get(i) == ua1.get(i));
     }
     ua2.set(3, "=");
     ua1.print();
    
     std::cout << "assignment operator test completed" << std::endl;
     std::cout << "short string test completed" << std::endl;
     
     ua2.push_back("test");
     assert(ua2.get(6) == "test");
     std::cout<<"push back test completed"<<std::endl;
    //ua2.pop_back();
     assert(!ua2.initialized(5));
     
     ua2.set(5, "what");
     ua2.undo(6);
     ua2.set(6, "push");
     ua1.pop_back();
     std::cout<<"pop back test completed"<<std::endl;

     
     //=======================================================
     //invalid requests
     /*
     ua2.undo(1);//undo an uninitialized num
     ua2.set(10, "bug");//out of the array size
     ua2.get(1);//get an uninitialized num
      */

 }

 




// Batch test will repeatedly load & process a file with UndoArray
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.

void BatchTest(const char* filename, int num) {
    assert (num > 0);
    
    while (num > 0) {
        num--;
        
        // open the file stream for reading
        std::ifstream istr(filename);
        assert (istr);
        
        // read the size of the array to allocate
        char c;
        int i;
        istr >> c >> i;
        assert (c == 'a');
        // here we dynamically (explicitly) allocate memory for the UndoArray object
        UndoArray<char> *ua = new UndoArray<char>(i);
        
        // read in and perform various operations on the array
        while (istr >> c) {
            if (c == 's') {
                istr >> i >> c;
                ua->set(i,c);
            } else if (c == 'g') {
                istr >> i;
                if (ua->initialized(i)) {
                    char val = ua->get(i);	
                    assert (val >= 'a' && val <= 'z');
                }
            } else {
                assert (c == 'u');
                istr >> i;
                if (ua->initialized(i)) {
                    ua->undo(i);	
                }
            }
        }

        // Because the UndoArray memory was allocated dynamically (using new)
        // we need to explicitly deallocate the memory (using delete)
        delete ua;
    }

}
