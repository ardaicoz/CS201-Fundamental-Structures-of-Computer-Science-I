//Author: Arda İçöz
//ID: 21901443

#include <iostream>
#include <sstream>
#include "ReservationSystem.h"
using namespace std;

ReservationSystem::ReservationSystem() {
	noOfFlights = 0;
	noOfReservations = 0;
	flightsList = NULL;
	tempList = NULL;
	reservationList = NULL;
	tempResList = NULL;
}

ReservationSystem::~ReservationSystem() {
	if ( tempResList )
		delete[] tempResList;
	
	if ( reservationList ) 
		delete[] reservationList;
	
	if ( tempList ) 
		delete[] tempList;
	
	if ( flightsList )
		delete[] flightsList;
}

void ReservationSystem::addFlight( const int flightNo, const int rowNo, const int seatNo ) {
	//if there are no flights in the list increment the flight number by one and create two new arrays with that size
	if ( noOfFlights == 0 ) {
		noOfFlights++;
		
		flightsList = new Flight[noOfFlights];
		tempList = new Flight[noOfFlights];
		
		//initializing both arrays with same elements
		for ( int i = 0; i < noOfFlights; i++ ) {
			flightsList[i] = Flight( flightNo, rowNo, seatNo );
			tempList[i] = Flight( flightNo, rowNo, seatNo );
		}
		
		cout << "Flight " << flightNo << " has been added." << endl;
	}
	//if there are already flights, then our we need to increment the size of "flightsList" array by 1.
	else {
		if ( alreadyExists(flightNo) ) {
			cout << "Flight " << flightNo << " already exists." << endl;
		}
		else {
			noOfFlights++;
			
			//deleting the old array and creating a new one with bigger(by 1) array.
			delete[] flightsList;
			flightsList = new Flight[noOfFlights];
			
			//copying the elements in the deleted array to this new one.
			for ( int i = 0; i < noOfFlights - 1; i++ ) 
				flightsList[i] = tempList[i];
			
			//adding the new flight to the last index of this new array
			flightsList[ noOfFlights - 1] = Flight( flightNo, rowNo, seatNo );
			
			//deleting tempList array and creating a new array for make it same with flightsList array (after copying elements to FlightsList of course)
			//so that we can make further additions to our flightList
			delete[] tempList;
			tempList = new Flight[noOfFlights];
		
			for ( int i = 0; i < noOfFlights; i++ ){
				tempList[i] = flightsList[i];
			}
				
			cout << "Flight " << flightNo << " has been added." << endl;
		}
	}
}

void ReservationSystem::cancelFlight( const int flightNo ) {
	if ( noOfFlights == 0 ) {
		cout << "No flights exists." << endl;
	}
	else {
		if ( !alreadyExists( flightNo ) ) {
			cout << "Flight "<< flightNo << " does not exist." << endl;
		}
		else {
			string flightNoStr = "";
			int size = noOfFlights;
			int index = locationOfFlight( flightNo );
			noOfFlights--;
			
			for ( int i = 0; i < noOfReservations; i++ ) {
				if ( flightNo == reservationList[i].getFlightNo() ) {
					int code = reservationList[i].getReservationCode();
					cancelReservation( code );
				}
			}
			
			//deleting the old array and creating a new one with one less size
			delete[] flightsList;
			flightsList = new Flight[noOfFlights];
			
			//copying the elements in the deleted one to the new array
			//but this time we will not copy the one we want to delete
			//so we divide the array into two and use two for loops
			for ( int i = 0; i < index; i++ ) {
				flightsList[i] = tempList[i];
			}
			
			for ( int j = index + 1; j < size; j++ ) {
				flightsList[j - 1] = tempList[j];
			}
			
			//deleting tempList array and creating a new array for make it same with flightsList array (after copying elements to FlightsList of course)
			delete[] tempList;
			tempList = new Flight[noOfFlights];
			
			for ( int i = 0; i < noOfFlights; i++ ) {
				tempList[i] = flightsList[i];
			}
			
			cout << "Flight " << flightNo << " and all of its reservations are cancelled" << endl;
			cout << endl;
		}
	}
}

void ReservationSystem::showAllFlights() {
	cout << endl;
	
	if ( noOfFlights != 0 ) {	
		cout << "Flights currently operated:" << endl;
		for ( int i = 0; i < noOfFlights; i++ ) {
			cout << "Flight " << flightsList[i].getFlightNo() << " (" << flightsList[i].availableSeatNum() << " available seats)" << endl;
		}
		
		cout << endl;
	}
	else {
		cout << "No flights exist." << endl;
		cout << endl;
	}
}

void ReservationSystem::showFlight( const int flightNo ) {
	cout << endl;
	
	if ( alreadyExists( flightNo ) ) {
		cout << "Flight " << flightNo << " has " << flightsList[locationOfFlight(flightNo)].availableSeatNum() << " available seats." << endl;
		
		flightsList[locationOfFlight(flightNo)].showFlight();
		
		cout << endl;
	}
	else {
		cout << "Flight "<< flightNo << " does not exist." << endl;
		cout << endl;
	}
}

int ReservationSystem::makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol ) {
	//checking if there is a flight in the list
	//if not, return -1
	if ( !alreadyExists( flightNo ) ) {
		return -1;
	}
	//if exists:
	else {
		int count = 0;
		
		//check if the seats are available
		//if available increment the count by 1, else return -1 and display error message
		for ( int i = 0; i < numPassengers; i++ ) {
			int index = flightsList[locationOfFlight(flightNo)].findIndexOfSeatNum( seatRow[i] * (int) seatCol[i] );
			
			if ( flightsList[locationOfFlight(flightNo)].isEmpty( index ) ) {
				count++;
			}
			else {
				cout << seatRow[i] << "" << seatCol[i] << " ";
			}
		}
		
		if ( count == numPassengers ) {
			for ( int i = 0; i < numPassengers; i++ ) {
				int index = flightsList[locationOfFlight(flightNo)].findIndexOfSeatNum( seatRow[i] * (int) seatCol[i] );
				flightsList[locationOfFlight(flightNo)].changeAvailability(index, false);
				tempList[locationOfFlight(flightNo)].changeAvailability(index, false);
			}
		}
		else {
			cout << "is not available." << endl;
			return -1;
		}
		
		//After reserving the seats, lets store this reservation in the array
		//if there are no reservations in the ReservationSystem, increment the reservation number by one and create two new arrays with that size
		if ( noOfReservations == 0 ) {
			noOfReservations++;
			
			reservationList = new Reservation[noOfReservations];
			tempResList = new Reservation[noOfReservations];
			
			//initializing both arrays with same elements
			for ( int i = 0; i < noOfReservations; i++ ) {
				reservationList[i] = Reservation( flightNo, numPassengers, seatRow, seatCol );
				tempResList[i] = Reservation( flightNo, numPassengers, seatRow, seatCol );
			}
			
			return reservationList[0].getReservationCode();
		}
		//if there are already reservations, then our we need to increment the size of "reservationList" array by 1.
		else {
			if ( reservationExists( flightNo, numPassengers, seatRow ) ) {
				return -1;
			}
			else {
				noOfReservations++;
				
				//deleting the old array and creating a new one with bigger(by 1) array.
				delete[] reservationList;
				reservationList = new Reservation[noOfReservations];
				
				//copying the elements in the deleted array to this new one.
				for ( int i = 0; i < noOfReservations - 1; i++ ) 
					reservationList[i] = tempResList[i];
				
				//adding the new reservation to the last index of this new array
				reservationList[ noOfReservations - 1] = Reservation( flightNo, numPassengers, seatRow, seatCol );
				
				//deleting tempResList array and creating a new array for make it same with reservationList array (after copying elements to reservationList of course)
				//so that we can make further additions to our reservationList
				delete[] tempResList;
				tempResList = new Reservation[noOfReservations];
			
				for ( int i = 0; i < noOfReservations; i++ ){
					tempResList[i] = reservationList[i];
				}
				
				return reservationList[ noOfReservations - 1].getReservationCode();
			}
		}
	}
}

void ReservationSystem::cancelReservation( const int resCode ) {
   if ( !reservationExists( resCode ) ) {
	   cout << "Reservation under code " << resCode << " does not exist." << endl;
	   cout << endl;
   }
   else {
		int indexOfRes = 0;
		int indexOfLetterX = 0;
		int sizeOfId = 0;
		int sizeOfIdButOnlySeats = 0;
		string flightNoStr = "";
		string seatsStr = "";
		int flightNo = 0;
		
		//finding the location of the reservation we want to delete
		for ( int i = 0; i < noOfReservations; i++ ) {
			if ( reservationList[i].getReservationCode() == resCode )
				indexOfRes = i;
		}
		//size of the ID of that reservation as int
		sizeOfId = reservationList[indexOfRes].getReservationID().size();
		
		//then getting the flightNo as a string from that Reservation object's ID (flightNo always ends with letter 'x')
		for ( int j = 0; j < sizeOfId; j++ ) {
			if ( reservationList[indexOfRes].getReservationID()[j] == 'x' ) {
				indexOfLetterX = j;
			}
		}
		
		sizeOfIdButOnlySeats = sizeOfId - (indexOfLetterX + 1);
		
		flightNo = reservationList[indexOfRes].getFlightNo();
		seatsStr = reservationList[indexOfRes].getReservationID().substr( indexOfLetterX + 1, sizeOfId - (indexOfLetterX + 1) );
				
		//Other part begins
		//now we change the seat availability of that flight to "true" (means that seats are empty now)
		//we get the row number and column number(ASCII num) to find the index of that seat
		//and we change the availability to true in that index
		for ( int j = 0; j < sizeOfIdButOnlySeats; j = j + 2 ) {
			stringstream ss1( seatsStr.substr(j, 1) );
			int seatRow = 0;
			ss1 >> seatRow;
			
			int seatNum = seatRow * ( (int)seatsStr[j + 1] );
			int index = flightsList[locationOfFlight(flightNo)].findIndexOfSeatNum( seatNum );
			flightsList[locationOfFlight(flightNo)].changeAvailability( index, true );
			tempList[locationOfFlight(flightNo)].changeAvailability( index, true );
		}
		
		//lastly we need to delete this reservation from the array
		int size = noOfReservations;
		//int index = locationOfFlight( flightNo );
		noOfReservations--;
		
		//deleting the old array and creating a new one with one less size
		delete[] reservationList;
		reservationList = new Reservation[noOfReservations];
		
		//copying the elements in the deleted one to the new array
		//but this time we will not copy the one we want to delete
		//so we divide the array into two and use two for loops
		for ( int i = 0; i < indexOfRes; i++ ) {
			reservationList[i] = tempResList[i];
		}
		
		for ( int j = indexOfRes + 1; j < size; j++ ) {
			reservationList[j - 1] = tempResList[j];
		}
		
		//deleting tempResList array and creating a new array for make it same with reservationList array (after copying elements to reservationList of course)
		delete[] tempResList;
		tempResList = new Reservation[noOfReservations];
		
		for ( int i = 0; i < noOfReservations; i++ ) {
			tempResList[i] = reservationList[i];
		}
		
		cout << "Reservation for the seats ";
		for ( int a = 0; a < sizeOfIdButOnlySeats; a = a + 2 )
			cout << seatsStr.substr(a, 2) << " ";
		cout << "is canceled in Flight " << flightNo << endl;
		
		cout << endl;
	}
}

void ReservationSystem::showReservation( const int resCode ) {
	if ( !reservationExists( resCode ) ) {
		cout << "No reservations under code " << resCode << endl;
		cout << endl;
	}
	else {
		int indexOfRes = 0;
		int indexOfLetterX = 0;
		int sizeOfId = 0;
		string seatStr = "";
		
		for ( int i = 0; i < noOfReservations; i++ ) {
			if ( reservationList[i].getReservationCode() == resCode )
				indexOfRes = i;
		}
		
		sizeOfId = reservationList[indexOfRes].getReservationID().size();
		
		for ( int j = 0; j < sizeOfId; j++ ) {
			if ( reservationList[indexOfRes].getReservationID()[j] == 'x' ) {
				indexOfLetterX = j;
			}
		}
		
		seatStr = reservationList[indexOfRes].getReservationID().substr(indexOfLetterX + 1, sizeOfId);
		
		cout << "Reservations under code " << resCode << " in Flight " << reservationList[indexOfRes].getReservationID().substr(0, indexOfLetterX) << ": ";
		for ( int k = 0; k < sizeOfId - (indexOfLetterX + 1); k = k + 2 ) {
			cout << seatStr.substr(k, 2) << " ";
		}
			
		cout << endl;
	}
}

bool ReservationSystem::alreadyExists( const int flightNo ) {
	bool exists = false;
	
	for ( int i = 0; i < noOfFlights; i++ ) 
		if ( flightsList[i].getFlightNo() == flightNo )
			exists = true;
			
	return exists;
}

bool ReservationSystem::reservationExists( const int flightNo, const int passengers, const int *seatRow ) {
	//first, lets change parameter variables to string to concate
	string flightNoStr = "";
	string seatRowStr = "";
	string strRow = "";
	string code = "";
	int codeInt = 0;
	
	ostringstream ss1;
	ss1 << flightNo;
	flightNoStr = ss1.str();
	
	for ( int i = 0; i < passengers; i++ ) {
		ostringstream ss2; 
		ss2 << seatRow[i];
		strRow = ss2.str();
	}
	seatRowStr += strRow;
	
	//then concate these two string (we are producing reservationCode)
	code = flightNoStr + "" + seatRowStr;
	
	//converting this string to int
	stringstream ssInt( code );
	ssInt >> codeInt;
	
	//lastly check if these code exists in list
	for ( int i = 0; i < noOfReservations; i++ ) {
		if ( reservationList[i].getReservationCode() == codeInt ) {
			return true;
		}
	}
	return false;
}

bool ReservationSystem::reservationExists( const int resCode ) {
	for ( int i = 0; i < noOfReservations; i++ ) {
		if ( reservationList[i].getReservationCode() == resCode ) {
			return true;
		} 
	}
	return false;
}

int ReservationSystem::locationOfFlight( const int flightNo ) {
	int location = 0;
	
	if ( alreadyExists( flightNo ) ) {
		for ( int i = 0; i < noOfFlights; i++ ) {
			if ( flightsList[i].getFlightNo() == flightNo ) {
				location = i;
			}
		}
	}
	
	return location;
}