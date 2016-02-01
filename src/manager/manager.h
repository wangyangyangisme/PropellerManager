#pragma once

#include "interface.h"

#include <QHash>

template <class Key, class Interface>
class Manager
{

protected:
    QHash<Key, Interface> _interfaces;

public:
    Manager()
    {
    }
    
    virtual ~Manager()
    {
    }

    bool exists(Key key)
    {
        return (_interfaces.contains(key) && _interfaces[key] != NULL);
    }

    bool enabled(Key key)
    {
        return interface(key)->isPaused();
    }

    void setEnabled(Key key, bool paused)
    {
        interface(key)->setPaused(paused);
    }

    virtual Interface interface(Key key) = 0;

    void remove(Key key)
    {
        if (exists(key))
        {
            interface(key)->detach();
            delete _interfaces[key];
            _interfaces.remove(key);
        }
    }

};