#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
typedef struct vertex *vertexPointer;
typedef struct vertex {
	char name;
	vertexPointer left;
	vertexPointer right;
}vertex;
typedef struct edge *edgePointer;
typedef struct edge {
	vertexPointer v;
	vertexPointer u;
	int weight;
}edge;
vertexPointer creatVertex(char str) {
	vertexPointer out = (struct vertex*)malloc(sizeof(struct vertex));
	out->name = str;
	out->left = NULL;
	out->right = NULL;
	return out;
}
edgePointer creatEdge(vertexPointer u, vertexPointer v, int w) {
	edgePointer out = (struct edge*)malloc(sizeof(struct edge));
	out->u = u;
	out->v = v;
	out->weight = w;
	return out;
}
void sort(edgePointer arr[], int size) {
	edgePointer temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (arr[j]->weight > arr[j + 1]->weight) swap(arr[j], arr[j + 1], temp);
		}
	}
}
vertexPointer findHeader(vertexPointer in) {
	while (in->left)
		in = in->left;
	return in;
}

vertexPointer findEnd(vertexPointer in) {
	while (in->right)
		in = in->right;
	return in;
}
void merge(vertexPointer p1, vertexPointer p2) {
	vertexPointer end, header;
	header = findHeader(p2);
	end = findEnd(p1);
	end->right = header;
	header->left = end;
}
void displaylist(vertexPointer in) {
	vertexPointer h = findHeader(in);
	while (h) {
		printf("%c  ", h->name);
		h = h->right;
	}
	puts("");
}
int main()
{
	char str[20], v1, v2;
	int w, f = 0, f2 = 0;
	edgePointer in[30], ans[30];
	vertexPointer tempv1, tempv2, record[126] = {NULL};
	printf("enter edge(enter empty end input):\n");
	while (fgets(str,sizeof(str),stdin) != NULL) {
		if (strlen(str) < 3) break;
		sscanf(str, "%c %c %d", &v1, &v2, &w);

		if (record[v1]) tempv1 = record[v1];
		else {
			tempv1 = creatVertex(v1);
			record[v1] = tempv1;
		}
		if (record[v2]) tempv2 = record[v2];
		else {
			tempv2 = creatVertex(v2);
			record[v2] = tempv2;
		}

		in[f] = creatEdge(tempv1, tempv2, w);
		f++;
	}
	sort(in, f);
	for (int i = 0; i < f; i++) {
		if (findHeader(in[i]->u) != findHeader(in[i]->v)) {
			merge(in[i]->u, in[i]->v);
			ans[f2] = in[i];
			f2++;
		}
	}
	for (int i = 0; i < f2; i++) {
		printf("%c  %c  %d\n",ans[i]->u->name, ans[i]->v->name, ans[i]->weight);
	}

	system("PAUSE");
}