// Copyright 2019 Simon Kim All Rights Reserved.

#ifndef RADON_RADON_LOG_H
#define RADON_RADON_LOG_H

#if DEBUG
#define RADON_LOG(category, msg, ...)
#else
#define RADON_LOG(...) ((void)0)
#endif

#define CREATE_LOG_CATEGORY(name, verbosity)

#endif