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
    plot->create(aCoeffNumGadget->value(), xEdgeNumGadget->value());
}

void MainWindow::addACoeffMenu(const int leftEdge, const int rightEdge)
{
    aCoeffHorLay = new QHBoxLayout();
    aCoeffLabel = new QLabel("a");
    aCoeffSlider = new QSlider(Qt::Horizontal);
    aCoeffSlider->setRange(leftEdge, rightEdge);
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
    plot->create(aCoeffNumGadget->value(), xEdgeNumGadget->value());
}

void MainWindow::onXEdgeValueChanged(int val)
{
    xEdgeNumGadget->display(val);
    plot->create(aCoeffNumGadget->value(), xEdgeNumGadget->value());
}

void MainWindow::showDeveloperInfo()
{
    QMessageBox::about(this, "Developer Info",
"<H2> <U>Developer</U>: </H2>"
"<H3> Kulikov Pavel. FIIT M80-311B-20. <font color=\"green\"> VARIANT 20.</font> </H3>"
"<h2> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;x^3 </h2>"
"<h2>y^2 = &nbsp;------ &nbsp;&nbsp;&nbsp;&nbsp;, x in range (0; B], B>0 </h2>"
"<h2> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;(a-x) </h2>");
}

void MainWindow::addXEdgeMenu(const int leftEdge, const int rightEdge)
{
    xEdgeHorLay = new QHBoxLayout();
    xEdgeLabel = new QLabel("B (x edge)");
    xEdgeSlider = new QSlider(Qt::Horizontal);
    xEdgeSlider->setRange(leftEdge, rightEdge);
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

void MainWindow::createToolBar()
{
    toolBar = this->addToolBar("Main toolbar");
    QAction* getDevInfo = toolBar->addAction(QIcon(":/pictures/devIcon.png"), "Developer Info");
    connect(getDevInfo, SIGNAL(triggered()), SLOT(showDeveloperInfo()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createToolBar();

    mainLayout = new QVBoxLayout();
    plot = new Plot();
    mainLayout->addWidget(plot, 4);
    menuHorLayout = new QHBoxLayout();
    this->setWindowTitle("Graphic`s plot");
    this->setWindowIcon(QIcon(":/pictures/PlotIcon.png"));
    this->centralWidget()->setLayout(mainLayout);

    addACoeffMenu(1, 60);
    addXEdgeMenu(20, 500);
    createPlot();
    mainLayout->addLayout(menuHorLayout, 1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

