#pragma once
#include "../controller/controller.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class consoleUI
{
private:
	Service& srv;
	bool sqlRepo;

public:
	// constructor
	consoleUI(Service& s) : srv(s), sqlRepo(false) {}
	void run();

private:
	static void printHelp();
	static void printVictims(vector<Victim> victims);
	static bool is_number(const string& s);
	static string trim(const string& str);
	static vector<string> split(const string& s, char delimiter);
	void setFileLocation();
	void setMylistFile();
	void runMorgueAdmin();
	void runMorgueAssistant();
	void adminAddVictim();
	void adminUpdateVictim();
	void adminDeleteVictim();
	void adminDisplayVictims();
	void assistantDisplayNext();
	void assistantSaveCurrent();
	void assistantFilterVictims();
	void assistantDisplayVictims();
};