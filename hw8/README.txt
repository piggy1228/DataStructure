HOMEWORK 8: BIDIRECTIONAL MAPS


NAME:  Kexin Zhu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

lecture note in class

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  50h



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer (please be concise!)  You may assume that the tree is
reasonably well balanced for all operations.  (You do not need to
implement re-balancing.)

n = the number of elements

k = maximum number of links stored in a single node 
    (for extra credit non one-to-one associations)


size: O(1)
should be constant since its member variable

insert:O(logn)
need to find the right position through binary search to insert

erase:O(logn)
need to find the right position through binary search to erase

find:O(logn)
need to find the right position through binary search

operator[]:O(logn)
need to find the right position through binary search to get link

key_begin:O(n)
need to go through the whole tree to find the smallest number

key_end:O(1)
just assign it be the NULL

value_begin:O(n)

value_end:O(1)

key iterator++/--: O(n)
go through the whole tree to find the node

value iterator++/--: O(n)

follow_link:O(1)
just need to point to the link

default constructor:O(1)
assign the root and size directly


copy constructor:O(n)
go through each node in the tree

destructor:O(n)
go through each node in the tree

assignment operator:O(n)
go through each node in the tree to copy, and then go through the old tree to delete


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


