#include <iostream>
#include <list>
#include <string>
using namespace std;
// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
    int value;
    Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
    // print the name of this list
    std::cout << name;
    // use a temporary pointer to walk down the list
    Node *tmp = my_linked_list;
    while (tmp) {
        cout<<" "<<tmp->value;
        tmp = tmp->ptr;
    }
    cout<<endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {
    // create a linked list chain of Nodes, populating the structure
    // with the data in the STL list
    Node* head = new Node;
    head ->value = *lst.begin();
    Node* p = head;
    for ( list<int>::const_iterator itr = ++lst.begin(); itr!= lst.end()--; ++itr) {
        p -> ptr = new Node;
        p = p -> ptr;
        p ->value = *itr;
    
    }
    p -> ptr = NULL;
    return head;
    // NOTE: this code should work for input STL lists of arbitrary
    // length
    
}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {
    
    Node* one = input;
    Node* two = NULL;
    while (one->ptr) {
        Node* three = one->ptr;
        one->ptr = two;
        two = one;
        one = three;

        
        
    }
    one->ptr = two;
    return one;
    // rearrange the pointers in the linked list chain of Nodes,
    // so that the structure is reversed.
    /*
    Node* head = input;
    Node* tmp = NULL;
    while (head->ptr!=NULL ) {
        Node* p = head->ptr;
        head = p;
        input->ptr = tmp;
        tmp = input;
        input = head;
    }
    input->ptr = tmp;
    return input;
    */
    
    // NOTE: Do not edit the values of the Nodes.  Do not create any new
    // Node objects (don't call 'new').  Instead, change the ptrs of the
    // existing Nodes to shuffle the order.
   
}


// ===========================================================================

int main() {
    
    // manually create a linked list of notes with 4 elements
    Node* a = new Node;
    a->value = 6;
    a->ptr = new Node;
    a->ptr->value = 7;
    a->ptr->ptr = new Node;
    a->ptr->ptr->value = 8;
    a->ptr->ptr->ptr = new Node;
    a->ptr->ptr->ptr->value = 9;
    a->ptr->ptr->ptr->ptr = NULL;
    // print out this list
    print_linked_list("a",a);
    
    // create an STL list with 4 elements
    std::list<int> b;
    b.push_back(10);
    b.push_back(11);
    b.push_back(12);
    b.push_back(13);
    
    // use the STL list as input to a creator function that creates
    // linked lists with the same data
    Node* c = make_linked_list_from_STL_list(b);
    // print that data
    print_linked_list("c",c);
    
    //
    // WRITE A FEW MORE TEST CASES OF make_linked_list_from_STL_list
    //
    
    // reverse a linked list of nodes
    Node* d = reverse_nodes_in_linked_list(c);
    // print this data
    print_linked_list("d",d);
    
    //
    // WRITE A FEW MORE TEST CASES OF reverse_nodes_in_linked_list
    //
    list<int> e;
    for (int i=0; i<10; i++) {
        e.push_back(i*i);
    }
    Node*g = make_linked_list_from_STL_list(e);
    Node*f = reverse_nodes_in_linked_list(g);
    //print_linked_list("g", g);
    print_linked_list("f", f);
    
    // NOTE: We are not deleting any of the Nodes we created...  so this
    //       program has some memory leaks!  More on this in future
    //       lectures & labs :)
    
}

// ===========================================================================
