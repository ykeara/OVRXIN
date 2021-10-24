#include "AppManifest.h"
#include <filesystem>
#include <iostream>


namespace appManifest
{
    bool initializeManifest()
    {
        auto curPath = std::filesystem::current_path();
        std::filesystem::path manifestPath = curPath / manifestName;
        if (!std::filesystem::exists(manifestPath))
        {
            return false;
        }
        if(vr::VRApplications()->IsApplicationInstalled(appID))
        {
            //ALREADY installed
            return true;
        }
        std::string manifestPathStr = manifestPath.generic_u8string();
        vr::EVRApplicationError error =  vr::VRApplications()->AddApplicationManifest(manifestPathStr.c_str());
        if(error == vr::VRApplicationError_None)
        {
            return true;
        }
        std::cerr << "Could not install Manifest" << vr::VRApplications()->GetApplicationsErrorNameFromEnum(error);
        return false;


        
    }

}
