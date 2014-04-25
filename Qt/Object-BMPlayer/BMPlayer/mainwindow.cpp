
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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "openurldialog.h"
#include "ui_openurldialog.h"
#include "aboutbmysoftdialog.h"
#include "ui_aboutbmysoftdialog.h"
#include "contributions.h"
#include "ui_contributions.h"
#include "internet_radio.h"
#include "ui_internet_radio.h"

#include "QFileDialog"
#include "QFileInfo" 
#include "QProcess"
#include "QString"
#include "QStringList"
#include "QFrame"
#include "QTimer"
#include "QCloseEvent"
#include "QPainter"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QApplication::setStyle("cleanlooks");
    ui->setupUi(this);
    ui->MainWidget->setStyleSheet("background-color:rgb(0, 0, 0);");
    //ui->statusBar->setStyleSheet("background-color:rgb(0, 0, 255);");
    isPlaying = false;
    isStop = false;
    isFullScreen = false;
    direct3d = true;
    xv = false;
    last_use_direct3d = true;
    ui->actionStop->setEnabled(false);
    setWindowTitle(tr("BMPlayer"));
    BMplayer = new QProcess(parent);
    time = new QTimer(parent);
    resize(550, 480);
    unCheck();
    /*-----------------------*/
    hide_some();
    /*-----------------------*/
    ConnectSignalSlot();
    ui->textlabel->setMinimumWidth(200);
    ui->volumeLine->setMinimumWidth(92);
    ui->volumeLine->setMaximumWidth(160);
    statusBar()->showMessage(tr("Ready"), 2000);
    BMplayer_loadarg();

}

void MainWindow::BMplayer_pause()
{
    if(isStop){
            BMplayer_play();
            isStop = false;
            ui->actionStop->setText(tr("Stop"));
        }  else if(!isPause) {
            BMplayer->write("pause\n");
            time->stop();
            isPause = true;
            ui->actionPlay_Pause->setIcon(QIcon(":/image/image/play.png"));
            ui->toolButton_play->setIcon(QIcon(":/image/image/play.png"));
            statusBar()->showMessage(tr("Paused."), 2000);
    }  else {
        BMplayer->write("pause\n");
        time->start(1000);
        isPause = false;
        ui->actionPlay_Pause->setIcon(QIcon(":/image/image/pause.png"));
        ui->toolButton_play->setIcon(QIcon(":/image/image/pause.png"));
        statusBar()->showMessage(tr("Playing."), 2000);
    }
}

void MainWindow::BMplayer_open()
{
    fileName = QFileDialog::getOpenFileName(this,tr("open a media"),".",tr("Media File (*.asf *avi *.wma *.wmv *.3gp *.ac3 *.ape *.cde *.dat *.vcd *.vob *.mpg *.mpeg *.divx *.dv *.mp1 *.mp2 *.mp3 *.mp4 *.mpa *.flac *.flv *.f4v *.mov *.ogg *.ogm *.ogv *.ra *.ram *.rec *.rm *.rmvb *.mpc *.wav *.rmp *.mid *.xa *.mpv *.mqv *.nsv)\n"
                                                                           "Windows Media File (*.asf,*avi,*.wma,*.wmv)\n"
                                                                           "Ac3 File (*.ac3)\n"
                                                                           "Sound CD File (*.ape *.cde)\n"
                                                                           "Video CD File (*.dat *.vcd)\n"
                                                                           "Digital Versatile Disc Movie (*.vob)\n"
                                                                           "MPEG Video File (*.mpg *.mpeg *.divx *.dv *.mp4 *.mp1 *.dat *.3gp)\n"
                                                                           "MPEG Audio File (*.mp1 *.mp2 *.mp3 *.mpa)\n"
                                                                           "MPEG Video elementary stream (*.m1v *.m4v)\n"
                                                                           "Flash Video File (*.flac *.flv *.f4v)\n"
                                                                           "QuickTime Movie File (*.mov)\n"
                                                                           "Ogg Vorbis File (*.ogg *.ogm *.ogv)\n"
                                                                           "RealOne Media (*.ra *.ram *.rec *.rm *.rmvb)\n"
                                                                           "Musepack File (*.mpc)\n"
                                                                           "Windows Wave Sonnd (*.wav *.rmp *.mid)\n"
                                                                           "Maxis Audio File (*.xa)\n"
                                                                           "Other File (*.mpv *.mqv *.nsv)\n"
                                                                           "All File (*)"));
    direct3d = true;
    last_use_direct3d = true;
    BMplayer_load();
}

void MainWindow::BMplayer_load()
{
    if(!fileName.isEmpty()){
        BMplayer_stop();
        BMplayer->close();
        isStop = false;
        ui->actionStop->setText(tr("Stop"));
        mplayerlist.clear();
        mplayerlist << "-slave" << "-quiet" << "-wid";
#ifdef Q_WS_WIN
        program = "MPlayer/mplayer.exe ";
        mplayerlist << QString::number(reinterpret_cast<qlonglong>(ui->widget->winId())) << "-vo";
        if (!direct3d){
            mplayerlist << "directx";
        } else {
            mplayerlist << "direct3d";
        }
        direct3d = true;
#else
        program = "mplayer";
        mplayerlist << QString::number(ui->widget->winId());
        xv = true;
#endif
        mplayerlist << fileName;
 // -wid ´®¿Ú¶¨Î»(COM pos located)
        BMplayer_play();
    }
}
void MainWindow::BMplayer_play()
{
        setCheck();
        BMplayer->start(program, mplayerlist);
        changeWindowTitle(fileName);
        time->start(1000);
        BMplayer->write("get_video_resolution\n");
        BMplayer->write("get_time_length\n");
        ui->volumeLine->setValue(50);
        ui->volumeLine_Fullscreen->setValue(50);
        volumeLineChanged(50);
        isPlaying = true;
        isPause = false;
}

//°´ÏÂÍ£Ö¹°´Å¥ºóÖ´ÐÐ 
void MainWindow::BMplayer_stop()
{
    if(!isStop){
        BMplayer->write("quit\n");
        mplayerEnded();
        changeWindowTitle(fileName);
        isStop = true;
        ui->actionPlay_Pause->setIcon(QIcon(":/image/image/play.png"));
        ui->toolButton_play->setIcon(QIcon(":/image/image/play.png"));
        ui->actionPlay_Pause->setEnabled(true);
        ui->actionStop->setEnabled(false);
        ui->volumeLine->setValue(50);
        volumeLineChanged(50);
        statusBar()->showMessage(tr("Stop"), 2000);
        //ui->actionStop->setText(tr("Play"));
    }/*else if (isStop){
        BMplayer_play();
        isStop = false;
        ui->actionStop->setText(tr("Stop"));
    }*/
}

void MainWindow::changeWindowTitle(const QString &fileName)
{
    QString curfile = fileName;
    QString showname = findFileName(curfile);
    setWindowTitle(tr("%1 - %2").arg(showname).arg(tr("BMPlayer")));
}

QString MainWindow::findFileName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
 
void MainWindow::BMplayer_about()
{
    QMessageBox::about(this,tr("About BMPlayer"),tr("<h2>BMPlayer 1.0.5 Alpha 3</h2>"
                                                    "<h4>Copyright 2007-2012 BMY-Soft"
                                                    "<p>BMPlayer GUI front-end for mplayer.</h4>"));

}

 //°´ÏÂ¹Ø±Õ°´Å¥ºóÖ´ÐÐ
bool MainWindow::stopMplayer()
{
    if(!isPlaying)
        return true;
    time->stop();
    BMplayer->write("quit\n");
    setWindowTitle(tr("BMPlayer"));
    BMplayer->close();
    return true;
}

// ·µ»ØÐÅÏ¢slot
void MainWindow::catchOutput()
{
        while(BMplayer->canReadLine())
        {
                QByteArray buffer(BMplayer->readLine());

                // get_video_resolution : ANS_VIDEO_RESOLUTION='<width> x <height>'
                if(buffer.startsWith("ANS_VIDEO_RESOLUTION"))
                {
                        buffer.remove(0, 21); // vire ANS_VIDEO_RESOLUTION=
                        buffer.replace(QByteArray("'"), QByteArray(""));
                        buffer.replace(QByteArray(" "), QByteArray(""));
                        buffer.replace(QByteArray("\n"), QByteArray(""));
                        buffer.replace(QByteArray("\r"), QByteArray(""));
                        int sepIndex = buffer.indexOf('x');
                        int resX = buffer.left(sepIndex).toInt();
                        int resY = buffer.mid(sepIndex+1).toInt();
                        //·ÀÖ¹ ÓÆµ³¬³öÆÁÄ»
                        if (resX>=700){
                            resX=resX/2;
                            resY=resY/2;
                        }

                        //if (resY>=500){
                        //    resY=resY/2;
                        //}
                        if (!resX>0){
                            //ui->widget->resX = resX;
                            //ui->widget->resY = resY;
                            ui->widget->aspect = 0;
                            //ÅÐ¶Ï²¥·ÅµÄ Ç·ñÎªmusic
                            setMinimumSize(390, 181);

                            ui->widget->setMinimumSize(0 ,0);
                            ui->widget->resize(0,0);
                            ui->MainWidget->resize(0,0);

                            resize(550,181);
                            //½ûÓÃÈ«ÆÁAction
                            ui->actionFullscreen->setEnabled(false);
                            if(buffer.startsWith("Audio only file format detected.")){
                                statusBar()->showMessage(tr("Audio only file format detected."), 2000);
                            }
                            else {
                                if(buffer.startsWith("Video: no video")){
                                    statusBar()->showMessage(tr("Audio only."), 2000);
                                 }
                                 if(buffer.startsWith("[lavf] stream 0: audio (adpcm_ea_maxis_xa), -aid 0")){
                                    ui->timeLine->setEnabled(false);
                                 }}
                        }else {
                            // Ç·ñÎªmove
                                    ui->widget->resX = resX;
                                    ui->widget->resY = resY;
                                    ui->widget->aspect = (double) resX / resY;
                            setMinimumSize(resX+10, resY+176);
                            ui->widget->setMinimumSize(resX, resY);
                        }
                }
                // get_time_length : ANS_LENGTH=xx.yy
                else if(buffer.startsWith("ANS_LENGTH"))
                {
                        buffer.remove(0, 11); // vire ANS_LENGTH=
                        buffer.replace(QByteArray("'"), QByteArray(""));
                        buffer.replace(QByteArray(" "), QByteArray(""));
                        buffer.replace(QByteArray("\n"), QByteArray(""));
                        buffer.replace(QByteArray("\r"), QByteArray(""));
                        maxTime = buffer.toFloat();
                        ui->timeLine->setMaximum(static_cast<int>(maxTime+1));
                        ui->timeLine_Fullscreen->setMaximum(static_cast<int>(maxTime+1));
                        ui->timelabel->setText(tr("%1/0.00").arg(maxTime));
                }
                // get_time_pos : ANS_TIME_POSITION=xx.y
                else if(buffer.startsWith("ANS_TIME_POSITION"))
                {
                        buffer.remove(0, 18); // vire ANS_TIME_POSITION=
                        buffer.replace(QByteArray("'"), QByteArray(""));
                        buffer.replace(QByteArray(" "), QByteArray(""));
                        buffer.replace(QByteArray("\n"), QByteArray(""));
                        buffer.replace(QByteArray("\r"), QByteArray(""));
                        float currTime = buffer.toFloat();
                        ui->timeLine->setValue(static_cast<int>(currTime+1));
                        ui->timeLine_Fullscreen->setValue(static_cast<int>(currTime+1));
                        ui->timelabel->setText(tr("%1/%2").arg(maxTime).arg(currTime));
                }
                // end mplayer,change windowtitle Exiting... (End of file)
                else if(buffer.startsWith("Exiting... (End of file)"))
                {
                       mplayerEnded();  
                }




                else if(buffer.startsWith("Video: no video"))
                {
                   if(!xv && !buffer.startsWith("Audio only file format detected.")){
                       if(last_use_direct3d){
                          last_use_direct3d = false;
                          direct3d = false;
                          time->stop();
                          BMplayer->close();
                          BMplayer_load();
                          statusBar()->showMessage(tr("No video, Try DirectX video output."), 4000);
                       }
                   }
                    else{
                        statusBar()->showMessage(tr("Audio only file format."), 4000);
                    }
                }




              //statusBar()->showMessage(tr(" "), 2000);
        }
}

// µÃµ½ ±¼ä½ø¶È,ÓÉTimeOut´¥·¢
void MainWindow::getTimepos()
{
        BMplayer->write("get_time_pos\n");
}

// ¸Ä±ä ±¼ä½ø¶ÈÌõ(Dirige la timeline)
void MainWindow::timeLineChanged(int pos)
{
        BMplayer->write(QString("seek " + QString::number(pos) + " 2\n").toUtf8());
        ui->timelabel->setText(tr("%1/%2").arg(maxTime).arg(pos));
}

// ¸Ä±äÒôÁ¿½ø¶ÈÌõ
void MainWindow::volumeLineChanged(int volume)
{
        BMplayer->write(QString("volume " + QString::number(volume) + " 2\n").toUtf8());
        ui->volumelabel->setText(tr("Volume:%1%").arg(volume));
}

//  Ó,ÒôÆµ²¥·Å½á øºóÖ´ÐÐ
void MainWindow::mplayerEnded()
{
        isPlaying = false;
        time->stop();
        ui->timeLine->setValue(0);
        ui->timeLine_Fullscreen->setValue(0);
        unCheck();
        //setWindowTitle(tr("BMPlayer"));
        //Èç¹û¼ÓÉÏ,½«»áÔÚ²¥·ÅÍê³Éºó×Ô¶¯¸Ä±äTitle
        isStop = true;
        ui->actionPlay_Pause->setIcon(QIcon(":/image/image/play.png"));
        ui->toolButton_play->setIcon(QIcon(":/image/image/play.png"));
        ui->actionPlay_Pause->setEnabled(true);
        //ÉèÖÃ²¥·Å°´Å¥Îª¿ÉÓÃ
        ui->actionStop->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent *exit)
{
        stopMplayer();
        exit->accept();
}

// È«ÆÁ
void MainWindow::BMplayer_fullscreen()
{
    if(!isFullScreen){
        show_some();
        isFullScreen = true;
    } else if(isFullScreen){
        hide_some();
        isFullScreen = false;
    }

}
void MainWindow::hide_some()
{
    ui->contralWidget->hide();

    ui->MainWidget->setWindowFlags(Qt::SubWindow);
    ui->MainWidget->showFullScreen();
    /*
    ui->toolButton_ExitFullscreen->hide();
    ui->toolButton_play->hide();
    ui->timeLine_Fullscreen->hide();
    ui->volumeLine_Fullscreen->hide();
    ui->toolButton_volume->hide();
    */
}

void MainWindow::show_some()
{
    ui->contralWidget->show();
    ui->MainWidget->setWindowFlags(Qt::Dialog);
    ui->MainWidget->showFullScreen();
    /*(
    ui->toolButton_fullscreen->show();
    ui->toolButton_play->show();
    ui->timeLine_Fullscreen->show();
    ui->volumeLine_Fullscreen->show();
    ui->toolButton_volume->show();
    */
}

void MainWindow::unCheck()
{
    ui->actionPlay_Pause->setEnabled(false);
    ui->actionFullscreen->setEnabled(false);
    ui->timeLine->setEnabled(false);
    ui->volumeLine->setEnabled(false);
    ui->timeLine_Fullscreen->setEnabled(false);
    ui->volumeLine_Fullscreen->setEnabled(false);
}

void MainWindow::setCheck()
{
    ui->actionPlay_Pause->setEnabled(true);
    ui->actionFullscreen->setEnabled(true);
    ui->actionStop->setEnabled(true);
    ui->timeLine->setEnabled(true);
    ui->volumeLine->setEnabled(true);
    ui->timeLine_Fullscreen->setEnabled(true);
    ui->volumeLine_Fullscreen->setEnabled(true);
    ui->actionPlay_Pause->setIcon(QIcon(":/image/image/pause.png"));
    ui->toolButton_play->setIcon(QIcon(":/image/image/pause.png"));
}

void MainWindow::BMplayer_loadarg()
{
    QStringList args = QApplication::arguments();
    args.removeFirst();
    if(!args.isEmpty()){
        foreach (fileName,args);
        BMplayer_load();
    }
}

void MainWindow::BMplayer_openurl()
{
    OpenUrlDialog *dialog = new OpenUrlDialog(this);
    if(dialog->exec()){
        fileName = dialog->ui->UrllineEdit->text();
        BMplayer_load();
    }
}

void MainWindow::BMplayer_Internet_Radio()
{
    Internet_Radio *dialog = new Internet_Radio(this);
    dialog->show();
}

void MainWindow::AboutBMYSoft()
{
    AboutBMYSoftDialog *aboutbmy = new AboutBMYSoftDialog(this);
    aboutbmy->exec();
}

void MainWindow::ConnectSignalSlot()
{
    connect(BMplayer, SIGNAL(readyReadStandardOutput()),this, SLOT(catchOutput()));
    connect(time, SIGNAL(timeout()), this, SLOT(getTimepos()));
    connect(BMplayer, SIGNAL(finished()),this, SLOT(mplayerEnded()));
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}
void MainWindow::Contribution()
{
    Contributions *ContributionsDialog = new Contributions(this);
    ContributionsDialog->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
