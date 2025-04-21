/***************************************************************
 * Name:      DemoProcessingUnitControls.cpp
 * Purpose:   Implementation for displaying camera UVC properties.
 * Author:     ()
 * Created:   2021-03-05
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved
 * License:
 **************************************************************/

#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.

#include <iostream>
#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"

#define WHITE_BALANCE_NUMBER_OF_FRACTION_BITS			12
#define WHITE_BALANCE_RANGE_MAX							0x4000
#define WHITE_BALANCE_RANGE_MIN		                    0


/**
 * Convert uint16_t value into 4.12 floating point value.
 * round it into 3 decimal points.
 */
static float ConvertUint16ToFloat(uint16_t actual_value, int number_of_fraction_bits)
{
	float return_vlue;
	char value_in_string[17];
	return_vlue = (float)actual_value / (float)(1 << number_of_fraction_bits);

	// round it to .3f
	sprintf(value_in_string, "%.3f", return_vlue);
	sscanf(value_in_string, "%f", &return_vlue);

	return return_vlue;
}

/**
 * Convert floating point vlue into uint16_t value.
 */
static uint16_t ConvertFloatToUint16(float actual_value, int number_of_fraction_bits)
{
	return (uint16_t)(actual_value * (1 << number_of_fraction_bits));
}					

void BiopticColorCameraDemoFrame::PopulateProcessingUnitInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera) 
    {
        try
        {
            PopulateBrightness(camera);
            PopulateContrast(camera);
            PopulateSaturation(camera);
            PopulateSharpness(camera);
            PopulateGamma(camera);
            PopulateWhiteBalanceComponent(camera);
            PopulateBacklight(camera);
            PopulateGain(camera);
            PopulateAbsoluteExposureTime(camera);
        }
        catch (...) {}
       
    }
}

// Get brightness property value and set value to brightness slider
void BiopticColorCameraDemoFrame::PopulateBrightness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimun = 0, maximum = 0, value = 0, resolution = 0;

    SliderBrightness->Enable();
    TextCtrlBrightness->Enable();

    minimun = camera->Brightness.Minimum();
    maximum = camera->Brightness.Maximum();
    value = camera->Brightness.Value();
    resolution = camera->Brightness.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlBrightness->GetValidator();
    ivalidator->SetMin(minimun);
    ivalidator->SetMax(maximum);

    property_brightness = value;

    SliderBrightness->SetMin(minimun);
    SliderBrightness->SetMax(maximum);
    SliderBrightness->SetTickFreq(resolution);

    ivalidator->TransferToWindow();
    SliderBrightness->GetValidator()->TransferToWindow();
}

// Get contrast property value and set value to contrast slider
void BiopticColorCameraDemoFrame::PopulateContrast(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, value = 0, resolution = 0;

    SliderContrast->Enable();
    TextCtrlContrast->Enable();

    try {
        minimum = camera->Contrast.Minimum();
        maximum = camera->Contrast.Maximum();
        value = camera->Contrast.Value();
        resolution = camera->Contrast.Resolution();

        ivalidator = (wxIntegerValidator<int>*)TextCtrlContrast->GetValidator();
        ivalidator->SetMin(minimum);
        ivalidator->SetMax(maximum);

        property_contrast = value;

        SliderContrast->SetMin(minimum);
        SliderContrast->SetMax(maximum);
        SliderContrast->SetTickFreq(resolution);

        ivalidator->TransferToWindow();
        SliderContrast->GetValidator()->TransferToWindow();
    }
    catch (...) {
    }
}

// Get saturation property value and set value to saturation slider
void BiopticColorCameraDemoFrame::PopulateSaturation(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, val = 0, res = 0;

    SliderSaturation->Enable();
    TextCtrlSaturation->Enable();

    minimum = camera->Saturation.Minimum();
    maximum = camera->Saturation.Maximum();
    val = camera->Saturation.Value();
    res = camera->Saturation.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlSaturation->GetValidator();
    ivalidator->SetMin(minimum);
    ivalidator->SetMax(maximum);

    property_saturation = val;

    SliderSaturation->SetMin(minimum);
    SliderSaturation->SetMax(maximum);
    SliderSaturation->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderSaturation->GetValidator()->TransferToWindow();
}

// Get sharpness property value and set value to sharpness slider
void BiopticColorCameraDemoFrame::PopulateSharpness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, val = 0, res = 0;

    SliderSharpness->Enable();
    TextCtrlSharpness->Enable();

    minimum = camera->Sharpness.Minimum();
    maximum = camera->Sharpness.Maximum();
    val = camera->Sharpness.Value();
    res = camera->Sharpness.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlSharpness->GetValidator();
    ivalidator->SetMin(minimum);
    ivalidator->SetMax(maximum);

    property_sharpness = val;

    SliderSharpness->SetMin(minimum);
    SliderSharpness->SetMax(maximum);
    SliderSharpness->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderSharpness->GetValidator()->TransferToWindow();
}

// Get gamma property value and set value to gamma slider
void BiopticColorCameraDemoFrame::PopulateGamma(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum= 0, val = 0, res = 0;

    SliderGamma->Enable();
    TextCtrlGamma->Enable();

    minimum = camera->Gamma.Minimum();
    maximum = camera->Gamma.Maximum();
    val = camera->Gamma.Value();
    res = camera->Gamma.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlGamma->GetValidator();
    ivalidator->SetMin(minimum);
    ivalidator->SetMax(maximum);

    property_gamma = val;

    SliderGamma->SetMin(minimum);
    SliderGamma->SetMax(maximum);
    SliderGamma->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderGamma->GetValidator()->TransferToWindow();
}

// Get white balance rad and blue property values and set values to respective white balance sliders
void BiopticColorCameraDemoFrame::PopulateWhiteBalanceComponent(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxFloatingPointValidator<float>* fvalidator;
    WhiteBalance minimum, maximum, val, res;

    bool auto_supported = camera->WhiteBalanceComponent.IsAutoSupported();
    CheckBoxWhiteBalanceAuto->Enable(auto_supported);

    SliderWhiteBalanceBlue->Enable();
    TextCtrlWhiteBalanceBlue->Enable();

    SliderWhiteBalanceRed->Enable();
    TextCtrlWhiteBalanceRed->Enable();

    if (auto_supported)
    {
        bool auto_enabled = camera->WhiteBalanceComponent.IsAutoEnabled();
        CheckBoxWhiteBalanceAuto->SetValue(auto_enabled);

        if (auto_enabled)
        {
            // Auto enabled. Disable the slider and text controls.
            SliderWhiteBalanceBlue->Disable();
            TextCtrlWhiteBalanceBlue->Disable();

            SliderWhiteBalanceRed->Disable();
            TextCtrlWhiteBalanceRed->Disable();

            // Start value field refresh timer.
            auto_white_balance_monitor_timer_.Start(WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS);
        }
        else
        {
        	auto_white_balance_monitor_timer_.Stop();
        }
    }

    try {
    	minimum = camera->WhiteBalanceComponent.Minimum();
    	maximum = camera->WhiteBalanceComponent.Maximum();
    	val = camera->WhiteBalanceComponent.Value();
    	res = camera->WhiteBalanceComponent.Resolution();

    	// Update blue component properties, but DO NOT UPDATE THE UI CONTROLLERS YET!
        fvalidator = (wxFloatingPointValidator<float>*)TextCtrlWhiteBalanceBlue->GetValidator();
        fvalidator->SetMin(ConvertUint16ToFloat(minimum.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));
        fvalidator->SetMax(ConvertUint16ToFloat(maximum.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));

        property_wb_blue = val.Blue();
        property_wb_blue_in_float = ConvertUint16ToFloat(val.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

        SliderWhiteBalanceBlue->SetMin(minimum.Blue());
        SliderWhiteBalanceBlue->SetMax(maximum.Blue());
        SliderWhiteBalanceBlue->SetTickFreq(res.Blue());

        // Update red component properties
        fvalidator = (wxFloatingPointValidator<float>*)TextCtrlWhiteBalanceRed->GetValidator();
		fvalidator->SetMin(ConvertUint16ToFloat(minimum.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));
		fvalidator->SetMax(ConvertUint16ToFloat(maximum.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS));

        property_wb_red = val.Red();
        property_wb_red_in_float = ConvertUint16ToFloat(val.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

        SliderWhiteBalanceRed->SetMin(minimum.Red());
        SliderWhiteBalanceRed->SetMax(maximum.Red());
        SliderWhiteBalanceRed->SetTickFreq(res.Red());

        // Finally transfer the property values to UI controllers.
        /*
         * IMPORTANT: If we update properties one after the other along with their UI controllers,
         * the control that is updated last will not reflect the actual value.
         * This is because property_wb_blue, property_wb_red are used inside UI control update handlers
         * OnTextCtrlWhiteBalanceBlueText, OnTextCtrlWhiteBalanceRedText and set to camera white-balance.
         * So, if we update property_wb_blue first and then invoke TransferToWindow for blue component
         * before updating property_wb_red, old value of the red component will be set to camera in
         * OnTextCtrlWhiteBalanceBlueText.
         * This is causing issues SSDK-11434, SSDK-11456.
         */
        TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();
        TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();

        SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();
        SliderWhiteBalanceRed->GetValidator()->TransferToWindow();
    }
    catch (...) {
    }
}
// Get backlight property value and set value to backlight slider
void BiopticColorCameraDemoFrame::PopulateBacklight(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, val = 0, res = 0;

    SliderBacklight->Enable();
    TextCtrlBacklight->Enable();

    minimum = camera->BacklightCompensation.Minimum();
    maximum = camera->BacklightCompensation.Maximum();
    val = camera->BacklightCompensation.Value();
    res = camera->BacklightCompensation.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlBacklight->GetValidator();
    ivalidator->SetMin(minimum);
    ivalidator->SetMax(maximum);

    property_backlight = val;

    SliderBacklight->SetMin(minimum);
    SliderBacklight->SetMax(maximum);
    SliderBacklight->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderBacklight->GetValidator()->TransferToWindow();
}

// Get gain property value and set value to gain slider
void BiopticColorCameraDemoFrame::PopulateGain(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, val = 0, res = 0;

    SliderGain->Enable();
    TextCtrlGain->Enable();

    minimum = camera->Gain.Minimum();
    maximum = camera->Gain.Maximum();
    val = camera->Gain.Value();
    res = camera->Gain.Resolution();

    ivalidator = (wxIntegerValidator<int>*)TextCtrlGain->GetValidator();
    ivalidator->SetMin(minimum);
    ivalidator->SetMax(maximum);

    property_gain = val;

    SliderGain->SetMin(minimum);
    SliderGain->SetMax(maximum);
    SliderGain->SetTickFreq(res);

    ivalidator->TransferToWindow();
    SliderGain->GetValidator()->TransferToWindow();
}

// Get exposure property value and set value to exposure slider
void BiopticColorCameraDemoFrame::PopulateAbsoluteExposureTime(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxIntegerValidator<int>* ivalidator;
    int16_t minimum = 0, maximum = 0, val = 0, res = 0;

    try {
    	bool auto_supported = camera->AbsoluteExposureTime.IsAutoSupported();
    	CheckBoxExposureTimeAuto->Enable(auto_supported);

    	SliderAbsoluteExposureTime->Enable();
    	TextCtrlAbsoluteExposureTime->Enable();

    	if (auto_supported)
    	{
    		bool auto_enabled = camera->AbsoluteExposureTime.IsAutoEnabled();
    		CheckBoxExposureTimeAuto->SetValue(auto_enabled);

    		if (auto_enabled)
    		{
    			// Auto enabled. Disable the slider and text controls.
    			SliderAbsoluteExposureTime->Disable();
    			TextCtrlAbsoluteExposureTime->Disable();
    		}
    	}


    	minimum = camera->AbsoluteExposureTime.Minimum();
    	maximum = camera->AbsoluteExposureTime.Maximum();
    	val = camera->AbsoluteExposureTime.Value();
    	res = camera->AbsoluteExposureTime.Resolution();

    	ivalidator = (wxIntegerValidator<int>*)TextCtrlAbsoluteExposureTime->GetValidator();
    	ivalidator->SetMin(minimum);
    	ivalidator->SetMax(maximum);

    	property_abs_exposure_time = val;

    	SliderAbsoluteExposureTime->SetMin(minimum);
    	SliderAbsoluteExposureTime->SetMax(maximum);
    	SliderAbsoluteExposureTime->SetTickFreq(res);

    	ivalidator->TransferToWindow();
    	SliderAbsoluteExposureTime->GetValidator()->TransferToWindow();
    }
    catch(...) {
    }
}

void BiopticColorCameraDemoFrame::OnSliderBrightnessCmdScrollChanged(wxScrollEvent& event)
{
    SliderBrightness->GetValidator()->TransferFromWindow();
    TextCtrlBrightness->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_brightness=%d", __func__, event.GetPosition(), property_brightness);
    EventLog("Propery brightness CHANGED : ",property_brightness);
}

void BiopticColorCameraDemoFrame::OnSliderContrastCmdScrollChanged(wxScrollEvent& event)
{
    SliderContrast->GetValidator()->TransferFromWindow();
    TextCtrlContrast->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_contrast=%d", __func__, event.GetPosition(), property_contrast);
    EventLog("Propery contrast CHANGED : ",property_contrast);
}

void BiopticColorCameraDemoFrame::OnSliderSaturationCmdScrollChanged(wxScrollEvent& event)
{
    SliderSaturation->GetValidator()->TransferFromWindow();
    TextCtrlSaturation->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_saturation=%d", __func__, event.GetPosition(), property_saturation);
    EventLog("Propery saturation CHANGED : ",property_saturation);
}

void BiopticColorCameraDemoFrame::OnSliderSharpnessCmdScrollChanged(wxScrollEvent& event)
{
    SliderSharpness->GetValidator()->TransferFromWindow();
    TextCtrlSharpness->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_sharpness=%d", __func__, event.GetPosition(), property_sharpness);
    EventLog("Propery sharpness CHANGED : ",property_sharpness);
}

void BiopticColorCameraDemoFrame::OnSliderGammaCmdScrollChanged(wxScrollEvent& event)
{
    SliderGamma->GetValidator()->TransferFromWindow();
    TextCtrlGamma->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_gamma=%d", __func__, event.GetPosition(), property_gamma);
    EventLog("Propery gamma CHANGED : ",property_gamma);
}

void BiopticColorCameraDemoFrame::OnSliderWhiteBalanceBlueCmdScrollChanged(wxScrollEvent& event)
{
    SliderWhiteBalanceBlue->GetValidator()->TransferFromWindow();
    property_wb_blue_in_float = ConvertUint16ToFloat(property_wb_blue, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_wb_blue_in_float=%f", __func__, event.GetPosition(), property_wb_blue_in_float);
    EventLog("Propery white balance (Blue) CHANGED : ",property_wb_blue_in_float);
}

void BiopticColorCameraDemoFrame::OnSliderWhiteBalanceRedCmdScrollChanged(wxScrollEvent& event)
{
    SliderWhiteBalanceRed->GetValidator()->TransferFromWindow();
    property_wb_red_in_float = ConvertUint16ToFloat(property_wb_red, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_wb_red_in_float=%f", __func__, event.GetPosition(), property_wb_red_in_float);
    EventLog("Propery white balance (Red) CHANGED : ",property_wb_red_in_float);
}

void BiopticColorCameraDemoFrame::OnSliderBacklightCmdScrollChanged(wxScrollEvent& event)
{
    SliderBacklight->GetValidator()->TransferFromWindow();
    TextCtrlBacklight->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_backlight=%d", __func__, event.GetPosition(), property_backlight);
    EventLog("Propery backlight CHANGED : ",property_backlight);
}

void BiopticColorCameraDemoFrame::OnSliderGainCmdScrollChanged(wxScrollEvent& event)
{
    SliderGain->GetValidator()->TransferFromWindow();
    TextCtrlGain->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_gain=%d", __func__, event.GetPosition(), property_gain);
    EventLog("Propery gain CHANGED : ",property_gain);
}

void BiopticColorCameraDemoFrame::OnSliderAbsoluteExposureTimeCmdScrollChanged(wxScrollEvent& event)
{
    SliderAbsoluteExposureTime->GetValidator()->TransferFromWindow();
    TextCtrlAbsoluteExposureTime->GetValidator()->TransferToWindow();
    wxLogMessage("%s: pos=%d, property_abs_exposure_time=%d", __func__, event.GetPosition(), property_abs_exposure_time);
    EventLog("Propery exposure CHANGED : ",property_abs_exposure_time);
}


void BiopticColorCameraDemoFrame::OnTextCtrlBrightnessText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlBrightness->GetValidator()->TransferFromWindow();
    SliderBrightness->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Brightness.Value(property_brightness);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlContrastText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlContrast->GetValidator()->TransferFromWindow();
    SliderContrast->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Contrast.Value(property_contrast);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlSaturationText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlSaturation->GetValidator()->TransferFromWindow();
    SliderSaturation->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Saturation.Value(property_saturation);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlSharpnessText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlSharpness->GetValidator()->TransferFromWindow();
    SliderSharpness->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Sharpness.Value(property_sharpness);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlAbsoluteExposureTimeText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlAbsoluteExposureTime->GetValidator()->TransferFromWindow();
    SliderAbsoluteExposureTime->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	if (camera->AbsoluteExposureTime.IsAutoSupported() &&
        			camera->AbsoluteExposureTime.IsAutoEnabled())
        	{
        		return;
        	}
        	camera->AbsoluteExposureTime.Value(property_abs_exposure_time);
        }
        catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlGammaText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlGamma->GetValidator()->TransferFromWindow();
    SliderGamma->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Gamma.Value(property_gamma);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlWhiteBalanceBlueText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlWhiteBalanceBlue->GetValidator()->TransferFromWindow();

    SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();

    property_wb_blue = (uint16_t)ConvertFloatToUint16(property_wb_blue_in_float, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

    SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		if (camera->WhiteBalanceComponent.IsAutoSupported() &&
    				camera->WhiteBalanceComponent.IsAutoEnabled())
    		{
    			return;
    		}
    		wxLogMessage("%s: property_wb_blue=%d, property_wb_red=%d", __func__, property_wb_blue, property_wb_red);

    		camera->WhiteBalanceComponent.Value(WhiteBalance((uint16_t)property_wb_blue, (uint16_t)property_wb_red));
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlWhiteBalanceRedText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlWhiteBalanceRed->GetValidator()->TransferFromWindow();
    SliderWhiteBalanceRed->GetValidator()->TransferToWindow();

    property_wb_red = (uint16_t)ConvertFloatToUint16(property_wb_red_in_float, WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

	SliderWhiteBalanceRed->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		if (camera->WhiteBalanceComponent.IsAutoSupported() &&
    				camera->WhiteBalanceComponent.IsAutoEnabled())
    		{
    			return;
    		}
    		wxLogMessage("%s: property_wb_blue=%d, property_wb_red=%d", __func__, property_wb_blue, property_wb_red);

    		camera->WhiteBalanceComponent.Value(WhiteBalance((uint16_t)property_wb_blue, (uint16_t)property_wb_red));
    	}
    	catch (...) {}
    }

}


void BiopticColorCameraDemoFrame::OnTextCtrlBacklightText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlBacklight->GetValidator()->TransferFromWindow();
    SliderBacklight->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->BacklightCompensation.Value(property_backlight);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnTextCtrlGainText(wxCommandEvent& event)
{

    (void)event;

    TextCtrlGain->GetValidator()->TransferFromWindow();
    SliderGain->GetValidator()->TransferToWindow();

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->Gain.Value(property_gain);
    	}
    	catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnCheckBoxExposureTimeAutoClick(wxCommandEvent& event)
{

    wxLogMessage("%s: checked=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        try
        {
        	camera->AbsoluteExposureTime.AutoEnable(event.IsChecked());
        	bool auto_enabled = camera->AbsoluteExposureTime.IsAutoEnabled();

        	wxLogMessage("%s: auto_enabled=%d", __func__, auto_enabled);

        	if (auto_enabled)
        	{
        		// Auto enabled. Disable the slider and text controls.
        		SliderAbsoluteExposureTime->Disable();
        		TextCtrlAbsoluteExposureTime->Disable();
                EventLog("Exposure AUTO ENABLED ");
        	}
        	else
        	{
        		SliderAbsoluteExposureTime->Enable();
        		TextCtrlAbsoluteExposureTime->Enable();

        		PopulateAbsoluteExposureTime(camera);
                EventLog("Exposure AUTO DISABLED ");
        	}
        }
        catch (...) {}
    }

}

void BiopticColorCameraDemoFrame::OnCheckBoxWhiteBalanceAutoClick(wxCommandEvent& event)
{

    wxLogMessage("%s: checked=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    		camera->WhiteBalanceComponent.AutoEnable(event.IsChecked());
    		bool auto_enabled = camera->WhiteBalanceComponent.IsAutoEnabled();

    		wxLogMessage("%s: auto_enabled=%d", __func__, auto_enabled);

    		if (auto_enabled)
    		{
    			// Auto enabled. Disable the slider and text controls.
    			SliderWhiteBalanceBlue->Disable();
    			TextCtrlWhiteBalanceBlue->Disable();

    			SliderWhiteBalanceRed->Disable();
    			TextCtrlWhiteBalanceRed->Disable();

    			// Start value field refresh timer.
    			auto_white_balance_monitor_timer_.Start(WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS);
                EventLog("White Balance AUTO ENABLED ");
    		}
    		else
    		{
    			SliderWhiteBalanceBlue->Enable();
    			TextCtrlWhiteBalanceBlue->Enable();

    			SliderWhiteBalanceRed->Enable();
    			TextCtrlWhiteBalanceRed->Enable();

    			PopulateWhiteBalanceComponent(camera);

    			// Stop value field refresh timer.
    			auto_white_balance_monitor_timer_.Stop();
                EventLog("White Balance AUTO DISABLED ");
    		}
    	}
    	catch (...) {}
    }

}



void BiopticColorCameraDemoFrame::OnAutoWhiteBalanceUpdateTimer(wxTimerEvent& event)
{

    (void)event;

    wxLogMessage("%s", __func__);

    auto camera = GetCamera();
    if (camera)
    {
    	try
    	{
    	    // Get the values.
    		WhiteBalance white_balance = camera->WhiteBalanceComponent.Value();
    		property_wb_red = white_balance.Red();
    		property_wb_red_in_float = ConvertUint16ToFloat(white_balance.Red(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);
    		property_wb_blue = white_balance.Blue();
    		property_wb_blue_in_float = ConvertUint16ToFloat(white_balance.Blue(), WHITE_BALANCE_NUMBER_OF_FRACTION_BITS);

    		// Transfer the values to controls.
    		TextCtrlWhiteBalanceRed->GetValidator()->TransferToWindow();
    		TextCtrlWhiteBalanceBlue->GetValidator()->TransferToWindow();

    		SliderWhiteBalanceRed->GetValidator()->TransferToWindow();
    		SliderWhiteBalanceBlue->GetValidator()->TransferToWindow();
    	}
    	catch (...) {}
    }

}



void BiopticColorCameraDemoFrame::ClearProcessingUnitInfo()
{
    wxSlider *sliders[] = {
        SliderBrightness,
        SliderContrast,
        SliderSaturation,
        SliderSharpness,   
        SliderGamma,
        SliderBacklight,
        SliderGain,
        SliderAbsoluteExposureTime,
        SliderWhiteBalanceBlue,
        SliderWhiteBalanceRed,
    };

    wxTextCtrl *textboxes[] = { 
        TextCtrlBrightness,
        TextCtrlContrast,
        TextCtrlSaturation,
        TextCtrlSharpness, 
        TextCtrlGamma,
        TextCtrlWhiteBalanceBlue,
        TextCtrlGain,
        TextCtrlAbsoluteExposureTime,
        TextCtrlBacklight,
        TextCtrlWhiteBalanceRed,
    };

    for (unsigned int i = 0; i < sizeof(sliders)/sizeof(sliders[0]); i++)
    {
        wxSlider *slider = sliders[i];
        wxTextCtrl *txtbox = textboxes[i];

        txtbox->Clear();
        slider->Disable();
        txtbox->Disable();
    }

    CheckBoxExposureTimeAuto->Disable();
    CheckBoxWhiteBalanceAuto->Disable();

    auto_white_balance_monitor_timer_.Stop();
}

