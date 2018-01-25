#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mydialog.h>
#include <QString>
#include <QSerialPort>

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

    void updateLCD(const QString);

private:
    Ui::MainWindow *ui;
    MyDialog *mDialog;

    QSerialPort *device;
    static const quint16 device_vendor_id = 9025;
    static const quint16 device_product_id = 67;
    QByteArray serialData;
    QString serialBuffer;
};

#endif // MAINWINDOW_H
