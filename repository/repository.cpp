#include "repository.h"
#include <algorithm>
#include <Windows.h>


Victim Repository::getVictim(const string& name)
{
	auto it = find(victims.begin(), victims.end(), Victim(name));
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	return *it;
}

void Repository::addVictim(const Victim& v)
{
	auto it = find(victims.begin(), victims.end(), v);
	if (it != victims.end())
		throw RepositoryException("There already exists a victim with this name!");
	victims.push_back(v);	
}

void Repository::updateVictim(const Victim& newVictim)
{
	auto it = find(victims.begin(), victims.end(), newVictim);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	*it = newVictim;
}

void Repository::deleteVictim(const Victim& v)
{
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	victims.erase(it);
	if (this->iterPos > 0)
		this->iterPos--;
}

Victim Repository::getNextVictim()
{
	if (!victims.size())
		throw RepositoryException("There are no victims!");
	if (this->iterPos == victims.size())
		this->iterPos = 0;
	Victim v = victims[iterPos];
	this->iterPos++;
	return v;
}

void Repository::openInApplication()
{
	throw RepositoryException("No file set for this repository!");
}


/// FILE Repository methods

void FileRepository::setVictimsFile(const string& filePath)
{
	ifstream fin(filePath);
	bool ok = 0;
	if (fin.good())
	{
		this->victimsFile = filePath;
		fin.close();
	}
	else {
		ofstream f(filePath);
		if (f.fail()){
			this->victimsFile = "repository/victims.txt";
			ifstream fin(victimsFile);
			if (fin.fail()){ ofstream f(victimsFile); f.close(); } 
			fin.close();
			throw RepositoryException("File couldn't be created at the provided location. Default file 'victims.txt' was set."); }
		this->victimsFile = filePath;
		f.close();
	}
	//filePath = filePath.substr(0, filePath.find_last_of('\\')+1) + "newDataFile.txt";    studiu de caz :)
}

void FileRepository::loadVictimsFromFile()
{
	if (victimsFile == "")
		throw RepositoryException("No repository file given!");
	Victim victim;
	ifstream fin(this->victimsFile);
	while (fin >> victim)
		if(victim.getName() != "")
			this->victims.push_back(victim);
	fin.close();
}

void FileRepository::writeVictimsToFile(vector<Victim> victims)
{
	if (victimsFile == "") throw RepositoryException("No repository file given!");
	ofstream fout(this->victimsFile);
	for (const Victim& victim : victims)
		fout << victim;
	fout.close();
}

Victim FileRepository::getVictim(const string& name)
{
	Victim v(name,"",0,"");
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	return *it;
}

void FileRepository::addVictim(const Victim& v)
{
	auto it = find(victims.begin(), victims.end(), v);
	if (it != victims.end())
		throw RepositoryException("There already exists a victim with this name!");
	victims.push_back(v);
	writeVictimsToFile(victims);
}

void FileRepository::updateVictim(const Victim& newVictim)
{
	auto it = find(victims.begin(), victims.end(), newVictim);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	*it = newVictim;
	writeVictimsToFile(victims);
}

void FileRepository::deleteVictim(const Victim& v)
{
	auto it = find(victims.begin(), victims.end(), v);
	if (it == victims.end())
		throw RepositoryException("There is no victim with this name!");
	victims.erase(it);
	if (this->iterPos > 0)
		this->iterPos--;
	writeVictimsToFile(victims);
}

Victim FileRepository::getNextVictim()
{
	if (!victims.size())
		throw RepositoryException("There are no victims!");
	if (this->iterPos == victims.size())
		this->iterPos = 0;
	Victim v = victims[iterPos];
	this->iterPos++;
	return v;
}


/// ASSISTANT repository

AssistantTxtRepository::AssistantTxtRepository(string filePath)
{
	ofstream fin(filePath);
	if (fin.fail())
		filePath = "repository/selectedVictims.txt";
	fin.close();
	this->file = filePath;
	ofstream fout(this->file);
	fout.close();
}

void AssistantTxtRepository::writeVictimsToFile() const
{
	ofstream fout(file);
	for_each(victims.begin(), victims.end(), [&](const Victim& v) {fout << v; });
	fout.close();
}

void AssistantTxtRepository::addVictim(const Victim& v)
{
	this->victims.push_back(v);
	fstream fout;
	fout.open(file, ios::app); // append instead of overwrite
	fout << v;
}

void AssistantTxtRepository::openInApplication()
{
	string path = "\"" + this->file + "\"";
	/// Windows specific
	ShellExecuteA(NULL, NULL, "C:/Windows/system32/notepad.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}