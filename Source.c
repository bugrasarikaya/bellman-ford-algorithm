#include <stdio.h> //This program is developed in Visual Studio 2017.
#include <stdlib.h>
#define INFINITY 9999
int report_graph[10][10] =	{ //This graph is from bellman-ford_example_graph_for_program.pdf.
							{ 0, 45, 56, -13, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY },
							{ INFINITY, 0, INFINITY, 27, -12, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY },
							{ INFINITY, INFINITY, 0, 35, INFINITY, -5, INFINITY, INFINITY, INFINITY, INFINITY },
							{ INFINITY, 27, 35, 0, 77, 41, 29, INFINITY, INFINITY, INFINITY },
							{ INFINITY, INFINITY, INFINITY, 77, 0, INFINITY, 50, 38, INFINITY, INFINITY },
							{ INFINITY, INFINITY, INFINITY, 41, INFINITY, 0, 32, INFINITY, 49, INFINITY },
							{ INFINITY, INFINITY, INFINITY, 29, 50, 32, 0, 21, INFINITY, -3},
							{ INFINITY, INFINITY, INFINITY, INFINITY, 38, INFINITY, 21, 0, INFINITY, 76},
							{ INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 49, -9, INFINITY, 0, 11},
							{ INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, INFINITY, 0 } };
int presentation_graph[6][6] =	{ //This graph is taken from our presentation and this link: https://youtu.be/obWXjtg0L64 (Last visited Dec. 6, 2020.)
								{ 0, 10, INFINITY, INFINITY, INFINITY, 8 },
								{ INFINITY, 0, INFINITY, 2, INFINITY, INFINITY },
								{ INFINITY, 1, 0, INFINITY, INFINITY, INFINITY },
								{ INFINITY, INFINITY, -2, 0, INFINITY, INFINITY },
								{ INFINITY, -4, INFINITY, -1, 0, INFINITY },
								{ INFINITY, INFINITY, INFINITY, INFINITY, 1, 0 } };
void minimize_distance( int *graph, int *weight, int path[], int vertices_number, int *negative_cycle) { //Implements the edge relaxation.
	for (int i = 0; i < vertices_number; i++) { //i is for previous vertex.
		for (int j = 0; j < vertices_number; j++) { //j is for next vertex.
			if (weight[i] + *(graph + i * vertices_number + j) < weight[j]) {
				weight[j] = weight[i] + *(graph + i * vertices_number + j);
				if (weight[j] + *(graph + j * vertices_number + i) < weight[i]) { //Detects the negative cycle by verifying edge relaxation reversely.
					*negative_cycle = 1;
					return;
				}
				path[j] = i; //Tracks path. The elemenet of the array path[] is previous vertex, it's index is next vertex.
			}
		}
	}
}
void display_result(int weight[], int path[], int vertices_number, int source_vertex) { //Displays shortest distances and paths.
	printf("Vertex\tDistance from source\tPath\n");
	for (int i = 0; i < vertices_number; i++) {
		printf("%d\t", i);
		if (weight[i] != INFINITY)printf("%d\t\t\t", weight[i]);
		else printf("INFINITE\t\t");
		if (weight[i] != INFINITY) {
			int destination = i;
			if (i != source_vertex) {
				int j = i;
				int *temp = (int *)malloc(vertices_number * sizeof(int));
				int k = 0;
				do {
					j = path[j]; //The elements of the array path[] and their indexes are compatible. With this assignment, exposing the shortest paths is possible.
					temp[k++] = j; //Inserts the path into array temp, reversely.
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
int bellman_ford(int *graph, int vertices_number, int source_vertex) { //Finds shortest distances from source and paths by using the Bellman-Ford Algorithm.
	int *weight = (int *)malloc(vertices_number * sizeof(int));
	int *path = (int *)malloc(vertices_number * sizeof(int));
	int negative_cycle = 0;
	for (int i = 0; i < vertices_number; i++) {
		path[i] = source_vertex;
	}
	for (int i = 0; i < vertices_number; i++) { //Beginning of the Bellman-Ford Algorithm.
		if (i == source_vertex) weight[i] = 0;
		else weight[i] = INFINITY;
	}
	for (int i = 0; i < vertices_number -1; i++) { //Main of bellman_ford function.
		minimize_distance( graph, weight, path, vertices_number, &negative_cycle);
		if (negative_cycle)return -1; //If there is a negative cycle, function belman_ford returns "-1" value for alerting.
	}
	display_result(weight, path, vertices_number, source_vertex);
	return 1;
}
int main() {
	do {
		printf("---Bellman-Ford Algorithm---\n");
		printf("1. Work on the presentation graph.\n");
		printf("2. Work on the report graph.\n");
		printf("3. Enter a new graph.\n");
		printf("4. Clear screen.\n");
		printf("5. Exit.\n");
		printf("Select an option: ");
		int option;
		while (scanf_s("%d", &option) != 1) getchar(); //If user enters characters instead of integers, this getchar() discards characters.
		switch (option) {
		case 1:
			printf("\n");
			if(bellman_ford((int*)presentation_graph, 6, 0)==-1)printf("WARNING: This graph has negative cycle.\n");
			break;
		case 2:
			printf("\n");
			if(bellman_ford((int*)report_graph, 10, 0)==-1)printf("WARNING: This graph has negative cycle.\n");
			break;
		case 3:
			printf("\nEnter the number of vertices: ");
			int vertices_number;
			while (scanf_s("%d", &vertices_number) != 1) getchar(); //If user enters characters instead of integers, this getchar() discards characters.
			int *graph_new = (int *)malloc(vertices_number * vertices_number * sizeof(int));
			printf("Enter the vertices (For infinite value, enter 9999):\n");
			for (int i = 0; i < vertices_number; i++)
				for (int j = 0; j < vertices_number; j++)
					while (scanf_s("%d", (graph_new + i * vertices_number + j)) != 1) getchar();
			printf("Enter the source vertex: ");
			int source_vertex;
			while (scanf_s("%d", &source_vertex) != 1) getchar();
			printf("\n");
			if (bellman_ford((int*)graph_new, vertices_number, source_vertex) == -1){  //If the graph has not any negative cycle, system works successfully.
				printf("WARNING: This graph has negative cycle.\n");}  //If the graph has negative cycle, system alerts user and returns to menu.
			break;
		case 4:
			system("cls");
			break;
		default:
			return 0;
		}
	} while (1);
}
