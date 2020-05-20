#ifndef SERIALPORTCONTROLLER_H
#define SERIALPORTCONTROLLER_H

#include <QObject>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



class SerialPortController : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortController(QObject *parent = nullptr);
    ~SerialPortController();

    void updateSerialPortList(); //查找可用的串口

    void openSerialPort(QSerialPortInfo portinfo);
    int writeData(char* data,int len);
    int recvData(char *data,int max);
    void closeSerialPort();

    QList<QSerialPortInfo> serialportList;//本地可用的串口
private:
    QSerialPort *serial;// 当前打开的串口
};

#endif // SERIALPORTCONTROLLER_H
