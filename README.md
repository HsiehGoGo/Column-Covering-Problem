## Problem definition
Let X and Y be two sets, and R be a relation defined on XY. We say that y covers x
when xRy. The matrix associated with the column covering problem <X, Y, R> has rows 
labeled with elements of X and columns labeled with elements of Y, such that the 
element [x, y] of the matrix is equal to 1 iff xRy. A subset C of Y is a column cover of 
X iff for each element x in X, there exists some element y in C such that xRy.

## Solve
Convert the column cover problem into a binary tree search, employing Depth-First-Search (DFS) to identify the optimal covering set. In this context, each node within the binary tree represents a column. The left child node indicates the inclusion of the corresponding column in the covering set, while the right child node signifies its exclusion. The objective is to continually explore options to achieve the best possible cost.
