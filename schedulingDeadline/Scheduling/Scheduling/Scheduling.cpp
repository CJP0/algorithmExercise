#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define swap(x,y,z) ((z)=(x), (x)=(y), (y)=(z))
typedef struct job *jobPointer;
typedef struct job {
	int num;
	int deadline;
	int profit;
}job;
jobPointer creatJob(int num, int dead, int profit) {
	jobPointer out = (struct job*)malloc(sizeof(struct job));
	out->num = num;
	out->deadline = dead;
	out->profit = profit;
	return out;
}
void sortProfit(jobPointer in[], int size) {
	jobPointer temp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (in[j]->profit < in[j + 1]->profit) swap(in[j], in[j + 1], temp);
		}
	}
}
void copy(jobPointer a[], jobPointer b[], int size) {
	for (int i = 0; i < size; i++)
		a[i] = b[i];
}
void sortDay(jobPointer in[], int size) {
	jobPointer temp;
	for (int i = 0; i < size - 1; i++)
		for (int j = 0; j < size - 1 - i; j++)
			if (in[j]->deadline > in[j + 1]->deadline) swap(in[j], in[j + 1], temp);
}
int main() {
	char str[20];
	int tempn, tempd, tempp, f = 0, ansf = 1, bufferf=1;
	jobPointer jobs[50], ans[50] = {NULL}, buffer[50];
	printf("input workNumber deadline profit(enter empty end):\n");
	while (fgets(str, sizeof(str), stdin) != NULL) {
		if (strlen(str) < 3) break;
		sscanf(str, "%d %d %d", &tempn, &tempd, &tempp);
		jobs[f] = creatJob(tempn, tempd, tempp);
		f++;
	}
	sortProfit(jobs,f);
	ans[0] = jobs[0];
	for (int i = 1; i < f; i++) {
		int day = 1;
		ans[ansf] = jobs[i];
		copy(buffer, ans, ansf + 1);
		sortDay(buffer, ansf + 1);
		for (int j = 0; j < (ansf + 1); j++) {
			if (day <= buffer[j]->deadline) day++;
			else break;
		}
		ansf += day == (ansf + 2) ? 1 : 0;
	}
	int maxProfit = 0;
	printf(" workNumber, deadline, profit\n");
	for (int i = 0; i < ansf; i++) {
		printf("  %d,   %d,   %d\n", ans[i]->num, ans[i]->deadline, ans[i]->profit);
		maxProfit += ans[i]->profit;
	}
	printf("  maxProfit : %d\n", maxProfit);
	system("PAUSE");
}