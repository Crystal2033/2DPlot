/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "plot.h"

void Plot::drawPlot() // drawing plot.
{
    painter.setPen(*pen);

    for(int i = 0; i < pointsFirstHalf.size() - 1; i++){ //we can do this because these lists have the same value of points
        drawLine(*pointsFirstHalf[i], *pointsFirstHalf[i+1]);
        drawLine(*pointsSecondHalf[i], *pointsSecondHalf[i+1]);
    }

    qDebug() << "drawingPlotOK" << Qt::endl;
}

void Plot::clearLists()
{
    //clearingIsDone = false;
    if(pointsFirstHalf.size() != pointsSecondHalf.size()){
        qDebug() << "SIZE ERROR" << Qt::endl;
        exit(0);
    }
    qDebug() << "Clearing... " << pointsFirstHalf.size() << " elements" << Qt::endl;
    qDebug() << "Clearing... " << pointsSecondHalf.size() << " elements" << Qt::endl;
    for(auto point : pointsFirstHalf){
        qDebug() << point << Qt::endl;
        delete point;
    }
    for(auto point : pointsSecondHalf){
        delete point;
    }
//    for (int i = 0; i < pointsFirstHalf.size(); i++){ //we can do this because these lists have the same value of points
//        //qDebug() << "First point: " << *pointsFirstHalf[i] << " Second point: "  << *pointsSecondHalf[i] << Qt::endl;
//        delete pointsFirstHalf[i];
//        delete pointsSecondHalf[i];
//    }
    //clearingIsDone = true;
    qDebug() << "clearOK" << Qt::endl;
}

void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    if(clearingIsDone){
    painter.begin(this);
    //painter.setPen(*pen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(width()/2, height()/2);

    draw2DAxis();
    drawPlot();
    painter.end();
    //}

}

void Plot::drawLine(const QPointF &firstPoint, const QPointF &secondPoint) // method draws line between firstPoint and secondPoint points
{
    if(firstPoint.x() == abs(INFINITY)){ //diff == oo
        return;
    }
    painter.drawLine(firstPoint, secondPoint);
}


void Plot::create(const int aCoeff, const int xRange) // creating plot
{
    qDebug() << "Before clear" << Qt::endl;
    clearLists();
    qDebug() << "After clear" << Qt::endl;
    //this->xRange = xRange;
    xMax = xRange;

    initPoints(aCoeff);
    qDebug() << "createOK" << Qt::endl;
}

void Plot::initPoints(const int aCoeff) // appending function`s points in list
{
    qDebug() << pointsFirstHalf.size() << Qt::endl;

    for (int x = 0; x <= xMax; x++){
        if(aCoeff == x){
            QPointF* point = new QPointF(-INFINITY, -INFINITY);
            QPointF* negativePoint = new QPointF(INFINITY, INFINITY);
            pointsFirstHalf.append(point);
            pointsSecondHalf.append(negativePoint);
            //qDebug() << "DIFF == oo:  " << *point << Qt::endl;
            continue;
        }
        double y = getFunctionRes(x, aCoeff);
        QPointF* negativePoint = new QPointF(x, y/10); // its negative because in Qt Ox -> right direction, Oy -> down direction
        QPointF* point = new QPointF(x, -y/10);
        checkAndSetMax(*point, VALUE);
        checkAndSetMax(*negativePoint, VALUE);
        checkAndSetMin(*point, VALUE);
        checkAndSetMin(*negativePoint, VALUE);

        //qDebug() << *negativePoint << Qt::endl;

        pointsFirstHalf.append(point);
        pointsSecondHalf.append(negativePoint);
    }
    qDebug() << "initOK" << Qt::endl;
}

double Plot::getFunctionRes(const int x, const int aCoeff) const // drawing function
{
    return pow(x, 3)/(aCoeff - x);
}

void Plot::draw2DAxis()
{
    painter.setPen(QPen(Qt::red, 1));
    drawOxOyLines();

}

void Plot::drawOxOyLines() // this method draws Ox and Oy lines
{
    painter.drawLine(leftOxLineEdge, 0, rightOxLineEdge, 0);
    painter.drawLine(0, downOyLineEdge, 0, upperOyLineEdge);
}

void Plot::drawPlotArrows() // this method draws arrows at the end of the Ox and Oy lines
{

}

void Plot::checkAndSetMax(const QPointF &point, const TYPE_OF_VAR type)
{
    if (type == ARGUMENT){ // type is X
        if(point.x() > xMax){
            xMax = point.x();
        }
    }
    else if (type == VALUE){ // type is Y
        if(point.y() > yMax){
            yMax = point.y();
        }
    }
}

void Plot::checkAndSetMin(const QPointF &point, const TYPE_OF_VAR type)
{
    if (type == ARGUMENT){ // type is X
        if(point.x() < xMin){
            xMin = point.x();
        }
    }
    else if (type == VALUE){// type is Y
        if(point.y() < yMin){
            yMin = point.y();
        }
    }
}

void Plot::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    rightOxLineEdge = 9*width()/20;
    leftOxLineEdge = -rightOxLineEdge;
    upperOyLineEdge = -9*height()/20;
    downOyLineEdge = -upperOyLineEdge;
}


Plot::Plot(QWidget *parent) : QWidget(parent)
{
    pen = new QPen(Qt::black, 1);
    setMinimumSize(400, 200); //fixex min size
}

Plot::~Plot()
{
    clearLists();
    delete pen;
    qDebug() << "~Plot() OK" << Qt::endl;
}
