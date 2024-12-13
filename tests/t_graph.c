#include "graph.h"
#include "test_struct.h"

#include <assert.h>

void add() {
    Graph *graph = Graph_new(sizeof(int), sizeof(char), NULL, NULL);

    int keyBuffer[100];
    char valueBuffer[100];
    for (int i = 0; i < 100; i++) {
        keyBuffer[i] = i;
        valueBuffer[i] = (char)i;
    }

    for (int i = 0; i < 100; i++) {
        Graph_add(graph, &keyBuffer[i], &valueBuffer[i]);
    }
    for (int i = 0; i < 100; i++) {
        char *value = (char*)Graph_find(graph, &keyBuffer[i]);
        assert(*value == valueBuffer[i]);
    }

    Graph_free(graph);
}

void connect() {
    Graph *graph = Graph_new(sizeof(int), sizeof(char), NULL, NULL);

    int keyBuffer[10000];
    char valueBuffer[10000];
    for (int i = 0; i < 10000; i++) {
        keyBuffer[i] = i;
        valueBuffer[i] = (char)i;
    }

    for (int i = 0; i < 10000; i++) {
        Graph_add(graph, &keyBuffer[i], &valueBuffer[i]);
    }
    for (int i = 0; i < 10000; i++) {
        char *value = (char*)Graph_find(graph, &keyBuffer[i]);
        assert(*value == valueBuffer[i]);
    }

    for (int i = 0; i < 9999; i++) {
        Graph_connect(graph, &keyBuffer[i], &keyBuffer[i + 1], 1.5);
    }
    for (int i = 0; i < 9999; i++) {
        int connected = Graph_isConnected(graph, &keyBuffer[i], &keyBuffer[i + 1]);
        assert(connected == true);
    }
    Graph_free(graph);
}
void disconnect() {
    Graph *graph = Graph_new(sizeof(int), sizeof(char), NULL, NULL);

    int keyBuffer[10000];
    char valueBuffer[10000];
    for (int i = 0; i < 10000; i++) {
        keyBuffer[i] = i;
        valueBuffer[i] = (char)i;
    }

    for (int i = 0; i < 10000; i++) {
        Graph_add(graph, &keyBuffer[i], &valueBuffer[i]);
    }
    for (int i = 0; i < 10000; i++) {
        char *value = (char*)Graph_find(graph, &keyBuffer[i]);
        assert(*value == valueBuffer[i]);
    }

    for (int i = 0; i < 9999; i++) {
        Graph_connect(graph, &keyBuffer[i], &keyBuffer[i + 1], 1.5);
    }
    for (int i = 0; i < 9999; i++) {
        Graph_disconnect(graph, &keyBuffer[i], &keyBuffer[i + 1]);
    }
    for (int i = 0; i < 9999; i++) {
        int connected = Graph_isConnected(graph, &keyBuffer[i], &keyBuffer[i + 1]);
        assert(connected == false);
    }
    Graph_free(graph);
}

void destroy() {
    Graph *graph = Graph_new(sizeof(int), sizeof(char), NULL, NULL);

    int keyBuffer[10000];
    for (int i = 0; i < 10000; i++) {
        keyBuffer[i] = i;
    }

    for (int i = 0; i < 10000; i++) {
        Graph_add(graph, &keyBuffer[i], TestStruct_new());
    }

    for (int i = 0; i < 9999; i++) {
        Graph_connect(graph, &keyBuffer[i], &keyBuffer[i + 1], 1.5);
    }

    Graph_destroy(graph, NULL, TestStruct_free);
}

int main () {
    add();
    connect();
    disconnect();
    destroy();
}
