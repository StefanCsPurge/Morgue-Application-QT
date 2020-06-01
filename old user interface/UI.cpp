#include "UI.h"

void consoleUI::printHelp()
{
	cout << "The possible commands are: \n";
	cout << "\tfileLocation file_path (needed for repository)\n";
	cout << "\tmylistLocation file_path (needed for repository)\n";
	cout << "\tmode X (e.g. mode A - works off-mode)\n";
	cout << "   In morgue administrator mode:\n";
	cout << "\t\t add name, placeOfOrigin, age, photograph\n";
	cout << "\t\t update name, newPlaceOfOrigin, newAge, newPhotograph\n";
	cout << "\t\t delete name\n";
	cout << "\t\t list\n";
	cout << "   In morgue assistant mode:\n";
	cout << "\t\t next\n";
	cout << "\t\t save name\n";
	cout << "\t\t list placeOfOrigin, age\n";
	cout << "\t\t mylist\n";
	cout << "\thelp (any mode)\n";
	cout << "\texit (to exit the current mode/program)\n\n";
}

void consoleUI::setFileLocation()
{
	string fileLoc;
	getline(cin, fileLoc);
	this->srv.setFile(trim(fileLoc));
}

void consoleUI::setMylistFile()
{
	string fileLoc,extension;
	getline(cin, fileLoc);
	fileLoc = trim(fileLoc);
	extension = fileLoc.substr(fileLoc.find_last_of(".")+1);
	this->srv.createMylistRepo(fileLoc,extension);
}

void consoleUI::printVictims(vector<Victim> victims)
{
	if (!victims.size()) { cout << "There are no victims!\n"; return; }
	for_each(victims.begin(), victims.end(), [](Victim& v) {cout << v.toString() << endl; });
}

bool consoleUI::is_number(const string& s)
{
	bool ok = false;
	string::const_iterator it = s.begin();
	if (*it == '-') it++;
	while (it != s.end() && isdigit(*it)) {++it; ok = true;}
	return !s.empty() && it == s.end() && ok;
}

string consoleUI::trim(const string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
		return "";
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
	//restCmd.erase(remove_if(restCmd.begin(), restCmd.end(), isspace), restCmd.end());  this erases all spaces
}

vector<string> consoleUI::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream tokenStream(s);
	while (getline(tokenStream, token, delimiter))
		tokens.push_back(trim(token));
	return tokens;
}

void consoleUI::adminAddVictim()
{
	string restCmd;
	getline(cin, restCmd);
	vector<string> args = split(restCmd, ',');
	if (args.size() < 4) {cout << "Too few arguments!\n"; return;}
	string name = args[0];
	string placeOfOrigin = args[1];
	if (!is_number(args[2])) { cout << "Age must be a number!!\n"; return; }
	int age = stoi(args[2]);
	string photo = args[3];
	this->srv.addVictimToRepo(name, placeOfOrigin, age, photo);
}

void consoleUI::adminUpdateVictim()
{
	string restCmd;
	getline(cin, restCmd);
	vector<string> args = split(restCmd, ',');
	if (args.size() < 4) { cout << "Too few arguments!\n"; return; }
	string name = args[0];
	string newPlaceOfOrigin = args[1];
	if (!is_number(args[2])) { cout << "Age must be a number!\n"; return; }
	int newAge = stoi(args[2]);
	string newPhoto = args[3];
	this->srv.updateVictim(name, newPlaceOfOrigin, newAge, newPhoto);
}

void consoleUI::adminDeleteVictim()
{
	string name;
	getline(cin, name);
	name = trim(name);
	this->srv.deleteVictim(name);
}

void consoleUI::adminDisplayVictims()
{
	printVictims(this->srv.getAllVictims());
}

void consoleUI::assistantDisplayNext()
{
	this->srv.nextVictim();
	Victim v = this->srv.getCurrentVictim();
	cout << v.toString() << endl;
}

void consoleUI::assistantSaveCurrent()
{
	string name;
	getline(cin, name);
	name = trim(name);
	this->srv.moveVictimToAssistantList(name);
}

void consoleUI::assistantFilterVictims()
{
	vector<Victim> selectedVictims;
	string restCmd, name;
	getline(cin, restCmd);
	vector<string> args = split(restCmd, ',');
	if (!args.size()) { cout << "No arguments!\n"; return; }
	if (args.size() == 1)
	{
		if (!is_number(args[0])) { cout << "Invalid age!\n"; return; }
		int age = stoi(args[0]);
		selectedVictims = this->srv.filterVictims("", age);
	}
	else
	{
		if (!is_number(args[1])) { cout << "Invalid age!\n"; return; }
		int age = stoi(args[1]);
		selectedVictims = this->srv.filterVictims(args[0], age);
	}
	printVictims(selectedVictims);
}

void consoleUI::assistantDisplayVictims()
{
	this->srv.showAssistantVictims();
}

void consoleUI::runMorgueAdmin()
{
	cout << "You are now in EC-PD MORGUE administrator mode. Have fun with the corpses!\n";
	string cmd;
	while (true)
	{
		cout << ">>";
		cin >> cmd;
		try {
			if (cmd == "add")
				adminAddVictim();
			else if (cmd == "update")
				adminUpdateVictim();
			else if (cmd == "delete")
				adminDeleteVictim();
			else if (cmd == "list")
				adminDisplayVictims();
			else if (cmd == "help")
				printHelp();
			else if (cmd == "exit")
				exit(0);
			else if (cmd == "mode")
			{
				cin >> cmd;
				if (cmd == "B")
				{
					runMorgueAssistant();
					return;
				}
			}
			else
			{
				cout << "Non-existent command!\n";
				getline(cin, cmd);
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	cout << "You are not a morgue administrator anymore. The corpses thank you for your service.\n\n";
}

void consoleUI::runMorgueAssistant()
{
	cout << "You are now in EC-PD MORGUE assistant mode. Have fun with the corpses!\n";
	string cmd;
	while (true)
	{
		cout << ">>";
		cin >> cmd;
		try {
			if (cmd == "help")
				printHelp();
			else if (cmd == "next")
				assistantDisplayNext();
			else if (cmd == "save")
				assistantSaveCurrent();
			else if (cmd == "mylist")
				assistantDisplayVictims();
			else if (cmd == "list")
				assistantFilterVictims();
			else if (cmd == "exit")
				exit(0);
			else if (cmd == "mode")
			{
				cin >> cmd;
				if (cmd == "A")
				{
					runMorgueAdmin();
					return;
				}
			}
			else
			{
				cout << "Non-existent command!\n";
				getline(cin, cmd);
			}
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
	cout << "You are not a morgue assistant anymore. The corpses thank you for your service.\n\n";
}

void consoleUI::run()
{
	cout << "WELCOME TO THE MORGUE ! \n\n";
	cout << "Enter 'help' to see the possible commands\n\n";
	string cmd;
	bool victimsFile = false, mylistFile = false;
	while (true)
	{
		if (sqlRepo || victimsFile && mylistFile)
			cout << "Choose between:  EC-PD morgue ADMIN (mode A)  /  EC-PD morgue ASSISTANT (mode B)\n";
		else
		{
			if (!victimsFile)
				cout << "Enter victims file location (ex: fileLocation repository/victims.txt <- the default text file location) \n";
			if (!mylistFile)
				cout << "Enter mylist file (ex: mylistLocation repository/selectedVictims.csv) \n";
		}
		cout << ">>";
		cin >> cmd;
		try {
			if (cmd == "help")
				this->printHelp();
			else if (cmd == "fileLocation" && !sqlRepo)
			{
				victimsFile = true;
				setFileLocation();
				continue;
			}
			else if (cmd == "mylistLocation" && !sqlRepo)
			{
				setMylistFile();
				mylistFile = true;
				continue;
			}
			else if (cmd == "exit")
				break;
			else if (cmd == "mode" && (victimsFile && mylistFile || sqlRepo))
			{
				if (sqlRepo)
					this->srv.createMylistRepo("", "txt");
				srv.addEntries(); // we add the entries when we have a file
				cin >> cmd;
				if (cmd == "A")
					runMorgueAdmin();
				else if (cmd == "B")
					runMorgueAssistant();
				else
					cout << "N/A mode!\n";
			}
			else
				cout << "Invalid command!\n";
			getline(cin, cmd); // get rid of the remaining user garbage on the line
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
	}
}