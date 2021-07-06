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
    int array[] = {-2, 11, -4, 13, -5, 20};
    int size = 6;

    cout << "Algo 1: " << maxSubSum1(array, size) << endl;
    cout << "Algo 2: " << maxSubSum2(array, size) << endl;
    cout << "Algo 3: " << maxSubSum3(array, size) << endl;
    cout << "Algo 4: " << maxSubSum4(array, size) << endl;

    return 0;
}
