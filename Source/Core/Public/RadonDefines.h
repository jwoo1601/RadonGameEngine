// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_DEFINES_H
#define RADON_DEFINES_H

#include "RadonPlatform.h"
#include "RadonAssert.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
	#pragma once
#endif

#define ABSTRACT_BODY(functionBody) \
{ \
	RADON_ASSERT("A function that has an abstract body must not be directly called"); \
	functionBody; \
}

#define INHERITS_FROM(baseClassName) \
public: \
	typedef baseClassName Super;

#define CLASS_NOT_COPY_CONSTRUCTIBLE(className)       RADON_DELETE_FUNCTION(className(const className &));
#define CLASS_NOT_MOVE_CONSTRUCTIBLE(className)       RADON_DELETE_FUNCTION(className(className &&))

#define CLASS_NOT_CM_CONSTRUCTIBLE(className)         CLASS_NOT_COPY_CONSTRUCTIBLE(className) \
                                                      CLASS_NOT_MOVE_CONSTRUCTIBLE(className)

#define CLASS_NOT_COPY_ASSIGNABLE(className)          RADON_DELETE_FUNCTION(className& operator=(const className &));
#define CLASS_NOT_MOVE_ASSIGNABLE(className)          RADON_DELETE_FUNCTION(className& operator=(className &&));

#define CLASS_NOT_CM_ASSIGNABLE(className)            CLASS_NOT_COPY_ASSIGNABLE(className) \
                                                      CLASS_NOT_MOVE_ASSIGNABLE(className)

#define CLASS_NOT_COPYABLE(className)                 CLASS_NOT_CM_CONSTRUCTIBLE(className) \
                                                      CLASS_NOT_CM_ASSIGNABLE(className)

#endif