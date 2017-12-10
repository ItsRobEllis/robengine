/**
  * Stdafx is a precompiled header file.
  * This contains all header files included in the solution, as well as system and required external libraries
  * @file: Stdafx.h
  * @author: Rob Ellis
  * @date: 27/11/2017
  */

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

// SDL & Glew
#include "SDL.h"
#include "glew.h"

// GLM
#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"
#include "glm\gtc\matrix_transform.hpp"

// Class Headers
#include "Core.h"
#include "Entity.h"
#include "Mesh.h"
#include "Shader.h"

// Components
#include "Camera.h"
#include "Component.h"
#include "Material.h"
#include "Transform.h"

#endif