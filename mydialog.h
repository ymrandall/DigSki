#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();


private slots:
    void on_lineEdit_returnPressed();

    //void on_lineEdit_textEdited(const QString &arg1);

    //void on_lineEdit_textEdited(const QString &arg1);

signals:
    void newTextEntered(const QString &text);

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
