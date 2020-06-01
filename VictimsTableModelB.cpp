#include "VictimsTableModelB.h"

int VictimsTableModelB::rowCount(const QModelIndex& parent) const
{
	return this->assistantRepo->getVictims().size();
}

int VictimsTableModelB::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant VictimsTableModelB::data(const QModelIndex& index, int role) const
{
	int row = index.row(), col = index.column();
	Victim currentVictim = this->assistantRepo->getVictims()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (col)
		{
		case 0:
			return QString::fromStdString(currentVictim.getName());
		case 1:
			return QString::fromStdString(currentVictim.getPlaceOfOrigin());
		case 2:
			return QString::number(currentVictim.getAge());
		case 3:
			return QString::fromStdString(currentVictim.getPhoto());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant VictimsTableModelB::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Name"; 
			case 1:
				return "Place of origin"; 
			case 2:
				return "Age"; 
			case 3:
				return "Photo"; 
			default:
				break;
			}
		}
	}
	return QVariant();
}

bool VictimsTableModelB::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if(role != Qt::EditRole)
		return false;

	int row = index.row(), col = index.column();

	Victim& currentVictim = this->assistantRepo->getVictims()[row];

	switch (col)
	{
	case 1:
	{
		string placeOfOrigin{ value.toString().toStdString() };
		currentVictim.setPlaceOfOrigin(placeOfOrigin);
		break;
	}
	case 2:
	{
		string age{ value.toString().toStdString() };
		currentVictim.setAge(stoi(age));
		break;
	}
	case 3:
	{
		string photo{ value.toString().toStdString() };
		currentVictim.setPhoto(photo);
		break;
	}
	default:
		break;
	}

	emit dataChanged(index, index);
	return true;
}

Qt::ItemFlags VictimsTableModelB::flags(const QModelIndex& index) const
{
	int col = index.column();
	if (col == 0)
		return Qt::ItemFlags{};
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void VictimsTableModelB::update()
{
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}



