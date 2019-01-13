//
//  bidirectional_map.h
//  hw8
//
//  Created by KEXIN ZHU on 11/5/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#ifndef bidirectional_map_h
#define bidirectional_map_h
#include <utility>
#include <string>
#include <iostream>

using namespace std;
//=============================================================================
//NODE CLASS
//=============================================================================
template <class A, class B>
class Node{
public:
    //CONSTRUCTOR
    //default constructor
    Node(): left(NULL), right(NULL),link(NULL),parent(NULL){}
    //constrcutor with value
    Node(const A& init) : data(init),left(NULL),right(NULL),link(NULL),parent(NULL){}
    //ALL THE VARIABLES WILL BE USED
    A data;
    Node<A,B>* left;
    Node<A,B>* right;
    Node<B,A>* link;
    Node<A,B>* parent;
};

//=============================================================================
//ITERATOR CLASS
//=============================================================================
template <class C,class D>
class tree_iterator{
public:
    //CONSTRUCTOR
    //default c onstructor
    tree_iterator(): ptr_(NULL){}
    
    tree_iterator(Node<C,D>* p): ptr_(p) {}
    tree_iterator(const tree_iterator& old): ptr_(old.ptr_) {}
    ~tree_iterator(){}
    //operator assignment
    tree_iterator& operator=(const tree_iterator& old){ptr_=old.ptr_;return* this;}
    
    //OPERATOR
    //operator gives constant access to the value at the pointer
    const pair<C,D> operator*() const {
        return pair<C, D>(ptr_->data,ptr_ -> link ->data);
        //return both key data and value data
    }
    //comparions operators
    bool operator== (const tree_iterator& rgt) {return ptr_ == rgt.ptr_;}
    bool operator!= (const tree_iterator& rgt) {return ptr_ != rgt.ptr_;}
    //INCREMENT AND DECREMENT OPERATOR
    
    /*
     Find the value that is one data  
     if it point to right is not NULL, first go to right and then go to the most
     left to find the value that is one data larger than the object, if th right
     point to null go back to th parent. Until the parent point to the right is
     null, it is the increment data,since it is the midpoint of two set,otherwise,
     go back to the parent one by one
     */
    tree_iterator<C,D>& operator++() {
        //if it point to right, go to the leftmost node
        if (ptr_ -> right != NULL) {
            ptr_ = ptr_ ->right;
            while (ptr_ -> left != NULL) {
                ptr_ = ptr_ -> left;
            }
        }
        //go to the parent which do not point to right
        else{
            while (ptr_->parent != NULL && ptr_ ->parent->right == ptr_) {
                ptr_ = ptr_ ->parent;
            }
            ptr_ = ptr_ -> parent;

        }
        return *this;
    }
    //same as ++x, both iterator and the object increment
    tree_iterator<C,D> operator++(int) {
        tree_iterator<C,D> temp(*this);
        ++(*this);
        return temp;
    }
    
    //decrement is the same as increment just change the left and right, so it
    //will point to the smaller one
    tree_iterator<C,D> &operator--(){
        if (ptr_ -> left != NULL) {
            ptr_ = ptr_ -> left;
            while (ptr_ -> right != NULL) {
                ptr_ = ptr_ -> right;
            }
        }
        else{
            while (ptr_->parent !=NULL && ptr_ ->parent ->left ==ptr_) {
                ptr_ = ptr_ -> parent;
            }
            ptr_ = ptr_ -> parent;
        }
        return *this;
    }
    //decrement both iterator and object
    tree_iterator<C,D> operator--(int) {tree_iterator<C,D> temp(*this);
        --(*this); return temp;}
    
    //it will return to the node that is linked with the node the iterator is
    //point to
    tree_iterator<D,C> follow_link(){
        return ptr_->link;
    }
    //helper function, it will return to the node the iterator point to
    Node<C, D>* return_node(){return ptr_;}

    
private:
    //representation
    Node<C, D>* ptr_;
};

//=============================================================================
//BIDIRECTIONAL MAP CLASS
//=============================================================================
template<class T1,class T2>
class bidirectional_map{
public:
    //CONSTRUCTOR
    //default constructor
    bidirectional_map():size_(0),key_root_(NULL),value_root_(NULL) {}
    //copy constructor
    bidirectional_map( bidirectional_map<T1,T2>& old){
        size_ = old.size_;
        Node<T1,T2>* new_parent = NULL;
        Node<T2, T1>* new_p = NULL;
        
        //call the helper function, which will copy the key tree and the value
        //tree seperately
        key_root_ = copy_key(old.key_root_,new_parent);
        value_root_ = copy_value(old.value_root_,new_p);
        key_iterator ki;
        //link them together
        for (ki = old.key_begin(); ki!=old.key_end(); ki++) {
            T1 key_data;
            T2 value_data;
            //use the old tree to find the link data and link them one by one
            key_data = ki.return_node()->data;
            value_data =ki.return_node()->link->data;
            key_iterator ki_new = find(key_data);
            value_iterator vi_new = find(value_data);
            ki_new.return_node()-> link = vi_new.return_node();
            vi_new.return_node() -> link = ki_new.return_node();
        }
    }
    
    //DESTRUCTOR
    ~bidirectional_map(){
        //call the helper function to delete the tree seperately and make two
        //root point to NULL
        destroy_key(key_root_);
        destroy_value(value_root_);
        key_root_ = NULL;
        value_root_ = NULL;
    }
    
    //ASSIGNMENT OPERATOR
    // same as copy constructor but need to delete the old one, so the old map
    //will not exist
    bidirectional_map& operator=(const bidirectional_map<T1,T2>& old){
        size_ = old.size_;
        Node<T1,T2>* new_parent = NULL;
        Node<T2, T1>* new_p = NULL;
        key_root_ = copy_key(old.key_root_,new_parent);
        value_root_ = copy_value(old.value_root_,new_p);
        key_iterator ki;
        for (ki = old.key_begin(); ki!=old.key_end(); ki++) {
            T1 key_data;
            T2 value_data;
            key_data = ki.return_node()->data;
            value_data =ki.return_node()->link->data;
            key_iterator ki_new = find(key_data);
            value_iterator vi_new = find(value_data);
            ki_new.return_node()-> link = vi_new.return_node();
            vi_new.return_node() -> link = ki_new.return_node();
        }
        //delete the original tree
        destroy_key(old.key_root_);
        destroy_value(old.value_root_);
    }
    
    //TYPEDEFINE THE CLASS AOBVE
    typedef tree_iterator<T1, T2> key_iterator;
    typedef tree_iterator<T2, T1> value_iterator;
    
    //define iterator begin and end
    //begin is the smallest data in the tree
    /*
     go to the leftmost node find the smallest data
     */
    key_iterator key_begin() const{
        //if the tree is empty, the key begin is same as key end
        if (size() == 0) {
            return key_end();
        }
        Node<T1, T2> *tmp = key_root_;
        while (tmp -> left != NULL) {
            tmp =tmp -> left;
        }
        //iterator will point to the Node
        return key_iterator(tmp);
    }
    
    //iterator will point to NULL
    key_iterator key_end() const {return key_iterator(NULL);}
    
    
    //value iterator
    //same as the key_begin, but find the smallest data in the value tree
    value_iterator value_begin() const{
        if (size() == 0) {
            return value_end();
        }
        Node<T2, T1> *tmp = value_root_;
        while (tmp -> left != NULL) {
            tmp =tmp -> left;
        }
        return value_iterator(tmp);
    }
    
    //end should point to NULL
    value_iterator value_end() const {return value_iterator(NULL);}
    
    //get the size, return member variable
    int size() const  {return size_;}
    
    //equal operator, if the two root are the same, the whole map is the same
    bool operator==(const bidirectional_map<T1,T2>& old) const {
        return old.key_root_ == this -> key_root_
        && old.value_root_ == this -> value_root_;}
    
    //FIND, INSERT AND ERASE
    /**
     insert the data should first find the right position in both trees, and link
     the two data togerther
     */
    pair<key_iterator, bool> insert(const pair<T1, T2>& key_value){
        //first find if the data is already in key data or value data
        key_iterator ki;
        value_iterator vi;
        ki = find(key_value.first);
        vi = find(key_value.second);
        if (ki != key_iterator(NULL) || vi != value_iterator(NULL)) {
            return make_pair(find(key_value.first), false);
        }
        else{
        Node<T1, T2>* key_parent = NULL;
        Node<T2, T1>* p2;
        Node<T2, T1>* value_parent = NULL;
        pair<key_iterator, bool> tmp;
        //call the helper function to find the right position to create the new
        // node and link it correctly
        p2 = insert_value(key_value.second, value_root_,value_parent);
        tmp = insert_key(key_value.first,key_root_,p2,key_parent);
        return tmp;
        }
    }
    
    //PRINT FUNCTION
    void print(ostream& ostr) const {
        cout<<"=================================================\n";
        cout<<"KEYS:\n";
        print_key(ostr,key_root_,0);
        cout<<"-------------------------------------------------\n";
        cout<<"VALUES:\n";
        print_value(ostr, value_root_,0);
        cout<<"=================================================\n";
    }
    
    //OPERATOR[],ORDER NOTATION SHOULD BE LOGN
    T2 operator[](const T1& key_data) {
        return operator_map(key_data,key_root_);
    }
    T1 operator[](const T2& value_data) {
        return operator_map_2(value_data,value_root_);
    }
    
    //FIND FUNCTION,return iterator
    key_iterator find(const T1& key_data){
        return find(key_data,key_root_);
    }
    
    value_iterator find(const T2& value_data){
        return find(value_data,value_root_);
    }
    //ERASE KEY
    int erase(const T1 & key_data){
        int count = 0;
        key_iterator ki=find(key_data);
        if (ki != key_end()) {
            erase(ki.return_node()->link ->data ,value_root_);
            count =erase(key_data,key_root_);
            size_--;
        }
        
        return count;
    }

private:
    //member variable
    Node<T1,T2>* key_root_;
    Node<T2,T1>* value_root_;
    int size_;
    
    
    /**
      insert key value
     find the right place in the tree then link node together
     @para:p2 is the link data the map should link together
     key_value: the data should be inserted
     p1: the Node will pointer through the tree from the root to find correct
     place
     p3: the parent
     */
    pair<key_iterator, bool> insert_key(const T1& key_value,Node<T1, T2>* &p1,
                                        Node<T2, T1>* &p2,Node<T1, T2>* &p3){
        //if it find the right place
        //insert the new Node,link the parent and value_data node
        if (!p1) {
            p1 = new Node<T1, T2>(key_value);
            p1 ->link = p2;
            p2 -> link = p1;
            p1 -> parent = p3;
            this ->size_++;//increment size
            return pair<key_iterator, bool>(key_iterator(p1), true);
        }
        else if (key_value< p1->data){
            //move the node to the smaller data
            return insert_key(key_value,p1 -> left,p2,p1);
        }
        else if(key_value > p1 -> data){
            //move to the larger data
            return insert_key(key_value,p1 -> right,p2,p1);
        }
        else{
            //if there already exist the data
            return  pair<key_iterator, bool>(key_iterator(p1),false);
        }
    }
    
    
    //insert value data
    //p3 is the parent, others are the same as the above one, but the type of
    //node is changed
    Node<T2, T1>* insert_value(const T2& value,Node<T2, T1>* &p2,
                               Node<T2, T1>* &p3){
        if (!p2) {
            //find the right place, link the parent
            p2 = new Node<T2, T1>(value);
            p2 -> parent = p3;
            return p2;
        }
        else if (value< p2->data){
            return insert_value(value,p2 -> left,p2);
        }
        else if(value > p2 -> data){
            return insert_value(value,p2 -> right,p2);
        }
        else{
            //if already exist
          return  NULL;
        }
    }
    
    //PRINT
    void print_key(ostream& ostr,Node<T1, T2>* p1,int h) const{
        string blank;
        //get the height of the node and print the right blank
        for (int i=0; i<h; i++) {
            blank +="    ";
        }
        if (p1) {
            //first go to the right, then go to the left
            print_key(ostr, p1->right,h+1);//increase the height
            ostr<<blank<<p1->data<<" [" <<p1 ->link ->data<<"]\n";
            print_key(ostr, p1->left,h+1);
            
        }
    }
    
    void print_value(ostream& ostr,Node<T2, T1>* p2,int h) const{
        string blank;
        for (int i=0; i<h; i++) {
            blank +="    ";
        }
        if (p2) {
            print_value(ostr, p2->right,h+1);
            ostr<<blank<<p2->data<<" ["<<p2 ->link ->data<<"]\n";
            print_value(ostr, p2->left,h+1);
        }
    }
    
    //operator for the key
    //same as find, after find the data, point to its link data
    T2 operator_map(const T1& key_data,Node<T1,T2>*& p){
        if(p ->data == key_data){
            return p ->link ->data;
        }
        else if (key_data < p ->data){
            return operator_map(key_data, p->left);
        }
        else {
            return operator_map(key_data, p-> right);
        }

    }
    //oeprator for the value
    T1 operator_map_2(const T2& key_data,Node<T2,T1>*& p){
        if(p ->data == key_data){
            return p ->link ->data;
        }
        else if (key_data < p ->data){
            return operator_map_2(key_data, p->left);
        }
        else {
            return operator_map_2(key_data, p-> right);
        }
    }
    
    //find the iterator
    key_iterator find(const T1& key_data, Node<T1, T2>* &p ){
        //if cannot find the data, point to end
        if (!p) {
            return key_end();
        }//if the data equal the find data, return the iterator
        else if (p -> data == key_data){
            return key_iterator(p);
        }
        //if the node data too large, point to left
        else if (key_data < p->data) return find(key_data, p->left);
        //if the node data too small, point to the right
        else{
            return find(key_data,p->right);
        }
    }
    //find the iterator
    value_iterator find(const T2& value_data, Node<T2, T1>* &p ){
        if (!p) {
            return value_end();
        }
        else if (p -> data == value_data){
            return value_iterator(p);
        }
        else if (value_data < p->data) return find(value_data, p->left);
        else{
            return find(value_data,p->right);
        }
    }
    
    //COPY CONSTRUCTOR
    Node<T1, T2>* copy_key(Node<T1, T2>* &old_root,Node<T1, T2>* &new_parent){
        if (old_root == NULL) {
            return NULL;
        }
        //create node on the heap
        Node<T1,T2>* new_root = new Node<T1,T2>(old_root->data);
        //root point to left is the same as the old root point to left
        new_root ->left = copy_key(old_root -> left,new_root);
        //copy the root right
        new_root -> right = copy_key(old_root ->right,new_root);
        //after it copy the left adn right, find its parent
        new_root ->parent = new_parent;
        return new_root;
    }
    
    //same as the copy_key, change the data type
    Node<T2, T1>* copy_value(Node<T2, T1>* &old_root,Node<T2, T1>* &new_parent){
        if (old_root == NULL) {
            return NULL;
        }
        Node<T2,T1>* new_root = new Node<T2,T1>(old_root->data);
        new_root ->left = copy_value(old_root -> left,new_root);
        new_root -> right = copy_value(old_root ->right,new_root);
        new_root ->parent = new_parent;
        return new_root;
    }
    
    
    
    //DESTRCUTOR
    void destroy_key(Node<T1, T2>* p){
        if (!p) {
            return;
        }
        destroy_key(p->left);
        destroy_key(p->right);
        delete p;
        //delete the node from the whole tree
    }
    void destroy_value(Node<T2, T1>* p){
        if (!p) {
            return;
        }
        destroy_value(p->left);
        destroy_value(p->right);
        delete p;
    }
    
    //ERASE
    //erase the key data in the key_root_
    int erase(T1 const & key_data,Node<T1, T2>* &p){
        //cannot find the data, back to 0
        if (!p) {
            return 0;
        }
        //find the node
        if (key_data<p->data) {
            return erase(key_data,p->left);
        }
        else if (key_data > p->data){
            return erase(key_data,p->right);
        }
        //when find the node
        else{
            //NO CHILDREN
            if (p->left == NULL && p->right == NULL) {
                //delete p
                delete p;
                p = NULL;
                return 1;
            }
            //JUST A LEFT CHILD
            else if (p->right==NULL){
                Node<T1, T2>* tmp = p-> left;
                //tmp node will replace p
                delete p;
                p = tmp;
                return 1;
            }
            //JUST A RIGHT CHILD
            else if (p->left == NULL){
                Node<T1, T2>* tmp = p->right;
                delete p;
                p = tmp;
                return 1;
            }
            //TWO CHILDREN
            else{
                //FIND LARGEST ELEMENT TO LEFT
                //replace the data for th parent and delete the a node which
                //is not parent, at the same time, copy all the link data
                Node<T1, T2>* tmp = p->left;
                while (tmp -> right != NULL) {
                    tmp = tmp ->right;
                }
                //make the data replace the original data
                p->data = tmp ->data;
                //all the link will change
                p -> link = tmp ->link;
                p ->link -> link = p;
                tmp -> link = NULL;
                //erase the same data
                erase(tmp -> data,p -> left);
                
                return 1;
            }
        }
    }
    
    int erase(T2 const & value_data,Node<T2, T1>* &p){
        if (!p) {
            return 0;
        }
        if (value_data<p->data) {
            return erase(value_data,p->left);
        }
        else if (value_data > p->data){
            return erase(value_data,p->right);
        }
        else{
            //NO CHILDREN
            if (p->left == NULL && p->right == NULL) {
                delete p;
                p = NULL;
                return 1;
            }
            //JUST A LEFT CHILD
            else if (p->right==NULL){
                Node<T2, T1>* tmp = p-> left;
                delete p;
                p = tmp;
                return 1;
            }
            //JUST A RIGHT CHILD
            else if (p->left == NULL){
                Node<T2, T1>* tmp = p->right;
                delete p;
                p = tmp;
                return 1;
            }
            //TWO CHILDREN
            else{
                //FIND LARGEST ELEMENT TO LEFT
                Node<T2, T1>* tmp = p->left;
                while (tmp -> right != NULL) {
                    tmp = tmp ->right;
                }
                p->data = tmp ->data;
                p->link = tmp -> link;
                p -> link -> link =p;
                tmp -> link = NULL;
                erase(tmp -> data,p -> left);
                return 1;
            }
        }
    }
    
};

#endif /* bidirectional_map_h */
