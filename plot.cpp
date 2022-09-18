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
    for(int i = 0; i < pointsFirstHalf.size() - 1; i++){ //we can do this because these lists have the same value of points
        drawLine(pointsFirstHalf[i], pointsFirstHalf[i+1]);
        drawLine(pointsSecondHalf[i], pointsSecondHalf[i+1]);
    }
}

void Plot::clearLists()
{
    pointsFirstHalf.clear();
    pointsSecondHalf.clear();
}

void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(width()/X_AXIS_SHIFT_COEFF, height()/Y_AXIS_SHIFT_COEFF);

    draw2DAxis();
    drawPlot();
    painter.end();
}

void Plot::drawLine(const QPointF &firstPoint, const QPointF &secondPoint) // method draws line between firstPoint and secondPoint points
{

    if(abs(firstPoint.y()) == INFINITY || abs(secondPoint.y()) == INFINITY){ //diff == oo

        int xPosition = 0;
        if(abs(firstPoint.y()) == INFINITY){
             xPosition = firstPoint.x() * scaledCoeffX;
            painter.drawText(xPosition + 5, 20, QString::number(firstPoint.x())); //yMax string point
        }
        else{
            xPosition = secondPoint.x() * scaledCoeffX;
            painter.drawText(xPosition + 5, 20, QString::number(secondPoint.x())); //yMax string point
        }

        painter.setPen(QPen(Qt::red, 1, Qt::PenStyle::DashLine));
        painter.drawLine(xPosition, upperOyLineEdge - ARROW_OFFSET, xPosition, downOyLineEdge);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawLine(xPosition, -5, xPosition, 5);

        return;
    }
    painter.setPen(*pen);
    painter.drawLine(firstPoint.x() * scaledCoeffX, firstPoint.y() * scaledCoeffY, secondPoint.x() *scaledCoeffX, secondPoint.y() *scaledCoeffY);
}


void Plot::create(const int aCoeff, const int xMax) // creating plot
{
    clearLists();
    this->xMax = xMax;
    this->aCoeff = aCoeff;

    initPoints();
}

bool Plot::isSpecialPoint(const int x)
{
    if(aCoeff == x){
        QPointF point = QPointF(x, -INFINITY);
        QPointF negativePoint = QPointF(x, INFINITY);
        pointsFirstHalf.append(point);
        pointsSecondHalf.append(negativePoint);
        return true;
    }
    return false;
}

void Plot::initPoints() // appending function`s points in list
{
    yMax = 0;
    for (int x = 0; x <= xMax; x++){
        if(isSpecialPoint(x)){
            continue;
        }
        double y = getFunctionRes(x, aCoeff);
        QPointF negativePoint = QPointF(x, y); // its negative because in Qt Ox -> right direction, Oy -> down direction
        QPointF point = QPointF(x, -y);
        checkAndSetMax(point, VALUE);
        checkAndSetMax(negativePoint, VALUE);

        pointsFirstHalf.append(point);
        pointsSecondHalf.append(negativePoint);
    }
    scaledCoeffX = double(rightOxLineEdge)/double(xMax);
    scaledCoeffY = double(upperOyLineEdge)/double(yMax);
    update();
}

double Plot::getFunctionRes(const int x, const int aCoeff) const // drawing function
{
    return pow(x, 3)/(aCoeff - x);
}

void Plot::draw2DAxis()
{
    painter.setPen(QPen(Qt::black, 1));
    drawOxOyLines();
    drawPlotArrows();
    addNumbersOnAxis();

}

void Plot::drawOxOyLines() // this method draws Ox and Oy lines
{
    painter.drawLine(leftOxLineEdge, 0, rightOxLineEdge + ARROW_OFFSET, 0);
    painter.drawLine(0, downOyLineEdge, 0, upperOyLineEdge - ARROW_OFFSET);
}

void Plot::addNumbersOnAxis()
{
    painter.drawText(-10, 15, "0");

    painter.drawText(-QString::number(yMax).size()*8, upperOyLineEdge, QString::number(yMax)); //yMax string point
    painter.drawLine(-5, upperOyLineEdge, 5, upperOyLineEdge); //mini-line yMax on axis

    painter.drawText(rightOxLineEdge, 20, QString::number(xMax)); //xMax string point
    painter.drawLine(rightOxLineEdge, -5, rightOxLineEdge, 5); //mini-line xMax on axis

}

void Plot::drawPlotArrows() // this method draws arrows at the end of the Ox and Oy lines
{
    painter.drawLine(rightOxLineEdge + ARROW_OFFSET, 0, rightOxLineEdge + ARROW_OFFSET/2, -3); //drawing OX arrow
    painter.drawLine(rightOxLineEdge + ARROW_OFFSET, 0, rightOxLineEdge + ARROW_OFFSET/2,  3);//drawing OX arrow
    painter.drawText(rightOxLineEdge + ARROW_OFFSET - 5, 10, "x"); //X LABEL

    painter.drawLine(0, upperOyLineEdge - ARROW_OFFSET,  3, upperOyLineEdge - ARROW_OFFSET/2); //drawing OY arrow
    painter.drawLine(0, upperOyLineEdge - ARROW_OFFSET, -3, upperOyLineEdge - ARROW_OFFSET/2);//drawing OY arrow
    painter.drawText(-10, upperOyLineEdge - ARROW_OFFSET + 5, "y"); // Y LABEL
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

//void Plot::checkAndSetMin(const QPointF &point, const TYPE_OF_VAR type)
//{
//    if (type == ARGUMENT){ // type is X
//        if(point.x() < xMin){
//            xMin = point.x();
//        }
//    }
//    else if (type == VALUE){// type is Y
//        if(point.y() < yMin){
//            yMin = point.y();
//        }
//    }
//}

void Plot::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    rightOxLineEdge = 9*(width() - width()/X_AXIS_SHIFT_COEFF)/10;// should remain 10% before the width window
    leftOxLineEdge = -rightOxLineEdge;
    upperOyLineEdge = -9*(height() - height()/Y_AXIS_SHIFT_COEFF)/10; //should remain 10% before the height window
    downOyLineEdge = -upperOyLineEdge;

    scaledCoeffX = double(rightOxLineEdge)/double(xMax);
    scaledCoeffY = double(upperOyLineEdge)/double(yMax);
}


Plot::Plot(QWidget *parent) : QWidget(parent)
{
    pen = new QPen(Qt::darkCyan, 2, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin);
    setMinimumSize(350, 350); //fixex min size
}

Plot::~Plot()
{
    clearLists();
    delete pen;
}
