#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Morgue_qtDesignerGUI.h"
#include "controller/controller.h"
#include "MyListWidget.h"
#include "VictimsTableModelB.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <qshortcut.h>
using namespace QtCharts;

class Morgue_qtDesignerGUI : public QMainWindow
{
	Q_OBJECT

public:
	Morgue_qtDesignerGUI(Service& s, QWidget *parent = Q_NULLPTR);

private:
	Service& srv;
	Ui::Morgue_qtDesignerGUIClass ui;
	QChart* chart;
	MyListWidget* tableWindow;

	void connectSignalsAndSlots();
	//void populateList();
	void populateTable();
	//int getSelectedIndex() const;
	int getTableSelectedIndex() const;
	void deleteVictim();
	void updateVictim();
	void initiateChart();
	void populateChart();
	void adminUndo();
	void adminRedo();

	void assistantDisplayNext();
	void assistantSaveCurrent();
	void assistantFilterVictims();
	void assistantDisplayVictims();
	void assistantDisplayVictimsTableView();
	void assistantUndoSave();
	void assistantRedoSave();

public slots:
	void addVictim();
	
};
