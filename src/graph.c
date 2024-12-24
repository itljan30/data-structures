#include "graph.h"
#include "hash_map.h"
#include "dyn_arr.h"
#include "linked_list.h"
#include "iterator.h"

#include <stdio.h>

static GraphNode *Graph_findNode(Graph *graph, void *key) {
    return (GraphNode*)HashMap_find(graph->nodes, key);
}

static DynArr *recursiveDFS(Graph *graph, DynArr *finalPath, DynArr *curPath, void *srcKey, 
                            void *destKey, size_t depth, size_t maxDepth, bool exhaustive) {
    if (DynArr_contains(curPath, srcKey, graph->keyCompare)) {
        return NULL;
    }

    if (maxDepth != 0 && depth >= maxDepth) {
        return NULL;
    }

    DynArr_append(curPath, srcKey);

    if (srcKey == destKey) {
        if (!exhaustive) {
            return curPath;
        }
        DynArr_append(finalPath, curPath);
        return NULL;
    }

    GraphNode *parent = Graph_findNode(graph, srcKey);
    Iterator *neighbors = DynArr_iter(parent->edges);
    while (Iterator_hasNext(neighbors)) {
        Edge *neighbor = Iterator_next(neighbors);
        DynArr *nextPath = DynArr_clone(curPath);
        nextPath = recursiveDFS(graph, finalPath, nextPath, neighbor->dest, destKey, depth + 1, maxDepth, exhaustive);
        if (!exhaustive && nextPath != NULL) {
            return nextPath;
        }
        DynArr_free(nextPath);
    }

    DynArr_free(curPath);
    if (!exhaustive) {
        return NULL;
    }
    else {
        return finalPath;
    }
}


static int Edge_compare(void *edge1, void *edge2) {
    Edge *e1 = (Edge*)edge1;
    Edge *e2 = (Edge*)edge2;

    return e1->dest - e2->dest;
}

GraphNode *GraphNode_new(void *data) {
    GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
    node->data = data;
    node->edges = DynArr_new();

    return node;
}

void GraphNode_free(GraphNode *node) {
    GraphNode_destroy(node, NULL);
}

void GraphNode_destroy(GraphNode *node, FreeFunc freeFunc) {
    if (freeFunc != NULL) {
        freeFunc(node->data);
    }
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

Graph *Graph_new(size_t keySize, CompareFunc keyCompare) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nodes = HashMap_new(keySize, keyCompare);

    return graph;
}

void Graph_add(Graph *graph, void *key, void *data) {
    GraphNode *node = GraphNode_new(data);
    HashMap_set(graph->nodes, key, node);
}

void Graph_remove(Graph *graph, void *key) {
    GraphNode *node = HashMap_find(graph->nodes, key);
    for (int i = 0; i < node->edges->length; i++) {
        Edge_free(DynArr_at(node->edges, i));
    }
    GraphNode_free(node);
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
    if (srcNode == NULL) {
        printf("ERROR: Attempted to connect from data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    if (DynArr_contains(srcNode->edges, edge, Edge_compare) == true) {
        printf("ERROR: Attempted to connect data that is already connected\n");
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

void *Graph_find(Graph *graph, void *key) {
    GraphNode *node = (GraphNode*)HashMap_find(graph->nodes, key);
    void *data = node->data;
    return data;
}

int Graph_isConnected(Graph *graph, void *srcKey, void *destKey) {
    GraphNode *srcNode = HashMap_find(graph->nodes, srcKey);
    if (srcNode == NULL) {
        printf("ERROR: Source key does not exist in graph\n");
        exit(EXIT_FAILURE);
    }
    GraphNode *destNode = HashMap_find(graph->nodes, destKey);
    if (destNode == NULL) {
        printf("ERROR: Destination key does not exist in graph\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < DynArr_len(srcNode->edges); i++) {
        Edge *currentEdge = DynArr_at(srcNode->edges, i);
        if (currentEdge->dest == destNode) {
            return true;
        }
    }
    return false;
}

void Graph_free(Graph *graph) {
    Graph_destroy(graph, NULL, NULL);
}

void Graph_destroy(Graph *graph, FreeFunc freeKey, FreeFunc freeValue) {
    DynArr *map = graph->nodes->map;
    for (int i = 0; i < map->capacity; i++) {
        if (DynArr_at(map, i) == NULL) {
            continue;
        }
        LinkedList *list = DynArr_at(map, i);
        ListNode *currentNode = list->firstNode;
        while (currentNode != NULL) {
            ListNode *nextNode = currentNode->nextNode;

            KeyValue *pair = currentNode->data;
            GraphNode *node = pair->value;
            DynArr *arr = node->edges;

            for (int i = 0; i < arr->length; i++) {
                Edge_free(DynArr_at(arr, i));
            }

            GraphNode_destroy(node, freeValue);
            currentNode = nextNode;
        }
    }

    HashMap_destroy(graph->nodes, freeKey, NULL);
    free(graph);
}

void *Graph_next(Iterator *iter) {
    GraphNode *node = HashMap_next(iter);
    return node->data;
}

Iterator *Graph_iter(Graph *graph) {
    Iterator *iter = HashMap_iter(graph->nodes);
    iter->next = Graph_next;
    return iter;
}

DynArr *Graph_getVertices(Graph *graph) {
    DynArr *vertices = DynArr_new();
    Iterator *iter = Graph_iter(graph);
    while (Iterator_hasNext(iter)) {
        void *vertex = Iterator_next(iter);
        DynArr_append(vertices, vertex);
    }
    return vertices;
}

DynArr *Graph_DFS(Graph *graph, void *srcKey, void *destKey, size_t maxDepth) {
    return recursiveDFS(graph, DynArr_new(), DynArr_new(), srcKey, destKey, 0, maxDepth, false);
}

DynArr *Graph_DFSAll(Graph *graph, void *srcKey, void *destKey, size_t maxDepth) {
    DynArr *paths = recursiveDFS(graph, DynArr_new(), DynArr_new(), srcKey, destKey, 0, maxDepth, true);
    if (DynArr_len(paths) == 0) {
        return NULL;
    }
    return paths;
}

DynArr *Graph_BFS(Graph *graph, void *srcKey, void *destKey, size_t maxDepth) {
}
