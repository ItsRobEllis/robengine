// Game Engine Programming Assignment
// By Rob Ellis
// Bournemouth University

#ifndef _STDAFX_H_
#define _STDAFX_H_

// Disable warning for localtime
#pragma warning(disable : 4996)

// System Includes
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <time.h>
#include <string>
#include <vector>
#include <Windows.h>

// SDL & glew
#include "SDL.h"
#include "glew.h"

// Class Headers
#include "Core.h"
#include "Entity.h"

// Components
#include "Camera.h"
#include "Component.h"
#include "Transform.h"

#endif