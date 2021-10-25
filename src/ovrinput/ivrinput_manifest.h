//Copyright 2021 Bennett Bartel
#pragma once
#include <openvr.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace input
{
    /// <summary>
    /// Initializes IVRInput to point to correct action manifest.
    /// CANT be done in constructor body as other objects require.
    /// </summary>
    class manifest
    {
    public:
        manifest()
        {
            auto working_dir = std::filesystem::current_path();
            const auto action_manifest_path = working_dir / "action_manifest.json";

            if (!action_manifest_path.has_filename())
            {
                std::cerr << "Could not find action manifest. Action manifests "
                    "not initialized." << std::endl;
                return;
            }
            const auto valid_manifest_path = action_manifest_path.generic_string();

            const auto error = vr::VRInput()->SetActionManifestPath(valid_manifest_path.c_str());
            if (error != vr::EVRInputError::VRInputError_None)
            {
                std::cerr << "Error setting action manifest path: "
                    << valid_manifest_path << ". OpenVR Error: " << error << std::endl;
            }
        }

        /// Destructor left blank on purpose since there are no terminating calls.
        /// Constructors explicitly deleted to prevent mis-use
        ~manifest() = default;
        manifest(const manifest&) = delete;
        manifest& operator=(const manifest&) = delete;
        manifest(const manifest&&) = delete;
        manifest& operator=(const manifest&&) = delete;
    };
} // namespace input
