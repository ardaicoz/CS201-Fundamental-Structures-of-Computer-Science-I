//Author: Arda İçöz
//ID: 21901443

#include <iostream>
#include <string.h>
#include "Flight.h"
using namespace std;

Flight::Flight( const int newFlightNo, const int newRowNo, const int newSeatNo ) {
	if ( newFlightNo <= 0 || newRowNo <= 0 || newSeatNo <= 0 ) {
		flightNo = 0;
		rowNo = 0;
		seatNo = 0;
		availableSeats = 0;
		seatNumbers = NULL;
		seatAvailability = NULL;
	}
	else {
		flightNo = newFlightNo;
		rowNo = newRowNo;
		seatNo = newSeatNo;
		availableSeats = newRowNo * newSeatNo;
		seatNumbers = new int[newRowNo * newSeatNo];
		seatAvailability = new bool[newRowNo * newSeatNo];
	}
		
	/* Below loop is to initiliaze "seatNumbers" array. Number of every element is calculated by multiplying
	 * its element's row number and column number. ASCII is used for column numbers because columns are originally
	 * represented by letters. And also every element has its unique number becasue of different ASCII numbers. Neat!
	 * Oh, why this array? This array is used to determine the index of the seats. Because users will enter the row numbers and
	 * column chars it is possible to find which seats they want to reserve by getting a unique number. After determining the index
	 * of these seats, those indexes in "SeatAvailability" will turn true. Neat, eh? Or a bad solution, idk.
	 */
	char letter = 65; //65 means its 'A'
	int index = 0;
	for ( int i = 1; i <= newRowNo; i++ ) {
		for ( int k = 0; k < newSeatNo; k++ ) {
			seatNumbers[index] = (int)letter * i;
			index++;
			letter++;
		}
		letter = 65;
	}
	
	//This loop is to initiliaze all elements of "seatAvailability" array to false.
	for ( int j = 0; j < newRowNo * newSeatNo; j++ ) {
		seatAvailability[j] = true;
	}
} 

Flight::Flight( const Flight& flightToCopy ) : flightNo(flightToCopy.flightNo), rowNo(flightToCopy.rowNo), 
												seatNo(flightToCopy.seatNo), availableSeats(flightToCopy.availableSeats) {
	if ( rowNo * seatNo > 0 ) {
		seatNumbers = new int[rowNo * seatNo];
		seatAvailability = new bool[rowNo * seatNo];
		
		for ( int i = 0; i < rowNo * seatNo; i++ ) {
			seatNumbers[i] = flightToCopy.seatNumbers[i];
			seatAvailability[i] = flightToCopy.seatAvailability[i];
		}
	}
	else {
		seatNumbers = NULL;
		seatAvailability = NULL;
	}
}

Flight::~Flight() {
	if ( seatAvailability ) 
		delete[] seatAvailability;
	
	if ( seatNumbers )
		delete[] seatNumbers;
}

Flight& Flight::operator=( const Flight& right ) {
	if ( &right != this ) {
		if ( (flightNo != right.flightNo) && (rowNo != right.rowNo) && (seatNo != right.seatNo) && (availableSeats != right.availableSeats) ) {
			if ( flightNo > 0 && rowNo > 0 && seatNo > 0 ) {
				delete[] seatAvailability;
				delete[] seatNumbers;
			}
			
			flightNo = right.flightNo;
			rowNo = right.rowNo;
			seatNo = right.seatNo;
			availableSeats = right.availableSeats;
			
			if ( flightNo > 0 && rowNo > 0 && seatNo > 0 ) {
				seatNumbers = new int[rowNo * seatNo];
				seatAvailability = new bool[rowNo * seatNo];
			}
			else {
				seatNumbers = NULL;
				seatAvailability = NULL;
			}
		}
		
		for ( int i = 0; i < rowNo * seatNo; i++ ) {
			seatNumbers[i] = right.seatNumbers[i];
			seatAvailability[i] = right.seatAvailability[i];
		}
	}
	return *this;
}

void Flight::showFlight() {
	char letterA = 65; //ASCII
	int index = 0;
	
	//Initially, printing the seat letters(seatNo)
	cout << "  "; //to allign the letters with the symbol "x" and "o"
	for ( int i = 0; i < seatNo; i++ ) {
		cout << (char) (letterA + i) << " "; //using ASCII, it will print enough letters
	}
	cout << endl;
	
	//Then, printing the available seats with the row number at the very beginning
	for ( int i = 1; i <= rowNo; i++ ) {
		cout << i << " "; //printing the row number first
		
		for ( int j = 0; j < seatNo; j++ ) {
			index = findIndexOfSeatNum(i * (65 + j) );
			
			if ( seatAvailability[index] == true ) //then, printing the availability of the seats
				cout << "o" << " ";
			else
				cout << "x" << " ";
		}
		cout << endl;
	}
}

void Flight::printSeatNumbers() {
	cout << "seatNumbers = [";
	for ( int i = 0; i < (rowNo * seatNo) - 1; i++ ) {
		cout << seatNumbers[i] << ", ";
	} 
	cout << seatNumbers[ (rowNo*seatNo) - 1 ] << "]" << endl;
}

void Flight::changeAvailability( const int index, const bool availability ) { 
	seatAvailability[index] = availability;
}

void Flight::printAvailability() {
	cout << "seatAvailability = [";
	for ( int i = 0; i < (rowNo * seatNo) - 1; i++ ) {
		cout << seatAvailability[i] << ", ";
	}
	cout << seatAvailability[ (rowNo*seatNo) - 1 ] << "]" << endl;
}

int Flight::findIndexOfSeatNum( const int seatNum ) {
	for (int i = 0; i < rowNo * seatNo; i++ ) { 
		if ( seatNumbers[i] == seatNum ) {
			return i;
		}
	}
	cout << "Element not found, returning -1." << endl;
	return -1;
}

int Flight::availableSeatNum() {
	int count = 0;
	
	for ( int i = 0; i < rowNo * seatNo; i++ ) {
		if ( seatAvailability[i] == true )
			count++;
	}
	
	return count;
}

int Flight::getFlightNo() {
	return flightNo;
}

bool Flight::getSeatAvailability( const int index ) {
	return seatAvailability[index];
}

bool Flight::isEmpty( const int index ) {
	if ( getSeatAvailability( index ) ) {
		return true;
	}
	
	return false;
}

void Flight::setTrueAvailability() {
	for ( int i = 0; i < rowNo * seatNo; i ++ )
		changeAvailability(i , true);
}