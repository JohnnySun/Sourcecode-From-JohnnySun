#ifndef INTERNET_READIO_H
#define INTERNET_READIO_H

#include <QDialog>

namespace Ui {
    class Internet_readio;
}

class Internet_readio : public QDialog
{
    Q_OBJECT

public:
    explicit Internet_readio(QWidget *parent = 0);
    ~Internet_readio();
    Ui::Internet_readio *ui;

private:

};

#endif // INTERNET_READIO_H
