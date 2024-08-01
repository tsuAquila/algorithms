#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

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

void prims_mst(int graph[MAX_VERTICES][MAX_VERTICES], int num_vertices) {
	int smallest_vertex = INT_MAX;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {

		}
	}
}


int main() {
	
	int graph[MAX_VERTICES][MAX_VERTICES];
	int num_vertices = MAX_VERTICES;

	generate_random_graph(graph, num_vertices);

		

	return 0;
}
