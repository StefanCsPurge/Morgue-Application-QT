#pragma once
#include <qabstractitemmodel.h>
#include "repository/repository.h"

class VictimsTableModelB : public QAbstractTableModel
{
private:
	Repository* assistantRepo;

public:
    enum class UpdateType { add, remove, update };
	
	VictimsTableModelB(Repository* r) : assistantRepo(r) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const; 
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex& index) const;

public slots:
	void update();
};

