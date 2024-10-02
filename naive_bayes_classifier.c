#include <stdio.h>

void preprocessing(int dataset[][], int dataset_size, int feature_count) {
	
}

int main() {
	int dataset_size, feature_count;
	printf("Dataset Size: ");
	scanf("%d", &dataset_size);
	printf("No. of Features: ");
	scanf("%d", &feature_count);

	int dataset[dataset_size][feature_count + 1];
	printf("Enter the Dataset: \n");
	for (int i = 0; i < dataset_size; i++) {
		printf("%d: ", i + 1);
		for (int j = 0; j < feature_count; j++) {
			scanf("%d", &dataset[i][j]);
		}
		scanf("%d", &dataset[i][feature_count]);
	}

	preprocessing(dataset, dataset_size, feature_count);

	return 0;
}

