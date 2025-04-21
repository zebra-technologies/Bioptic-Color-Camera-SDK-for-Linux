/***************************************************************
 * Name:      DemoExtensionUnit1Controls.cpp
 * Purpose:   Implementation for quering camera asset tracking information.
 * Author:     ()
 * Created:   2021-03-01
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved
 * License:
 **************************************************************/



#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"
#include <regex>
#include <iostream>

// Method to remove leading spaces
std::string LeadingSpace(const std::string& str) {
    return std::regex_replace(str, std::regex("^\\s+"), "", std::regex_constants::format_default);
}
 
// Method to remove trailing spaces
std::string TrailingSpace(const std::string& str) {
    return std::regex_replace(str, std::regex("\\s+$"), "", std::regex_constants::format_default);
}
 
std::string Trim(const std::string& str) {
    return LeadingSpace(TrailingSpace(str));
}

void BiopticColorCameraDemoFrame::PopulateCameraAssetTrackingInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    try
    {
    	std::string serial_number = Trim(camera->GetSerialNumber());
    	std::string model_number = Trim(camera->GetModelNumber());
    	std::string firmware_version = Trim(camera->GetFirmwareVersion());
    	std::string hardware_version = Trim(camera->GetHardwareVersion());
    	std::string date_of_manufacture = Trim(camera->GetDateOfManufacture());
    	std::string date_of_program = Trim(camera->GetDateOfFirstProgram());
    	std::string date_of_service = Trim(camera->GetFirstServiceDate());


    	text_serial_number->SetValue(serial_number.c_str());
    	text_model_number->SetValue(model_number.c_str());
    	text_firmware_version->SetValue(firmware_version.c_str());
    	text_hardware_version->SetValue(hardware_version.c_str());
    	text_dom->SetValue(date_of_manufacture.c_str());
    	text_dofp->SetValue(date_of_program.c_str());
    	text_dos->SetValue(date_of_service.c_str());
    }
    catch (...) {}
}

void BiopticColorCameraDemoFrame::ClearCameraAssetTrackingInfo()
{
    text_serial_number->SetValue("");
    text_model_number->SetValue("");
    text_firmware_version->SetValue("");
    text_hardware_version->SetValue("");
    text_dom->SetValue("");
    text_dofp->SetValue("");
    text_dos->SetValue("");
}

// Method to handle video mode selection
void BiopticColorCameraDemoFrame::OnChoiceVideoModeSelect(wxCommandEvent& event)
{

    (void)event;

    ChoiceVideoMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_videomode=%d", __func__, property_videomode);

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->VideoModeSetting.Value((VideoMode)property_videomode);
        }
        catch (...) {}
    }

}

// Method to populate video mode , illumination mode and power user mode
void BiopticColorCameraDemoFrame::PopulateExtensionUnit1Info(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        try
        {
            PopulateVideoMode(camera);
            PopulateIlluminationMode(camera);
            PopulatePowerUserMode(camera);
        }
        catch (...)
        {

        }
    }
}

// Method to populate video mode
void BiopticColorCameraDemoFrame::PopulateVideoMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    ChoiceVideoMode->Enable();

    try
    {
    	VideoMode mode = camera->VideoModeSetting.Value();
    	property_videomode = (int)mode;
    	ChoiceVideoMode->GetValidator()->TransferToWindow();
    	wxLogMessage("%s: mode=%d", __func__, (int)mode);
    }
    catch (...) {}
}

// Method to clear video mode , illumination mode and power user mode
void BiopticColorCameraDemoFrame::ClearExtensionUnit1Info()
{
    ChoiceVideoMode->Disable();
    ChoiceIlluminationMode->Disable();
    ChoicePowerUserMode->Disable();
}

// Method to populate illumination mode
void BiopticColorCameraDemoFrame::PopulateIlluminationMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    ChoiceIlluminationMode->Enable();

    try
    {
    	IlluminationMode mode = camera->IlluminationModeSetting.Value();
    	property_illuminationmode = (int)mode;
    	ChoiceIlluminationMode->GetValidator()->TransferToWindow();
    	wxLogMessage("%s: mode=%d", __func__, (int)mode);
    }
    catch (...) {}
}

// Method to populate power user mode
void BiopticColorCameraDemoFrame::PopulatePowerUserMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    ChoicePowerUserMode->Enable();

    try
    {
    	PowerUserMode mode = camera->PowerUserModeSetting.Value();
    	property_powerusermode = (int)mode;
    	ChoicePowerUserMode->GetValidator()->TransferToWindow();

    	OnPowerUserModeChange(!property_powerusermode);

    	wxLogMessage("%s: mode=%d", __func__, (int)mode);
    }
    catch (...) {}
}

// Mthod to handle illumination mode selection
void BiopticColorCameraDemoFrame::OnChoiceIlluminationModeSelect(wxCommandEvent& event)
{

    (void)event;

    ChoiceIlluminationMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_illuminationmode=%d", __func__, property_illuminationmode);

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->IlluminationModeSetting.Value((IlluminationMode)property_illuminationmode);
        }
        catch (...) {}
    }

}

// method to handle power user mode selection
void BiopticColorCameraDemoFrame::OnChoicePowerUserModeSelection(wxCommandEvent& event)
{

    (void)event;

    ChoicePowerUserMode->GetValidator()->TransferFromWindow();
    wxLogMessage("%s: property_powerusermode=%d", __func__, property_powerusermode);

    auto camera = GetCamera();

    if (camera)
    {
        try
        {
            camera->PowerUserModeSetting.Value((PowerUserMode)property_powerusermode);
            OnPowerUserModeChange(!property_powerusermode);

            if(property_powerusermode == 0 )
            {
                EventLog("power user mode DISABLED");
            }
            else
            {
                EventLog("power user mode ENABLED");
            }
            
        }
        catch (...) {}
    }

}

// Method to disable and enable UVC properties based on power user mode selection
void BiopticColorCameraDemoFrame::OnPowerUserModeChange(bool mode)
{
    wxLogMessage("%s: mode=%d", __func__, (int)mode);

    if (!CheckBoxExposureTimeAuto->IsChecked())
    {
        // If exposure auto is checked, it's okay to enable/disable it. Otherwise don't enable the controls.
        SliderAbsoluteExposureTime->Enable(mode);
        TextCtrlAbsoluteExposureTime->Enable(mode);
        CheckBoxExposureTimeAuto->Enable(mode);
    }
    CheckBoxExposureTimeAuto->Enable(mode);

    if (!CheckBoxWhiteBalanceAuto->IsChecked())
    {
        // If white balance auto is checked, it's okay to enable/disable it. Otherwise don't enable the controls.
        SliderWhiteBalanceBlue->Enable(mode);
        SliderWhiteBalanceRed->Enable(mode);
        TextCtrlWhiteBalanceBlue->Enable(mode);
        TextCtrlWhiteBalanceRed->Enable(mode);
        CheckBoxWhiteBalanceAuto->Enable(mode);
    }
    CheckBoxWhiteBalanceAuto->Enable(mode);
    SliderGain->Enable(mode);
    TextCtrlGain->Enable(mode);
}




