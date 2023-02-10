#pragma once
#include"DBAbstraction.h"

class MTIM_DBAbstraction : DBAbstraction {

public:
	MTIM_DBAbstraction(string pathToFile);
	void recipt();
	void bookTickit();
	void metroGraphic(string graphicFilePath);


private:
	void createStationsTable();
	void createTransactionsTable();
	void insertStations();
};