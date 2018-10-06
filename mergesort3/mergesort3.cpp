#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
int mini(int a, int b) {
	return a < b ? a : b;
}
void printArr(int *in, int n) {
	for (int i = 0; i < n; i++)
		printf("  %d", in[i]);
	puts("");
}
void merge3(int low, int mid, int high, int *s, int *u) {
	int i = low, j = mid + 1, k = low;
	while (i <= mid && j < high) {
		if (s[i] < s[j]) {
			u[k] = s[i];
			i++;
		}
		else {
			u[k] = s[j];
			j++;
		}
		k++;
	}
	while (i <= mid) {
		u[k] = s[i];
		i++;
		k++;
	}
	while (j < high) {
		u[k] = s[j];
		j++;
		k++;
	}
}
int* mergesort3(int n, int *s) {
	int *u = (int*)malloc(n * sizeof(int));
	int repeat = ceil(log2(n)), *temp, size = 1, m, low, mid, high;
	m = pow(2, repeat);
	while (repeat--) {
		for (low = 0; low < m - size + 1; low += 2 * size) {
			mid = low + size - 1;
			high = mini((low + 2 * size), n);
			merge3(low, mid, high, s, u);
		}
		swap(s, u, temp);
		size *= 2;
	}
	//free(u);
	return s;
}
int main() {
	int n;
	printf("Enter n : ");
	while (scanf("%d", &n) != EOF) {
		int* arr = (int*)malloc(n * sizeof(int));
		printf("Enter array : \n");
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		arr = mergesort3(n, arr);
		for (int i = 0; i < n; i++)
			printf("  %d", arr[i]);
		puts("");
		free(arr);
		printf("Enter n : ");
	}
}