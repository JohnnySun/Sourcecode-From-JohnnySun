
/*  BMplayer, GUI front-end for mplayer.
    Copyright 2007-2012 BMY-Soft <bmy001@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the BMY-Soft,
    DaGang Oil Field, BinHai New Area, Tianjin,  300280  China
*/
#include "bmplayerwidget.h"
#include "QPainter"

BMPlayerWidget::BMPlayerWidget(QWidget *parent) :
    QWidget(parent)
{
    setStyleSheet("background-color:rgb(0, 0, 0);");
    w = resX;
    h = resY;
    aspect = (double) 16 / 9;
}

/*
void BMPlayerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
         painter.setPen(Qt::blue);
         painter.setFont(QFont("Arial", 30));
         painter.drawText(rect(), Qt::AlignCenter, "BMPlayer V1.0.3");
}
*/

void BMPlayerWidget::resizeEvent( QResizeEvent * /* e */)
{
   /*qDebug("MplayerWindow::resizeEvent: %d, %d",
           e->size().width(), e->size().height() );*/
    updateVideoWindow();
}

void BMPlayerWidget::updateVideoWindow()
{
        //qDebug("MplayerWindow::updateVideoWindow");

    //qDebug("aspect= %f", aspect);

    int w_width = size().width();
    int w_height = size().height();

        int w = w_width;
        int h = w_height;
        int x = 0;
        int y = 0;

        if (aspect != 0) {
            int pos1_w = w_width;
            int pos1_h = w_width / aspect + 0.5;

            int pos2_h = w_height;
            int pos2_w = w_height * aspect + 0.5;

            //qDebug("pos1_w: %d, pos1_h: %d", pos1_w, pos1_h);
            //qDebug("pos2_w: %d, pos2_h: %d", pos2_w, pos2_h);

            if (pos1_h <= w_height) {
                //qDebug("Pos1!");
                        w = pos1_w;
                        h = pos1_h;

                        y = (w_height - h) /2;
            } else {
                //qDebug("Pos2!");
                        w = pos2_w;
                        h = pos2_h;

                        x = (w_width - w) /2;
            }
        }

    move(x,y);
    resize(w, h);

    //qDebug( "w_width: %d, w_height: %d", w_width, w_height);
    //qDebug("w: %d, h: %d", w,h);
}

QSize BMPlayerWidget::sizeHint() const {
        //qDebug("MplayerWindow::sizeHint");
        return QSize( video_width, video_height );
}

QSize BMPlayerWidget::minimumSizeHint () const {
        return QSize(0,0);
}
