
#ifndef __LICFLS
#define __LICFLS

#include <LicFls/LicFlsExport.h>

#include <LicFls/hasp_api.h>

#include <string>
#include <map>
#include <vector>
#include <atomic>


namespace LicLdkFlsNs {
	int initServer(const std::string& serverName);

 	int lock(int licId);
 	int unlock(int licId);
 	bool exists(int licId);
 
	int lock(const std::string& licName);
 	int unlock(const std::string& licName);
 	bool exists(const std::string& licName);

    int getHaspIds(std::string& haspids);
};



#endif //__LICFLS


