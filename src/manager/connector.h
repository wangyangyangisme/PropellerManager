#pragma once

#include "interface.h"

#include <QDebug>

template <class Target>
class Connector : public Interface 
{
    bool        _attached;
    bool        _paused;

protected:
    Target      _target;

    virtual void attachSignals()
    {
        connect(_target,    SIGNAL(sendError(const QString &)), this,   SIGNAL(sendError(const QString &)));
        connect(_target,    SIGNAL(bytesWritten(qint64)),       this,   SIGNAL(bytesWritten(qint64)));
        connect(_target,    SIGNAL(baudRateChanged(qint32)),    this,   SIGNAL(baudRateChanged(qint32)));
        connect(_target,    SIGNAL(readyRead()),                this,   SIGNAL(readyRead()));
    }

    virtual void detachSignals()
    {
        disconnect(_target,    SIGNAL(sendError(const QString &)), this,   SIGNAL(sendError(const QString &)));
        disconnect(_target,    SIGNAL(bytesWritten(qint64)),       this,   SIGNAL(bytesWritten(qint64)));
        disconnect(_target,    SIGNAL(baudRateChanged(qint32)),    this,   SIGNAL(baudRateChanged(qint32)));
        disconnect(_target,    SIGNAL(readyRead()),                this,   SIGNAL(readyRead()));
    }

public:
    Connector() : Interface()
    {
        _attached = false;
        _paused = false;
    }

    Target target()
    {
        return _target;
    }

    bool isPaused()
    {
        return _paused;
    }

    void setPaused(bool paused)
    {
        _paused = paused;
    }

    bool isAttached()
    {
        if (_target == NULL) return false;
        return _attached;
    }

    bool isActive()
    {
        return (!isPaused() && isAttached());
    }

    bool attach(Target target)
    {
        if (isAttached()) return false;
        if (target == NULL) return false;
    
        _target = target;

//        qDebug() << "connecting" << this << "to" << _target;

        attachSignals();
    
        _attached = true;

        return true;
    }

    void detach()
    {
        if (!isAttached()) return;
    
//        qDebug() << "removing" << this << "from" << _target;

        detachSignals();
    
        _attached = false;
    }

    bool isOpen()
    {
        if (!isActive()) return false;
        return _target->isOpen();
    }

    bool clear()
    {
        if (!isActive()) return false;
        return _target->clear();
    }

    bool setBaudRate(quint32 baudRate)
    {
        if (!isActive()) return false;
        return _target->setBaudRate(baudRate);
    }

    QString portName()
    {
        return _target->portName();
    }

    quint32 baudRate()
    {
        return _target->baudRate();
    }

    qint64 bytesToWrite()
    {
        if (!isActive()) return 0;
        return _target->bytesToWrite();
    }

    qint64 bytesAvailable()
    {
        if (!isActive()) return 0;
        return _target->bytesAvailable();
    }

    QByteArray read(qint64 maxSize)
    {
        if (!isActive()) return QByteArray();
        return _target->read(maxSize);
    }

    QByteArray readAll()
    {
        if (!isActive()) return QByteArray();
        return _target->readAll();
    }

    bool putChar(char c)
    {
        if (!isActive()) return false;
        return _target->putChar(c);
    }

    qint64 write(QByteArray ba)
    {
        if (!isActive()) return -1;
        return _target->write(ba);
    }

    quint32 minimumTimeout()
    {
        if (!isActive()) return 0;
        return _target->minimumTimeout();
    }

    void setMinimumTimeout(quint32 milliseconds)
    {
        if (!isActive()) return;
        _target->setMinimumTimeout(milliseconds);
    }

    quint32 calculateTimeout(quint32 bytes)
    {
        if (!isActive()) return 0;
        return _target->calculateTimeout(bytes);
    }

    void useReset(QString name, int pin)
    {
        if (!isActive()) return;
        _target->useReset(name, pin);
    }

    void useDefaultReset()
    {
        if (!isActive()) return;
        return _target->useDefaultReset();
    }

    bool reset()
    {
        if (!isActive()) return false;
        return _target->reset();
    }

    quint32 resetPeriod()
    {
        if (!isActive()) return 0;
        return _target->resetPeriod();
    }

    int error()
    {
        if (!isActive()) return 0;
        return _target->error();
    }

    QString errorString()
    {
        if (!isActive()) return QString();
        return _target->errorString();
    }

};

