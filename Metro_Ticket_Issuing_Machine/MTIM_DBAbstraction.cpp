#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#include<ctime>
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

	// transactions (id INTEGER PRIMARY KEY, from TEXT, to TEXT, time TEXT, fare INTEGER)
	string sql = "CREATE TABLE IF NOT EXISTS transactions (depart TEXT, arrive TEXT, timeOfJourney TEXT, fare INTEGER);";


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
						return;
					}
				}
				catch(string e) {
					cout << e << endl;
					return;
				}
			}
		}
	}
}

void MTIM_DBAbstraction::bookTickit() {

	int userChoiceId[2] = { 0,0 };
	string userChoiceStation[2];




	string sql = "SELECT stations.id, stations.stationName FROM stations ORDER BY stations.id";
	string stations[12];
	int stationsId[12]={0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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

		//Taking usert departing station
	label_1:
		system("CLS");
		cout << "\n\n" << endl;
		metroGraphic("metro_route.txt");
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\t\t\t\t\tChoose departing station from the options below. \n";
		cout << "\t\t\t\t\tChoose a number corresponding to the station you want to Select. " << endl;
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		for (i = 0; i < 12; i++) {
			cout << "\t\t\t\t\t" << stationsId[i] << ".	" << stations[i] << "\n";
		}
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\tChoose From : ";
		cin >> userChoiceId[0];
		if (userChoiceId[0] > 12 || userChoiceId[0] < 1) {
			cout << "\t\t\t\t\tEnter valid station number" << endl;
			system("PAUSE");
			goto label_1;
		}
		else {
			userChoiceStation[0] = stations[userChoiceId[0] - 1];
		}cout << endl;
		system("PAUSE");

		system("CLS");
		cout << "\n\n" << endl;
		metroGraphic("metro_route.txt");
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\t\t\t\t\tChoose arriving station from the options below. \n";
		cout << "\t\t\t\t\tChoose a number corresponding to the station you want to Select. " << endl;
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		for (i = 0; i < 12; i++) {
			cout << "\t\t\t\t\t" << stationsId[i] << ".	" << stations[i] << "\n";
		}
		cout << "\t\t\t\t\t__________________________________________________________________" << endl;
		cout << "\n\t\t\t\t\tChoose To : ";
		cin >> userChoiceId[1];
		if (userChoiceId[1] > 12 || userChoiceId[1] < 1 || userChoiceId[0] == userChoiceId[1]) {
			cout << "\t\t\t\t\tEnter valid station number" << endl;
			system("PAUSE");
			goto label_1;
		}
		else {
			userChoiceStation[1] = stations[userChoiceId[1] - 1];
		}
		cout << endl;




	}
	catch (string e) {
		cout << e << endl;
		return;
	}

	//to get fare
	int journeyFare = getFare(userChoiceId);
	if (updateTransaction(userChoiceStation, journeyFare)) {
		// to print recipt
		recipt(journeyFare, userChoiceStation);
	}
	



}

int MTIM_DBAbstraction::getFare(int* userChoicesStation) {
	int fare = 0;
	int tempResult=0;
	int departId = userChoicesStation[0];
	int arriveId = userChoicesStation[1];
	
	//checking if user entered 0  

	if (departId == 0 && arriveId == 0) {
		return 0;
	}
	
	// evaluating tempResult

	if (departId > arriveId) {
		tempResult = departId - arriveId;
	}
	else if (arriveId > departId) {
		tempResult = arriveId - departId ;
	}
	else {
		return 0;
	}

	// evaluating fare

	if (tempResult == 1) {
		fare = 10;
	}
	else if (tempResult == 2 || tempResult == 3 || tempResult == 4) {
		fare = 20;
	}
	else if (tempResult == 5 || tempResult == 6 || tempResult == 7 || tempResult == 8) {
		fare = 30;
	}
	else if (tempResult == 9 || tempResult == 10 || tempResult == 11) {
		fare = 40;
	}
	else {
		fare = 0;
	}
	return fare;
}

void MTIM_DBAbstraction::recipt(int fare, string* userChoicesStation) {

	system("CLS");
	time_t now = time(0);		//getting local time 
	char* date = ctime(&now); 	//Converting toa string 
	cout << "\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t\t\t|" << setw(36) << "MUMBAI METRO" << setw(27) << "|" << endl;
	cout << "\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t\t\t  Origin :" << userChoicesStation[0] << endl;
	cout << "\t\t\t\t\t  Destination :" << userChoicesStation[1] << endl;
	cout << "\t\t\t\t\t  Amount : "<<fare<<" Rupees." << endl;
	cout << "\t\t\t\t\t  Date : " << date << endl;
	cout << "\t\t\t\t\t        *********************************************         " << endl;
	cout << "\t\t\t\t\t          Journey to be completed on the issue date. " << endl;
	cout << "\t\t\t\t\t        *********************************************         " << endl;
	cout << "\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	system("PAUSE");

}

bool MTIM_DBAbstraction::updateTransaction(string* userChoicesStation, int fare) {

	bool retVal = false;
	time_t now = time(0);
	string date = ctime(&now);
	string sql = "INSERT INTO transactions(depart, arrive, timeOfJourney, fare) VALUES(?,?,?,?);";
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
	try {
		if (statusOfPrep != SQLITE_OK) {
			throw(string)"Error : Preparing Statement.";
		}

		sqlite3_bind_text(myStatement, 1, userChoicesStation[0].c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 2, userChoicesStation[1].c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(myStatement, 3, date.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(myStatement, 4, fare);


		try {
			retVal = executeQueryNoResultsBack(myStatement);
			if (retVal == false) {
				throw (string)"Error : Inserting Into Transactions Table";
			}

		}
		catch (string e) {
			cout << e << endl;
			return retVal;
		}
		
	}
	catch (string e) {
		cout << e << endl;
		return retVal;
	}

	return retVal;
}