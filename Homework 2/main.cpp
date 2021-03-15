#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
using namespace std;

//global function prototypes
int* algorithm_one( const int *arr1, const int *arr2, const int size );
int* algorithm_two( const int *arr1, const int *arr2, const int size );

//main function
int main() {
	int N = 1000;
	
	//FIRST ALGORITHM
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	//first case
	//declaring variables
	int *arr1 = new int[N];
	int *arr2 = new int[N];
	int *arr3_first = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = rand() % 200;
		arr2[i] = 200 + (rand() % 200);
	}
	
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	double duration;
	clock_t startTimeOne_1 = clock();
	
	arr3_first = algorithm_one( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeOne_1 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_one (first case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_first;
	delete[] arr2;
	delete[] arr1;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//second case
	//declaring variables
	arr1 = new int[N];
	arr2 = new int[N];
	arr3_first = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = 200 + (rand() % 200);
		arr2[i] = rand() % 200;
	}
		
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	clock_t startTimeOne_2 = clock();
	
	arr3_first = algorithm_one( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeOne_2 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_one (second case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_first;
	delete[] arr2;
	delete[] arr1;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//third case
	//declaring variables
	arr1 = new int[N];
	arr2 = new int[N];
	arr3_first = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = rand() % 200;
		arr2[i] = rand() % 200;
	}
		
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	clock_t startTimeOne_3 = clock();
	
	arr3_first = algorithm_one( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeOne_3 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_one (third case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_first;
	delete[] arr2;
	delete[] arr1;
	
	cout << endl; //***************************************************************************************************************************************
	
	//SECOND ALGORITHM
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	N = 10000000;
	
	//first case
	//declaring variables
	arr1 = new int[N];
	arr2 = new int[N];
	int *arr3_second = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = rand() % 200;
		arr2[i] = 200 + (rand() % 200);
	}
	
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	duration = 0.0;
	clock_t startTimeTwo_1 = clock();
	
	arr3_second = algorithm_two( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeTwo_1 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_two (first case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_second;
	delete[] arr2;
	delete[] arr1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//second case
	//declaring variables
	arr1 = new int[N];
	arr2 = new int[N];
	arr3_second = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = 200 + (rand() % 200);
		arr2[i] = rand() % 200;
	}
	
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	duration = 0.0;
	clock_t startTimeTwo_2 = clock();
	
	arr3_second = algorithm_two( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeTwo_2 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_two (second case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_second;
	delete[] arr2;
	delete[] arr1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//third case
	//declaring variables
	arr1 = new int[N];
	arr2 = new int[N];
	arr3_second = NULL;
	
	//initializing variables
	for ( int i = 0; i < N; i++ ) {
		arr1[i] = rand() % 200;
		arr2[i] = rand() % 200;
	}
	
	//sorting
	sort( arr1, arr1 + N );
	sort( arr2, arr2 + N );
	
	//using algorithms
	//Store the starting time
	duration = 0.0;
	clock_t startTimeTwo_3 = clock();
	
	arr3_second = algorithm_two( arr1, arr2, N );
	
	//Compute the number of seconds that pissed since the starting time
	duration = 1000 * double( clock() - startTimeTwo_3 ) / CLOCKS_PER_SEC;
	cout << "Execution took for algorithm_two (third case) " << duration << " milliseconds." << endl;
	
	delete[] arr3_second;
	delete[] arr2;
	delete[] arr1;
	
	
	return 0;
}

//global functions
//First algorithm
int* algorithm_one( const int *arr1, const int *arr2, const int size ) {
	int *arr3 = new int[size * 2];
	int position = 0;
	
	//making all elements of arr3, zero.
	for ( int i = 0; i < size * 2; i++ ) {
		arr3[i] = 0;
	}
	
	//appending all items in arr1 to arr3
	for ( int i = 0; i < size; i++ ) {
		arr3[i] = arr1[i];
	}
	
	//adding elements of arr2 to arr3
	for ( int i = 0; i < size; i++ ) { //for every number in arr2
		for ( int k = 0; k < size*2; k++ ) {
			if ( arr3[k] > arr2[i] ) {
				position = k;
				break;
			}
			else {
				position = k;
			}
		}
		
		for ( int j = (size*2) - 1; j >= position; j-- ) {
			arr3[j] = arr3[j-1];
		}
		arr3[position] = arr2[i];
	}
	
	return arr3;
}


//Second algorithm
int* algorithm_two( const int *arr1, const int *arr2, const int size ) {
	int *arr3 = new int[size * 2];
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	
	while ( (index1 < size )  && (index2 < size ) ) {
		if ( arr1[index1] > arr2[index2] ) {
			arr3[index3] = arr2[index2];
			index2 += 1;
			index3 += 1;
		}
		else if ( arr1[index1] <= arr2[index2] ) {
			arr3[index3] = arr1[index1];
			index1 += 1;
			index3 += 1;
		}
	}
		
	if ( index1 < size ) {
		for ( int i = index1; i < size; i++ ) {
			arr3[index3++] = arr1[i];
		}
	}
	else if ( index2 < size ) {
		for ( int i = index2; i < size; i++ ) {
			arr3[index3++] = arr2[i];
		}
	}
		
	return arr3;
}

