#pragma once

// API Definition
#ifdef RADON_CORE
#define RADONCORE_API __declspec(dllexport)

#else
#define RADONCORE_API __declspec(dllimport)
#endif


// STL Includes
#include <memory>
#include <list>
#include <forward_list>

template <typename T>
using TList = std::list<T>;

template <typename T>
using TForwardList = std::forward_list<T>;

// Platform Includes
#include "RadonPlatform.h"


// Core Includes
// #include "RadonMemory.h"


// Additional Includes


// Additional Macros
#define PURE_VIRTUAL

#define INHERITS_FROM(baseClassName) \
public: \
typedef baseClassName Super;

#define CLASS_NOT_COPY_CONSTRUCTIBLE(className) \
className(const className &) = delete;
#define CLASS_NOT_MOVE_CONSTRUCTIBLE(className) \
className(className &&) = delete;
#define CLASS_NOT_CM_CONSTRUCTIBLE(className) \
CLASS_NOT_COPY_CONSTRUCTIBLE(className) \
CLASS_NOT_MOVE_CONSTRUCTIBLE(className)

#define CLASS_NOT_COPY_ASSIGNABLE(className) \
className& operator =(const className &) = delete;
#define CLASS_NOT_MOVE_ASSIGNABLE(className) \
className& operator =(className &&) = delete;
#define CLASS_NOT_CM_ASSIGNABLE(className) \
CLASS_NOT_COPY_ASSIGNABLE(className) \
CLASS_NOT_MOVE_ASSIGNABLE(className)

#define CLASS_NOT_COPYABLE(className) \
CLASS_NOT_CM_CONSTRUCTIBLE(className) \
CLASS_NOT_CM_ASSIGNABLE(className)

#if defined(DEBUG)
#define DEBUG	1
#define NDEBUG	0
#define RELEASE 0

#elif defined(RELEASE)
#define DEBUG	0
#define NDEBUG	1
#define RELEASE 1

#else
#define DEBUG	0
#define NDEBUG	1
#define RELEASE 0
#endif

#if defined(RADON_CONSOLE_APP)
#define RADON_CONSOLE_APP		1
#define RADON_WINDOWED_APP		0
#define RADON_SHARED_LIBRARY	0
#define RADON_STATIC_LIBRARY	0

#define RADON_IS_EXECUTABLE		1
#define RADON_BINARY_UNKNOWN	0

#elif defined(RADON_WINDOWED_APP)
#define RADON_CONSOLE_APP		0
#define RADON_WINDOWED_APP		1
#define RADON_SHARED_LIBRARY	0
#define RADON_STATIC_LIBRARY	0

#define RADON_IS_EXECUTABLE		1
#define RADON_BINARY_UNKNOWN	0

#elif defined(RADON_STATIC_LIBRARY)
#define RADON_CONSOLE_APP		0
#define RADON_WINDOWED_APP		0
#define RADON_STATIC_LIBRARY	1
#define RADON_SHARED_LIBRARY	0

#define RADON_IS_EXECUTABLE		0
#define RADON_BINARY_UNKNOWN	0

#elif defined(RADON_SHARED_LIBRARY)
#define RADON_CONSOLE_APP		0
#define RADON_WINDOWED_APP		0
#define RADON_STATIC_LIBRARY	0
#define RADON_SHARED_LIBRARY	1

#define RADON_IS_EXECUTABLE		0
#define RADON_BINARY_UNKNOWN	0

#else
#define RADON_CONSOLE_APP		0
#define RADON_WINDOWED_APP		0
#define RADON_STATIC_LIBRARY	0
#define RADON_SHARED_LIBRARY	0

#define RADON_IS_EXECUTABLE		0
#define RADON_BINARY_UNKNOWN	1
#endif

#define MEMORY_PROFILING		1