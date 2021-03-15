//Author: Arda İçöz
//ID: 21901443

#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

class Reservation {
public:
	Reservation( const int flightNo = 0, const int passengers = 0, const int* seatRow = NULL, const char* seatCol = NULL );
	Reservation( const Reservation &reservationToCopy );
	~Reservation();
	
	std::string getReservationID();
	int getReservationCode();
	int getFlightNo();
	void showReservation();
	
private:
	std::string reservation;
	int reservationCode;
	int flightNumber;
};

#endif // RESERVATION_H
 