#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int heapSize, n, k;
void siftdown(int *in, int parent) {
	int temp = in[parent], child = parent * 2;
	while (child <= heapSize) {
		if (child < heapSize && in[child] < in[child + 1]) child++;
		if (temp >= in[child]) break;
		in[parent] = in[child];
		parent = child;
		child *= 2;
	}
	in[parent] = temp;
}
int root(int *in) {
	int out = in[1];
	in[1] = in[heapSize];
	heapSize--;
	siftdown(in, 1);
	return out;
}
int* remove(int *in) {
	int i;
	int* out = (int*)malloc((heapSize + 1) * sizeof(int));
	for (i = 1; i <= k; i++)
		out[i] = root(in);
	if (heapSize) {
		for (int j = 1; j <= heapSize; j++, i++)
			out[i] = in[j];
	}
	free(in);
	return out;
}
void makeHeap(int *in) {
	for (int i = floor(heapSize / 2); i; i--)
		siftdown(in, i);
}
int main() {
	printf("enter n and k : ");
	while (scanf("%d %d", &heapSize, &k) != EOF) {
		n = heapSize;
		int *arr = (int*)malloc((heapSize + 1) * sizeof(int));
		printf("enter array : \n");
		for (int i = 1; i <= heapSize; i++)
			scanf("%d", &arr[i]);
		makeHeap(arr);
		arr = remove(arr);
		for (int i = 1; i <= n; i++)
			printf("  %d", arr[i]);
		puts("");
		puts("-----------------");
		printf("enter n and k : ");
	}
}