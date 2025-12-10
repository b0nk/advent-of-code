#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
	int left;
	int right;
} PageOrder;

typedef struct PageOrderNode PageOrderNode;
struct PageOrderNode{
	PageOrder page_order;
	PageOrderNode* next;
};

typedef struct PageNode PageNode;
struct PageNode{
	int page;
	PageNode* next;
};

typedef struct PageToProduce PageToProduce;
struct PageToProduce{
	PageNode pages;
	PageToProduce* next;
};

PageOrder create_page_order(int l, int r){
	PageOrder po;
	po.left = l;
	po.right = r;
	return po;
}

PageOrderNode* create_page_order_node(int l, int r){
	PageOrderNode* pon = malloc(sizeof(PageOrderNode));
	pon->page_order = create_page_order(l, r);
	return pon;
}

int main(void){

	char line[BUFSIZ];
	int part1 = 0;
	int part2 = 0;
	int ordering = 1;
	PageOrderNode* page_order_head = NULL;
	PageNode* page_node_head = NULL;
	int* left = malloc(sizeof(int));
	int* right = malloc(sizeof(int));
	int* page = malloc(sizeof(int));

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(ordering){
			if(sscanf(line, "%d|%d", left, right) == -1){
				ordering = 0;
			} else {
				// create page order
			}
		} else {

		}
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
