//Author: Arda İçöz
//ID: 21901443

#ifndef RESERVATIONSYSTEM_H
#define RESERVATIONSYSTEM_H
#include "Flight.h"
#include "Reservation.h"

class ReservationSystem {
public:
	ReservationSystem();
	~ReservationSystem();
	
	void addFlight( const int flightNo, const int rowNo, const int seatNo );
	void cancelFlight( const int flightNo );
	
	void showAllFlights();
	void showFlight( const int flightNo );
	int makeReservation( const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol );
	void cancelReservation( const int resCode );
	void showReservation( const int resCode );
	
	bool alreadyExists( const int flightNo );
	bool reservationExists( const int flightNo, const int passengers, const int *seatRow );
	bool reservationExists( const int resCode );
 	int locationOfFlight( const int flightNo );
	
	Flight *flightsList;
	Flight *tempList;
	Reservation *reservationList;
	Reservation *tempResList;
	int noOfReservations;
	int noOfFlights;
};

#endif // RESERVATIONSYSTEM_H
