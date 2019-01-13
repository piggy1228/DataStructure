HOMEWORK 3: UNDO ARRAY


NAME:  kexin zhu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  16h


ORDER NOTATION:
For each function, using the variables:
  n = size of the array
  h = the length of the longest history for one slot of the array
Include a short description of your order notation analysis 
for the non-trivial functions.

size:O(1)

set:O(n)

initialized:O(1)

get:O(1)

undo:O(n)

print:O(nh)

basic constructor:O(n)

copy constructor:O(nh)

destructor:O(n)
find out the size of the for loop is almost the order notation of the function



EXTRA CREDIT:
Discuss your implementation & order notation of push_back and pop_back.
//to build a new array on the heap to adjust its size, and through for loop to copy
all the info as the same.except the adjustment at the last index.
push_back:o(nh)

pop_back:O(n)



MISC. COMMENTS TO GRADER:  
Optional, please be concise!

