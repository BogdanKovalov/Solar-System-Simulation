#pragma once
#ifndef _MODEL_SYSTEM_H_
#define _MODEL_SYSTEM_H_

#include "System.h"

class ModelSystem : public ISystem
{
public:
    virtual void Update() override;
};

#endif
