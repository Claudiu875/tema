/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// -------------------- Utils --------------------

Node* create_node(int v) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

Graph* create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(int nr_vertices, int nr_edges, Graph *graph) {
    int src, dest;
    printf("Adauga %d muchii (nodurile de la 0 la %d):\n", nr_edges, nr_vertices - 1);
    for (int i = 0; i < nr_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void wipe_visited_list(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// -------------------- BFS Utilities --------------------

int is_empty(Node *queue) {
    return queue == NULL;
}

void enqueue(Node **queue, int data) {
    Node *new_node = create_node(data);

    if (*queue == NULL) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(Node **queue) {
    if (*queue == NULL) return -1;

    int data = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);

    return data;
}

// -------------------- DFS --------------------

void DFS(Graph *graph, int vertex) {
    Node *adj_list = graph->adjacency_lists[vertex];
    Node *temp = adj_list;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;

        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }

        temp = temp->next;
    }
}

// -------------------- BFS --------------------

void BFS(Graph *graph, int start_vertex) {
    Node *queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        Node *temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

// -------------------- Main --------------------

int main() {
    int nr_vertices, nr_edges;
    int start_vertex;

    printf("Cate noduri are graful? ");
    scanf("%d", &nr_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &nr_edges);

    Graph *graph = create_graph(nr_vertices);

    insert_edges(nr_vertices, nr_edges, graph);

    printf("De unde plecam in DFS? ");
    scanf("%d", &start_vertex);

    printf("Parcurgere DFS: ");
    DFS(graph, start_vertex);
    printf("\n");

    wipe_visited_list(graph);

    printf("De unde plecam in BFS? ");
    scanf("%d", &start_vertex);

    printf("Parcurgere BFS: ");
    BFS(graph, start_vertex);
    printf("\n");

    return 0;
}