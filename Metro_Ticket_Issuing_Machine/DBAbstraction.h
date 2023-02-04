#pragma once
#include<string>
#include"sqlite3.h"
using namespace std;

class DBAbstraction {

public:
	DBAbstraction(string pathToFile);
	~DBAbstraction();

protected:
	sqlite3* db;

	bool executeQueryNoResultsBack(sqlite3_stmt* myStatement);
	bool executeQueryNoResultsBack(string sql);
	bool prepareQueryWithResults(string sql, sqlite3_stmt*& myStatement);

};