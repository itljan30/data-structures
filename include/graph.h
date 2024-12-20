#ifndef GRAPH_H
#define GRAPH_H

#include "dyn_arr.h"
#include "hash_map.h"
#include "callbacks.h"

typedef struct {
    void *data;
    DynArr *edges; // DynArr of Edge
} GraphNode;

GraphNode *GraphNode_new(void *data);

void GraphNode_free(GraphNode *node);

void GraphNode_destroy(GraphNode *node, FreeFunc freeFunc);

typedef struct {
    GraphNode *dest;
    float weight;
} Edge;

Edge *Edge_new(GraphNode *dest, float weight);

void Edge_free(Edge *edge);

typedef struct {
    HashMap *nodes; // HashMap of GraphNode
    CompareFunc valueCompare;
    CompareFunc keyCompare;
} Graph;

Graph *Graph_new(size_t keySize, CompareFunc keyCompare);

void Graph_free(Graph *graph);

void Graph_add(Graph *graph, void *key, void *data);

void Graph_remove(Graph *graph, void *key);

void Graph_connect(Graph *graph, void *srcKey, void *destKey, float weight);

void Graph_disconnect(Graph *graph, void *srcKey, void *destKey);

void *Graph_find(Graph *graph, void *key);

int Graph_isConnected(Graph *graph, void *srcKey, void *destKey);

void Graph_destroy(Graph *graph, FreeFunc freeKey, FreeFunc freeValue);

#endif
