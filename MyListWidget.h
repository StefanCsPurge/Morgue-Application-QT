#pragma once

#include <QWidget>
#include "ui_MyListWidget.h"
#include "VictimsTableModelB.h"

class MyListWidget : public QWidget
{
	Q_OBJECT

public:
	MyListWidget(VictimsTableModelB* model, QWidget *parent = Q_NULLPTR);
	~MyListWidget();

	void updateSize();
private:
	Ui::MyListWidget ui;
	VictimsTableModelB* model;
};
