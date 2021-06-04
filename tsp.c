/* 
Created by: Carbonell-Kiamtia, Maxim 
mjcarbon 
May 2nd, 2021

Assignment 4: Navigations of Denver Long 
CSE 13S, Computer Systems and C Programming 
UC Santa Cruz, Spring 2021

Description: This directory is for the purposes of finding the shortest hamiltonian path given a set of vertices and edges connecting them. It will handle an error if not given the proper format of veritces, edges, and names. 

*/

#include "tsp.h"

#include "graph.h"
#include "path.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hvui:o:"
#define BLOCK   4096
bool vPrint = false;
uint32_t temp = 0;
uint32_t rounds = 0;
uint32_t calls = 0;
uint32_t lastLength = 0;
void DFS(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[],
    FILE *outfile) { // DFS is a recursive function that finds all possible hamiltonian paths.
    graph_mark_visited(G, v); // Begin by marking the vertex as visited
    uint32_t amountVertices = graph_vertices(G);
    for (uint32_t i = 0; i < (amountVertices); ++i) { // Iterate through all possible paths
        if ((graph_visited(G, i)
                == false)) { // If we have not visited it and it has an edge connecting the two vertices then we must push it to the path and call DFS to find all possible options from our new vertex.
            if (graph_has_edge(G, v, i)) {
                path_push_vertex(curr, i, G);
                calls += 1;
                DFS(G, i, curr, shortest, cities, outfile);
            }
        }
        if ((path_vertices(curr))
            == (amountVertices
                - 1)) { // If our path's length is one short of all the vertices that exist then that means we have found a hamiltonian path since we did not pass the origin onto the path
            path_push_vertex(curr, 0, G);
            if (rounds == 0) {
                path_copy(shortest, curr);
                lastLength = path_length(curr);
            }
            if (vPrint == true) { // If verbose printing is on print all paths
                if (rounds == 0) {
                    fprintf(stdout, "Path length: %d\n", path_length(curr));
                    path_print(curr, stdout, cities);
                } else {
                    if (path_length(curr) < lastLength) {
                        fprintf(stdout, "Path length: %d\n", path_length(curr));
                        path_print(curr, stdout, cities);
                        lastLength = path_length(curr);
                    }
                }
            }
            if (path_length(curr)
                < path_length(shortest)) { // Logic to copy the track the shortest Path we take
                path_copy(shortest, curr);
            }
            path_pop_vertex(curr, &temp, G);
            rounds += 1;
        }
    }
    graph_mark_unvisited(G,
        v); // We perform this when we have already tried all of our options and none succeeded. Eventually all vertices will come to this point anyway.
    path_pop_vertex(curr, &v, G);
}

int main(int argc, char **argv) {
    int i, j, k, c;
    char buffer[BLOCK];
    char *names[53];
    int numVertices = 1;
    bool unDir = false;
    char *newFile = malloc(256);
    char *newFileOut = malloc(256);
    for (int i = 0; i < argc; i++) { // Handles arguments
        if (strcmp(argv[i], "-h") == 0) {
            fprintf(stdout, "SYNOPSIS\n");
            fprintf(stdout, "	Travelling Salesman Problem using DFS.\n\n");
            fprintf(stdout, "USAGE\n");
            fprintf(stdout, "	./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
            fprintf(stdout, "OPTIONS\n");
            fprintf(stdout, "	-u	Use undirected graph.\n");
            fprintf(stdout, "	-v	Enable verbose printing.\n");
            fprintf(stdout, "	-h	program usage and help.\n");
            fprintf(stdout, "	-i infile	Input containing graph (default: stdin)\n");
            fprintf(stdout, "	-o outfile	Output of computed path (default: stdout)\n");
        }
        if (strcmp(argv[i], "-u") == 0) {
            unDir = true;
        }
        if (strcmp(argv[i], "-i") == 0) {
            strcpy(newFile, argv[i + 1]);
            freopen(newFile, "r", stdin);
        }
        if (strcmp(argv[i], "-o") == 0) {
            strcpy(newFileOut, argv[i + 1]);
            freopen(newFileOut, "w", stdout);
        }
        if (strcmp(argv[i], "-v") == 0) {
            vPrint = true;
        }
    }
    for (int i = 0; i < (numVertices + 1); ++i) { // Reading input
        fgets(buffer, BLOCK, stdin);
        if (i == 0) {
            numVertices = atoi(buffer);
            if (numVertices > 26) {
                exit(1);
            }
        } else {
            names[i - 1] = strdup(buffer);
            strtok(names[i - 1], "\n");
        }
    }
    Graph *graph = graph_create(numVertices, unDir); // Creating graph
    Path *currentPath = path_create();
    Path *shortestPath = path_create();
    while ((c = fscanf(stdin, "%d %d %d\n", &i, &j, &k)) != EOF) {
        if (c != 3) {
            printf("Error: malformed edge.\n");
            exit(1);
            break;
        }
        graph_add_edge(graph, i, j, k);
    }
    // CREATING GRAPH
    //graph_print(graph);
    DFS(graph, 0, currentPath, shortestPath, names, stdout); // Calling DFS
    if (vPrint == false) {
        fprintf(stdout, "Path length: %d\n", path_length(shortestPath));
        path_print(shortestPath, stdout, names);
    }
    fprintf(stdout, "Total recursive calls: %d\n", (calls + 1));

    return 0;
}
