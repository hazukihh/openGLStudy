#pragma once


#include "Log.h"


#define ENGI_ASSERT(x,...) {if (!(x)) { ENGI_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
#define ENGI_CORE_ASSERT(x,...) {if (!(x)) { ENGI_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
