#include "serial.h"
#include <QDebug>

serial::serial(QObject *parent) : QObject(parent)
{

   mserial = new QSerialPort();

}

serial::~serial(){

   delete mserial;

}

void serial::setSerial(QString portName,unsigned int baud,short data,short parity,short stop){

    mserial->setPortName(portName);
    mserial->open(QIODevice::ReadWrite);
    mserial->setBaudRate(baud);

    switch(data){

    case 5:mserial->setDataBits(QSerialPort::Data5); break;
    case 6:mserial->setDataBits(QSerialPort::Data6); break;
    case 7:mserial->setDataBits(QSerialPort::Data7); break;
    case 8:mserial->setDataBits(QSerialPort::Data8); break;
    default :break;

    }


    switch(parity){
    case 0: mserial->setParity(QSerialPort::NoParity); break;
    default :break;
    }
    switch(stop){
    case 0:mserial->setStopBits(QSerialPort::OneStop);break;
    case 1:mserial->setStopBits(QSerialPort::TwoStop);break;
    default :break;
    }
    mserial->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->mserial,SIGNAL(readyRead()),this,SLOT(serialRevData()));

}


void serial::serialSendData_(QByteArray bufferdata){

    mserial->write(bufferdata);
}

void serial::serialRevData(){

    QByteArray tmp;
    tmp = mserial->readAll();
    qDebug()<<tmp;

    buffer_+=tmp;

    emit serial_GetBits();
}
