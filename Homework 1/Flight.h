//Author: Arda İçöz
//ID: 21901443

#ifndef FLIGHT_H
#define FLIGHT_H

class Flight {
public:
	Flight( const int newFlightNo = 0, const int newRowNo = 0, const int newSeatNo = 0 );
	Flight( const Flight &flightToCopy );
	~Flight();
	Flight& operator=( const Flight& );
	
	void showFlight();
	void printSeatNumbers();
	void changeAvailability( const int index, const bool availability );
	void printAvailability();
	int findIndexOfSeatNum( const int seatNum );
	int availableSeatNum();
	int getFlightNo();
	bool isEmpty( const int index );
	bool getSeatAvailability( const int index );
	void setTrueAvailability();

private:
	int flightNo;
	int rowNo;
	int seatNo;
	int availableSeats;
	int *seatNumbers;
	bool *seatAvailability;
};

#endif // FLIGHT_H
