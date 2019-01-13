#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


using namespace std;
template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;
public:
    //CONSTRUCTOR
  priority_queue() {
      vector<T> values;
      m_heap = values;
  }

  priority_queue( std::vector<T> const& values )
  {
      this -> create(values);
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }
    
    void percolate_up(int index){
        if (index <1) {
            return;
        }
        if (m_heap[index] < m_heap[(index-1)/2]) {
            T tmp = m_heap[index];
            m_heap[index] = m_heap[(index-1)/2 ];
            m_heap[(index-1)/2] = tmp;
            percolate_up((index-1)/2);
        }
        else{
            return;
        }
        
    }

  void push( const T& entry )
  {
      m_heap.push_back(entry);
      int index = m_heap.size()-1;
      percolate_up(index);
      
  }
    
void percolate_down(int index,int max_i){

    if (max_i == 0) {
        return;
    }
        if (index >= max_i) {
            return;
        }
        else if (index == max_i-1){
            if (m_heap[index]>m_heap[max_i]) {
                int tmp =m_heap[max_i];
                m_heap[max_i] = m_heap[index];
                m_heap[index] = tmp;
                return;
            }
        }
        else{
            int childOne = m_heap[2*index+1];
            int childTwo = m_heap[2*index+2];
            if (m_heap[index] > childTwo && m_heap[index] > childOne) {
                if (childOne < childTwo) {
                    int tmp = childOne;
                    m_heap[2*index+1] = m_heap[index];
                    m_heap[index] = tmp;
                    percolate_down(2*index+1, max_i);
                }
                else{
                    int tmp = childTwo;
                    m_heap[2*index+2] = m_heap[index];
                    m_heap[index] = tmp;
                    percolate_down(2*index+2, max_i);
                }
                
            }
            else if(m_heap[index] > childOne && m_heap[index] <childTwo){
                int tmp = childOne;
                m_heap[2*index+1] = m_heap[index];
                m_heap[index] = tmp;
                percolate_down(2*index+1, max_i);
            }
            else if(m_heap[index] > childTwo && m_heap[index] <childOne){
                int tmp = childTwo;
                m_heap[2*index+2] = m_heap[index];
                m_heap[index] = tmp;
                percolate_down(2*index+2, max_i);
            }
            else{
                return;
            }
        }
    }

    
    /*
  void pop() 
  {
    assert( !m_heap.empty() );
     
      m_heap[0]=m_heap.back();
      m_heap.pop_back();
      int max_i = m_heap.size()-1;
      percolate_down(0,max_i);*/
      /*
      m_heap[0] = m_heap.back();
      m_heap.pop_back();
      for (int i=0; i<m_heap.size(); i++) {
          int left = 2*i+1;
          int right = 2*i+2;
          if (m_heap[left]<m_heap[right] && m_heap[i]>m_heap[left] && left <m_heap.size()) {
              T tmp =m_heap[i];
              m_heap[i] = m_heap[left];
              m_heap[left] = tmp;
          }
          if (m_heap[right]<m_heap[left] && m_heap[i]>m_heap[right] && right <m_heap.size()) {
              T tmp =m_heap[i];
              m_heap[i] = m_heap[right];
              m_heap[right] = tmp;
          }

      }
      if (m_heap.size() == 1) {
          return m_heap.clear();
      }
      else {
          m_heap[0] = m_heap[m_heap.size() - 1];
          m_heap.pop_back();
          int index = 0;
          while (2 * index + 1 < m_heap.size()) {
              if (2*index+2 < m_heap.size() && m_heap[2*index+2] < m_heap[2*index+1]) {
                  if (m_heap[2 * index + 2] < m_heap[index]) {
                      int value = m_heap[index];
                      m_heap[index] = m_heap[2 * index + 2];
                      m_heap[2 * index + 2] = value;
                  }
                  else {
                      break;
                  }
              }
              else {
                  if (m_heap[2 * index + 1] < m_heap[index]) {
                      int value = m_heap[index];
                      m_heap[index] = m_heap[2 * index + 1];
                      m_heap[2 * index + 1] = value; 
                  }
                  else {
                      break;
                  }
              }
          }
      }
      
  }*/
    void pop()
    
    {
        
        assert( !m_heap.empty() );
        
        m_heap[0]=m_heap[m_heap.size()-1];
        
        m_heap.pop_back();
        
        int curidx=0;
        
        int childidx;
        
        if(m_heap[1]<m_heap[2]){
            
            childidx=1;
            
        }else{
            
            childidx=2;
            
        }
        
        while(m_heap[curidx]>m_heap[childidx]&&(2*curidx+1)<m_heap.size()){
            
            std::swap(m_heap[curidx],m_heap[childidx]);
            
            curidx=childidx;
            
            if(m_heap[2*curidx+1]<m_heap[2*curidx+2]){
                
                childidx=2*curidx+1;
                
            }else{
                
                childidx=2*curidx+2;
                
            }
            
        }
        
    }

    
    int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }

  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

    bool check_heap(const vector<T>& heap,int index,int max_i){
        if (max_i==-1) {
            return true;
        }
        if (index == max_i) {
            return true;
        }
        else if (index == max_i-1){
            if (heap[index]<heap[max_i-1]) {
                return true;
            }
        }
        else if (heap[index] <heap[index+1] && heap[index]<heap[index+2]) {
            check_heap(heap,index+1,max_i);
            return true;
        }
        else{
            return false;
        }
        return false;
    }
  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
      int max_i = heap.size()-1;
      return check_heap(heap,0,max_i);
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
    
  void create(std::vector<T> const& values){
        for (int i = 0; i<values.size(); i++) {
            push(values[i]);
        }
    }
  
};

template<class T>
void percolate_down(int index,int max_i,vector<T> m_heap){
    
    if (max_i == 0) {
        return;
    }
    if (index >= max_i) {
        return;
    }
    else if (index == max_i-1){
        if (m_heap[index]>m_heap[max_i]) {
            int tmp =m_heap[max_i];
            m_heap[max_i] = m_heap[index];
            m_heap[index] = tmp;
            return;
        }
    }
    else{
        int childOne = m_heap[2*index+1];
        int childTwo = m_heap[2*index+2];
        if (m_heap[index] > childTwo && m_heap[index] > childOne) {
            if (childOne < childTwo) {
                int tmp = childOne;
                m_heap[2*index+1] = m_heap[index];
                m_heap[index] = tmp;
                percolate_down(2*index+1, max_i,m_heap);
            }
            else{
                int tmp = childTwo;
                m_heap[2*index+2] = m_heap[index];
                m_heap[index] = tmp;
                percolate_down(2*index+2, max_i,m_heap);
            }
            
        }
        else if(m_heap[index] > childOne && m_heap[index] <childTwo){
            int tmp = childOne;
            m_heap[2*index+1] = m_heap[index];
            m_heap[index] = tmp;
            percolate_down(2*index+1, max_i,m_heap);
        }
        else if(m_heap[index] > childTwo && m_heap[index] <childOne){
            int tmp = childTwo;
            m_heap[2*index+2] = m_heap[index];
            m_heap[index] = tmp;
            percolate_down(2*index+2, max_i,m_heap);
        }
        else{
            return;
        }
    }
}



template <class T>
void heap_sort( std::vector<T> & v )

{
    if (v.size() == 0) {
        return;
    }
    
    int s = v.size()-1;
    while (s>= 0) {
        percolate_down(0,v.size()-1,v);
        T tmp = v[0];
        //cout<<tmp<<endl;
        v[0] = v[s];
        v[s] = tmp;
        s--;
    }
   std::reverse(v.begin(), v.end());
}





#endif
