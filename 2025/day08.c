#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct Node Node;
struct Node {
	int x, y, z;
	Node *next;
};

typedef struct DistanceNode DistanceNode;
struct DistanceNode {
	Node *a;
	Node *b;
	double distance;
};

typedef struct Circuit Circuit;
struct Circuit {
	Node *box;
	Circuit *next;
};

int circuit_exists(){

	return 0;
}

int compare_distance_ascending(const void *a, const void *b) {
	DistanceNode *da = *(DistanceNode * const *)a;
	DistanceNode *db = *(DistanceNode * const *)b;

	if (da->distance < db->distance) return -1;
	if (da->distance > db->distance) return 1;
	return 0;
}

double euclidean_distance(Node * a, Node * b) {
	double distance = 0;
	// sqrt( (a.x - b.x)^2 + (a.y - b.y)^2 + (a.z - b.z)^2 )
	int d1 = a->x - b->x;
	int d2 = a->y - b->y;
	int d3 = a->z - b->z;

	int d1p = d1 * d1;
	int d2p = d2 * d2;
	int d3p = d3 * d3;

	distance = sqrt((double)d1p + (double)d2p + (double)d3p);
	// printf("distance from (%d,%d,%d) to (%d,%d,%d) is %.5f\n", a.x, a.y, a.z, b.x, b.y, b.z, distance);
	return distance;
}

Node *create_node(int x, int y, int z) {
	Node *n = (Node *)malloc(sizeof(Node));
	n->x = x;
	n->y = y;
	n->z = z;
	n->next = NULL;

	return n;
}

DistanceNode *create_distance_node(Node * a, Node * b, double distance) {
	DistanceNode *dn = (DistanceNode *)malloc(sizeof(DistanceNode));
	dn->a = a;
	dn->b = b;
	dn->distance = distance;

	return dn;
}

int main(void) {
	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int x, y, z;
	int n_nodes = 0;
	Node *head = NULL;
	Node *curr = NULL;

	while (fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		sscanf(line, "%d,%d,%d", &x, &y, &z);
		if (curr) {
			curr->next = create_node(x, y, z);
			curr = curr->next;
		} else {
			curr = create_node(x, y, z);
			head = curr;
		}
		++n_nodes;
	}

	double distance;
	double minDistance;
	Node *minNode = head;
	int n_distance_nodes = 0;
	DistanceNode *distanceNodes[n_nodes];

	for (Node *a = head; a != NULL; a = a->next) {
		minDistance = INFINITY;
		for (Node *b = head; b != NULL; b = b->next) {
			if (a == b) continue;

			distance = euclidean_distance(a, b);
			if (distance < minDistance) {
				minDistance = distance;
				minNode = b;
			}
		}

		if (minNode != NULL) {
			//printf("min distance from (%d,%d,%d) to (%d,%d,%d) is %.5f\n", a->x, a->y, a->z, minNode->x, minNode->y, minNode->z, minDistance);
			distanceNodes[n_distance_nodes++] = create_distance_node(a, minNode, minDistance);
		}
	}

	qsort(distanceNodes, n_distance_nodes, sizeof(distanceNodes[0]), compare_distance_ascending);

	int n_circuits = 0;
	for (int i = 0; i < n_distance_nodes; i++) {
		printf("distance: %.5f, a(%d,%d,%d) -> b(%d,%d,%d)\n", distanceNodes[i]->distance, distanceNodes[i]->a->x, distanceNodes[i]->a->y, distanceNodes[i]->a->z, distanceNodes[i]->b->x, distanceNodes[i]->b->y, distanceNodes[i]->b->z);

	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);
	return 0;
}
