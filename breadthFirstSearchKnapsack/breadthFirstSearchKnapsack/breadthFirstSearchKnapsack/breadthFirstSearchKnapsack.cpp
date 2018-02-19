#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
int queueSize, rear, front;
typedef struct node *nodePointer;
typedef struct node{
	int level, profit, weight;
}node;
typedef struct element *elementPointer;
typedef struct element{
	int weight, profit;
	float pw;
}element;
nodePointer *queue;
elementPointer *item;
void initQueue(void) {
	queueSize = 5;
	queue = (struct node**)malloc(5 * sizeof(struct node*));
	rear = -1;
	front = -1;
}
void addQueue(int size) {
	queue = (struct node**)realloc(queue, size * sizeof(struct node*));
	int start = (front + 1) % queueSize;
	if (start == 0) {
		front = size - 1;
	}
	else if(start == 1) {
		rear = queueSize;
	}
	else {
		for (int i = start; i < queueSize; i++) {
			queue[i + queueSize] = queue[i];
		}
		front += queueSize;
	}
	queueSize = size;
}
void enQueue(nodePointer in) {
	rear = (rear + 1) % queueSize;
	if (front == rear)
		addQueue(queueSize * 2);
	queue[rear] = in;
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
nodePointer deQueue(void) {
	if (front == rear)
		return NULL;
	front = (front + 1) % queueSize;
	return queue[front];
}
nodePointer creatNode(int level, int profit, int weight) {
	nodePointer out = (struct node*)malloc(sizeof(struct node));
	out->level = level;
	out->profit = profit;
	out->weight = weight;
	return out;
}
elementPointer creatItem(int weight, int profit) {
	elementPointer out= (struct element*)malloc(sizeof(struct element));
	out->weight = weight;
	out->profit = profit;
	out->pw = profit / weight;
	return out;
}
float bound(nodePointer in, int w, int n) {
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
int knapsack(int n, int w) {
	int maxProfit = 0;
	initQueue();
	nodePointer u, v;
	u = creatNode(0, 0, 0);
	enQueue(u);
	while (front != rear) {
		v = deQueue();
		u = creatNode((v->level + 1), (v->profit + item[v->level]->profit), (v->weight + item[v->level]->weight));
		//printf("--%d  %d  %d  %f\n", u->level, u->profit, u->weight, bound(u, w, n));
		if (u->weight <= w && u->profit > maxProfit)
			maxProfit = u->profit;
		if (bound(u, w, n) > maxProfit)
			enQueue(u);
		else
			free(u);
		v->level += 1;
		//printf("--%d  %d  %d  %f\n", v->level, v->profit, v->weight, bound(v, w, n));
		if (bound(v, w, n) > maxProfit)
			enQueue(v);
		else
			free(v);
	}
	return maxProfit;
}
int main() {
	char str[50];
	int tempWeight, tempProfit, n, bestProfit = 0, w;
	printf("enter n: ");
	scanf("%d", &n);
	printf("enter maxWeight: ");
	scanf("%d", &w);
	item = (struct element**)malloc(n * sizeof(struct element*));
	printf("enter profit and weight : \n");
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &tempProfit, &tempWeight);
		item[i] = creatItem(tempWeight, tempProfit);
	}
	sort(item, n);
	bestProfit = knapsack(n, w);
	printf("%d\n", bestProfit);
	system("PAUSE");
}