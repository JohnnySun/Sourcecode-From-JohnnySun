#include "openurl.h"
#include "ui_openurl.h"

openurl::openurl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openurl)
{
    ui->setupUi(this);
}

openurl::~openurl()
{
    delete ui;
}
