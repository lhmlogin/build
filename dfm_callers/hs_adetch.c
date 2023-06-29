#define NLS_GROUP "hs_adetch"
#include <dlfcn.h>
#include <stdlib.h>
#include "odb.h"


_ODB_START(seaflow_hs_adetch)
{
	int status = 0;
	char * env_p;
	env_p=getenv("INCAM_SERVER");
	char so_path[512]="";
	sprintf(so_path,"%s/site_data/plugin/hs_adetch.so",env_p);
	void* handle = dlopen(so_path, RTLD_LAZY);
    int (*arc_check_repair)(void);
    arc_check_repair = (int (*) (void)) dlsym(handle, "seaflow_hs_adetch");  // 获取函数
	status = arc_check_repair();
	dlclose(handle);
	return(status);
}

_ODB_SUMMARY(seaflow_hs_adetch)
{
	ODB_RETURN_OK;
}

#undef NLS_GROUP