#pragma once

#include <QMainWindow>
#include "ui_todo_mainwindow.h"

class TodoMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	TodoMainWindow(QWidget *parent = nullptr);
	~TodoMainWindow();

private:
	Ui::TodoMainWindow ui;
};
