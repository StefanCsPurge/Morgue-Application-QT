#include "HTMLassistantRepository.h"
#include <algorithm>
#include <Windows.h>

HTMLassistantRepo::HTMLassistantRepo(string filePath)
{
	ofstream fout(filePath);
	if (fout.fail())
		filePath = "repository/selectedVictims.html";
	this->file = filePath;
	fout.close();
}

void HTMLassistantRepo::writeVictimsToFile() const
{
	ofstream fout(file);
	fout << "<!DOCTYPE html>\n<html><head><title>The morgue victims</title></head><body>\n";
	fout << "<table border=\"4\">\n";
	fout << "<tr><td>Name</td><td>Place of origin</td><td>Age</td><td>Picture</td></tr>\n";
	for_each(victims.begin(), victims.end(), [&](const Victim& v) {fout << v.getHTMLString() << endl; });
	fout << "</table></body></html>";
	fout.close();
}

void HTMLassistantRepo::addVictim(const Victim& v)
{
	this->victims.push_back(v);
	writeVictimsToFile();
}

void HTMLassistantRepo::openInApplication()
{
	string path = "\"" + this->file + "\"";
	if (ShellExecuteA(NULL, NULL, "C:/Program Files/Mozilla Firefox/firefox.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED) < (HINSTANCE)32)
		ShellExecuteA(NULL, NULL, "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}