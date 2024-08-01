#include <stdio.h>
#include <time.h>

#define MAX_VERTICES 100

struct Edge{
	int from, to, weight;
} edges[MAX_VERTICES];

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

void convert_graph_to_edges(int graph[MAX_VERTICES][MAX_VERTICES], int *edge_count, struct Edge edges);

int main() {
	int graph[MAX_VERTICES][MAX_VERTICES];
	int num_vertices = MAX_VERTICES;

	generate_random_graph(graph, num_vertices);

	int edge_count = 0;
//	convert_graph_to_edges(graph, &edge_count, edges);

	return 0;

}
