/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plot.h"
#include <QLayout>
#include <QSlider>
#include <QLCDNumber>
#include <QLabel>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QToolBar* toolBar = nullptr;


    Plot* plot = nullptr;
    QVBoxLayout* mainLayout = nullptr;
    void createPlot();

    QHBoxLayout* menuHorLayout = nullptr;
    QLabel* aCoeffLabel = nullptr;
    QSlider* aCoeffSlider = nullptr;
    QLCDNumber* aCoeffNumGadget = nullptr;
    QHBoxLayout* aCoeffHorLay = nullptr;

    QLabel* xEdgeLabel = nullptr;
    QSlider* xEdgeSlider = nullptr;
    QLCDNumber* xEdgeNumGadget = nullptr;
    QHBoxLayout* xEdgeHorLay = nullptr;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addACoeffMenu(const int leftEdge, const int rightEdge);
    void addXEdgeMenu(const int leftEdge, const int rightEdge);

private slots:
    void onACoeffValueChanged(int val);
    void onXEdgeValueChanged(int val);
    void showDeveloperInfo();

private:
    Ui::MainWindow *ui;
    void createToolBar();
};
#endif // MAINWINDOW_H
