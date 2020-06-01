#pragma once
#include <qwidget.h>
#include "../controller/controller.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QHorizontalBarSeries>
using namespace QtCharts;

class MainWindow : public QWidget {
private:
	Service& srv;

	//graphical elements
	QListWidget* victimsListWidget;
	QLineEdit* nameLineEdit, * originPlaceLineEdit, * ageLineEdit, * photoLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, * exitButton;
	QChart* chart;

public:
	MainWindow(Service& s);

private: 
	void initGUI();
	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addVictim();
	void deleteVictim();
	void updateVictim();
	void populateChart();
};
