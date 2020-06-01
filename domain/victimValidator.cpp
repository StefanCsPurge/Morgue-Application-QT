#include "victimValidator.h"
#include "../exceptions/exceptions.h"

void VictimValidator::validateVictim(const Victim& v)
{
	string error = "";
	if (v.getName() == "")
		error += "Invalid name; ";
	if (v.getName() == "Iliescu")
		error += "Reptiles are immortal! ";
	if (v.getPlaceOfOrigin() == "")
		error += "Invalid place of origin; ";
	if (v.getAge() < 0)
		error += "Invalid age; ";
	if (v.getPhoto() == "")
		error += "Invalid photo;";
	if (error != "")
		throw ValidationException(error);
}