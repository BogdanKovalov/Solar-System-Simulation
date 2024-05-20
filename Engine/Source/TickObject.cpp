#include "TickObject.h"
#include "Aplication.h"

TickObject::TickObject() 
{
    auto API = Aplication::GetAPI();
    if (API)
    {
        API->AddTickObject(this);
    }
}