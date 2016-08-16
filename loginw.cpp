#include "loginw.h"
#include "ui_loginw.h"

loginw::loginw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginw)
{
    ui->setupUi(this);
}

loginw::~loginw()
{
    delete ui;
}
