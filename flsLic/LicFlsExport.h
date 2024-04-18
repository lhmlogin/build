#ifndef __LICFLSEXPORTS
#define __LICFLSEXPORTS

#ifdef _WIN32
	#ifdef LICLDKFLS_EXPORTS
	#define LICFLS_API  __declspec(dllexport)
	#define LICFLS_TEMPL_API
	#else
	#define LICFLS_API  __declspec(dllimport)
	#define LICFLS_TEMPL_API extern
	#endif // LICLDKFLS_EXPORTS
#else  // _WIN32
	#define LICFLS_API      __attribute__ ((visibility("default")))
	#define LICFLS_TEMPL_API
#endif // _WIN32


#endif // __LICFLSEXPORTS
