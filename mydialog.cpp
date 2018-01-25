#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)

{

    ui->setupUi(this);
    connect(ui->lineEdit, SIGNAL(returnPressed),
            this, SIGNAL(onLineEditReturnPressed()));
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_lineEdit_returnPressed()
{
    emit this->newTextEntered(ui->lineEdit->text());
}
