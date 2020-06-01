#include "controller.h"

#include <qdebug.h>

void Service::createMylistRepo(const string& filePath, const string& extension)
{
	if (extension == "")
		assistantRepo = new Repository();
	else if (extension == "txt")
		assistantRepo = new AssistantTxtRepository(filePath);
	else if (extension == "csv")
		assistantRepo = new CSVassistantRepo(filePath);
	else if (extension == "html")
		assistantRepo = new HTMLassistantRepo(filePath);
	else throw exception("Invalid mylist file extension!\n");
	this->model_B = new VictimsTableModelB{ assistantRepo };
}

vector<Victim> Service::getAllVictims() const
{
	return this->repo->getVictims();
}

void Service::addVictimToRepo(const string& name, const string& placeOfOrigin, int age, const string& photo)
{
	Victim v{ name,placeOfOrigin,age,photo };
	VictimValidator::validateVictim(v);
	this->repo->addVictim(v);
	
	auto ptrA = make_unique<ActionAdminAdd>(*repo, v);
	undo_stack_A.push_back(move(ptrA));
	redo_stack_A.clear();
}

void Service::updateVictim(const string& name, const string& newPlaceOfOrigin, int newAge, const string& newPhoto)
{
	Victim newV{ name,newPlaceOfOrigin,newAge,newPhoto };
	VictimValidator::validateVictim(newV);
	Victim oldV = this->repo->getVictim(name);
	this->repo->updateVictim(newV);

	auto ptrU = make_unique<ActionAdminUpdate>(*repo,oldV,newV);
	undo_stack_A.push_back(move(ptrU));
	redo_stack_A.clear();
}

void Service::deleteVictim(const string& name)
{
	Victim v(name,"dummyPlace",0,"dummyPhoto.png");
	VictimValidator::validateVictim(v);
	auto deletedVictim = this->repo->getVictim(name);
	this->repo->deleteVictim(v);

	auto ptrR = make_unique<ActionAdminRemove>(*repo,deletedVictim);
	undo_stack_A.push_back(move(ptrR));
	redo_stack_A.clear();
}

void Service::nextVictim()
{
	this->currentVictim = this->repo->getNextVictim();
}

Victim Service::getCurrentVictim()
{
	return this->currentVictim;
}

Victim Service::getVictim(const string& name)
{
	return this->repo->getVictim(name);
}

void Service::moveVictimToAssistantList(const string& name)
{
	/// Transfers a victim to the assistant's list
	Victim v = repo->getVictim(name);
	this->assistantRepo->addVictim(v); 
	this->repo->deleteVictim(v);
	this->model_B->update();

	auto ptrS = make_unique<ActionAssistantSave>(*repo,*assistantRepo, v);
	undo_stack_B.push_back(move(ptrS));
	redo_stack_B.clear();
}

void Service::showAssistantVictims() const
{
	this->assistantRepo->openInApplication();
}

vector<Victim> Service::filterVictims(const string& orig, int age) const
{
	vector<Victim> newV, victims = getAllVictims();
	auto goodVictim = [&](const Victim& v) {return v.getAge() < age && (orig.size() && v.getPlaceOfOrigin() == orig || !orig.size()); };
	copy_if(victims.begin(), victims.end(), back_inserter(newV), goodVictim);
	return newV;
}

void Service::undoAdmin()
{
	if (!undo_stack_A.size())
		throw exception("Undo limit reached!");
	auto action = move(undo_stack_A.back());
	undo_stack_A.pop_back();
	action->executeUndo();
	redo_stack_A.push_back(move(action));
}

void Service::redoAdmin()
{
	if (!redo_stack_A.size())
		throw exception("Redo limit reached!");
	auto action = move(redo_stack_A.back());
	redo_stack_A.pop_back();
	action->executeRedo();
	undo_stack_A.push_back(move(action));
}

void Service::undoAssistantSave()
{
	if (!undo_stack_B.size())
		throw exception("Undo limit reached!");
	auto action = move(undo_stack_B.back());
	undo_stack_B.pop_back();
	action->executeUndo();
	redo_stack_B.push_back(move(action));
	this->model_B->update();
}

void Service::redoAssistantSave()
{
	if (!redo_stack_B.size())
		throw exception("Redo limit reached!");
	auto action = move(redo_stack_B.back());
	redo_stack_B.pop_back();
	action->executeRedo();
	undo_stack_B.push_back(move(action));
	this->model_B->update();
}

void Service::addEntries()
{
	try {
		addVictimToRepo("Danutz Ilie", "Brasov", 19, "deadNakedDanutz.jpeg");
		addVictimToRepo("Trumpy Boi", "USA", 60, "deadEagle.jpeg");
		addVictimToRepo("YOLO Lover", "Tanzania", 18, "epicParachuteFail.jpeg");
		addVictimToRepo("Hatz Johnule", "Bucales", 27, "tooHeavyLifting.png");
		addVictimToRepo("Gucci Gang", "Italy", 69, "valueOverload.png");
		addVictimToRepo("Costel Biju", "Japan", 19, "hangedEmo.jpeg");
		addVictimToRepo("Edward Snowden", "Russia", 35, "NSA&CIAgotPissed.jpeg");
		addVictimToRepo("Chuck Norris", "Everywhere", 420, "missingBody.wtf");
		addVictimToRepo("Anatoly Boris", "Ukraine", 33, "ChernobySurprise.jpeg");
		addVictimToRepo("Giovanni Ferrari", "Italy", 44, "coronaVirusHadFun.jpeg");
	}
	catch(exception&){ return; }
}