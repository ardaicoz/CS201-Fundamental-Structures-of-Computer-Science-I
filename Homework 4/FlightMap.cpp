//Arda Icoz
//21901443
//Section 1

#include "FlightMap.h"
#include "Stack.h"
#include <fstream>
#include <iostream>
using namespace std;

FlightMap::FlightMap( const std::string cityFile, const std::string flightFile ) {
	//initializing variables first
	citySize = 0;
	citiesList = NULL;
	graph = NULL;
	citiesVisited = NULL;
	
	//reading all cities from the cityFile to determine the number of cities
	initializeCitySize( cityFile );
	
	//creating the graph, string array and citiesVisited array
	graph = new int*[citySize];
	for( int i = 0; i < citySize; i++ ) {
		graph[i] = new int[citySize];
	}
	
	citiesVisited = new bool[citySize];
	citiesList = new string[citySize];
	
	//1. initializing the graph matrix and citiesVisited array
	for (int i = 0; i < citySize; i++) {
		citiesVisited[i] = false;
			for (int j = 0; j < citySize; j++) 
				graph[i][j] = 0; 
	}
	
	//2. initializing the string array to hold all cities
	initializeCitiesList( cityFile );
	
	createAdjacency( flightFile );
}


FlightMap::~FlightMap() {
	delete[] citiesList;
	delete[] citiesVisited;
	
	for( int i = 0; i < citySize; ++i ) 
		delete [] graph[i];
	delete [] graph;
}

void FlightMap::displayAllCities() const {
	for ( int i = 0; i < citySize; i++ ) {
		cout << citiesList[i] << ",";
	}
}

void FlightMap::displayAdjacentCities( const string cityName ) const {
	int index = getIndexFromCitiesList( cityName );
	
	cout << citiesList[index] << " -> ";
	for ( int i = 0; i < citySize; i++ ) {
		if ( graph[index][i] == 1 ) {
			cout << citiesList[i] << ", ";
		}
	}
	cout << endl;
}

void FlightMap::displayFlightMap() const {
	for ( int i = 0; i < citySize; i++ ) {
		displayAdjacentCities( citiesList[i] );
	}
}

void FlightMap::findFlights( const std::string deptCity, const std::string destCity ) const {
//	cout << "Request is to fly from " << deptCity << " to " << destCity << endl;
//	
//	//marking all cities as unvisited
//	for ( int i = 0; i < citySize; i++ ) 
//		citiesVisited[i] = false;
//	
//	//pushing the deptCity and making it visited
//	stack->push(deptCity);
//	citiesVisited[getIndexFromCitiesList(deptCity)] = true;
//	
//	//pushing the first city that we can move from deptCity
//	for ( int i = 0; i < citySize; i++ ) {
//		if ( graph[getIndexFromCitiesList(deptCity)][i] == 1 ) {
//			stack->push( citiesList[i] );
//			citiesVisited[getIndexFromCitiesList(citiesList[i])] = true;
//			break;
//		}
//	}
//	
//	int count = 0;
//	while ( destCity != stack->getTop() ) {
//		for ( int i = 0; i < citySize; i++ ) {
//			if ( graph[getIndexFromCitiesList( stack->getTop() )][i] == 0 ) {
//				count++;
//			}
//		}
//		
//		if ( count == citySize ) {
//			stack->pop();
//		}
//		else {
//			for ( int i = 0; i < citySize; i++ ) {
//				if ( graph[getIndexFromCitiesList( stack->getTop() )][i] == 1 && !citiesVisited[i] ) {
//					stack->push( citiesList[i] );
//					citiesVisited[getIndexFromCitiesList(citiesList[i])] = true;
//					break;
//				}
//			}
//		}
//	}	
//	if ( stack->isEmpty() )
//		cout << "Sorry. HPAir does not fly from " << deptCity << " to " << destCity << endl;
//	else {		
//	}
}

void FlightMap::findLeastCostFlight( const std::string deptCity, const std::string destCity ) const {
	
}

void FlightMap::runFlightRequests( const std::string requestFile ) const {
	
}

int FlightMap::getCitySize() const {
	return citySize;
}

int FlightMap::getIndexFromCitiesList( const string cityName ) const {
	for ( int i = 0; i < citySize; i++ ) {
		if ( citiesList[i] == cityName ) {
			return i;
		}
	}
	return -1;
}

void FlightMap::printGraph() const {
	for (int i = 0; i < citySize; i++) 
		for (int j = 0; j < citySize; j++) 
			cout << graph[i][j] << " \n"[j == citySize-1]; 
}

void FlightMap::initializeCitySize( const string cityFile ) {
	string filename = cityFile;
	string line; //will be used in counting the lines in cityFile
	ifstream inputFile;

	inputFile.open( filename.c_str(), ios_base::in );
	while ( inputFile.eof() == false ) {
		while ( getline(inputFile,line) )
			citySize++;
	}
	inputFile.close();
}

void FlightMap::initializeCitiesList( const string cityFile ) {
	//putting the cities into this string array
	string tempFileName = cityFile;
	ifstream tempFile;
	string text;
	int loop = 0;
	
	tempFile.open( tempFileName.c_str(), ios_base::in );
	while ( tempFile.eof() == false ) {
		getline( tempFile, text, '\n' );
		citiesList[loop] = text;
		loop++;
	}
	tempFile.close();
}

void FlightMap::createAdjacency( const string flightFile ) {
	string firstCity = "";
	string secondCity = "";
	string tempString = "";
	int firstCityIndex = 0;
	int secondCityIndex = 0;
	
	string filename = flightFile;
	ifstream inputFile;
	
	inputFile.open( filename.c_str(), ios_base::in );
	while ( inputFile.eof() == false ) {
		getline( inputFile, firstCity, ',' );
		getline( inputFile, secondCity, ',' );
		
		firstCityIndex = getIndexFromCitiesList( firstCity );
		secondCityIndex = getIndexFromCitiesList( secondCity );
		graph[firstCityIndex][secondCityIndex] = 1;
		
		getline( inputFile, tempString , '\n' );
	}
}

void FlightMap::clearVisited() {
	for ( int i = 0; i < citySize; i++ ) 
		citiesVisited[i] = false;
}

void FlightMap::setVisited( const int index, const bool choice ) {
	citiesVisited[index] = choice;
}