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


class Plot : public QWidget
{
    Q_OBJECT
private:
    QList<QPointF*> pointsFirstHalf;
    QList<QPointF*> pointsSecondHalf;
    QPainter painter;
    QPen* pen = nullptr;

    int yRange = 0;
    int xRange = 0;
    int xMax = 0, xMin = 0, yMax = 0, yMin = 0;

    void paintEvent(QPaintEvent* event) override;
    void drawLine(const QPointF& firstPoint, const QPointF& secondPoint);
    void initPoints(const int aCoeff);
    //void drawAxis();

public:
    explicit Plot(QWidget *parent = nullptr);
    void create(const int aCoeff, const int xRange);
    ~Plot();

signals:

};

#endif // PLOT_H
