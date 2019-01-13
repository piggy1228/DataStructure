HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  Kexin Zhu


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

None

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  38h


ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)
costume_shop inventory types number(T)
average inventory numbers for each type(N)
customer number(C)
average times the customer comes to the shop(R)
addCostume: 1. find the costume name in the shop O(logT)
2.make pair O(1)
3.insert the key into the shop O(logT)
total:O(logT)

rentCostume: 1.find the specific costume name in the costume_shop map O(logT)
2.make pair O(1)
3.have the key to get the value O(1)
4.in the else for loop to get the name in the map.second.second vector to erase the name O(N)
total:O(N+logT)


lookup: 1.find the specific costume name in the costume_shop map O(logT)
2.in the for loop to print all the customers who rent the costume:O(N)
total:O(logT+N)

printPeople: 1.print all the objects in the people map(using by iterator) O(C).only 1 for loop.
2.get the costume_name for each people O(1)
there are others constant order notation are ignored
total:O(C)

EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.
use the vector to store all the objects. the costume shop store pair in the vector
addCostume_nonmap:in the first for loop to check if the costume already have the costume O(T*1) = O(T).All the push back is O(1).(the second vector in the costume shop only have
1 object so the Order notation is O(1)).
total:O(T)

rentCostume_nonmap: 1. to look for the info of the customer is O(C)
2.to look for the specific costume O(N),erase is  O(N*T)
total is O(NT+C)

lookup_nonmap: 1.first find the costume in the for loop O(T),
second to find out all the rent customers:O(N)
total: O(T*N)

printPeople_nonmap: 1.sort the people :O(C^2)
2.print in order O(C)
total: O(C^2)
map should be much more faster than vector version since its order notation for erase insert and find is sublinear.
in the map version for the large_input dataset Time: 0.000113 s
in the vector version for the large_input dataset Time: 0.847651 s


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






