#pragma once
#include "../repository/repository.h"
#include "../repository/CSVassistantRepository.h"
#include "../repository/HTMLassistantRepository.h"
#include "../domain/victimValidator.h"
#include "../domain/action.h"
#include "../VictimsTableModelB.h"
#include <algorithm>
#include <memory>

class Service
{
private:
	Repository* repo;
	Repository* assistantRepo;
	Victim currentVictim;
	VictimsTableModelB* model_B;

	vector<unique_ptr<Action>> undo_stack_A;
	vector<unique_ptr<Action>> redo_stack_A;
	vector<unique_ptr<Action>> undo_stack_B;
	vector<unique_ptr<Action>> redo_stack_B;

public:
	Service(Repository* r): repo(r), assistantRepo(NULL), model_B(NULL) {}

	void createMylistRepo(const string& filePath,const string& extension);

	vector<Victim> getAllVictims() const;

	VictimsTableModelB* getAssistantModel() { return this->model_B; }
	
	// Adds some entries for testing purposes
	void addEntries();
	
	/// Adds a victim with the given data to the repository.
	void addVictimToRepo(const string& name, const string& placeOfOrigin,int age, const string& photo);

	/// Updates a victim with the given data.
	void updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto);

	/// Deletes the victim with a given name.
	void deleteVictim(const string& name);

	/// Gets the next victim for the assistant.
	void nextVictim();

	/// Gets the current victim for the assistant.
	Victim getCurrentVictim();

	/// Gets the victim with the given name.
	Victim getVictim(const string& name);

	/// Moves a victim to the assistant's "to be transferred" list
	void moveVictimToAssistantList(const string& name);

	void showAssistantVictims() const;

	/// Selects the victims from a given placeOfOrigin that have the age less than a given age
	vector<Victim> filterVictims(const string& placeOfOrigin, int age) const;

	void undoAdmin();

	void redoAdmin();

	void undoAssistantSave();

	void redoAssistantSave();

	~Service() { delete repo;  delete assistantRepo; delete model_B; }
};