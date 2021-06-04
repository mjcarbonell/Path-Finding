#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices; // NUM OF VERTICES.
    bool undirected; // UNDIRECTED GRAPH?
    bool visited[26]; // WHERE HAVE WE GONE?
    uint32_t matrix[26][26]; // ADJACENCY MATRIX
};

Graph *graph_create(uint32_t vertices,
    bool
        undirected) { // initalizing all vertices w/ edges of 0 and specified length of vertices and whether it is directed
    Graph *g = (Graph *) malloc(sizeof(Graph));
    if (g) {
        g->vertices = vertices;
        g->undirected = undirected;
        for (uint32_t i = 0; i < 26; ++i) {
            g->visited[i] = false;
            for (uint32_t j = 0; j < vertices; ++j) {
                g->matrix[i][j] = 0;
            }
        }
    }
    return g;
}
void graph_delete(Graph **G) { // Freeing memory
    free(((*G)->matrix));
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return (G->vertices);
}
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j,
    uint32_t
        k) { // Setting the value at specified coords to whichever edge it is. Must be within bounds.
    if (i > (G->vertices) || j > (G->vertices)) { // CHECKING IF WITHIN BOUNDS
        return false;
    }
    if (i < 0 || j < 0) {
        return false;
    }
    if ((G->undirected) == true) {
        G->matrix[i][j] = k;
        G->matrix[j][i] = k;
        return true;
    }
    G->matrix[i][j] = k;
    return true;
}
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i > (G->vertices) || j > (G->vertices)) { // CHECKING IF WITHIN BOUNDS
        return false;
    }
    if (i < 0 || j < 0) {
        return false;
    }
    if ((G->matrix[i][j]) > 0) { //  Must be greater than 0 to count as an edge
        return true;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i > (G->vertices) || j > (G->vertices)) { // CHECKING IF WITHIN BOUNDS
        return false;
    }
    if (i < 0 || j < 0) {
        return false;
    }
    return (G->matrix[i][j]);
}

bool graph_visited(Graph *G, uint32_t v) {
    return (G->visited[v]);
}

void graph_mark_visited(Graph *G, uint32_t v) { // Setting value to true
    G->visited[v] = true;
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v) { // Setting value to false
    G->visited[v] = false;
    return;
}

void graph_print(Graph *G) { // Printing contents of graph. newline at each row.
    for (uint32_t i = 0; i < (G->vertices); ++i) {
        printf("\n");

        for (uint32_t j = 0; j < (G->vertices); ++j) {
            printf("%d	", G->matrix[i][j]);
        }
    }
    printf("\n");
    return;
}
