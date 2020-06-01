/// The VICTIM implementation
#include "victim.h"
#include <iostream>

Victim::Victim(const string& name, const string& placeOfOrigin, const int& age, const string& photo)
{
	this->name = name;
	this->placeOfOrigin = placeOfOrigin;
	this->age = age;
	this->photo = photo;
}

ostream& operator << (ostream& out, const Victim& v) // file format
{
    out << v.name << ',' << v.placeOfOrigin << ',' << v.age << ',' << v.photo << endl;
    return out;
}

istream& operator >> (istream& in, Victim& v)
{
	string line,token;
	getline(in, line);
	if (line == "")
		return in;
	stringstream tokenStream(line);
	getline(tokenStream, token, ',');
	v.name = token;
	getline(tokenStream, token, ',');
	v.placeOfOrigin = token;
	getline(tokenStream, token, ',');
	v.age = stoi(token);
	getline(tokenStream, token, ',');
	v.photo = token;
    return in;
}

string Victim::toString()  //list format
{
	return "NAME: " + this->name + string(18-name.size(), ' ') + 
		   "PLACE OF ORIGIN: " + this->placeOfOrigin + string(12 - placeOfOrigin.size(), ' ') +
		   "AGE: " + to_string(this->age) + string(5-to_string(age).size(), ' ') +
		   "PHOTO: " + this->photo;
}

string Victim::toUnFmtString()  //list format
{
	return "NAME: " + this->name + " - " +
		"PLACE OF ORIGIN: " + this->placeOfOrigin + " - "  +
		"AGE: " + to_string(this->age) + " - "  +
		"PHOTO: " + this->photo;
}

string Victim::getHTMLString() const
{
	return "<tr><td>" + name + "</td>"
		+ "<td>" + placeOfOrigin + "</td>"
		+ "<td>" + to_string(age) + "</td>"
		+ "<td>" + photo + "</td></tr>";
}
