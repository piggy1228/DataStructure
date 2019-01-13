//
//  undoarray.h
//  hw3
//
//  Created by KEXIN ZHU on 9/24/16.
//  Copyright © 2016 KEXIN ZHU. All rights reserved.
//

#ifndef undoarray_h
#define undoarray_h

//TYPEDEFS
typedef unsigned int size_type;

template <class T>
class UndoArray{
public:

    //constructors, assignment operator, destructor
    UndoArray() {this -> create();}//default constructor
    UndoArray(size_type size_)  {this -> create(size_);}//constructor
    UndoArray(const UndoArray& ua){another(ua);};//copy function
    UndoArray& operator=(const UndoArray& ua);//assignment operator
    ~UndoArray() {
        delete [] counts_;
        for (int i=0; i<size_; i++) {
            delete [] values_[i];
        }
        delete [] values_;
        std::cout<<"destrcutor test completed"<<std::endl;
        //to make sure that the class was dectructed at the end
    }//destrctor
    
    //Member functions and other operators
    size_type size()const {return size_;}
    const size_type& operator[] (size_type i) const{return counts_[i];}
    //to get each slot in the counts array
    const T& values(size_type i, size_type j) const{return values_[i][j];}
    //to get each slot in the values array
    
    bool initialized(size_type n);//to check if the values are initialized
    void set(int n,T word);//set the n slot with the word(type is T)
    T get(int n);// to find what is at the end of the n slot
    void undo(int n);// undo the last word in the n slot
    void print();//print all the message the class have
    void push_back(const T& word);//push back word at the new slot
    void pop_back();//pop back the last arrat slot

private:
    //private member function
    void create();//default create
    void create(size_type size_);
    void another(const UndoArray<T>& ua);//copy function


    //Representation
    size_type size_;//size of the array
    size_type* counts_;//the counts array
    T** values_;//the values array of array
};




// =======================================================
//IMPLEMENTATION
/**
create an empty array(null pointer)
*/
template <class T>  void UndoArray<T>::create(){
    values_ = NULL;
    size_=0;
    counts_ = NULL;
}
/**
Create two array with counts and values
 */
template <class T>
void UndoArray<T>:: create(size_type n){
    size_ = n;
    counts_ = new size_type[n];
    for (int i=0; i<n; i++) {
        counts_[i] = 0;
    }
    values_ = new T*[n];
    for (int i=0; i<n; i++) {
        values_[i] = NULL;
    }

}

/**
bool function ,if the values are initialized
 */
template <class T>
bool UndoArray<T>::initialized(size_type n){
    if (counts_[n]==0) {
        return false;//if the counts of the value is 0, then it is uninitialized
    }
    return true;
}

/**
 set funtion
 set the slot n with word under values array
 @para n the counts at slot n will also increment,
 build a new array and delete the old one
 @para word, at the values slot n, increment the array, and make the back position
 of the array word
 */
template <class T>
void UndoArray<T>::set(int n, T word){
    //error check
    if (n<0||n>=size_) {
        std::cerr<<"Out of range\n";
        exit(9);
    }
    size_type k=counts_[n];//get the size of the array
    counts_[n]++;//increment
        T* temp = values_[n];
        values_[n] =new T[k+1];//the array of array will be 1 larger than the old one
        for (int i=0; i<k; i++) {
            values_[n][i] = temp[i];
            //all the words before are all the same
        }
        values_[n][k] = word;//add the one is set by the function at the end
        delete []temp;//delete the old array
    
}


/**
 get function,
 to get the word at the end of the slot n
 @para n the slot n at the values array
 @return the word
 */
template <class T>
T UndoArray<T>::get(int n){
    //error check
    if (n<0 || n>=size_) {
        std::cerr<<"Out of range\n";
        exit(9);
    }
    if (!initialized(n)) {
        std::cerr<<"not initialized\n";
        exit(9);
    }
    return values_[n][counts_[n]-1];
}


/**
 delete the word at the slot n, the back position of the array
 if there is no array,it become NULL
 else, build a new array under the slot n, copy the word before the last position
 delete the original array on the heap
 */
template <class T>
void UndoArray<T>::undo(int n){
    size_type k =counts_[n];
    //to find if the commands out of range
    if (counts_[n]==0) {
        std::cerr<<"cannot undo a null array\n";
        exit(9);
    }
    if (n<0 || n>=size_) {
        std::cerr<<"Out of range\n";
        exit(9);
    }
    counts_[n]--;
    //if the array counts become 0, it become null pointer
    T* temp = values_[n];
    if (counts_[n]==0) {
        values_[n]=NULL;
    }

    else{
        values_[n] =new T[k - 1];
        for (int i=0; i<k-1; i++) {
            values_[n][i] = temp[i];
    //copy the words on the original array except the last one
        }
    }
    delete [] temp;
}


/**
 print out the message about the class
 the size and numbers in counts
 two arrays in the values
 */
template <class T>
void UndoArray<T>::print(){
    int max_n=0;
    std::cout<<"size_:  "<<size_<<std::endl;
    std::cout<<"counts_:  ";
    for (int i=0; i<size_; i++) {
        if (max_n<counts_[i]) {
            max_n=counts_[i];
            //find out the max array under the values array
        }
        std::cout<<counts_[i]<<"  ";
    }
    std::cout<<"\nvalues_:  ";
    //print out whether there is somthing in the values array at index n
    for (int i=0; i<size_; i++) {
            if (counts_[i]==0) {
                std::cout<<"/  ";
            }
            else{
                std::cout<<".  ";
            }
        }
    std::cout<<"\n          ";
    //print the standard of the arrays at index n of values_ array
    for (int i=0; i<max_n; i++) {
        for (int j = 0; j<size_; j++) {
            if (counts_[j]<=i) {
                std::cout<<"   ";
            }
            else{
                std::cout<<values_[j][i]<<"  ";
            }
        }
        std::cout<<"\n          ";
    }
}

/**
 the copy function, make the another array same as the ua array
 copy the size and two arrays
 build the arrays on the heap and do not delete the original one
 */
template <class T>
void UndoArray<T>::another(const UndoArray<T>& ua){
    size_ = ua.size();//get the size of the array
    counts_=new size_type[ua.size()];//build the heap
    for (int i=0; i<ua.size(); i++) {
        counts_[i] = ua.counts_[i];//get the same word at the same slot
    }
    values_ = new T*[ua.size()];
    for (int i=0; i<ua.size(); i++) {
        values_[i] = new T[counts_[i]];//build a heap under each slot
        for (int j=0; j<counts_[i]; j++) {
            values_[i][j] = ua.values(i,j);
            // get the word at values[i][j] slot
        }
    }
}

/**
Assign one vector to another, avoiding duplicate copying
the only difference with copy function is to delete the original class
 @return the left hand side object
 */
template <class T>
UndoArray<T>& UndoArray<T>::operator=(const UndoArray<T>& ua){
    if (this != & ua) { //to find out the two objects are different
        delete []counts_;//delete all the heap to prevent the memory leak
        for (int i=0; i<ua.size(); i++) {
            delete [] values_[i];
        }
        delete [] values_;
        this -> another(ua);// assign the object to the left hand side
        //use the copy function already created
    }
    return *this;
}

/**
 push back function to add a word at the end of the values array
 the size and the counts size, and values size both increment
 need to copy the old info to the new class and delete them
 */
template<class T>
void UndoArray<T>::push_back(const T& word){
    //Allocate a larger array,and copy the old values
    size_type* temp_c = counts_;//make the pointer to the counts_ array
    counts_ = new size_type[size_ + 1];//make the array one slot bigger
    for (int i=0; i<size_; i++) {
        counts_[i] = temp_c [i];//copy all the info in counts_
    }
    counts_[size_] = 1;
    T** temp_v = values_;
    values_ = new T*[size_+1];//copy the values info
    for (int i =0; i<size_; i++) {
        values_[i] = temp_v[i];
        T* temp_v_t = values_[i];
        values_[i] = new T[counts_[i]];
        for (int j=0; j<counts_[i]; j++) {
            values_[i][j] = temp_v_t[j];
        }
        delete [] temp_v_t;
    }
    values_[size_] = new T[1];//make the word at the new slot in values
    values_[size_][0] = word;
    size_++;
    delete [] temp_c;
    delete [] temp_v;//delete the old arrays on heap
}

/**
 pop back function delete the last position in the array
 size decrement and all the info except the last slot need to be copy to the
 new function
 */

template <class T>
void UndoArray<T>::pop_back(){
    if (size_ <= 0 ) {
        std::cerr<<"Cannot pop back\n";
        exit(9);
    }
    //if it is only one size, it becomes to 0,make all the pointer to null
    if (size_ == 1) {
        size_ = 0;
        delete [] counts_;
        if (counts_[0] !=0) {
            delete [] values_[0];
        }
        delete [] values_;
        counts_ = NULL;
        values_ = NULL;
    }
    else{
        //Allocate a larger array,and copy the old values
        size_type* temp_c = counts_; //copy all the info except the back slot
        counts_ = new size_type[size_ - 1];
        for (int i=0; i<size_-1; i++) {
            counts_[i] = temp_c [i];
        }
        T** temp_v = values_;
        values_ = new T*[size_-1];//build a array one size smaller
        for (int i =0; i<size_- 1; i++) {
            values_[i] = temp_v[i];
        }
        if (temp_c[size_-1] != 0) {
            delete temp_v[size_-1];
        }
        size_--;//decrement
        delete [] temp_c;//delete the original arrays on heap
        delete [] temp_v;
    }
}



#endif /* undoarray_h */
