#include <windows.h>
#include <iostream>
#include "openvr.h"
#include "ViGEm/Client.h"
#include "ivrinput.h"
#include <Xinput.h>
#include <chrono>
#include <thread>
#pragma comment(lib, "setupapi.lib")

void updateControllerState(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState);
void updateButtonState(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState);
void updateAnalog(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState);
void vibrationCallback(PVIGEM_CLIENT client, PVIGEM_TARGET pad, std::atomic_bool control);
BYTE floatToByte(float input);
SHORT floatToShort(float input);




int main(int argc, char* argv[]) {
    vr::EVRInitError err;
    vr::IVRSystem* sys = vr::VR_Init(&err, vr::VRApplication_Overlay);
    if(err != vr::VRInitError_None)
    {
        return 1;
    }

    const auto client = vigem_alloc();
    if (client == nullptr)
    {
        std::cerr << "Uh, not enough memory to do that?!" << std::endl;
        return -1;
    }
    const auto retval = vigem_connect(client);

    if (!VIGEM_SUCCESS(retval))
    {
        std::cerr << "ViGEm Bus connection failed with error code: 0x" << std::hex << retval << std::endl;
        return -1;
    }

    //
    // Allocate handle to identify new pad
    //
    const auto pad = vigem_target_x360_alloc();

    //
    // Add client to the bus, this equals a plug-in event
    //
    const auto pir = vigem_target_add(client, pad);

    //
    // Error handling
    //
    if (!VIGEM_SUCCESS(pir))
    {
        std::cerr << "Target plugin failed with error code: 0x" << std::hex << pir << std::endl;
        return -1;
    }

    auto m_actions = input::SteamIVRInput();
    XINPUT_STATE state;
    vr::VREvent_t event{};

    while(sys)
    {
        //Poll VR Quit and Exit if VR is exited.
        while (sys->PollNextEvent(&event, sizeof event))
        {
            const uint32_t et = event.eventType;
            if (et == vr::VREvent_Quit)
            {
                sys->AcknowledgeQuit_Exiting();
                vigem_target_remove(client, pad);
                vigem_target_free(pad);
                vigem_disconnect(client);
                vigem_free(client);
                return 0;
            }
        }
        updateControllerState(m_actions, state);

        // The XINPUT_GAMEPAD structure is identical to the XUSB_REPORT structure
        // so we can simply take it "as-is" and cast it.
        // Sends updates
        vigem_target_x360_update(client, pad, *reinterpret_cast<XUSB_REPORT*>(&state.Gamepad));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    

    system("pause");
    vigem_target_remove(client, pad);
    vigem_target_free(pad);
    vigem_disconnect(client);
    vigem_free(client);
    return 0;
}

BYTE floatToByte(float input)
{
    auto temp = input * 255;
    if (temp > 255)
    {
        temp = 255;
    }
    if(temp <0)
    {
        temp = 0;
    }
    return static_cast<BYTE>(temp);
}

SHORT floatToShort(float input)
{
    auto temp = input * 32768;
    if(temp >32767)
    {
        temp = 32767;
    }
    if(temp<-32768)
    {
        temp = -32768;
    }
    return static_cast<SHORT>(temp);
}

void updateButtonState(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState)
{
    //Button MAsks
    //https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad
    gamepadState.Gamepad.wButtons = static_cast<WORD>(0x0000);

    gamepadState.Gamepad.wButtons = vrInput.AButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x1000)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.BButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x2000)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.XButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x4000)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.YButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x8000)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.RBButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0200)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.LBButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0100)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.RThumbButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0080)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.LThumbButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0040)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.StartButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0010)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.BackButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0020)
        : gamepadState.Gamepad.wButtons;
    //Undocumented "Guide Button" There is also an unknown/unassigned at 0x0800
    gamepadState.Gamepad.wButtons = vrInput.GuideButton() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0400)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.UPDpad() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0001)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.DownDpad() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0002)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.LeftDpad() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0004)
        : gamepadState.Gamepad.wButtons;
    gamepadState.Gamepad.wButtons = vrInput.RightDpad() ? gamepadState.Gamepad.wButtons | static_cast<WORD>(0x0008)
        : gamepadState.Gamepad.wButtons;

}


void updateAnalog(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState)
{
    gamepadState.Gamepad.sThumbLX = floatToShort(vrInput.ThumbLeftX());
    gamepadState.Gamepad.sThumbLY = floatToShort(vrInput.ThumbLeftY());
    gamepadState.Gamepad.sThumbRX = floatToShort(vrInput.ThumbRightX());
    gamepadState.Gamepad.sThumbRY = floatToShort(vrInput.ThumbRightY());
    gamepadState.Gamepad.bLeftTrigger = floatToByte(vrInput.TriggerLeft());
    gamepadState.Gamepad.bRightTrigger = floatToByte(vrInput.TriggerRight());
}

void updateControllerState(input::SteamIVRInput& vrInput, XINPUT_STATE& gamepadState)
{
    vrInput.update_states();
    updateAnalog(vrInput, gamepadState);
    updateButtonState(vrInput, gamepadState);
}

VOID CALLBACK notification(
    PVIGEM_CLIENT Client,
    PVIGEM_TARGET pad,
    UCHAR LargeMotor,
    UCHAR SmallMotor,
    UCHAR LedNumber,
    LPVOID UserData
)
{
    //TODO vibrate global?
}