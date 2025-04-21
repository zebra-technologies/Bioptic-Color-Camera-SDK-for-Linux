/***************************************************************
 * Name:      DemoDeviceAvakeControls.cpp
 * Purpose:   Implementation of integrating device awake controls with UI 
 * Author:     ()
 * Created:   2021-03-25
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/


#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"


// Method to populate device awake
void BiopticColorCameraDemoFrame::PopulateDeviceAwake(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{

    try
    {
    	VideoMode mode = camera->VideoModeSetting.Value();
        // Change the session controller disable if video mode = off.
    	SetDeviceAwake(mode);

    }
    catch (...) {}
}

// Method to clear device awake
void BiopticColorCameraDemoFrame::ClearDeviceAwakeInfo()
{
    LedDeviceAwake->Disable();
}

void BiopticColorCameraDemoFrame::SetDeviceAwake(VideoMode mode)
{
    if(VideoMode::OFF == mode)
    {
        LedDeviceAwake->Disable();
    }
    else
    {
    	LedDeviceAwake->Enable();
    	LedDeviceAwake->SwitchOff();
    }
}
