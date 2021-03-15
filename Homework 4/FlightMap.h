//Arda Icoz
//21901443
//Section 1

#ifndef FLIGHTMAP_H
#define FLIGHTMAP_H
#include "Stack.h"
#include <string>


class FlightMap {
public:
	FlightMap( const std::string cityFile, const std::string flightFile );
	~FlightMap();
	
	void displayAllCities() const;
	void displayAdjacentCities( const std::string cityName ) const;
	void displayFlightMap() const;
	
	void findFlights( const std::string deptCity, const std::string destCity ) const;
	void findLeastCostFlight( const std::string deptCity, const std::string destCity ) const;
	
	void runFlightRequests( const std::string requestFile ) const;
	
	//extra functions
	int getCitySize() const;
	int getIndexFromCitiesList( const std::string cityName ) const;
	void printGraph() const;
	
private:
	int **graph;
	std::string *citiesList;
	bool *citiesVisited;
	int citySize;
	//Stack *stack = new Stack();
	
	void initializeCitySize( const std::string cityFile );
	void initializeCitiesList( const std::string cityFile );
	void createAdjacency( const std::string flightFile );
	void clearVisited();
	void setVisited( const int index, const bool choice );
};

#endif // FLIGHTMAP_H
