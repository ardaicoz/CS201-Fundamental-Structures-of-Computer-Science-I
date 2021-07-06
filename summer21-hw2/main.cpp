#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

//defining algorithm prototypes
int maxSubSum1(const int* array, const int size); //Cubic 
int maxSubSum2(const int* array, const int size); //Quadratic
int maxSubSum3(const int* array, const int size); //Logarithmic (recursive)
int maxSubRec(const int* array, const int size, const int left, const int right); //Recursive solution for 3rd algo
int max3(const int num1, const int num2, const int num3); //return the max number from three (used in 3rd algo)
int maxSubSum4(const int* array, const int size); //Linear

//implementing algorithms
//Algorithm 1 (cubic)
int maxSubSum1(const int* array, const int size) {
    int maxSum = 0;

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            int thisSum = 0;

            for (int k = i; k <= j; k++) 
                thisSum += array[k];

            if (thisSum > maxSum)
                maxSum = thisSum;
        }
    }

    return maxSum;
}

//Algorithm 2 (Quadratic)
int maxSubSum2(const int* array, const int size) {
    int maxSum = 0; 

    for (int i = 0; i < size; i++) {
        int thisSum = 0;

        for (int j = i; j < size; j++) {
            thisSum += array[j];

            if (thisSum > maxSum) 
                maxSum = thisSum;
        }
    }

    return maxSum;
}

//Algorithm 3 (logarithmic-recursive)
//func to find the max number among three ints
int max3(const int num1, const int num2, const int num3) {
    if ( (num1 > num2) && (num1 > num3) ) {
		return num1;
	} 
    if ( (num2 > num1) && (num2 > num3) ) {
		return num2;
	} 
    else {
		return num3;
	}
}

//recursive solution to 3rd algorithm (behaves like a helper function)
int maxSubRec(const int* array, const int size, const int left, const int right) {
    if (left == right)
        if (array[left] > 0)
            return array[left];
        else
            return 0;

    int center = (left + right) / 2;
    int maxLeftSum = maxSubRec(array, size, left, center);
    int maxRightSum = maxSubRec(array, size, center + 1, right);

    int maxLeftBorderSum = 0;
    int leftBorderSum = 0;
    for (int i = center; i >= left; i--) {
        leftBorderSum += array[i];

        if( leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }

    int maxRightBorderSum = 0;
    int rightBorderSum = 0;
    for (int j = center + 1; j <= right; j++) {
        rightBorderSum += array[j];
        
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }

    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

//actual algorithm (calls the recursive function)
int maxSubSum3(const int* array, const int size) {
    return maxSubRec(array, size, 0, size -1);
}

//Algorithm 4 (linear)
int maxSubSum4(const int* array, const int size) {
    int maxSum = 0;
    int thisSum = 0;

    for (int i = 0; i < size; i++) {
        thisSum += array[i];

        if (thisSum > maxSum)
            maxSum = thisSum;
        else if (thisSum < 0)
            thisSum = 0;
    }

    return maxSum;
}

int main() {
    //17 sized array (16 index)
    int sizes[] = {100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};

    //creating the array for test
    int* array = new int[ sizes[8] ];
    const int size = sizes[8];

    //random number generator to fill the array with values between -100 and 100
    srand(time(0));

    for (int i = 0; i < size; i++) {
        int randNum = rand() % 201 + (-100);
        array[i] = randNum;
    }

    //printing the elements of array
    /* for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    } */
    cout << endl;

    // Declare necessary variables
    std::chrono::time_point< std::chrono::system_clock > startTime;
    std::chrono::duration< double, milli > elapsedTime;
    
    // Store the starting time
    startTime = std::chrono::system_clock::now();
    // Code block
    maxSubSum1(array, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algo 1: Execution took " << elapsedTime.count() << " milliseconds." << endl;

    // Store the starting time
    startTime = std::chrono::system_clock::now();
    // Code block
    maxSubSum2(array, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algo 2: Execution took " << elapsedTime.count() << " milliseconds." << endl;

    // Store the starting time
    startTime = std::chrono::system_clock::now();
    // Code block
    maxSubSum3(array, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algo 3: Execution took " << elapsedTime.count() << " milliseconds." << endl;

    // Store the starting time
    startTime = std::chrono::system_clock::now();
    // Code block
    maxSubSum4(array, size);
    // Compute the number of milliseconds that passed since the starting time
    elapsedTime = std::chrono::system_clock::now() - startTime;
    cout << "Algo 4: Execution took " << elapsedTime.count() << " milliseconds." << endl;
    
    delete[] array;
    return 0;
}
