#define NLS_GROUP "plugin86"
#include <dlfcn.h>
#include <stdlib.h>
#include "odb.h"


_ODB_START(seaflow_plugin86)
{
	int status = 0;
	char * env_p;
	env_p=getenv("INCAM_SERVER");
	char so_path[512]="";
	sprintf(so_path,"%s/site_data/plugin/plugin86.so",env_p);
	void* handle = dlopen(so_path, RTLD_LAZY);
    int (*arc_check_repair)(void);
    arc_check_repair = (int (*) (void)) dlsym(handle, "seaflow_plugin86");  // 获取函数
	status = arc_check_repair();
	dlclose(handle);
	return(status);
}

_ODB_SUMMARY(seaflow_plugin86)
{
	ODB_RETURN_OK;
}

#undef NLS_GROUP