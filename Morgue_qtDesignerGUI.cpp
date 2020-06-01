#include "Morgue_qtDesignerGUI.h"
#include <qdebug.h>
#include <QMessageBox.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QHeaderView>


Morgue_qtDesignerGUI::Morgue_qtDesignerGUI(Service& s, QWidget *parent)
	: QMainWindow(parent) , srv(s)
{
	ui.setupUi(this);

	//this->populateList();
	this->populateTable();
	this->connectSignalsAndSlots();
	this->initiateChart();
	this->tableWindow = new MyListWidget{ srv.getAssistantModel() };
}


void Morgue_qtDesignerGUI::connectSignalsAndSlots()
{
	/*QObject::connect(this->ui.victimsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Victim v = this->srv.getAllVictims()[selectedIndex];
		this->ui.nameLineEdit->setText(QString::fromStdString(v.getName()));
		this->ui.originLineEdit->setText(QString::fromStdString(v.getPlaceOfOrigin()));
		this->ui.ageLineEdit->setText(QString::number(v.getAge()));
		this->ui.photoLineEdit->setText(QString::fromStdString(v.getPhoto()));
		});*/
	QObject::connect(this->ui.victimsTableWidget, &QTableWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getTableSelectedIndex();
		if (selectedIndex < 0)
			return;
		string victimName = this->ui.victimsTableWidget->item(selectedIndex, 0)->text().toStdString();
		Victim v = this->srv.getVictim(victimName);
		this->ui.nameLineEdit->setText(QString::fromStdString(v.getName()));
		this->ui.originLineEdit->setText(QString::fromStdString(v.getPlaceOfOrigin()));
		this->ui.ageLineEdit->setText(QString::number(v.getAge()));
		this->ui.photoLineEdit->setText(QString::fromStdString(v.getPhoto()));
		});
	//QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::addVictim);
	QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::deleteVictim);
	QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::updateVictim);
	QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantDisplayNext);
	QObject::connect(this->ui.saveButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantSaveCurrent);
	QObject::connect(this->ui.filterButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantFilterVictims);
	QObject::connect(this->ui.mylistButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantDisplayVictims);
	QObject::connect(this->ui.tableViewButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantDisplayVictimsTableView);
	QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::adminUndo);
	QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::adminRedo);
	QObject::connect(this->ui.undoButtonB, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantUndoSave);
	QObject::connect(this->ui.redoButtonB, &QPushButton::clicked, this, &Morgue_qtDesignerGUI::assistantRedoSave);
	QObject::connect(this->ui.exitButton, &QPushButton::clicked, this, &exit);
}

//void Morgue_qtDesignerGUI::populateList()
//{
//	this->ui.victimsListWidget->clear();
//	std::vector<Victim> allVictims = this->srv.getAllVictims();
//	for (Victim& v : allVictims)
//		this->ui.victimsListWidget->addItem(QString::fromStdString(v.toString()));
//}

void Morgue_qtDesignerGUI::populateTable()
{
	this->ui.victimsTableWidget->setRowCount(0);
	this->ui.victimsTableWidget->setColumnCount(4);
	QStringList tableHeader;
	tableHeader<<"Name"<<"Place of origin"<<"Age"<<"Photo";
	this->ui.victimsTableWidget->setHorizontalHeaderLabels(tableHeader);
	this->ui.victimsTableWidget->verticalHeader()->setVisible(false);
	this->ui.victimsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//this->ui.victimsTableWidget->horizontalHeader()->setStyleSheet("color : black; background-color:red");
	std::vector<Victim> allVictims = this->srv.getAllVictims();
	for (const Victim& v : allVictims)
	{
		int rowNr = this->ui.victimsTableWidget->rowCount();
		this->ui.victimsTableWidget->insertRow(rowNr);
		this->ui.victimsTableWidget->setItem(rowNr,0, new QTableWidgetItem(QString::fromStdString(v.getName())));
		this->ui.victimsTableWidget->setItem(rowNr,1, new QTableWidgetItem(QString::fromStdString(v.getPlaceOfOrigin())));
		this->ui.victimsTableWidget->setItem(rowNr,2, new QTableWidgetItem(QString::number(v.getAge())));
		this->ui.victimsTableWidget->setItem(rowNr,3, new QTableWidgetItem(QString::fromStdString(v.getPhoto())));
	}
}

//int Morgue_qtDesignerGUI::getSelectedIndex() const
//{
//	QModelIndexList selectedIndexes = this->ui.victimsListWidget->selectionModel()->selectedIndexes();
//	if (!selectedIndexes.size())   // in case there is something that is not selected
//	{
//		this->ui.nameLineEdit->clear();
//		this->ui.originLineEdit->clear();
//		this->ui.ageLineEdit->clear();
//		this->ui.photoLineEdit->clear();
//		return -1;
//	}
//	int selectedIndex = selectedIndexes.at(0).row();
//	return selectedIndex;
//}

int Morgue_qtDesignerGUI::getTableSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->ui.victimsTableWidget->selectionModel()->selectedIndexes();
	if (!selectedIndexes.size())   // in case there is something that is not selected
	{
		this->ui.nameLineEdit->clear();
		this->ui.originLineEdit->clear();
		this->ui.ageLineEdit->clear();
		this->ui.photoLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

void Morgue_qtDesignerGUI::addVictim()
{
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string placeOfOrigin = this->ui.originLineEdit->text().toStdString();
	int age = this->ui.ageLineEdit->text().toInt();
	std::string photo = this->ui.photoLineEdit->text().toStdString();

	try {
		this->srv.addVictimToRepo(name, placeOfOrigin, age, photo);
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	//this->populateList();
	this->populateTable();
	this->populateChart();

	int lastElemIdx = this->srv.getAllVictims().size() - 1;
	this->ui.victimsTableWidget->selectRow(lastElemIdx);
	this->ui.victimsTableWidget->setFocus();
	this->ui.filterListWidget->clear();
}

void Morgue_qtDesignerGUI::deleteVictim()
{
	int selectedIndex = this->getTableSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No corpse was selected!");
		return;
	}
	Victim v = this->srv.getAllVictims()[selectedIndex];
	try {
		this->srv.deleteVictim(v.getName());
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	//this->populateList();
	this->populateTable();
	this->populateChart();
	this->ui.filterListWidget->clear();
}

void Morgue_qtDesignerGUI::updateVictim()
{
	int selectedIndex = this->getTableSelectedIndex();
	if (selectedIndex < 0)
	{
		QMessageBox::critical(this, "Error", "No corpse was selected!");
		return;
	}
	std::string name = this->ui.nameLineEdit->text().toStdString();
	std::string newPlaceOfOrigin = this->ui.originLineEdit->text().toStdString();
	int newAge = this->ui.ageLineEdit->text().toInt();
	std::string newPhoto = this->ui.photoLineEdit->text().toStdString();
	try {
		this->srv.updateVictim(name, newPlaceOfOrigin, newAge, newPhoto);
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	//this->populateList();
	this->populateTable();
	this->populateChart();
	this->ui.filterListWidget->clear();
}

void Morgue_qtDesignerGUI::initiateChart()
{
	this->chart = new QChart();
	this->chart->setTheme(QChart::ChartThemeDark);
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->setTitle("Victims by the age of death");
	chart->setAnimationOptions(QChart::SeriesAnimations);
	QStringList categories;
	categories << ">70 years old" << "51-70 years old" << "36-50 years old" << "25-35 years old" << "15-24 years old" << "0-14 years old";
	QBarCategoryAxis* axisY = new QBarCategoryAxis();
	axisY->append(categories);
	chart->addAxis(axisY, Qt::AlignLeft);

	this->populateChart();
	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QHBoxLayout* chartLayout = new QHBoxLayout{};
	chartLayout->addWidget(chartView);
	this->ui.tab_3->setLayout(chartLayout);
}

void Morgue_qtDesignerGUI::populateChart()
{
	chart->removeAllSeries();
	chart->removeAxis(chart->axisX());
	QBarSet* set0 = new QBarSet("Number of victims");

	int cat1 = this->srv.filterVictims("", 15).size();
	int cat2 = this->srv.filterVictims("", 25).size() - cat1;
	int cat3 = this->srv.filterVictims("", 36).size() - cat2 - cat1;
	int cat4 = this->srv.filterVictims("", 51).size() - cat3 - cat2 - cat1;
	int cat5 = this->srv.filterVictims("", 71).size() - cat4 - cat3 - cat2 - cat1;
	int cat6 = this->srv.filterVictims("", 999).size() - cat5 - cat4 - cat3 - cat2 - cat1;
	*set0 << cat6 << cat5 << cat4 << cat3 << cat2 << cat1;

	set0->setColor("#5b1717");
	QHorizontalBarSeries* series = new QHorizontalBarSeries();
	series->append(set0);
	chart->addSeries(series);
	
	series->attachAxis(chart->axisY());
	QValueAxis* axisX = new QValueAxis();
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(chart->axisX());
	axisX->applyNiceNumbers();	
}

void Morgue_qtDesignerGUI::adminUndo()
{
	try {
		this->srv.undoAdmin();
	}
	catch (exception& e)
	{
		QMessageBox::information(this, "Undo finished!", e.what());
		return;
	}
	this->populateTable();
	this->populateChart();
	this->ui.filterListWidget->clear();
}

void Morgue_qtDesignerGUI::adminRedo()
{
	try {
		this->srv.redoAdmin();
	}
	catch (exception& e)
	{
		QMessageBox::information(this, "Redo finished!", e.what());
		return;
	}
	this->populateTable();
	this->populateChart();
	this->ui.filterListWidget->clear();
}

void Morgue_qtDesignerGUI::assistantDisplayNext()
{
	try {
		this->srv.nextVictim();
	}
	catch (exception& e)
	{
		this->ui.nextViewLine->clear();
		QMessageBox::critical(this, "Error", e.what());
		return;
	}
	Victim v = this->srv.getCurrentVictim();
	this->ui.nextViewLine->clear();
	this->ui.nextViewLine->setText(QString::fromStdString(v.toUnFmtString()));
	this->ui.saveNameLineEdit->clear();
	this->ui.saveNameLineEdit->setText(QString::fromStdString(v.getName()));
}

void Morgue_qtDesignerGUI::assistantSaveCurrent()
{
	std::string name = this->ui.saveNameLineEdit->text().toStdString();
	try {
		this->srv.moveVictimToAssistantList(name);
		this->populateChart();
		this->populateTable();
		this->ui.saveNameLineEdit->clear();
		tableWindow->updateSize();
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void Morgue_qtDesignerGUI::assistantFilterVictims()
{
	this->ui.filterListWidget->clear();
	std::string placeOfOrigin = this->ui.originFilterLineEdit->text().toStdString();
	int age = this->ui.ageFilterLineEdit->text().toInt();
	vector<Victim> selectedVictims;
	selectedVictims = this->srv.filterVictims(placeOfOrigin, age);
	if(!selectedVictims.size())
		this->ui.filterListWidget->addItem(QString("No victims with the given place-of-origin and the age lower than the given value were found!"));
	else
		for (Victim& v : selectedVictims)
			this->ui.filterListWidget->addItem(QString::fromStdString(v.toString()));
}

void Morgue_qtDesignerGUI::assistantDisplayVictims()
{
	try
	{
		this->srv.showAssistantVictims();
	}
	catch (exception& e)
	{
		QMessageBox::critical(this, "Error", e.what());
	}
}

void Morgue_qtDesignerGUI::assistantDisplayVictimsTableView()
{
	tableWindow->show();
}

void Morgue_qtDesignerGUI::assistantUndoSave()
{
	try {
		this->srv.undoAssistantSave();
	}
	catch (exception& e)
	{
		QMessageBox::information(this, "Undo finished!", e.what());
		return;
	}
	this->populateChart();
	this->populateTable();
	this->ui.saveNameLineEdit->clear();
	tableWindow->updateSize();
}

void Morgue_qtDesignerGUI::assistantRedoSave()
{
	try {
		this->srv.redoAssistantSave();
	}
	catch (exception& e)
	{
		QMessageBox::information(this, "Redo finished!", e.what());
		return;
	}
	this->populateChart();
	this->populateTable();
	this->ui.saveNameLineEdit->clear();
	tableWindow->updateSize();
}
