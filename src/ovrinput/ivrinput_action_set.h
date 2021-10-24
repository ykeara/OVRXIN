#pragma once
#include <openvr.h>
#include <iostream>

namespace input
{
    /// <summary>
    /// A wrapper to Handle OpenVR's action Sets.
    /// Simply put it is a collection of Actions.
    /// </summary>
    class ActionSet
    {
    public:
        ActionSet(const char* setName)
        {
            vr::VRActionSetHandle_t handle = 0;
            auto error = vr::VRInput()->GetActionSetHandle(setName, &handle);
            if (error != vr::EVRInputError::VRInputError_None)
            {
                std::cerr << "Error getting handle for '" << setName
                    << "'. OpenVR Error: " << error << std::endl;
            }

            m_activeActionSet.ulActionSet = handle;
            m_activeActionSet.ulRestrictedToDevice
                = vr::k_ulInvalidInputValueHandle;
            m_activeActionSet.nPriority = 0;
        }

        void setPriority(int32_t priority)
        {
            m_activeActionSet.nPriority = priority;
        }

        vr::VRActiveActionSet_t activeActionSet()
        {
            return m_activeActionSet;
        }

    private:
        vr::VRActiveActionSet_t m_activeActionSet = {};
    };
} // namespace input
