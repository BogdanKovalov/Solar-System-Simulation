#pragma once
#ifndef _TICK_OBJECT_H_
#define _TICK_OBJECT_H_

class TickObject
{
public:
    TickObject();
    virtual void Tick(float DeltaTime){};
};

#endif
