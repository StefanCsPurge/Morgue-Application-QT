#include "action.h"

void ActionAdminAdd::executeUndo()
{
	this->repo.deleteVictim(addedVictim);
}

void ActionAdminAdd::executeRedo()
{
	this->repo.addVictim(addedVictim);
}

void ActionAdminRemove::executeUndo()
{
	this->repo.addVictim(removedVictim);
}

void ActionAdminRemove::executeRedo()
{
	this->repo.deleteVictim(removedVictim);
}

void ActionAdminUpdate::executeUndo()
{
	this->repo.updateVictim(oldVictim);
}

void ActionAdminUpdate::executeRedo()
{
	this->repo.updateVictim(newVictim);
}

void ActionAssistantSave::executeUndo()
{
	this->adminRepo.addVictim(savedVictim);
	this->assistantRepo.deleteVictim(savedVictim);
}

void ActionAssistantSave::executeRedo()
{
	this->assistantRepo.addVictim(savedVictim);
	this->adminRepo.deleteVictim(savedVictim);
}