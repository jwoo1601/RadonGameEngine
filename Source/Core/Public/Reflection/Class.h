// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_CLASS_H
#define RADON_CLASS_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

#include "Class.generated.h"

#include "ReflectionCommon.h"

#include <any>

namespace Radon::Reflection
{
	template <typename T>
	class XNativeClass
	{
	public:

		
	};

	class RADON_API XClass
	{
	public:

		void GetNativeClass();

	public:

		template <typename Type>
		static TSharedPtr<XNativeClass<Type>> FindNativeClass();


	private:
		SConstString m_name;
		EAccessLevel m_accessLevel;
		XModule     *m_module;
		XNamespace  *m_namespace;
		XClass      *m_outerClass;
		TIntrusiveList<XClass*> m_baseClasses;
		EQualifier   m_qualifier;

		uint8        m_bBuiltIn : 1;
	};

#define REGISTER_BUILTIN_CLASS(...)

	REGISTER_BUILTIN_CLASS(int8)
	REGISTER_BUILTIN_CLASS(int16)
	REGISTER_BUILTIN_CLASS(int32)
	REGISTER_BUILTIN_CLASS(int64)
	REGISTER_BUILTIN_CLASS(uint8)
	REGISTER_BUILTIN_CLASS(uint16)
	REGISTER_BUILTIN_CLASS(uint32)
	REGISTER_BUILTIN_CLASS(uint64)
	REGISTER_BUILTIN_CLASS(float)
	REGISTER_BUILTIN_CLASS(double)
	REGISTER_BUILTIN_CLASS()
}

#endif