#pragma once

// Platform Macros
#define PLATFORM_DESKTOP	1
#define PLATFORM_CONSOLE	0
#define PLATFORM_MOBILE		0

#define PLATFORM_SUPPORTS_SIMD	1
#define PLATFORM_SUPPORTS_SSE2	1
#define PLATFORM_SUPPORTS_NEON	0


// Additional Macros
#define INTERFACE				__declspec(novtable)

#define FORCEINLINE				__forceinline
#define FORCENOINLINE			__declspec(noinline)

#define ALIGN_OF(x)				alignof(x)

#define RADON_NOEXCEPT(x)		noexcept(x)