#include "serialportcontroller.h"

SerialPortController::SerialPortController(QObject *parent) : QObject(parent)
{

}

SerialPortController::~SerialPortController()
{

}

void SerialPortController::updateSerialPortList()
{
    serialportList = QSerialPortInfo::availablePorts();
}

void SerialPortController::openSerialPort(QSerialPortInfo portinfo)
{
    serial = new QSerialPort(portinfo);//设置串口名
    serial->open(QIODevice::ReadWrite);// 读写方式
    serial->setBaudRate(9600); //设置波特率
    serial->setDataBits(QSerialPort::Data8);//数据位8
    serial->setParity(QSerialPort::NoParity);//校验位N
    serial->setStopBits(QSerialPort::OneStop);//停止位1
    serial->setFlowControl(QSerialPort::NoFlowControl); //无流控

}

int SerialPortController::writeData(char* data,int len)
{
    if(serial == NULL){
        return -1;
    }
    return serial->write(data,len);
}

int SerialPortController::recvData(char *data,int max)
{
    if(serial == NULL){
        return -1;
    }
    return serial->read(data,max);
}

void SerialPortController::closeSerialPort()
{
    serial->clear();//清空缓冲
    serial->close();//关闭串口
    delete serial;
    serial = NULL;
}



