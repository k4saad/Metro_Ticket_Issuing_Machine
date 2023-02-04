#include<iostream>
#include"DBAbstraction.h"
#include"sqlite3.h"

using namespace std;

DBAbstraction::DBAbstraction(string pathToFile) {
	int statusOfOpen = sqlite3_open(pathToFile.c_str(), &db);

	if (statusOfOpen != SQLITE_OK) {
		db = NULL;
	}
}

DBAbstraction::~DBAbstraction() {

	if (db != NULL) {
		sqlite3_close(db);
		db = NULL;
	}
}


bool DBAbstraction::executeQueryNoResultsBack(sqlite3_stmt* myStatement) {
	bool retVal = false;
	int statusOfStep = sqlite3_step(myStatement);
	if (statusOfStep == SQLITE_DONE){
		retVal = true;
	}
	sqlite3_finalize(myStatement);
	return retVal;
}

bool DBAbstraction::executeQueryNoResultsBack(string sql) {
	bool retVal = false;
	sqlite3_stmt* myStatement;
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
	if (statusOfPrep == SQLITE_OK) {
		retVal = executeQueryNoResultsBack(myStatement);
	}
	return retVal;
}

bool DBAbstraction::prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement) {
	bool retVal = false; 
	int statusOfPrep = sqlite3_prepare_v2(db, sql.c_str(), -1, &myStatement, NULL);
	if (statusOfPrep == SQLITE_OK) {
		retVal = true;
	}
	return retVal;
}