#pragma once
#include"DBAbstraction.h"

class MTIM_DBAbstraction : DBAbstraction {

public:
	MTIM_DBAbstraction(string pathToFile);

private:
	void createStationsTable();
	void createTransactionsTable();
	void insertStations();
};