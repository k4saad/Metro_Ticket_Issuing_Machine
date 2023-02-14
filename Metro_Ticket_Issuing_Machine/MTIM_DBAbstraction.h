#pragma once
#include"DBAbstraction.h"

class MTIM_DBAbstraction : DBAbstraction {

public:
	MTIM_DBAbstraction(string pathToFile);
	void recipt(int fare, string* userChoicesStation);
	void bookTickit();
	void metroGraphic(string graphicFilePath);
	int getFare(int* userChoicesId);
	bool updateTransaction(string* userChoicesStation, int fare);
private:
	void createStationsTable();
	void createTransactionsTable();
	void insertStations();
};