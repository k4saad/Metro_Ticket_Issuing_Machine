#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#include"MTIM_DBAbstraction.h"

using namespace std;

MTIM_DBAbstraction::MTIM_DBAbstraction(string pathToFile) : DBAbstraction(pathToFile) {

	//creating table and inserting stations in to one 
	metroGraphic("metro_route.txt");
	createStationsTable();
	createTransactionsTable();
	insertStations();
}

void MTIM_DBAbstraction::metroGraphic(string graphicFilePath) {
	ifstream inputFile(graphicFilePath);
	try {
		if (!inputFile) {
			throw (string)"Error : Opening File";
		}
		char str[1000];
		while (inputFile) {
			inputFile.getline(str, 1000);
			if (inputFile) {
				cout << str << endl;
			}
		}
	}
	catch (string e) {
		cout << e << endl;
	}
}

void MTIM_DBAbstraction::createStationsTable() {

	// stations (id, stationName)
	string sql = "CREATE TABLE IF NOT EXISTS stations(id INTEGER PRIMARY KEY, stationName TEXT NOT NULL);";


	try {
		// executing the query and checking it 
		bool querySuccess = executeQueryNoResultsBack(sql);
		if (querySuccess == false) {
			throw (string)"Error : Creating Stations Table";
		}
	}
	catch (string e) {
		cout << e << endl;
	}
}


void MTIM_DBAbstraction::createTransactionsTable() {

	// transactions (id INTEGER PRIMARY KEY, from TEXT, to TEXT, time TEXT, cost INTEGER)
	string sql = "CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY AUTOINCREMENT, depart TEXT, arrive TEXT, timeOfJourney TEXT, cost DOUBLE);";


	try {
		// executing the query and checking it 
		bool querySuccess = executeQueryNoResultsBack(sql);
		if (querySuccess == false) {
			throw (string)"Error : Creating Transactions Table";
		}
	}
	catch (string e) {
		cout << e << endl;
	}
}

void MTIM_DBAbstraction::insertStations() {
	
	// checking if value is to be added or not
	string sql = "SELECT id FROM stations";
	sqlite3_stmt* myStatement;
	if (prepareQueryWithResults(sql, myStatement)) {
		int statusOfStep = sqlite3_step(myStatement);
		if (statusOfStep != SQLITE_ROW) {
			sqlite3_finalize(myStatement);
			// inserting stations in the table
			sql = "INSERT INTO stations(id, stationName) VALUES(?,?);";
			string stations[12] = { "Ghatkopar", "Jagruti Nagar", "Asalpha", "Saki Naka", "Marol Naka", "Airport Road", "Chakala", "Western Express Highway", "Andheri", "Azad Nagar", "D N Nagar", "Versova" };
			for (int i = 0; i < 12; i++) {
				int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);

				// adding parameter
				try{ 
					if (statusOfPrep != SQLITE_OK) {
						throw (string)"Error : Preparing Statement";
					}
					sqlite3_bind_int(myStatement, 1, i + 1);
					sqlite3_bind_text(myStatement, 2, stations[i].c_str(), -1, SQLITE_STATIC);

					bool querySuccess = executeQueryNoResultsBack(myStatement);

					try {
						if (querySuccess == false) {
							throw (string)"Error : Inserting Into Station Table";
						}
					}
					catch (string e) {
						cout << e << endl;
					}
				}
				catch(string e) {
					cout << e << endl;
				}
			}
		}
	}
}

void MTIM_DBAbstraction::bookTickit() {

	int userChoice[2];

	system("CLS");
	cout <<"\n\n"<< endl;
	metroGraphic("metro_route.txt");
	
	
	string sql = "SELECT stations.id, stations.stationName FROM stations ORDER BY stations.id";
	string stations[12];
	int stationsId[12];
	sqlite3_stmt* myStatement;
	try {
		// preparing query and checking it 
		bool preparingSuccess = prepareQueryWithResults(sql, myStatement);
		if (preparingSuccess == false) {
			throw (string)"Error : Preparing Query";
		}
		int i = 0;
		int statusOfStep = sqlite3_step(myStatement);
		while (statusOfStep == SQLITE_ROW) {
			stationsId[i] = sqlite3_column_int(myStatement, 0);
			stations[i] = (char*)sqlite3_column_text(myStatement, 1);
			i++;
			statusOfStep = sqlite3_step(myStatement);
		}

		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\t\t\t\t\tChoose departing station from the options below. \n";
		cout << "\t\t\t\t\tChoose a number corresponding to the station you want to Select. " << endl;
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		for (int i = 0; i < 12; i++) {
			cout << "\t\t\t\t\t" << stationsId[i] << ".	" << stations[i] << "\n";
		}
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\tChoose : ";
		cin >> userChoice[0];
		cout << endl;
	}
	catch (string e) {
		cout << e << endl;
	}
}