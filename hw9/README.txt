HOMEWORK 9: IMAGE COMPARISON HASHING


NAME:  KEXIN ZHU


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  80h




i = # of images
w = width x h = height (average size image)
s x s = seed size
r x r = typical subregion match. 
t = hash table size 
c = fraction of hash table to compare


ANALYSIS OF SIMPLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

RUNNING TIME: in the function simple compare: first to find one same block O(w^2*h^2*s^2) this is the largest order notations
In the main function, it will run different image to compare,O(i^2)
So the total order notation is O(w^2*h^2*s^2*i^2)

MEMORY USAGE:1.for all the pictures O(i^2)
2.Only store the Point which decide the bound O(1)
so the memory usage is O(i^2)




ANALYSIS OF HASH TABLE ALGORITHM (RUNNING TIME & MEMORY USAGE)
Include a short explanation/justification of your answer.

RUNNING TIME: 1.initialize all the hash table(find a prime less than table size will be smaller than O(t),so can be ignored): O(i*t) 
2. in the compare part, to loop over all the images is O(i^2)
2.1 in the compareHashFunction, to find the match Block will cost O(t*c), since the hash table is considered events should be O(1),bound function can be ignored.
3.DELET node on the heap, same as constructor.
O(i*t+i^2*t*c) = O(i*t)

MEMORY USAGE:1.To construct a hash table for each image: O(i*t)
2.to construct vectors which will store all the points are the same:O(r*r)
So the total memory usage is O(i*t+r*r))



SUMMARY OF RESULTS: 
Test your implementation on a variety of images and command line
arguments and summarize and discuss the results (both running time and
quality of results).
The running time is a little bit long, maybe the hash table is not even enough. The output is basically correct. In order
To make the running time shorter, use the memory to trade off.
1.for the 4 marbles:0.2s it is almost the same with the expected output
2.for the noisy marbles:0.2 s.All of them are the similar with the first output(marbles)
3.for the data structure set:0.2 s.All of them are the similar with the first output(marbles)
4.for the 26 sunflowers:49.9 s. A lot slower, but it can get a relative correct answer.



EXTRA CREDIT -- MULTIPLE ROTATION AND/OR 90/180/270 ROTATION AND
HORIZONTAL/VERTICAL FLIP:
Discuss your implementation and results of testing.




MISC. COMMENTS TO GRADER:  
Optional, please be concise!






