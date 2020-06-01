#pragma once
#include "repository.h"


class HTMLassistantRepo : public AssistantTxtRepository
{
private:
	void writeVictimsToFile() const override;

public:
	HTMLassistantRepo(string filePath = "");
	void addVictim(const Victim& v) override;
	void openInApplication() override;
	~HTMLassistantRepo() {}
};