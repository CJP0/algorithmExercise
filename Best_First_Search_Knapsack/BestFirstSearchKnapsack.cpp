#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
typedef struct node *nodePointer;
typedef struct node {
	int level, profit, weight;
	float bound;
}node;
typedef struct element *elementPointer;
typedef struct element {
	int weight, profit;
	float pw;
}element;
nodePointer *heap;
elementPointer *item;
int heapSize, heapCapacity, w, n;
void initMaxHeap(int size) {
	heapSize = size - 1;
	heap = (struct node**)malloc(size * sizeof(struct node*));
	heapCapacity = 0;
}
void addMaxHeap(void) {
	heapSize = (heapSize + 1) * 2;
	heap = (struct node**)realloc(heap, heapSize * sizeof(struct node*));
	heapSize--;
}
void push(nodePointer in) {
	if (heapSize == heapCapacity)
		addMaxHeap();
	int i = ++heapCapacity;
	while (i > 1 && in->bound > heap[i / 2]->bound) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = in;
}
nodePointer pop(void) {
	if (heapCapacity == 0)
		return NULL;
	nodePointer out = heap[1], temp;
	int parent = 1, child = 2;
	temp = heap[heapCapacity];
	heapCapacity--;
	while (child <= heapCapacity) {
		if (child < heapCapacity && heap[child]->bound < heap[child + 1]->bound)
			child++;
		if (temp->bound >= heap[child]->bound) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return out;
}
void sort(elementPointer *arr, int n) {
	elementPointer temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j]->pw < arr[j + 1]->pw)
				swap(arr[j], arr[j + 1], temp);
		}
	}
}
float bound(nodePointer in) {
	int j, k, totalWeight;
	float out;
	if (in->weight > w)
		return 0;
	out = in->profit;
	j = in->level;
	totalWeight = in->weight;
	while (j < n && totalWeight + item[j]->weight <= w) {
		totalWeight += item[j]->weight;
		out += item[j]->profit;
		j++;
	}
	if (j < n)
		out += (w - totalWeight)*item[j]->pw;
	return out;
}
elementPointer creatItem(int weight, int profit) {
	elementPointer out = (struct element*)malloc(sizeof(struct element));
	out->weight = weight;
	out->profit = profit;
	out->pw = profit / weight;
	return out;
}
nodePointer creatNode(int level, int profit, int weight) {
	nodePointer out = (struct node*)malloc(sizeof(struct node));
	out->level = level;
	out->profit = profit;
	out->weight = weight;
	out->bound = bound(out);
	return out;
}
int knapsack3(void) {
	int maxProfit = 0;
	initMaxHeap(5);
	nodePointer u, v;
	v = creatNode(0, 0, 0);
	push(v);
	while (heapCapacity) {
		v = pop();
		if (v->bound > maxProfit) {
			u = creatNode(v->level + 1, v->profit + item[v->level]->profit, v->weight + item[v->level]->weight);
			//printf("--%d  %d  %d  %f\n", u->level, u->profit, u->weight, u->bound);
			if (u->weight <= w && u->profit > maxProfit)
				maxProfit = u->profit;
			if (u->bound > maxProfit)
				push(u);
			else
				free(u);
			v->level += 1;
			v->bound = bound(v);
			//printf("--%d  %d  %d  %f\n", v->level, v->profit, v->weight, v->bound);
			if (v->bound > maxProfit)
				push(v);
			else
				free(v);
		}
	}
	return maxProfit;
}
int main() {
	char str[50];
	int tempWeight, tempProfit, bestProfit = 0;
	printf("enter n : ");
	scanf("%d", &n);
	printf("enter maxWeight : ");
	scanf("%d", &w);
	item = (struct element**)malloc(n * sizeof(struct element*));
	printf("enter profit and weight : \n");
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &tempProfit, &tempWeight);
		item[i] = creatItem(tempWeight, tempProfit);
	}
	sort(item, n);
	bestProfit = knapsack3();
	printf("%d\n", bestProfit);
	system("PAUSE");
}