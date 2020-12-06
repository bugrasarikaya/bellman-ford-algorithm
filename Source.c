#include <stdio.h>
#include <stdlib.h>
#define INFINITE 9999
void minimize_distance( int *graph, int *weight, int path[], int vertices_number) { //Implements the edge relaxation.
	for (int i = 0; i < vertices_number; i++) { //i is for previous vertex.
		for (int j = 0; j < vertices_number; j++) { //j is for next vertex.
			if (weight[i] + *(graph + i * vertices_number + j) < weight[j]) {
				weight[j] = weight[i] + *(graph + i * vertices_number + j);
				path[j] = i; //Tracks path.
			}
		}
	}
}
void display_result(int weight[], int path[], int vertices_number, int source_vertex) { //Displays shortest distances and paths.
	printf("Vertex\tDistance from source\tPath\n");
	for (int i = 0; i < vertices_number; i++) {
		printf("%d\t", i);
		if (weight[i] != INFINITE)printf("%d\t\t\t", weight[i]);
		else printf("INFINITE\t\t");
		if (weight[i] != INFINITE) {
			int destination = i;
			if (i != source_vertex) {
				int j = i;
				int *temp = (int *)malloc(vertices_number * sizeof(int));
				int k = 0;
				do {
					j = path[j];
					temp[k++] = j; //Inserts the path into temp array, reversely.
				} while (j != source_vertex);
				for (int i = k - 1; i >= 0; i--) {
					printf("%d-", temp[i]);
				}
			}
			printf("%d", destination);
		}
		else {
			printf("No path.");
		}
		
		printf("\n");
	}
	printf("\n");
}
void bellman_ford(int *graph, int vertices_number, int source_vertex) { //Finds shortest distances from source and paths by using the Bellman-Ford Algorithm.
	int *weight = (int *)malloc(vertices_number * sizeof(int));
	int *path = (int *)malloc(vertices_number * sizeof(int));
	for (int i = 0; i < vertices_number; i++) {
		path[i] = source_vertex;
	}
	for (int i = 0; i < vertices_number; i++) { //Beginning of the Bellman-Ford Algorithm.
		if (i == source_vertex) weight[i] = 0;
		else weight[i] = INFINITE;
	}
	for (int i = 0; i < vertices_number -1; i++) { //Main of bellman_ford function.
		minimize_distance( graph, weight, path, vertices_number);
	}
	display_result(weight, path, vertices_number, source_vertex);
}
int main() {
	int graph_existing[6][6] = //This graph is taken from our presentation and this link: https://youtu.be/obWXjtg0L64 (Last visited Dec. 6, 2020.)
	{ { 0, 10, INFINITE, INFINITE, INFINITE, 8 },
	{ INFINITE, 0, INFINITE, 2, INFINITE, INFINITE },
	{ INFINITE, 1, 0, INFINITE, INFINITE, INFINITE },
	{ INFINITE, INFINITE, -2, 0, INFINITE, INFINITE },
	{ INFINITE, -4, INFINITE, -1, 0, INFINITE },
	{ INFINITE, INFINITE, INFINITE, INFINITE, 1, 0 } };
	do {
		printf("---Bellman-Ford Algorithm---\n");
		printf("1. Work on the existing graph.\n");
		printf("2. Enter a new graph.\n");
		printf("3. Exit.\n");
		printf("Select an option: ");
		int option;
		scanf_s("%d", &option);
		switch (option) {
		case 1:
			printf("\n");
			bellman_ford((int*)graph_existing, 6, 0);
			break;
		case 2:
			printf("\nEnter the number of vertices: ");
			int vertices_number;
			scanf_s("%d", &vertices_number);
			int *graph_new = (int *)malloc(vertices_number * vertices_number * sizeof(int));
			printf("Enter the vertices (For infinite value, enter 9999):\n");
			for (int i = 0; i < vertices_number; i++)
				for (int j = 0; j < vertices_number; j++)
					scanf_s("%d", (graph_new + i * vertices_number + j));
			printf("Enter the source vertex: ");
			int source_vertex;
			scanf_s("%d", &source_vertex);
			printf("\n");
			bellman_ford((int*)graph_new, vertices_number, source_vertex);
			break;
		default:
			return 0;
		}
	} while (1);

}
