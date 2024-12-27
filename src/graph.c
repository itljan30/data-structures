#include "graph.h"
#include "hash_map.h"
#include "dyn_arr.h"
#include "linked_list.h"
#include "iterator.h"

#include <float.h>
#include <stdio.h>

static DynArr *parsePath(Graph *graph, DynArr *vertices, DynArr *previous, void *destKey) {
    DynArr *path = DynArr_new();
    DynArr_append(path, destKey);

    int index = DynArr_index(vertices, destKey, graph->keyCompare);
    while (DynArr_at(previous, index) != NULL) {
        void *curKey = DynArr_at(previous, index);
        DynArr_append(path, curKey);
        index = DynArr_index(vertices, curKey, graph->keyCompare);
    }
    
    if (DynArr_len(path) == 1) {
        DynArr_free(path);
        return NULL;
    }

    DynArr *reversedPath = DynArr_new();

    for (int i = DynArr_len(path) - 1; i >= 0; i--) {
        DynArr_append(reversedPath, DynArr_at(path, i));
    }
    DynArr_free(path);

    return reversedPath;
}

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
    if (HashMap_find(graph->nodes, destKey) == NULL) {
        printf("ERROR: Attempted to connect to data that doesn't exist\n");
        exit(EXIT_FAILURE);
    }
    Edge *edge = Edge_new(destKey, weight);
    
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
    if (HashMap_find(graph->nodes, destKey) == NULL) {
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
        if (currentEdge->dest == destKey) {
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
    if (HashMap_find(graph->nodes, destKey) == NULL) {
        printf("ERROR: Destination key does not exist in graph\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < DynArr_len(srcNode->edges); i++) {
        Edge *currentEdge = DynArr_at(srcNode->edges, i);
        if (currentEdge->dest == destKey) {
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

void *Graph_nextData(Iterator *iter) {
    GraphNode *node = HashMap_nextData(iter);
    return node->data;
}

Iterator *Graph_iterData(Graph *graph) {
    Iterator *iter = HashMap_iterData(graph->nodes);
    iter->next = Graph_nextData;
    return iter;
}

void *Graph_nextKey(Iterator *iter) {
    return HashMap_nextKey(iter);
}

Iterator *Graph_iterKey(Graph *graph) {
    Iterator *iter = HashMap_iterKey(graph->nodes);
    iter->next = Graph_nextKey;
    return iter;
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
    DynArr *vertices = DynArr_new();
    DynArr *distance = DynArr_new();
    DynArr *previous = DynArr_new();
    DynArr *queue = DynArr_new();

    Iterator *graphIter = Graph_iterKey(graph);

    while (Iterator_hasNext(graphIter)) {
        void *key = Iterator_next(graphIter);

        DynArr_append(vertices, key);

        if (graph->keyCompare(key, srcKey) == 0) {
            float *zero = malloc(sizeof(float));
            *zero = 0;
            DynArr_append(distance, zero);
            DynArr_append(queue, key);
        }
        else {
            float *inf = malloc(sizeof(float));
            *inf = FLT_MAX;
            DynArr_append(distance, inf);
        }

        DynArr_append(previous, NULL);
    }
    Iterator_free(graphIter);

    while (DynArr_len(queue) != 0) {
        void *closestVertexKey = NULL;
        float closestDistance = FLT_MAX;
        
        for (int i = 0; i < DynArr_len(queue); i++) {
            void *currentVertex = DynArr_at(queue, i);

            int index = DynArr_index(vertices, currentVertex, graph->keyCompare);
            float curDistance = *(float*)DynArr_at(distance, index);
            if (curDistance < closestDistance) {
                closestDistance = curDistance;
                closestVertexKey = currentVertex;
            }
        }

        int removalIndex = DynArr_index(queue, closestVertexKey, graph->keyCompare);
        DynArr_remove(queue, removalIndex);

        if (maxDepth != 0 && closestDistance >= (float)maxDepth) {
            // do some freeing then return NULL
            break;
        }

        if (graph->keyCompare(closestVertexKey, destKey) == 0) {
            break;
        }

        int vertIndex = DynArr_index(vertices, closestVertexKey, graph->keyCompare);
        float curDist = *(float*)DynArr_at(distance, vertIndex);

        GraphNode *curNode = HashMap_find(graph->nodes, closestVertexKey);
        Iterator *neighbors = DynArr_iter(curNode->edges);

        while (Iterator_hasNext(neighbors)) {
            Edge *edge = Iterator_next(neighbors);
            float weight = edge->weight;
            void *neighborKey = edge->dest;

            float alt = curDist + weight;

            int index = DynArr_index(vertices, neighborKey, graph->keyCompare);
            if (alt < *(float*)DynArr_at(distance, index)) {
                if (!DynArr_contains(queue, neighborKey, graph->keyCompare)) {
                    DynArr_append(queue, neighborKey);
                }

                free(DynArr_at(distance, index));
                float *num = malloc(sizeof(float));
                *num = alt;
                DynArr_set(distance, index, num);

                DynArr_set(previous, index, closestVertexKey);
            }
        }
    }

    DynArr *path = parsePath(graph, vertices, previous, destKey);

    DynArr_free(queue);
    DynArr_free(vertices);
    DynArr_free(previous);
    DynArr_destroy(distance, free);

    return path;
}
