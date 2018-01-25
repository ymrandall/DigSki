#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"
#include <QTimer>
#include <QDateTime>
#include <QSerialPort>
#include <string>
#include <QDebug>
#include <QSerialPortInfo>
#include <QList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //digital clock
    QTimer *timer=new QTimer(this); //for clock
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime())); //signal/slot, update time
    timer->start();

    //TEMP DISPLAY
    ui->lcdNumber_TMP->display("------");

    //serial port
    device = new QSerialPort(this);
    serialBuffer = "";

    //DEBUG SERIAL
    /*
     qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
     foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor ID?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product ID? " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
     }
     */

    //Identify available ports
    bool device_available = false;
    QString device_port;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            if((serialPortInfo.productIdentifier() == device_product_id)
                    && (serialPortInfo.vendorIdentifier() == device_vendor_id)){
                device_available = true; //device is available on this port
                device_port = serialPortInfo.portName();
            }
        }
    }

    //Open port, if available
    if(device_available){
        qDebug() << "Found the device port...\n";
        device -> setPortName(device_port);
        device -> open(QSerialPort::WriteOnly);
        device -> setBaudRate(QSerialPort::Baud9600);
        device -> setDataBits(QSerialPort::Data8);
        device -> setFlowControl(QSerialPort::NoFlowControl);
        device -> setParity(QSerialPort::NoParity);
        device -> setStopBits(QSerialPort::OneStop);
        QObject::connect(device, SIGNAL(readyRead()),this,SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the device.\n";
        //QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to device");
    }

}

void MainWindow::readSerial()
{
    //qDebug() << "serialport works";
    //qDebug() << serialBuffer;

    QStringList bufferSplit = serialBuffer.split(",");
    if(bufferSplit.length() < 3){
        serialData = device -> readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }else{
        //bufferSplit[1] is a good value
        qDebug() << bufferSplit;
        MainWindow::updateLCD(bufferSplit[1]);
        serialBuffer = "";
    }

}

void MainWindow::updateLCD(const QString sensor_reading)
{
    ui -> lcdNumber_TMP -> display(sensor_reading);
}

void MainWindow::showTime()
{
    QTime time=QTime::currentTime(); //create time
    QString time_text=time.toString("hh : mm : ss"); //format time
    ui->DigitalClock->setText(time_text); //make label display time
    //ui->label_2->setText(name);
}


MainWindow::~MainWindow()
{
    if(device -> isOpen()){
        device -> close(); //close serial port if it is open
    }
    delete ui;
}

void MainWindow::on_actionNew_Window_triggered()
{
    mDialog = new MyDialog(this);
    mDialog->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText("Message sent");

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->setText("Message sent.");
}

void MainWindow::onNewTextEntered(const QString &text)
{
    ui->label_2->setText(text);
}
