
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
#ifndef OPENURLDIALOG_H
#define OPENURLDIALOG_H

#include <QDialog>

namespace Ui {
    class OpenUrlDialog;
}

class OpenUrlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenUrlDialog(QWidget *parent = 0);
    ~OpenUrlDialog();
    Ui::OpenUrlDialog *ui;

private:

};

#endif // OPENURLDIALOG_H
