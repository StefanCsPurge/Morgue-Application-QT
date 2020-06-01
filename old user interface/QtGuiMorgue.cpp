#include "QtGuiMorgue.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include <qicon.h>


MainWindow::MainWindow(Service& s) : srv(s)
{
	this->resize(1100,600);
	this->initGUI();
	this->populateList();
	this->connectSignalsAndSlots();
	this->setStyleSheet("QWidget{background-color : grey ; color : black; font: 11pt 'Courier New'; font-weight: bold}");
	this->setWindowIcon(QIcon("happySkull.png"));
	this->setWindowTitle(QString("EC-PD morgue"));
}

void MainWindow::initGUI()
{
	this->victimsListWidget = new QListWidget{};
	this->nameLineEdit = new QLineEdit();
	this->originPlaceLineEdit = new QLineEdit();
	this->ageLineEdit = new QLineEdit();
	this->photoLineEdit = new QLineEdit();
	this->addButton = new QPushButton("Add");
	this->deleteButton = new QPushButton("Delete");
	this->updateButton = new QPushButton("Update");
	this->exitButton = new QPushButton("Exit");
	this->chart = new QChart();
	this->chart->setTheme(QChart::ChartThemeDark);

	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	QTabWidget* tabs = new QTabWidget{};
	QVBoxLayout* adminLayout = new QVBoxLayout{};

	adminLayout->addWidget(this->victimsListWidget);

	QFormLayout* victimDetailsLayout = new QFormLayout{};
	victimDetailsLayout->addRow("Name", this->nameLineEdit);
	victimDetailsLayout->addRow("Place of origin", this->originPlaceLineEdit);
	victimDetailsLayout->addRow("Age", this->ageLineEdit);
	victimDetailsLayout->addRow("Photo name", this->photoLineEdit);
	adminLayout->addLayout(victimDetailsLayout);

	QGridLayout* buttonsLayout = new QGridLayout{};
	buttonsLayout->addWidget(this->addButton, 0, 0);
	buttonsLayout->addWidget(this->deleteButton, 0, 1);
	buttonsLayout->addWidget(this->updateButton, 0, 2);
	buttonsLayout->addWidget(this->exitButton, 1, 1);
	adminLayout->addLayout(buttonsLayout);

	QWidget* tab1 = new QWidget{};
	tab1->setLayout(adminLayout);
	tab1->setStyleSheet("QWidget{background-color: #1c1d1e; color: #dfedf0} QPushButton{background-color: #5b1717}");
	tabs->addTab(tab1, QString("Admin operations"));
	
	this->populateChart();
	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	
	QWidget* tab2 = new QWidget{};
	QHBoxLayout* chartLayout = new QHBoxLayout{};
	chartLayout->addWidget(chartView);
	tab2->setLayout(chartLayout);
	tabs->addTab(tab2, QString("Data representation"));
	
	mainLayout->addWidget(tabs);
}

void MainWindow::populateList()
{
	this->victimsListWidget->clear();
	std::vector<Victim> allVictims = this->srv.getAllVictims();
	for (Victim& v : allVictims)
		this->victimsListWidget->addItem(QString::fromStdString(v.toString()));
}

void MainWindow::connectSignalsAndSlots()
{
	QObject::connect(this->victimsListWidget, &QListWidget::itemSelectionChanged, [this]() {
		int selectedIndex = this->getSelectedIndex();
		if (selectedIndex < 0)
			return;
		Victim v = this->srv.getAllVictims()[selectedIndex];
		this->nameLineEdit->setText(QString::fromStdString(v.getName()));
		this->originPlaceLineEdit->setText(QString::fromStdString(v.getPlaceOfOrigin()));
		this->ageLineEdit->setText(QString::number(v.getAge()));
		this->photoLineEdit->setText(QString::fromStdString(v.getPhoto()));
		});

	QObject::connect(this->addButton, &QPushButton::clicked,this, &MainWindow::addVictim);
	QObject::connect(this->deleteButton, &QPushButton::clicked,this, &MainWindow::deleteVictim);
	QObject::connect(this->updateButton, &QPushButton::clicked,this, &MainWindow::updateVictim);
	QObject::connect(this->exitButton, &QPushButton::clicked,this,&exit);
}

int MainWindow::getSelectedIndex() const
{
	QModelIndexList selectedIndexes = this->victimsListWidget->selectionModel()->selectedIndexes();
	if (!selectedIndexes.size())   // in case there is something that is not selected
	{
		this->nameLineEdit->clear(); 
		this->originPlaceLineEdit->clear();
		this->ageLineEdit->clear();
		this->photoLineEdit->clear();
		return -1;
	}
	int selectedIndex = selectedIndexes.at(0).row();
	return selectedIndex;
}

 void MainWindow::addVictim()
{
	 std::string name = this->nameLineEdit->text().toStdString();
	 std::string placeOfOrigin = this->originPlaceLineEdit->text().toStdString();
	 int age = this->ageLineEdit->text().toInt();
	 std::string photo = this->photoLineEdit->text().toStdString();

	 try {
		 this->srv.addVictimToRepo(name, placeOfOrigin, age, photo);
	 }
	 catch (exception& e)
	 {
		 QMessageBox::critical(this, "Error", e.what());
		 return;
	 }
	 this->populateList();
	 this->populateChart();

	 int lastElemIdx = this->srv.getAllVictims().size() - 1;
	 this->victimsListWidget->setCurrentRow(lastElemIdx);
}

 void MainWindow::deleteVictim()
 {
	 int selectedIndex = this->getSelectedIndex();
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
	 this->populateList();
	 this->populateChart();
 }

 void MainWindow::updateVictim()
 {
	 int selectedIndex = this->getSelectedIndex();
	 if (selectedIndex < 0)
	 {
		 QMessageBox::critical(this, "Error", "No corpse was selected!");
		 return;
	 }
	 std::string name = this->nameLineEdit->text().toStdString();
	 std::string newPlaceOfOrigin = this->originPlaceLineEdit->text().toStdString();
	 int newAge = this->ageLineEdit->text().toInt();
	 std::string newPhoto = this->photoLineEdit->text().toStdString();
	 try {
		 this->srv.updateVictim(name,newPlaceOfOrigin,newAge,newPhoto);
	 }
	 catch (exception& e)
	 {
		 QMessageBox::critical(this, "Error", e.what());
		 return;
	 }
	 this->populateList();
	 this->populateChart();
 }

 void MainWindow::populateChart()
 {
	 chart->removeAllSeries();
	 chart->removeAxis(chart->axisX());
	 chart->removeAxis(chart->axisY());
	 QBarSet* set0 = new QBarSet("Number of victims");

	 int cat1 = this->srv.filterVictims("", 15).size();
	 int cat2 = this->srv.filterVictims("", 25).size() - cat1;
	 int cat3 = this->srv.filterVictims("", 36).size() - cat2-cat1;
	 int cat4 = this->srv.filterVictims("", 51).size() - cat3-cat2-cat1;
	 int cat5 = this->srv.filterVictims("", 71).size() - cat4- cat3 - cat2 - cat1;
	 int cat6 = this->srv.filterVictims("", 999).size() - cat5 - cat4 - cat3 - cat2 - cat1;
	 *set0 << cat6 << cat5 << cat4 << cat3 << cat2 << cat1;

	 set0->setColor("#5b1717");
	 QHorizontalBarSeries* series = new QHorizontalBarSeries();
	 series->append(set0);
	 chart->addSeries(series);
	 chart->setTitle("Victims by the age of death");
	 chart->setAnimationOptions(QChart::SeriesAnimations);

	 QStringList categories;
	 categories << ">70 years old" <<"51-70 years old" << "36-50 years old" << "25-35 years old" << "15-24 years old"  << "0-14 years old";
	 QBarCategoryAxis* axisY = new QBarCategoryAxis();
	 axisY->append(categories);
	 chart->addAxis(axisY, Qt::AlignLeft);
	 series->attachAxis(chart->axisY());
	 QValueAxis* axisX = new QValueAxis();
	 chart->addAxis(axisX, Qt::AlignBottom);
	 series->attachAxis(chart->axisX());
	 axisX->applyNiceNumbers();
	 
	 chart->legend()->setVisible(true);
	 chart->legend()->setAlignment(Qt::AlignBottom);
 }


 