//Author: Arda İçöz
//ID: 21901443

#include <iostream>
#include <sstream>
#include "Reservation.h"
using namespace std;

Reservation::Reservation( const int flightNo, const int passengers, const int *seatRow, const char *seatCol ) {
	flightNumber = flightNo;
	
	//below variable is used to return a reservation code as int
	string tempReservation = "";
	string intRow = "";
	reservationCode = 0;
	
	//below variables are used to return a reservation code as string
	reservation = "";
	string seats = "";
	string strRow = "";
	string strFlight = "";
	ostringstream flightNoStream;
	
	flightNoStream << flightNo;
	strFlight = flightNoStream.str();

	//Writing all reserved seat rows and columns, respectively (for each reserved seat)
	for (int i = 0; i < passengers; i++ ) {  
		ostringstream seatRowStream; 
		seatRowStream << seatRow[i];
		strRow = seatRowStream.str();
		
		seats += strRow + "" + seatCol[i];
		intRow += strRow;
	}
	
	//reservationID
	reservation = strFlight + "x" + seats;
	
	//reservationCode
	tempReservation = strFlight + "" + intRow;
	stringstream code( tempReservation );
	code >> reservationCode;
}

Reservation::~Reservation() {
}

string Reservation::getReservationID() {
	return reservation;
}

int Reservation::getReservationCode() {
	return reservationCode;
}

int Reservation::getFlightNo() {
	return flightNumber; 
}

void Reservation::showReservation() {
	int indexOfX = 0;
	
	for (int i = 0; i < (int) reservation.size(); i++ ) {
		if ( reservation[i] == 'x' ) {
			indexOfX = i;
		}
	}
	
	cout << "Reservations under Code " << reservationCode << " in Flight " <<  reservation.substr(0 ,indexOfX) << ": ";
	
	for ( int j = indexOfX + 1; j < (int) reservation.size(); j += 2 ) {
		cout << reservation.substr(j, 2) << " ";
	}
}


