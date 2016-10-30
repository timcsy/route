#include "stdio.h"

#define MAX_SIZE 1000

int bisearch(int low, int high, int search, int * array);
int polygon(int N, int * series);

int main()
{
	int N = 179;
	int series[MAX_SIZE] = {4, 4, 4, 3, 2, 6, 5, 8, 5, 6, 3, 20, 4, 4, 5, 10, 6, 5, 6, 5, 6, 5, 4, 6, 6, 5, 4, 4, 4, 6, 6, 5, 5, 5, 7, 5, 7, 8, 4, 8, 6, 5, 5, 4, 3, 2, 4, 8, 7, 4, 4, 4, 4, 5, 19, 7, 4, 5, 8, 4, 5, 6, 5, 4, 6, 4, 6, 7, 4, 5, 6, 3, 4, 3, 4, 6, 4, 4, 8, 3, 4, 5, 4, 9, 4, 4, 6, 4, 9, 8, 3, 5, 5, 4, 3, 3, 3, 4, 19, 6, 6, 5, 6, 6, 6, 7, 7, 5, 6, 32, 5, 12, 10, 12, 12, 10, 7, 9, 7, 7, 4, 8, 9, 8, 8, 7, 7, 8, 11, 14, 10, 4, 8, 7, 8, 6, 8, 5, 3, 5, 11, 6, 6, 5, 5, 4, 8, 8, 5, 9, 4, 8, 6, 6, 2, 5, 7, 3, 2, 6, 4, 5, 5, 4, 4, 5, 5, 6, 4, 6, 5, 7, 5, 5, 5, 7, 7, 4, 9};
	puts("polygon :");
	polygon(N, series);
	puts("\nrectangle :");
	rect(N, series);
	return 0;
}

int bisearch(int low, int high, int search, int * array)
{
	if(low > high) return -1;
	int mid = (low + high) / 2;
	if(array[mid] == search) return mid;
	if(array[mid] > search) return bisearch(low, mid - 1, search, array);
	return bisearch(mid + 1, high, search, array);
}

int polygon(int N, int * series)
{
	int i, sum = 0, n = 3;
	int points[MAX_SIZE] = {0};
	for(i = 0; i < N; i++)
	{
		points[i] = sum;
		sum += series[i];
	}
	while(sum >= n)
	{
		while(sum % n != 0) n++;
		printf("n = %d\n", n);
		int edge = sum / n;
		for(i = 0; i < N; i++)
		{
			int current = i, time = 0;
			while(time < n)
			{
				int next = bisearch(0, N-1, (points[current] + edge) % sum, points);
				if(next == -1) break;
				current = next;
				time++;
			}
			if(time == n)
			{
				printf("sum = %d, n = %d, ans = %d\n", sum, n, i);
				for(time = 0; time < n; time++)
					printf("\tpoint%d : %d\n", time + 1, bisearch(0, N-1, (points[i] + edge * time) % sum, points));
			}
		}
		n++;
	}
}

int rect(int N, int * series)
{
	int i, sum = 0;
	int points[MAX_SIZE] = {0};
	for(i = 0; i < N; i++)
	{
		points[i] = sum;
		sum += series[i];
	}
	
	if(sum % 2 == 1) return -1;
	
	for(i = 0; i < N; i++)
	{
		int j = (i + 1) % N;
		while(j < N && (points[j] + sum - points[i]) % sum < sum / 2)
		{
			int a = (points[j] + sum - points[i]) % sum;
			int next = bisearch(0, N-1, (points[i] + sum / 2) % sum, points);
			if(next == -1) break;
			next = bisearch(0, N-1, (points[i] + a) % sum, points);
			if(next == -1) break;
			next = bisearch(0, N-1, (points[i] + sum / 2 + a) % sum, points);
			if(next == -1) break;
			printf("sum = %d, start = %d, a = %d\n", sum, i, a);
			printf("\tpoint%d : %d\n", 1, bisearch(0, N-1, points[i], points));
			printf("\tpoint%d : %d\n", 2, bisearch(0, N-1, (points[i] + a) % sum, points));
			printf("\tpoint%d : %d\n", 3, bisearch(0, N-1, (points[i] + sum / 2) % sum, points));
			printf("\tpoint%d : %d\n", 4, bisearch(0, N-1, (points[i] + sum / 2 + a) % sum, points));
			j++;
		}
	}
}