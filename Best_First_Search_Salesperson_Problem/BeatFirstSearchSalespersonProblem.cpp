#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
int n, **w, heapSize, heapCapacity;
typedef struct node *nodePointer;
typedef struct node {
	int level, bound, length, *passOrder, *yetPassSet;
};
nodePointer *heap;
void initMiniHeap(int size) {
	heapSize = size - 1;
	heap = (struct node**)malloc(size * sizeof(struct node*));
	heapCapacity = 0;
}
void addMiniHeap(void) {
	heapSize = (heapSize + 1) * 2;
	heap = (struct node**)realloc(heap, heapSize * sizeof(struct node*));
	heapSize--;
}
void push(nodePointer in) {
	if (heapSize == heapCapacity)
		addMiniHeap();
	int i = ++heapCapacity;
	while (i > 1 && in->bound < heap[i / 2]->bound) {
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
		if (child < heapCapacity && heap[child]->bound > heap[child + 1]->bound)
			child++;
		if (temp->bound <= heap[child]->bound) break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return out;
}
int minimum(nodePointer in, int row, int star) {
	int mini = 10000, len = n - in->level - 1;
	for (int i = star; i <= len; i++) {
		if (w[row][in->yetPassSet[i]] && w[row][in->yetPassSet[i]] < mini)
			mini = w[row][in->yetPassSet[i]];
	}
	return mini;
}
int bound(nodePointer in) {
	int out = in->length, len = n - in->level;
	out += minimum(in, in->passOrder[in->level], 1);
	for (int i = 1; i < len; i++) {
		out += minimum(in, in->yetPassSet[i], 0);
	}
	return out;
}
void deleVertexFromYetPassSet(nodePointer in, int ver) {
	int temp, len = n - in->level;
	for (int i = 1; i <= len; i++) {
		if (in->yetPassSet[i] == ver) {
			swap(in->yetPassSet[i], in->yetPassSet[len], temp);
			break;
		}
	}
}
void insertVertexToPassOrder(nodePointer in, int ver) {
	in->passOrder[in->level] = ver;
	deleVertexFromYetPassSet(in, ver);
	in->bound = bound(in);
}
int length(nodePointer in) {
	int out = in->length, temp = in->yetPassSet[1];
	out += w[in->passOrder[in->level]][temp];
	out += w[temp][0];
	return out;
}
nodePointer creatNode(int level, nodePointer in) {
	nodePointer out = (struct node*)malloc(sizeof(struct node));
	out->passOrder = (int*)malloc(n * sizeof(int));
	out->yetPassSet = (int*)malloc(n * sizeof(int));
	if (in) {
		out->length = in->length;
		memcpy(out->passOrder, in->passOrder, sizeof(int)*n);
		memcpy(out->yetPassSet, in->yetPassSet, sizeof(int)*n);
	}
	out->level = level;
	return out;
}
void printNode(nodePointer in) {
	puts("---------------");
	printf("Level : %d\n", in->level);
	printf("Length : %d \n", in->length);
	printf("bound : %d\n", in->bound);
	for (int i = 0; i < n; i++)
		printf(" %d", in->passOrder[i]);
	puts("");
	for (int i = 0; i < n; i++)
		printf(" %d", in->yetPassSet[i]);
	puts("");

}
nodePointer travel2() {
	nodePointer u, v, out;
	int len, miniLength = 10000;
	initMiniHeap(5);
	out = creatNode(0, NULL);
	out->passOrder[0] = 0;
	for (int i = 0; i < n; i++) {
		out->yetPassSet[i] = i;
	}
	out->length = 0;
	out->bound = bound(out);
	//printNode(out);
	push(out);
	while (heapCapacity) {
		v = pop();
		if (v->bound < miniLength) {
			len = n - v->level - 1;
			for (int i = 1; i <= len; i++) {
				u = creatNode(v->level + 1, v);
				u->length += w[v->passOrder[v->level]][v->yetPassSet[i]];
				insertVertexToPassOrder(u, v->yetPassSet[i]);
				//printNode(u);
				//puts("#####  v");
				//printNode(v);
				if (u->level == (n - 2) && length(u)<miniLength) {
					miniLength = length(u);
					out = u;
				}
				else {
					if (u->bound < miniLength)
						push(u);
					else
						free(u);
				}
			}
		}
		free(v);
	}
	out->passOrder[out->level + 1] = out->yetPassSet[1];
	out->length = miniLength;
	return out;
}
int main() {
	nodePointer sol;
	printf("enter n : ");
	scanf("%d", &n);
	w = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		w[i] = (int*)malloc(n * sizeof(int));
	printf("enter adjacency matrix : \n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &w[i][j]);
	}
	sol = travel2();
	puts("-------------\n");
	printf("Length : %d\n", sol->length);
	for (int i = 0; i < n; i++)
		printf(" %d", sol->passOrder[i]);
	printf(" 0\n");
	system("PAUSE");
}