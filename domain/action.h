#pragma once
#include "../repository/repository.h"

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
	virtual ~Action() {}
};

class ActionAdminAdd : public Action
{
private:
	Victim addedVictim;
	Repository& repo;
public:
	ActionAdminAdd(Repository& repo, const Victim& v) : repo(repo), addedVictim(v) {}
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdminAdd() {}
};

class ActionAdminRemove: public Action
{
private:
	Victim removedVictim;
	Repository& repo;
public:
	ActionAdminRemove(Repository& repo, const Victim& v) : repo(repo), removedVictim(v) {}
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdminRemove() {}
};

class ActionAdminUpdate : public Action
{
private:
	Victim oldVictim, newVictim;
	Repository& repo;
public:
	ActionAdminUpdate(Repository& repo, const Victim& v1, const Victim& v2) : repo(repo), oldVictim(v1), newVictim(v2) {}
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdminUpdate() {}
};

class ActionAssistantSave : public Action
{
private:
	Victim savedVictim;
	Repository& adminRepo;
	Repository& assistantRepo;
public:
	ActionAssistantSave(Repository& r1, Repository& r2, const Victim& v) : adminRepo(r1), assistantRepo(r2), savedVictim(v) {}
	void executeUndo() override;
	void executeRedo() override;
	~ActionAssistantSave() {}
};

class ActionAssistantNext : public Action
{

};