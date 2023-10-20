Maxim Joel Carbonell-Kiamtia
mjcarbon


---------------------
DESCRIPTION
Description: This directory is for the purposes of finding the shortest hamiltonian path given a set of vertices and edges connecting them. It will handle an error if not given the proper format of veritces, edges, and names. 

1. Enter "make" in the terminal
2. Enter "./tsp -[INSERT COMMANDs HERE]". To insert an input file for the program to read user must type " < [insert input file here]" or "-i [insert input file here]" and if the user wishes to use an output file other than stdout they must type "-o [insert input file here]"
---------------------
FILES
DESIGN.pdf
Makefile
README.md
stack.c 
stack.h 
path.c 
path.h 
graph.c 
graph.h 
tsp.c
tsp.h
vertices.h 
graphs
-----------------------
stack.c contains the c program to perform all of the logic needed by the path data structure. It is used to hold all of the vertices.

path.c contains the c program to perform all of the logic to track the current path or shortest path. 
 
graph.c contains the c program to perform all of the logic needed to track the edges and vertices for a graph. 

tsp.c contaisn the c program to handle all of the input and output logic as well as the Depth First Search recursive function to calculate all possible hamiltonian paths. 

DESIGN.pdf contains a walkthrough or behind the scenes process to create or recreate this directory. 
---------------------


