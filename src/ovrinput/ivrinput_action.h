#pragma once
#include <iostream>
#include <openvr.h>

namespace input
{
    /// <summary>
    /// The type of function that should be called to get data for the action.
    /// The IVRInput API does not give explicit warnings when the wrong functions are
    /// called.This enum is an attempt at runtime checking.
    /// </summary>
    enum class action_type
    {
        undefined,
        digital,
        analog,
        haptic,
    };


    /// <summary>
    /// Instantiates a Single Action, should use a name that is similar to one in manifest.
    /// </summary>
    class action
    {
    public:
        /// <summary>
        /// wrapper for getting OpenVR's action handles
        /// </summary>
        /// <param name="actionName">Name of the action.</param>
        explicit action(const char* const actionName) : m_name(actionName)
        {
            const auto error = vr::VRInput()->GetActionHandle(actionName, &m_handle);

            if (error != vr::EVRInputError::VRInputError_None)
            {
                std::cerr << "Error getting handle for '" << actionName
                    << "'. OpenVR Error: " << error << std::endl;
            }
        }

        /// <summary>
        /// wrapper for OpenVr's handle to the action.
        /// </summary>
        /// <returns> returns the Action handle </returns>
        [[nodiscard]] vr::VRActionHandle_t handle() const noexcept
        {
            return m_handle;
        }

        /// <summary>
        /// returns Name of the Action (according to manifest)
        /// </summary>
        /// <returns>Name of Action in manifest </returns>
        [[nodiscard]] std::string name() const noexcept
        {
            return m_name;
        }

    private:
        vr::VRActionHandle_t m_handle = 0;
        const std::string m_name;
    };

    class DigitalAction : public action
    {
    public:
        explicit DigitalAction(const char* const actionName) : action(actionName)
        {
        }
    };

    class AnalogAction : public action
    {
    public:
        explicit AnalogAction(const char* const actionName) : action(actionName)
        {
        }
    };
} // namespace input
