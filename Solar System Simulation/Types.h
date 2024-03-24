#pragma once
#ifndef _TYPES_H_
#define _TYPES_H_

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum EKey
{
    W = GLFW_KEY_W,
    D = GLFW_KEY_D,
    S = GLFW_KEY_S,
    A = GLFW_KEY_A
};

enum ETriggerEvent
{
    PRESSED = GLFW_PRESS,
    RELEASED = GLFW_RELEASE
};

#endif _TYPES_H_