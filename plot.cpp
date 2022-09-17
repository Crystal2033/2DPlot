/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "plot.h"

void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    painter.setPen(*pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(width()/2, height()/2);
    qDebug() << width() << Qt::endl;
    qDebug() << height() << Qt::endl;
    if(!pointsFirstHalf.empty()){

        for(int i = 0; i < pointsFirstHalf.size() - 1; i++){
            drawLine(*pointsFirstHalf[i], *pointsFirstHalf[i+1]);
        }
    }

    if(!pointsSecondHalf.empty()){
        for(int i = 0; i < pointsSecondHalf.size() - 1; i++){
            drawLine(*pointsSecondHalf[i], *pointsSecondHalf[i+1]);
        }
    }
    painter.end();

}

void Plot::drawLine(const QPointF &firstPoint, const QPointF &secondPoint)
{
    if(firstPoint.x() == INFINITY){
        return;
    }
    painter.drawLine(firstPoint, secondPoint);
}


void Plot::create(const int aCoeff, const int xRange)
{
    this->xRange = xRange;
    //drawAxis();

    initPoints(aCoeff);
}

void Plot::initPoints(const int aCoeff)
{
    for (int x = 0; x <= xRange; x++){
        if(aCoeff == x){
            QPointF* point = new QPointF(INFINITY, INFINITY);
            QPointF* negativePoint = new QPointF(INFINITY, INFINITY);
            pointsFirstHalf.append(point);
            pointsSecondHalf.append(negativePoint);
            //qDebug() << "DIFF == oo:  " << *point << Qt::endl;
            continue;
        }
        double y = pow(x, 3)/(aCoeff - x);
        QPointF* point = new QPointF(x, y/10);
        QPointF* negativePoint = new QPointF(x, -y/10);
        //qDebug() << *negativePoint << Qt::endl;
        pointsFirstHalf.append(point);
        pointsSecondHalf.append(negativePoint);
    }

}


Plot::Plot(QWidget *parent) : QWidget(parent)
{
    pen = new QPen(Qt::black, 1);
}

Plot::~Plot()
{
    for(QPointF* point: pointsFirstHalf){
        delete point;
    }
    for(QPointF* point: pointsSecondHalf){
        delete point;
    }
    delete pen;
}
