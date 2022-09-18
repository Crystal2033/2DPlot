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

typedef enum {ARGUMENT, VALUE} TYPE_OF_VAR;
class Plot : public QWidget
{
    Q_OBJECT
private:
    QList<QPointF*> pointsFirstHalf;
    QList<QPointF*> pointsSecondHalf;
    QPainter painter;
    QPen* pen = nullptr;
    bool clearingIsDone = true;

    //int yRange = 0;
    //int xRange = 0;

    int rightOxLineEdge = 0; // the right edge of Ox line (need for drawAxis)
    int leftOxLineEdge = 0;
    int upperOyLineEdge = 0;
    int downOyLineEdge = 0;

    int xMax = 0, xMin = 0, yMax = 0, yMin = 0;

    void paintEvent(QPaintEvent* event) override;
    void drawLine(const QPointF& firstPoint, const QPointF& secondPoint);
    void initPoints(const int aCoeff);
    double getFunctionRes(const int x, const int aCoeff) const;
    void draw2DAxis();
    void drawOxOyLines();
    void drawPlotArrows();
    void checkAndSetMax(const QPointF& point, const TYPE_OF_VAR type);
    void checkAndSetMin(const QPointF& point, const TYPE_OF_VAR type);
    void resizeEvent(QResizeEvent* event) override;

    void drawPlot();

    void clearLists();

public:
    explicit Plot(QWidget *parent = nullptr);
    void create(const int aCoeff, const int xRange);
    ~Plot();

signals:

};

//bool pointMaxComparer(QPointF* const& first,  QPointF* const& second){
//    return first->y() > second->y();
//}

//bool pointMinComparer(QPointF* const& first, QPointF* const& second){
//    return first->y() < second->y();
//}

#endif // PLOT_H
