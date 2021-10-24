#include "ivrinput.h"
#include "ivrinput_action.h"
#include <openvr.h>
#include <iostream>
#include <array>

namespace input
{
    /// <summary>
    /// Wrapper For OVR's get digital action Data
    /// </summary>
    /// <param name="action">Digital Action to get state of</param>
    /// <returns></returns>
    vr::InputDigitalActionData_t getDigitalActionData(DigitalAction& action)
    {
        vr::InputDigitalActionData_t handle_data = {};

        const auto error = vr::VRInput()->GetDigitalActionData(
            action.handle(),
            &handle_data,
            sizeof(handle_data),
            vr::k_ulInvalidInputValueHandle);

        if (error != vr::EVRInputError::VRInputError_None)
        {
            std::cerr << "Error getting IVRInput Digital Action Data for handle "
                << action.name() << ". SteamVR Error: " << error << std::endl;
        }

        return handle_data;
    }


    /// <summary>
    /// Wrapper for OVR's get analog action Data
    /// </summary>
    /// <param name="action">Analog Action to get state of</param>
    /// <returns></returns>
    vr::InputAnalogActionData_t getAnalogActionData(AnalogAction& action)
    {
        vr::InputAnalogActionData_t handle_data = {};

        const auto error
            = vr::VRInput()->GetAnalogActionData(action.handle(),
                                                 &handle_data,
                                                 sizeof(handle_data),
                                                 vr::k_ulInvalidInputValueHandle);

        if (error != vr::EVRInputError::VRInputError_None)
        {
            std::cerr << "Error getting IVRInput Analog Action Data for handle "
                << action.name() << ". SteamVR Error: " << error << std::endl;
        }

        return handle_data;
    }


    float analogActionXAxis(AnalogAction& action)
    {
        const auto handle_data = getAnalogActionData(action);
        return handle_data.x;
    }

    float analogActionYAxis(AnalogAction& action)
    {
        const auto handle_data = getAnalogActionData(action);
        return handle_data.y;
    }


    /// <summary>
    /// Will force an action on activation to activate only once until released
    /// </summary>
    /// <param name="action">Action to use</param>
    /// <returns>
    ///   state of action
    /// </returns>
    bool isDigitalActionActivatedOnce(DigitalAction& action)
    {
        const auto handleData = getDigitalActionData(action);

        return handleData.bState && handleData.bChanged;
    }

    /// <summary>
    /// Will allow an action to evaluate while the button is held down for every update
    /// </summary>
    /// <param name="action">Action to use.</param>
    /// <returns>
    /// state of action
    /// </returns>
    bool isDigitalActionActivatedConstant(DigitalAction& action)
    {
        const auto handle_data = getDigitalActionData(action);

        return handle_data.bState;
    }


    /// <summary>
    /// Sets up the input system
    /// </summary>
    ///
    /// Actions should be added to the initializer list before body of constructor
    /// Actions should be certain the action name strings are correct
    /// Failure to do above may result in things just not working, and un-detectable from code.
    SteamIVRInput::SteamIVRInput()
        : m_manifest(), m_haptics(action_sets::haptic),
        m_main(action_sets::main),
        m_thumbRight(action_keys::rThumbstick),
        m_thumbLeft(action_keys::lThumbstick),
        m_triggerRight(action_keys::rTrigger),
        m_triggerLeft(action_keys::lTrigger),
        m_aBut(action_keys::aButton),
        m_bBut(action_keys::bButton),
        m_xBut(action_keys::xButton),
        m_yBut(action_keys::yButton),
        m_menuBut(action_keys::menuButton),
        m_guideBut(action_keys::GuideButton),
        m_rbBut(action_keys::rbButton),
        m_lbBut(action_keys::lbButton),
        m_RThumbBut(action_keys::rThumbstickButton),
        m_LThumbBut(action_keys::lThumbstickButton),
        m_leftHaptic(action_keys::hapticsLeft),
        m_rightHaptic(action_keys::hapticsRight),

          m_left_hand(input_keys::left_hand), m_right_hand(input_keys::right_hand),
          m_sets({
              m_haptics.activeActionSet(),
              m_main.activeActionSet()
          })
    {
    }

    /// <summary>
    /// Value of the x axis of the right thumbstick
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::ThumbRightX()
    {
        return analogActionXAxis(m_thumbRight);
    }

    /// <summary>
    /// Value of the y axis of the right thumbstick
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::ThumbRightY()
    {
        return analogActionYAxis(m_thumbRight);
    }

    /// <summary>
    /// Value of the x axis of the left thumbstick
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::ThumbLeftX()
    {
        return analogActionXAxis(m_thumbLeft);
    }

    /// <summary>
    /// Value of the y axis of the left thumbstick
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::ThumbLeftY()
    {
        return analogActionYAxis(m_thumbLeft);
    }

    /// <summary>
    /// Value of the axis of the Right Trigger
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::TriggerRight()
    {
        return analogActionXAxis(m_triggerRight);
    }

    /// <summary>
    /// Value of the axis of the left Trigger
    /// </summary>
    /// <returns></returns>
    float SteamIVRInput::TriggerLeft()
    {
        return analogActionXAxis(m_triggerLeft);
    }

    bool SteamIVRInput::AButton()
    {
        return isDigitalActionActivatedConstant(m_aBut);
    }
    bool SteamIVRInput::BButton()
    {
        return isDigitalActionActivatedConstant(m_bBut);
    }
    bool SteamIVRInput::XButton()
    {
        return isDigitalActionActivatedConstant(m_xBut);
    }
    bool SteamIVRInput::YButton()
    {
        return isDigitalActionActivatedConstant(m_yBut);
    }
    bool SteamIVRInput::MenuButton()
    {
        return isDigitalActionActivatedConstant(m_menuBut);
    }
    bool SteamIVRInput::GuideButton()
    {
        return isDigitalActionActivatedConstant(m_guideBut);
    }
    bool SteamIVRInput::RBButton()
    {
        return isDigitalActionActivatedConstant(m_rbBut);
    }
    bool SteamIVRInput::LBButton()
    {
        return isDigitalActionActivatedConstant(m_lbBut);
    }
    bool SteamIVRInput::LThumbButton()
    {
        return isDigitalActionActivatedConstant(m_LThumbBut);
    }
    bool SteamIVRInput::RThumbButton()
    {
        return isDigitalActionActivatedConstant(m_RThumbBut);
    }


    /// <summary>
    /// returns the value of the Left the haptic action handle.
    /// </summary>
    /// <returns></returns>
    vr::VRActionHandle_t SteamIVRInput::leftHapticActionHandle() const
    {
        return m_leftHaptic.handle();
    }


    /// <summary>
    /// returns the value of the right haptic action handle.
    /// </summary>
    /// <returns></returns>
    vr::VRActionHandle_t SteamIVRInput::rightHapticActionHandle() const
    {
        return m_rightHaptic.handle();
    }


    /// <summary>
    /// returns the input handle of the right hand controller
    /// </summary>
    /// <returns></returns>
    vr::VRInputValueHandle_t SteamIVRInput::rightInputHandle() const
    {
        return m_right_hand.handle();
    }


    /// <summary>
    /// returns the input handle of the left hand controller
    /// </summary>
    /// <returns></returns>
    vr::VRInputValueHandle_t SteamIVRInput::leftInputHandle() const
    {
        return m_left_hand.handle();
    }

    /// <summary>
    /// Updates the state of all the actions
    /// </summary>
    void SteamIVRInput::update_states()
    {
        const auto error = vr::VRInput()->UpdateActionState(
            m_sets.data(),
            sizeof(vr::VRActiveActionSet_t),
            action_sets::number_of_sets);

        if (error != vr::EVRInputError::VRInputError_None)
        {
            std::cerr
                << "Error during IVRInput action state update. OpenVR Error: "
                << error << std::endl;
        }
    }
} // namespace input
