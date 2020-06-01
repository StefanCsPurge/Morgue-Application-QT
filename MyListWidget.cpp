#include "MyListWidget.h"
#include "PictureDelegate.h"

MyListWidget::MyListWidget(VictimsTableModelB* model, QWidget *parent)
	: QWidget(parent), model{model}
{
	ui.setupUi(this);
	this->ui.victimsTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	this->ui.victimsTableView->setModel(this->model);
	this->ui.victimsTableView->setItemDelegate(new PictureDelegate{});

	this->ui.victimsTableView->verticalHeader()->hide();
}

void MyListWidget::updateSize()
{
	//this->ui.victimsTableView->resizeColumnsToContents();
	this->ui.victimsTableView->resizeRowsToContents();
}

MyListWidget::~MyListWidget()
{

}


