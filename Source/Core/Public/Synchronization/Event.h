// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_EVENT_H
#define RADON_EVENT_H

#include "RadonCore.h"

namespace Radon
{
	class RADON_API XEvent
	{
	public:

		XEvent();
		~XEvent();

		void Create();
		void Destroy();

		void Signal();

		static XEvent FindExistingEvent();
	};
}

#endif