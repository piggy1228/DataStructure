	HOMEWORK 6: PAINT BY PAIRS RECURSION


NAME:  Kexin Zhu



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Professor Cutler on lms, mentor Ethan, Sinclair,Xi Chen

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  80h



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of strokes (s)? 
The total number of painted cells(p) or unpainted cells (u)?
The average length of each stroke (l)?
Etc. 
order notation for all the helper function:
the number of points with value(not blank) on the board(c)
average possibilities that a point can find its pair(k)
the number of solutions(n)
sort_the_live_cells:O(c^2)
print_solved_board:O(s*l)
convert_letter_num: O(1)
print_all_points_all_path:O(n*s*l)
is_dead:O(l)
is_dead_for_all_path: O(l*s)
remove_from_live_cells: O(c)

one_pair:O(2^l)
O(l*s) is in the if statement
O(4^l) is in the else statement
since O(4^l) is larger than O(l*s),which can be ignored


find_all_path:O(2^l+k^s)
Multiply the function inside. and find the larger one
in the first big if,O(1)
in the else:if statement O(2^l)+O(C)
in the for loop: O(k^s) each stroke will repeat the path k times
so the total O(2^l+k^s)




The algorithm is a little bit slower, because the vector are 2D to store the whole one path, also, the one_path recursion call by value it will make it more slower.




SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.  Also, describe the
image in words.
puzzle 1 has 3 solutions, others only have 1 solution.
puzzle 1: a horse? hard to describe  one_solution time:0.001639 s     all_solutions time: 0.001742 s
puzzle 2: cat  one_solution time:0.002132 s      all_solutions time:0.002355 s
puzzle 3: human face one_solution time: 0.002933s         all_solutions time:0.002972 s
puzzle 4: batman one_solution time:6.3582 s	all_solutions time: 6.74515 s
puzzle 5: bird or chick one_solution time: 4.5mins        all_solutions time: 15 mins
puzzle 6: looks like a guy sitting behind a computer one_solution time: 47.4446 s
all_solutions time:48.433 s
puzzle 7: like an ice-cream or cake one_solution time: 4h? (not sure)

MISC. COMMENTS TO GRADER:  



