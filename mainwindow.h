#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mydialog.h>
#include <QString>
#include <QSerialPort>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onNewTextEntered(const QString &text);

private slots:
    void on_actionNew_Window_triggered();
    void showTime();
    void readSerial();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateLCD(QString);

private:
    Ui::MainWindow *ui;
    MyDialog *mDialog;

    QSerialPort *device;
    static const quint16 device_vendor_id = 6790;
    static const quint16 device_product_id = 29987;
    QByteArray serialData;
    QString serialBuffer;
    QString line;
};

#endif // MAINWINDOW_H
