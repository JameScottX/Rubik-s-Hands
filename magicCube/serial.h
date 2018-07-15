#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class serial : public QObject
{
    Q_OBJECT
public:
    explicit serial(QObject *parent = nullptr);
    ~serial();
    QSerialPort *mserial;

    QByteArray buffer_;

    void setSerial(QString portName,unsigned int baud,short data,short parity,short stop);
    void serialSendData_(QByteArray bufferdata);

    bool serial_flag = false;

signals:

    void serial_GetBits();

private slots:

    void serialRevData();

};

#endif // SERIAL_H
