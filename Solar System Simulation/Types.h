#pragma once
#ifndef _TYPES_H_
#define _TYPES_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <map>

enum ETrigger
{
    W = GLFW_KEY_W,
    D = GLFW_KEY_D,
    S = GLFW_KEY_S,
    A = GLFW_KEY_A,
    MOUSEMOVE
};

enum ETriggerEvent
{
    PRESSED = GLFW_PRESS,
    HOLD = GLFW_REPEAT,
    RELEASED = GLFW_RELEASE,
    TRIGGERED = 3
};

enum EInputValueType
{
    BOOL,
    VECTOR2D
};

enum EAxes
{
    X,
    Y,
    Z
};

struct FInputValue
{
public:
    FInputValue() : Value(glm::vec3(0.0f)), Type(EInputValueType::VECTOR2D) {}
    FInputValue(glm::vec3 InValue, EInputValueType InType) : Value(InValue), Type(InType) {}
    FInputValue(const FInputValue&) = default;
    FInputValue& operator=(const FInputValue&) = default;

    float& GetAxisValue(EAxes Axis)
    {
        switch (Axis)
        {
            case X: return Value.x;
            case Y: return Value.y;
            case Z: return Value.z;
        }
    }

    template <typename T>
    inline T Get() const
    {
        static_assert(sizeof(T) == 0, "Unsuported type");
    }

    template <>
    inline bool Get() const
    {
        return static_cast<bool>(Value.x);
    }

    template <>
    inline glm::vec2 Get() const
    {
        return glm::vec2(Value.x, Value.y);
    }

    inline void Set(glm::vec3 NewValue) { Value = NewValue; }

private:
    glm::vec3 Value = glm::vec3(0.0f);
    EInputValueType Type;
};

#endif _TYPES_H_