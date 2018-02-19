#include<malloc.h>  
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct matrix *matrixPointer;
typedef struct matrix {
	int row;
	int col;
	int size;
	int originalSize;
	int *data;
};
void tempMatrix(matrixPointer in,int size) {
	in->row = 0;
	in->col = 0;
	in->size = size;
	in->originalSize = size;
}
	
matrixPointer creatMatrix(int size, int *data) {
	matrixPointer out = (struct matrix*)malloc(1 * sizeof(struct matrix));
	out->row = 0;
	out->col = 0;
	out->size = size;
	out->originalSize = size;
	out->data = data;
	return out;
}
matrixPointer submatrix(matrixPointer in, int row, int col, int size) {
	matrixPointer out = (struct matrix*)malloc(1 * sizeof(struct matrix));
	out->row = in->row + row;
	out->col = in->col + col;
	out->size = size;
	out->originalSize = in->originalSize;
	out->data = in->data;
	return out;
}
int get(matrix *in, int row, int col) {
	return in->data[(in->originalSize)*(in->row + row) + in->col + col];
}
void set(matrix *in, int row, int col, int value) {
	in->data[(in->originalSize)*(in->row + row) + in->col + col] = value;
}
void plus(matrixPointer c, matrixPointer a, matrixPointer b) {
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			set(c, i, j, get(a, i, j) + get(b, i, j));
		}
	}
}
void minus(matrixPointer c, matrixPointer a, matrixPointer b) {
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			set(c, i, j, get(a, i, j) - get(b, i, j));
		}
	}
}
void add(matrixPointer a, matrixPointer b) {
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			set(a, i, j, get(a, i, j) + get(b, i, j));
		}
	}
}
void sub(matrixPointer a, matrixPointer b) {
	for (int i = 0; i < a->size; i++) {
		for (int j = 0; j < a->size; j++) {
			set(a, i, j, get(a, i, j) - get(b, i, j));
		}
	}
}
void printMatrix(matrixPointer in) {
	puts("");
	puts("==============================");
	for (int i = 0; i < (in->size); i++) {
		for (int j = 0; j < (in->size); j++) {
			printf("%5d ", get(in, i, j));
		}
		puts("");
	}
}
void strassen(matrixPointer c, matrixPointer a, matrixPointer b) {
	int size = a->size, half = a->size / 2;
	if (size == 1) {
		set(c, 0, 0, get(a, 0, 0)*get(b, 0, 0));
	}
	else {
		matrixPointer s[10], p[7], t;
		for (int i = 0; i < 10; i++) {
			s[i] = (struct matrix*)malloc(1 * sizeof(struct matrix));
			tempMatrix(s[i], half);
			s[i]->data = (int*)calloc(size*size, sizeof(int));
		}
		for (int i = 0; i < 7; i++) {
			p[i] = (struct matrix*)malloc(1 * sizeof(struct matrix));
			tempMatrix(p[i], half);
			p[i]->data = (int*)calloc(size*size, sizeof(int));
		}
		
		matrixPointer a11 = submatrix(a, 0, 0, half);
		matrixPointer a12 = submatrix(a, 0, half, half);
		matrixPointer a21 = submatrix(a, half, 0, half);
		matrixPointer a22 = submatrix(a, half, half, half);

		matrixPointer b11 = submatrix(b, 0, 0, half);
		matrixPointer b12 = submatrix(b, 0, half, half);
		matrixPointer b21 = submatrix(b, half, 0, half);
		matrixPointer b22 = submatrix(b, half, half, half);

		matrixPointer c11 = submatrix(c, 0, 0, half);
		matrixPointer c12 = submatrix(c, 0, half, half);
		matrixPointer c21 = submatrix(c, half, 0, half);
		matrixPointer c22 = submatrix(c, half, half, half);
		
		minus(s[0], b12, b22);
		plus(s[1], a11, a12);
		plus(s[2], a21, a22);
		minus(s[3], b21, b11);
		plus(s[4], a11, a22);
		plus(s[5], b11, b22);
		minus(s[6], a12, a22);
		plus(s[7], b21, b22);
		minus(s[8], a11, a21);
		plus(s[9], b11, b12);
		
		strassen(p[0], a11, s[0]);
		strassen(p[1], s[1], b22);
		strassen(p[2], s[2], b11);
		strassen(p[3], a22, s[3]);
		strassen(p[4], s[4], s[5]);
		strassen(p[5], s[6], s[7]);
		strassen(p[6], s[8], s[9]);
		
		add(c11, p[4]);
		add(c11, p[3]);
		sub(c11, p[1]);
		add(c11, p[5]);

		add(c12, p[0]);
		add(c12, p[1]);

		add(c21, p[2]);
		add(c21, p[3]);

		add(c22, p[4]);
		add(c22, p[0]);
		sub(c22, p[2]);
		sub(c22, p[6]);
		
		for (int i = 0; i < 10; i++) free(s[i]);
		for (int i = 0; i < 7; i++) free(p[i]);
	}
}
void matrixMlu(matrixPointer c, matrixPointer a, matrixPointer b) {
	int buffer;
	for (int i = 0; i < (c->size); i++) {
		for (int j = 0; j < (c->size); j++) {
			buffer = 0;
			for (int z = 0; z < (a->size); z++)
				buffer += get(a, i, z)*get(b, z, j);
			set(c, i, j, buffer);
		}
	}
}
int main() {
	int n, m;
	printf("enter matrix row and col : ");
	while (scanf("%d %d", &n, &m)!=EOF && n) {

		int *nums1 = (int*)calloc(n*m, sizeof(int));
		int *nums2 = (int*)calloc(n*m, sizeof(int));
		int *nums3 = (int*)calloc(n*n, sizeof(int));

		puts("enter matrix A\n");
		for (int i = 0; i < n*m; i++)
			scanf("%d", &nums1[i]);
		matrixPointer a = creatMatrix(m, nums1);

		puts("\nenter matrix B\n");
		for (int i = 0; i < n*m; i++)
			scanf("%d", &nums2[i]);
		matrixPointer b = creatMatrix(n, nums2);

		matrixPointer c = creatMatrix(n, nums3);

		if (m != n || log2(n) != int(log2(n))) 
			matrixMlu(c, a, b);
		else
			strassen(c, a, b);

		printMatrix(c);

		printf("\nenter matrix row and col : ");
	}
}