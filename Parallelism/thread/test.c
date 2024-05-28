#include<stdio.h>
#include<omp.h>

int main(){
	omp_set_num_threads(4);
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
	int N = sizeof(arr) / sizeof(int);

#pragma omp parrallel for
	for(int i = 0; i < N; ++i){
		printf("thread %d, i = %2d\n", omp_get_thread_num(), i);
		arr[i] = arr[i] + 10 * omp_get_thread_num();
	}
	for(int i = 0; i < N; ++i) printf("%2d ", arr[i]);
	printf("\n");	
}
