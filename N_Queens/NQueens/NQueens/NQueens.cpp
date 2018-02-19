#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int *buffer, **ans, size = 0;

int check(int row, int cul) {
	int cul2 = cul, cul1 = cul;
	for (int i = row - 1; i >= 0; i--) {
		cul2--;
		cul1++;
		if (buffer[i] == cul2 || buffer[i] == cul1 || buffer[i] == cul) return 0;
	}

	return 1;
}
void add(int n) {
	memcpy(ans[size], buffer, n * sizeof(int));
	size++;
	ans = (int**)realloc(ans, sizeof(int**)*(size + 1));
	ans[size] = (int*)malloc(n * sizeof(int));
}
void position(int row, int n) {
	if (row<n) {
		for (int i = 0; i<n; i++) {
			if (check(row, i)) {
				buffer[row] = i;
				position(row + 1, n);
			}
		}
	}
	else
		add(n);
}
char*** solveNQueens(int n, int* returnSize) {
	int temp;
	size = 0;
	ans = (int**)malloc(1 * sizeof(int*));
	ans[0] = (int*)malloc(sizeof(int)*n);
	buffer = (int*)malloc(n * sizeof(int));
	position(0, n);
	*returnSize = size;
	char ***out = (char***)malloc(size * sizeof(char**));
	for (int i = 0; i < size; i++) {
		out[i] = (char**)malloc(n * sizeof(char*));
		for (int j = 0; j < n; j++) {
			out[i][j] = (char*)calloc(n, sizeof(char));
			for (int z = 0; z < n; z++)
				out[i][j][z] = '.';
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < n; j++) {
			temp = ans[i][j];
			out[i][j][temp] = 'Q';
		}
	}
	
	return out;
}
int main() {
	int n, returnSize;
	char ***sol;

	printf("enter n:");
	scanf("%d", &n);
	sol=solveNQueens(n, &returnSize);

	for (int i = 0; i < returnSize; i++) {
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < n; z++)
				printf(" %c", sol[i][j][z]);
			puts("");
		}
		puts("");
		for (int j = 0; j < n; j++)
			printf("( %d, %d )\n", j, ans[i][j]);
		puts("----------------");
	}
	system("PAUSE");
}