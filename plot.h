/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <QLabel>
#define ARROW_OFFSET 20
#define X_AXIS_SHIFT_COEFF 4 // translate(width/X_AXIS_SHIFT_COEFF); shift the center of axis
#define Y_AXIS_SHIFT_COEFF 2 // translate(height/Y_AXIS_SHIFT_COEFF); shift the center of axis

typedef enum {ARGUMENT, VALUE} TYPE_OF_VAR;
class Plot : public QWidget
{
    Q_OBJECT
private:
    QList<QPointF> pointsFirstHalf;
    QList<QPointF> pointsSecondHalf;
    QPainter painter;
    QPen* pen = nullptr;

    int rightOxLineEdge = 0; // the right edge of Ox line (need for drawAxis)
    int leftOxLineEdge = 0;
    int upperOyLineEdge = 0;
    int downOyLineEdge = 0;


    int aCoeff = 0;
    int xMax = 0, xMin = 0, yMax = 0;;
    double scaledCoeffX = 0.0; //this coeff need for scaling between plot on widget and real data points from fucntion. Visualizing coefficient
    double scaledCoeffY = 0.0;

    void paintEvent(QPaintEvent* event) override;
    void drawLine(const QPointF& firstPoint, const QPointF& secondPoint);
    void initPoints();
    double getFunctionRes(const int x, const int aCoeff) const;
    void draw2DAxis();
    void drawOxOyLines();
    void drawPlotArrows();
    void checkAndSetMax(const QPointF& point, const TYPE_OF_VAR type);
    void resizeEvent(QResizeEvent* event) override;

    void drawPlot();

    void clearLists();

    void addNumbersOnAxis();
    bool isSpecialPoint(const int x);

public:
    explicit Plot(QWidget *parent = nullptr);
    void create(const int aCoeff, const int xRange);
    ~Plot();

signals:

};


#endif // PLOT_H
