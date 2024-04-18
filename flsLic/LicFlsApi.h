
#ifndef __LICFLSAPI
#define __LICFLSAPI

#include <LicFls/LicFlsExport.h>

enum lic_ldk_fls_error_codes
{
	/*No error*/
	LLF_OK = 0,
	
	/*License Type not supported*/
	LLF_TYPE_NO_SUPPORT = 100,

	/*Trying to unlock feature that not locked by this instance*/
	LLF_NOLOCK_UNLOCK = 101,

	/*This application cannot find feature id by given name*/
	LLF_NAME_NOT_DEFINED = 102
};

enum lic_ldk_fls_type
{
	/*CAM*/
	CAM_TYPE = 0,
	/*PS*/
	PS_TYPE = 1
};

//initialized license server 
extern "C" LICFLS_API int    lic_ldk_fls_init_server(const char* serverName, lic_ldk_fls_type t);

//lock LDK license 
extern "C" LICFLS_API int	lic_ldk_fls_lock_id(int licId);
extern "C" LICFLS_API int	lic_ldk_fls_lock_name(const char* licName);
//unlock LDK license 
extern "C" LICFLS_API int	lic_ldk_fls_unlock_id(int licId);
extern "C" LICFLS_API int	lic_ldk_fls_unlock_name(const char* licName);
//check LDK license existence 
extern "C" LICFLS_API bool	lic_ldk_fls_exists_id(int licId);
extern "C" LICFLS_API bool	lic_ldk_fls_exists_name(const char* licName);


#endif //__LICFLSAPI


