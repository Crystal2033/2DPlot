/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::createPlot()
{
    plot->create(20, 200);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout();
    plot = new Plot();
    mainLayout->addWidget(plot);
    this->centralWidget()->setLayout(mainLayout);
    createPlot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

