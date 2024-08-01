#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VERTICES 100

int find_min_distance_vertex(int distances[], int visited[], int num_vertices) {
  int min_distance = INT_MAX, min_index = -1;

  for (int v = 0; v < num_vertices; v++) {
    if (!visited[v] && distances[v] < min_distance) {
      min_distance = distances[v];
      min_index = v;
    }
  }

  return min_index;
}

void print_solution(int num_vertices, int distances[], int parents[],
                    int source_vertex) {
  printf("\n\nVertex\tDistance from Source %d\tPath\n", source_vertex);
  for (int v = 0; v < num_vertices; v++) {
    if (distances[v] == INT_MAX) {
      printf("%d\t\t-\t\t", v);
      printf("UNREACHABLE");
    } else {
      printf("%d\t\t%d\t\t", v, distances[v]);
      // print the path
      int current = v;
      while (current != source_vertex) {
        printf("%d <- ", current);
        current = parents[current];
      }
      printf("%d", source_vertex);
    }
    printf("\n");
  }
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int source_vertex,
              int num_vertices) {
  int *distances = (int *)malloc(sizeof(int) * num_vertices);
  int *parents = (int *)malloc(sizeof(int) * num_vertices);
  int *visited = (int *)malloc(sizeof(int) * num_vertices);

  // initialization
  for (int v = 0; v < num_vertices; v++) {
    distances[v] = INT_MAX;
    parents[v] = -1;
    visited[v] = 0;
  }

  distances[source_vertex] = 0;

  // main loop
  for (int iteration = 0; iteration < num_vertices - 1; iteration++) {
    int u = find_min_distance_vertex(distances, visited, num_vertices);
    if (u == -1) {
      break;  // all reachable vertices have been processed
    }
    visited[u] = 1;

    // update distances of adjacent vertices
    for (int v = 0; v < num_vertices; v++) {
      if (!visited[v] && graph[u][v] && distances[u] != INT_MAX &&
          distances[u] + graph[u][v] < distances[v]) {
        distances[v] = distances[u] + graph[u][v];
        parents[v] = u;
      }
    }
  }

  print_solution(num_vertices, distances, parents, source_vertex);

  free(distances);
  free(parents);
  free(visited);
}

void generate_random_graph(int graph[MAX_VERTICES][MAX_VERTICES],
                           int num_vertices) {
  srand(time(NULL));  // random num gen
  for (int i = 0; i < num_vertices; i++) {
    for (int j = i; j < num_vertices; j++) {
      if (i == j) {
        graph[i][j] = 0;  // no self loops
      } else {
        if (rand() % 50 ==
            0) {  // 100/50 percent chance of pair of vertices being connected
          int weight = 1 + rand() % 10;  // Random weight between 1 and 10
          graph[i][j] = weight;
          graph[j][i] = weight;  // Undirected graph
        } else {
          graph[i][j] = 0;
          graph[j][i] = 0;
        }
      }
    }
  }
}

int main() {
  int graph[MAX_VERTICES][MAX_VERTICES];
  int num_vertices = MAX_VERTICES;

  generate_random_graph(graph, num_vertices);

  printf("Running Dijkstra's algorithm from vertex 0...");
  dijkstra(graph, 0, num_vertices);

  return 0;
}
