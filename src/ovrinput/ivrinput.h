#pragma once

#include <openvr.h>
#include "ivrinput_action.h"
#include "ivrinput_manifest.h"
#include "ivrinput_action_set.h"
#include "ivrinput_input_source.h"
#include <array>

namespace input
{
    /// <summary>
    /// Action Paths, Since IVRInput system is finicky declare as constexpr auto to prevent errors
    /// </summary>
    namespace action_keys
    {
        constexpr auto aButton = "/actions/main/in/a";
        constexpr auto bButton = "/actions/main/in/b";
        constexpr auto xButton = "/actions/main/in/x";
        constexpr auto yButton = "/actions/main/in/y";
        constexpr auto rbButton = "/actions/main/in/rb";
        constexpr auto lbButton = "/actions/main/in/lb";
        constexpr auto menuButton = "/actions/main/in/menu";
        constexpr auto GuideButton = "/actions/main/in/guide";
        constexpr auto rTrigger = "/actions/main/in/rt";
        constexpr auto lTrigger = "/actions/main/in/lt";
        constexpr auto rThumbstick = "/actions/main/in/rthumb";
        constexpr auto lThumbstick = "/actions/main/in/lthumb";
        constexpr auto rThumbstickButton = "/actions/main/in/rthumbp";
        constexpr auto lThumbstickButton = "/actions/main/in/lthumbp";


        constexpr auto hapticsLeft = "/actions/haptic/out/hapticsleft";
        constexpr auto hapticsRight = "/actions/haptic/out/hapticsright";
    } // namespace action_keys


    /// <summary>
    /// Keys to get input source handles (things like hmd controllers etc.)
    /// </summary>
    namespace input_keys
    {
        constexpr auto left_hand = "/user/hand/left";
        constexpr auto right_hand = "/user/hand/right";
    } // namespace input_keys

    /// <summary>
    /// Keys for different action sets
    /// </summary>
    namespace action_sets
    {
        constexpr auto number_of_sets = 2;
        constexpr auto main = "/actions/main";
        constexpr auto haptic = "/actions/haptic";
    } // namespace action_sets

    using active_action_sets
    = std::array<vr::VRActiveActionSet_t, action_sets::number_of_sets>;

    /// <summary>
    /// Responsible for Controller Input
    /// Update States() will update the state, should be called every update
    /// </summary>
    /*
    Binary actions should only have one function,
    and they should reflect the expected behaviour. I.e. if a button being pressed
    and held should only return true the first time, that logic should be in the
    function.
    
    An action in the IVRInput API is entered in the actions manifest. This is a
    .json file that is included with the final binary.
    Currently an Action is created with a string and a type. The type determines
    which function should be used for getting information from the API. The type in
    the actions manifest must match the type in the source code.
    
    Actions should be added as member objects to SteamIVRInput and initialized in
    the constructor. They should then make a small number of accessor functions
    available for outside use. The internal structs of the IVRInput API are not
    entirely stable, and should not be leaked outside this class.
    
    The name of the actions manifest must be set in ivrinput_manifest.h.
     */
    class SteamIVRInput
    {
    public:
        SteamIVRInput();

        void update_states();

        float ThumbRightX();
        float ThumbRightY();
        float ThumbLeftX();
        float ThumbLeftY();
        float TriggerRight();
        float TriggerLeft();
        bool AButton();
        bool BButton();
        bool XButton();
        bool YButton();
        bool MenuButton();
        bool GuideButton();
        bool RBButton();
        bool LBButton();
        bool LThumbButton();
        bool RThumbButton();

        vr::VRActionHandle_t leftHapticActionHandle() const;
        vr::VRActionHandle_t rightHapticActionHandle() const;

        vr::VRInputValueHandle_t rightInputHandle() const;
        vr::VRInputValueHandle_t leftInputHandle() const;

        // Destructor. There are no terminating calls for the IVRInput API, so it
        // is left blank.
        ~SteamIVRInput() = default;

        //Deleted other constructors to prevent undefined behavior
        SteamIVRInput(const SteamIVRInput&) = delete;
        SteamIVRInput& operator=(const SteamIVRInput&) = delete;
        SteamIVRInput(SteamIVRInput&&) = delete;
        SteamIVRInput& operator=(const SteamIVRInput&&) = delete;

    private:
        manifest m_manifest;

        ActionSet m_haptics;
        ActionSet m_main;

        AnalogAction m_thumbRight;
        AnalogAction m_thumbLeft;

        AnalogAction m_triggerRight;
        AnalogAction m_triggerLeft;

        DigitalAction m_aBut;
        DigitalAction m_bBut;
        DigitalAction m_xBut;
        DigitalAction m_yBut;
        DigitalAction m_menuBut;
        DigitalAction m_guideBut;
        DigitalAction m_rbBut;
        DigitalAction m_lbBut;
        DigitalAction m_RThumbBut;
        DigitalAction m_LThumbBut;

        DigitalAction m_leftHaptic;
        DigitalAction m_rightHaptic;

        // input sources
        InputSource m_left_hand;
        InputSource m_right_hand;

        // Initialize the set of actions after everything else.
        active_action_sets m_sets;
    };
} // namespace input
