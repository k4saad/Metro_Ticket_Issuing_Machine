#include<iostream>
#include<vector>
#include<string>
#include"MTIM_DBAbstraction.h"

using namespace std;

MTIM_DBAbstraction::MTIM_DBAbstraction(string pathToFile) : DBAbstraction(pathToFile) {

	//creating table and inserting stations in to one 
	createStationsTable();
	createTransactionsTable();
	insertStations();
}

void MTIM_DBAbstraction::createStationsTable() {

	// stations (id, stationName)
	string sql = "CREATE TABLE IF NOT EXISTS stations(id INTEGER PRIMARY KEY, stationName TEXT);";

	// executing the query and checking it 
	bool querySuccess = executeQueryNoResultsBack(sql);

	try {
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
	string sql = "CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY, depart TEXT, arrive TEXT, timeOfJourney TEXT, cost DOUBLE);";

	// executing the query and checking it 
	bool querySuccess = executeQueryNoResultsBack(sql);

	try {
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
				sqlite3_bind_int(myStatement, 1, i + 1);
				sqlite3_bind_text(myStatement, 2, stations[i].c_str(), -1, SQLITE_STATIC);

				bool querySuccess = executeQueryNoResultsBack(sql);

				try {
					if (querySuccess == false) {
						throw (string)"Error : Inserting Into Station Table";
					}
				}
				catch (string e) {
					cout << e << endl;
				}

				sqlite3_finalize(myStatement);
			}
		}
	}
}