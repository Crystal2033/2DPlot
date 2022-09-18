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
    plot->create(20, 20);
}

void MainWindow::addACoeffMenu()
{
    aCoeffHorLay = new QHBoxLayout();
    aCoeffLabel = new QLabel("a");
    aCoeffSlider = new QSlider(Qt::Horizontal);
    aCoeffSlider->setRange(1, 40);
    aCoeffSlider->setTickPosition(QSlider::TicksBelow);

    aCoeffNumGadget = new QLCDNumber();
    aCoeffNumGadget->display(aCoeffSlider->minimum());
    aCoeffNumGadget->setFixedSize(70, 70);

    aCoeffHorLay->addWidget(aCoeffLabel, 1);
    aCoeffHorLay->addWidget(aCoeffSlider, 6);
    aCoeffHorLay->addWidget(aCoeffNumGadget, 1);

    menuHorLayout->addLayout(aCoeffHorLay);
    connect(aCoeffSlider, SIGNAL(valueChanged(int)), this, SLOT(onACoeffValueChanged(int)));
}

void MainWindow::onACoeffValueChanged(int val)
{
    aCoeffNumGadget->display(val);
//    qDebug() << aCoeffNumGadget->value() << Qt::endl;
//    qDebug() << xEdgeNumGadget->value() << Qt::endl;
    plot->create(aCoeffNumGadget->value(), xEdgeNumGadget->value());
}

void MainWindow::onXEdgeValueChanged(int val)
{
    xEdgeNumGadget->display(val);
//    qDebug() << aCoeffNumGadget->value() << Qt::endl;
//    qDebug() << xEdgeNumGadget->value() << Qt::endl;
    plot->create(aCoeffNumGadget->value(), xEdgeNumGadget->value());
}

void MainWindow::addXEdgeMenu()
{
    xEdgeHorLay = new QHBoxLayout();
    xEdgeLabel = new QLabel("B (x edge)");
    xEdgeSlider = new QSlider(Qt::Horizontal);
    xEdgeSlider->setRange(20, 200);
    xEdgeSlider->setTickPosition(QSlider::TicksBelow);

    xEdgeNumGadget = new QLCDNumber();
    xEdgeNumGadget->display(xEdgeSlider->minimum());
    xEdgeNumGadget->setFixedSize(70, 70);

    xEdgeHorLay->addWidget(xEdgeLabel, 1);
    xEdgeHorLay->addWidget(xEdgeSlider, 6);
    xEdgeHorLay->addWidget(xEdgeNumGadget, 1);

    menuHorLayout->addLayout(xEdgeHorLay);
    connect(xEdgeSlider, SIGNAL(valueChanged(int)), this, SLOT(onXEdgeValueChanged(int)));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout();
    plot = new Plot();
    mainLayout->addWidget(plot, 4);
    menuHorLayout = new QHBoxLayout();



    this->centralWidget()->setLayout(mainLayout);
    createPlot();

    addACoeffMenu();
    addXEdgeMenu();
    mainLayout->addLayout(menuHorLayout, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

