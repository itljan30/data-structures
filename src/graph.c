#include "graph.h"
#include "hash_map.h"

#include <stdio.h>

GraphNode *GraphNode_new(void *data, size_t dataSize) {
    GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
    node->data = data;
    node->edges = DynArr_new(dataSize);

    return node;
}

void GraphNode_free(GraphNode *node) {
    DynArr_free(node->edges);
    free(node);
}

Edge *Edge_new(GraphNode *dest, float weight) {
    Edge *edge = (Edge*)malloc(sizeof(Edge));
    edge->dest = dest;
    edge->weight = weight;

    return edge;
}

void Edge_free(Edge *edge) {
    free(edge);
}

Graph *Graph_new(size_t keySize, size_t dataSize, CompareFunc keyCompare, CompareFunc valueCompare) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = HashMap_new(keySize, sizeof(GraphNode), keyCompare);
    graph->dataSize = dataSize;
    graph->valueCompare = valueCompare;

    return graph;
}

void Graph_free(Graph *graph) {
    HashMap_free(graph->nodes);
    free(graph);
}

void Graph_add(Graph *graph, void *key, void *data) {
    HashMap_set(graph->nodes, key, data);
}

void Graph_remove(Graph *graph, void *key) {
    HashMap_remove(graph->nodes, key);
}

void Graph_connect(Graph *graph, void *srcKey, void *destKey, float weight) {
    GraphNode *destNode = (GraphNode*)HashMap_find(graph->nodes, destKey);
    if (destNode == NULL) {
        printf("ERROR: Attempted to connect to data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    Edge *edge = Edge_new(destNode, weight);
    
    GraphNode *srcNode = (GraphNode*)HashMap_find(graph->nodes, srcKey);
    if (destNode == NULL) {
        printf("ERROR: Attempted to connect from data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    DynArr_append(srcNode->edges, edge);
}

void Graph_disconnect(Graph *graph, void *srcKey, void *destKey) {
    GraphNode *destNode = (GraphNode*)HashMap_find(graph->nodes, destKey);
    if (destNode == NULL) {
        printf("ERROR: Attempted to connect to data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    GraphNode *srcNode = (GraphNode*)HashMap_find(graph->nodes, srcKey);
    if (srcNode == NULL) {
        printf("ERROR: Attempted to connect from data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }

    int index = -1;
    for (int i = 0; i < DynArr_len(srcNode->edges); i++) {
        Edge *currentEdge = (Edge*)DynArr_at(srcNode->edges, i);
        if (currentEdge->dest == destNode) {
            index = i;
            Edge_free(currentEdge);
            break;
        }
    }
    if (index == -1) {
        printf("ERROR: Attempted to disconnect data that wasn't connected\n");
        exit(EXIT_FAILURE);
    }
    DynArr_remove(srcNode->edges, index);
}
