#pragma once
#include "../domain/victim.h"
#include "../exceptions/exceptions.h"
#include <vector>
#include <fstream>


class Repository
{
protected:
	vector<Victim> victims;
	int iterPos;
public:
	Repository() : iterPos(0) {}
	virtual Victim getVictim(const string& name);

	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	virtual void addVictim(const Victim& v);

	/*	Updates a victim in the repository.
		Input: newVictim - Victim
		Output: the victim is updated in the repository */
	virtual void updateVictim(const Victim& newVictim);

	/*	Deletes a victim from the repository.
		Input: name - string (the name of the victim to remove)
		Output: the victim is eliminated from the repository */
	virtual void deleteVictim(const Victim& v);

	/// Gets an immutable DynamicVector with all the victims
	virtual vector<Victim>& getVictims() { return this->victims; }

	/// Iterate through the victims
	virtual Victim getNextVictim();

	virtual void openInApplication();

	virtual ~Repository() {}
};

class FileRepository: public Repository
{
private:
	string victimsFile;
	void loadVictimsFromFile();
	void writeVictimsToFile(vector<Victim>);

public:
	///Default constructor
	FileRepository(const string& file = "") : victimsFile(file) { loadVictimsFromFile(); }

	void setVictimsFile(const string& filePath);

	Victim getVictim(const string& name) override;

	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	void addVictim(const Victim& v) override;

	/*	Updates a victim in the repository.
		Input: newVictim - Victim
		Output: the victim is updated in the repository */
	void updateVictim(const Victim& newVictim) override;

	/*	Deletes a victim from the repository.
		Input: name - string (the name of the victim to remove)
		Output: the victim is eliminated from the repository */
	void deleteVictim(const Victim& v) override;

	/// Iterate through the victims
	Victim getNextVictim() override;
};


/// Default txt class for the assistant repository
class AssistantTxtRepository: public Repository
{
protected:
	string file;
	virtual void writeVictimsToFile() const;

public:
	AssistantTxtRepository(string filePath = "");

	/*	Adds a victim to the repository.
		Input: v - Victim
		Output: the victim is added to the repository */
	virtual void addVictim(const Victim& v) override;

	virtual void openInApplication() override;

	virtual ~AssistantTxtRepository() {}
};
