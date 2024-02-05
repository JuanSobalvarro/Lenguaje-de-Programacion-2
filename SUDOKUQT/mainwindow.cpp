#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // here we set up all the UI widgets, gl screens, etc
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
