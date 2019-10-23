// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_FILE_H
#define RADON_FILE_H

#include "RadonCoreMinimal.h"

#if RADON_COMPILER_SUPPORTS_PRAGMA_ONCE
#pragma once
#endif

namespace Radon::IO
{
	class RADON_API IPathObject
	{

	};

	class RADON_API XFile : public IPathObject
	{
	public:
		bool CanRead() const;
		bool CanWrite() const;
		bool IsReadOnly() const;

		XText 

	private:
		XString m_name;
		XString m_extension;
		SPlatformFile m_native;
	};

	class RADON_API XPath
	{
	public:

	private:
		XPath *m_parent;
		TList<XPath*> m_children;
	};
}

#endif