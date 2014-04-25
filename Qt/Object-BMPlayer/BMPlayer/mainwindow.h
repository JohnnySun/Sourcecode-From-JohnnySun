
/*  BMPlayer, GUI front-end for mplayer.
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}


class QProcess;
class QCloseEvent;
class QTimer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void BMplayer_pause();
    void BMplayer_open();
    void BMplayer_load();
    void BMplayer_loadarg();
    void BMplayer_about();
    void BMplayer_play();
    void BMplayer_stop();
    void BMplayer_fullscreen();
    void BMplayer_openurl();
    void BMplayer_Internet_Radio();
    void Contribution();
    void hide_some();
    void show_some();
    void AboutBMYSoft();
    void catchOutput();
    void ConnectSignalSlot();
    void getTimepos();
    void timeLineChanged(int pos);
    void volumeLineChanged(int volume);
    void mplayerEnded();

private:
    void changeWindowTitle(const QString &fileName);
    void unCheck();
    void setCheck();
    bool isPlaying;
    bool isPause;
    bool isStop;
    bool isFullScreen;
    bool direct3d;
    bool xv;
    bool last_use_direct3d;
    bool stopMplayer();
    QString findFileName(const QString &fullFileName);
    QStringList mplayerlist;
    QString program;
    QString fileName;
    Ui::MainWindow *ui;
    QProcess *BMplayer;
    QWidget *widget;
    QTimer *time;
    float maxTime;

protected:
    virtual void closeEvent(QCloseEvent *exit);

};

#endif // MAINWINDOW_H
