#include <stdio.h>
#include <limits.h>

#define MAX 1000
#define INF INT_MAX

void add_edge(int graph[MAX][MAX], int start, int end) {
    int weight;
    printf("Enter the weight of the edge\n");
    scanf("%d", &weight);
    graph[start][end] = weight;
}

void displayGraph(int graph[MAX][MAX], int vertices) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void delete_edge(int graph[MAX][MAX], int v1, int v2) {
    graph[v1][v2] = 0;
}

void bfs(int graph[MAX][MAX], int vertices, int startVertex) {
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    queue[rear++] = startVertex;
    visited[startVertex] = 1;

    printf("BFS Traversal: ");

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] != 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void dfs_util(int graph[MAX][MAX], int vertices, int vertex, int visited[MAX]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < vertices; i++) {
        if (graph[vertex][i] != 0 && !visited[i]) {
            dfs_util(graph, vertices, i, visited);
        }
    }
}

void dfs(int graph[MAX][MAX], int vertices, int startVertex) {
    int visited[MAX] = {0};
    printf("DFS Traversal: ");
    dfs_util(graph, vertices, startVertex, visited);
    printf("\n");
}

int minDistance(int dist[], int visited[], int vertices) {
    int min = INF, minIndex;

    for (int v = 0; v < vertices; v++) {
        if (visited[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void dijkstra(int graph[MAX][MAX], int vertices, int startVertex) {
    int dist[MAX], visited[MAX] = {0};

    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
    }
    dist[startVertex] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INF) {
            printf("%d \t\t INF\n", i);
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}

int main() {
    int vertices, edges, choice;
    int graph[MAX][MAX] = {0};

    printf("Enter the number of nodes\n");
    scanf("%d", &vertices);

    printf("Enter the number of edges\n");
    scanf("%d", &edges);

    if (edges < 0 || edges > vertices * (vertices - 1)) {
        printf("Invalid number of edges\n");
        return 1;
    }

    for (int i = 0; i < edges; i++) {
        int start, end;
        printf("Enter edge %d (start end): ", i + 1);
        scanf("%d %d", &start, &end);

        if (start < 0 || start >= vertices || end < 0 || end >= vertices) {
            printf("Invalid vertices. Try again.\n");
            i--;
            continue;
        }

        add_edge(graph, start, end);
    }

    while (1) {
        printf("\n\nEnter the operation you would like to perform on the graph\n");
        printf("To add edge, press 1\n");
        printf("To delete edge, press 2\n");
        printf("To display graph, press 3\n");
        printf("To perform BFS, press 4\n");
        printf("To perform DFS, press 5\n");
        printf("To perform Dijkstra's Algorithm, press 6\n");
        printf("To exit, press 7\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int start, end;
                printf("Enter the start and end vertices for the edge\n");
                scanf("%d %d", &start, &end);

                if (start < 0 || start >= vertices || end < 0 || end >= vertices) {
                    printf("Invalid vertices. Try again.\n");
                    continue;
                }

                add_edge(graph, start, end);
                break;
            }
            case 2: {
                int v1, v2;
                printf("Enter the vertices of the edge to delete\n");
                scanf("%d %d", &v1, &v2);

                if (v1 < 0 || v1 >= vertices || v2 < 0 || v2 >= vertices) {
                    printf("Invalid vertices. Try again.\n");
                    continue;
                }

                delete_edge(graph, v1, v2);
                break;
            }
            case 3:
                displayGraph(graph, vertices);
                break;
            case 4: {
                int startVertex;
                printf("Enter the start vertex for BFS\n");
                scanf("%d", &startVertex);

                if (startVertex < 0 || startVertex >= vertices) {
                    printf("Invalid start vertex. Try again.\n");
                    continue;
                }

                bfs(graph, vertices, startVertex);
                break;
            }
            case 5: {
                int startVertex;
                printf("Enter the start vertex for DFS\n");
                scanf("%d", &startVertex);

                if (startVertex < 0 || startVertex >= vertices) {
                    printf("Invalid start vertex. Try again.\n");
                    continue;
                }

                dfs(graph, vertices, startVertex);
                break;
            }
            case 6: {
                int startVertex;
                printf("Enter the start vertex for Dijkstra's Algorithm\n");
                scanf("%d", &startVertex);

                if (startVertex < 0 || startVertex >= vertices) {
                    printf("Invalid start vertex. Try again.\n");
                    continue;
                }

                dijkstra(graph, vertices, startVertex);
                break;
            }
            case 7:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
