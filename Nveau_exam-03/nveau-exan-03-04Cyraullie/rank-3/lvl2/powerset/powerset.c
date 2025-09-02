#include <stdio.h>
#include <stdlib.h>

void find_subsets(int *arr, int size, int target, int *subset, int index, int sum, int start)
{
	int i;
	if (sum == target) {
		i = 0;
		while (i < index) {
			printf("%d", subset[i]);
			if (i < index - 1)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	
	i = start;
	while (i < size) {
		subset[index] = arr[i];
		find_subsets(arr, size, target, subset, index + 1, sum + arr[i], i + 1);
		i++;
	}
}

int main(int argc, char **argv) {
	int i;
	int target;
	int size;
	int *arr;
	int *subset;
	
	if (argc < 3) {
		printf("Usage: %s target num1 num2 ...\n", argv[0]);
		return (1);
	}
	
	target = atoi(argv[1]);
	size = argc - 2;
	arr = malloc(size * sizeof(int));
	if (!arr)
		return (1);
	
	i = 0;
	while (i < size) {
		arr[i] = atoi(argv[i + 2]);
		i++;
	}
	
	subset = malloc(size * sizeof(int));
	if (!subset) {
		free(arr);
		return (1);
	}
	
	find_subsets(arr, size, target, subset, 0, 0, 0);
	
	free(arr);
	free(subset);
	return (0);
}
