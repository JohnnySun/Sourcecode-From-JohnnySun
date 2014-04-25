#ifndef OPENURL_H
#define OPENURL_H

#include <QDialog>

namespace Ui {
    class openurl;
}

class openurl : public QDialog
{
    Q_OBJECT

public:
    explicit openurl(QWidget *parent = 0);
    ~openurl();

private:
    Ui::openurl *ui;
};

#endif // OPENURL_H
