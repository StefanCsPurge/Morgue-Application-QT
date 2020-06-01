#include "CSVassistantRepository.h"
#include <algorithm>
#include <Windows.h>

CSVassistantRepo::CSVassistantRepo(string filePath)
{
	ofstream fout(filePath);
	if (fout.fail())
		filePath = "repository/selectedVictims.csv";
	this->file = filePath;
	fout.close();
	writeVictimsToFile();
}

void CSVassistantRepo::writeVictimsToFile() const
{
	ofstream fout(file);
	fout << "Name, Place of origin, Age, Picture\n";
	for_each(victims.begin(), victims.end(), [&](const Victim& v) {fout << v; });
	fout.close();
}

void CSVassistantRepo::addVictim(const Victim& v)
{
	this->victims.push_back(v);
	fstream fout;
	fout.open(file, ios::app); // append instead of overwrite
	fout << v;
	fout.close();
}

void CSVassistantRepo::openInApplication()
{
	string path = "\"" + this->file + "\"";
	ShellExecuteA(NULL, NULL, "C:/Program Files/Microsoft Office/root/Office16/EXCEL.EXE", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}
