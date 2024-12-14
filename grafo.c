#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists; //array de listas
};

struct Node* createNode(int vertex) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct Node*));

    for(int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

//ADICIONA ARESTA NÃO DIRECIONADA ENTRE DOIS VÉRTICES
void addEdge(struct Graph* graph, int src, int dest) {
    //Adiciona a aresta de src para dest
    struct Node* newNode = createNode(dest); //cria o nó dest
    newNode->next = graph->adjLists[src]; //aponta o nó dest para a lista de adjacencia de src
    graph->adjLists[src] = newNode; //aponta a lista de adjacencia de src para o nó dest

    //Adiciona a aresta de dest para src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    for(int i = 0; i < graph->numVertices; i++) {
        struct Node* temp = graph->adjLists[i];

        printf("Vértice %d: ", i);
        while(temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    struct Graph* graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 3, 4);

    printGraph(graph);
    
    return 0;
}