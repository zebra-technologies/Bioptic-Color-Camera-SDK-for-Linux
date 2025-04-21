/***************************************************************
 * Name:      BiopticColorCameraDemoMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-03-01
 * Copyright: ©2021 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#ifndef BIOPTICCOLORCAMERADEMOMAIN_H

#define BIOPTICCOLORCAMERADEMOMAIN_H

//(*Headers(BiopticColorCameraDemoFrame)
#include <wx/gauge.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/statbmp.h>
//*)

#include <sstream>
#include <string>
#include "led.h"
#include "CameraPlugAndPlay.h"
#include "CameraFirmwareDownload.h"
#include "CameraImageEvents.h"
#include "VideoPanel.h"
#include "ImageBuffer.h"

#include "device_manager.h"
#include "zebra_camera_client.h"
#include "zebra_camera_manager_client.h"
#include "image_event_subscription_impl.h"
#include "directory_observer.h"
#include "image_event.h"

#include <opencv2/core/core.hpp>

using namespace zebra::camera_sdk;

/*
* enum ImageFileFormat is used to enumerate image file format
* Compiler will assign  JPG to the integral value 0 and BMP to the integral value 1 by default
* Ths will improve the readability and the maintability of the code when handling image format selection for saving images
*/
enum ImageFileFormat
{
    JPG,
    BMP,
};
#define WHITE_BALANCE_POLLING_INTERVAL_IN_MILLISECONDS 	1000

class BiopticColorCameraDemoFrame: public wxFrame
{
    public:

        ImageBuffer image_buffer_;
        ImageBuffer snapshot_image_;
        ImageBuffer last_saved_image_;
        std::string image_resolution_=""; 
        std::string image_event_type_ = "";
        bool continuous_image_received_ = false ;

        BiopticColorCameraDemoFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BiopticColorCameraDemoFrame();

        /**
        * Add camera attached event to the event queue when a camera is attached
        * @param DeviceInfo received from device enumeration
        * @return void function
        */
        void QueueCameraArrivedEvent(zebra::DeviceInfo info);

        /**
        * Add  camera detached event to the event queue when a camera is detached
        * @param FirmwareDownloadEventsArgs
        * @return void function
        */
        void QueueCameraLeftEvent(zebra::DeviceInfo info);

        /**
        * Enumerate devices and send device info to QueueCameraArrivedEvent method
        * @return void function
        */
        void QueueAlreadyAttachedCameraEvents();

        /**
        * Add firmware update event to the event queue when a firmware download event is received
        * @param FirmwareDownloadEventsArgs
        * @return void function
        */
        void QueueFirmwareDownloadEvent(FirmwareDownloadEventsArgs status);
        
        /** This method is responsible for reseting the progress bar of firmware update during camera detach and reboot events*/
        void ResetFirmwareUpdateProgressBar();

        /**
        * Create snapshot image event and add to the event queue when the snapshot button is clicked in scanner
        * @return void function
        */
        void QueueSnapshotImageEvent();

        /**
        * Create continuous image event and add to the event queue when continuous video mode is selected
        * @return void function
        */
        void QueueContinuousImageEvent();

    private:
        /**
        * Create device attach and detach listners and add listeners to device manager
        * @return void function
        */
        void CreatePnpListeners();

         /**
        * Remove device attach and detach listeners from device manager
        * @return void function
        */
        void ReleasePnpListeners();

        /**
        * Make zebra camera client object null during application close
        * @return void function
        */
        void ReleaseCameras();

        /**
        * Create listeners for image events during camera attachment
        * @return void function
        */
        void CreateImageEventListeners();

        /**
        * Stop camera video and unbind image event listeners during application closure
        * @return void function
        */
        void ReleaseImageEventListeners();

        // Method to update event information when an image event is occured
        void UpdateEventInformation(string event_type_,string image_format_,string image_size_,string time_stamp_, string image_resolution_,string decode_data_);  
        
        // Get current date and time
        std::string GetDateAndTime(); 


        /**
        * Create zebra camera client objecr=t
        * @return camera client object
        */
        std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> GetCamera();

        /**
        * Method to populate properties for newly selected camera
        * @return void function
        */
        void PopulateCameraProperties(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        /**
        * Method to populate camera asset tracking information
        * @return void function
        */
        void PopulateCameraAssetTrackingInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        /**
        * Method to populate camera UVC properties during camera attachment
        * @return void function
        */
        void PopulateProcessingUnitInfo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        /**
        * Method to display camera video 
        * @return void function
        */
        void PopulateVideoProfiles(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        // Methods responsible for event viewer
        void ChangeCameraVideoProfile(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera, const FrameType& frame_type);
        void StopCameraVideo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);


       
        /**
        * Method to clear camera properties when the selected camera is detached
        * @return void function
        */
        void ClearAllCameraProperties();

        /**
        * Method to clear camera asset information when the selected camera is detached
        * @return void function
        */
        void ClearCameraAssetTrackingInfo();

        /**
        * Method to clear camera UVC properties when the selected camera is detached
        * @return void function
        */
        void ClearProcessingUnitInfo();

        /**
        * Method to clear camera video in event viewer when the selected camera is detached
        * @return void function
        */
        void ClearVideoEvents();

        /**
        * Create camera client object using the device info and camera manager client object. Select newly arrived camera if a camera is not selected
        * @param deviceAttachedEvent
        * @return void function
        */
        void OnCameraArrivedEvent(wxCommandEvent& event);


        /**
        * Release currently selected camera and call methods to clear camera asset info and UVC properties
        * @param deviceDetachedEvent
        * @return void function
        */
        void OnCameraLeftEvent(wxCommandEvent& event);

        // Method to handle video mode selection
        void OnChoiceVideoModeSelect(wxCommandEvent& event);

        // Method responsible for handling user selection of vide mode , Illumination mode and power user mode
        void PopulateExtensionUnit1Info(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        // Method responsible for populating video mode
        void PopulateVideoMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        // Method responsible for illumination mode
        void PopulateIlluminationMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);

        // Method to clear video mode , illumination mode choices
        void ClearExtensionUnit1Info();

        // Method to handle illumination mode selection
        void OnChoiceIlluminationModeSelect(wxCommandEvent& event);

        //(*Handlers(BiopticColorCameraDemoFrame)
        void OnChoiceSelectedCameraSelect(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);

        // Methods responsible for dispalying brightness property
        void PopulateBrightness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderBrightnessCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlBrightnessText(wxCommandEvent& event);

        // Methods responsible for dispalying contrast property
        void PopulateContrast(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderContrastCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlContrastText(wxCommandEvent& event);

        // Methods responsible for dispalying saturation property
        void PopulateSaturation(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderSaturationCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlSaturationText(wxCommandEvent& event);

        // Methods responsible for dispalying sharpness property
        void PopulateSharpness(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderSharpnessCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlSharpnessText(wxCommandEvent& event);

        // Methods responsible for dispalying gamma property
        void PopulateGamma(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderGammaCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlGammaText(wxCommandEvent& event);

        // Methods responsible for dispalying backlight property
        void PopulateBacklight(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderBacklightCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlBacklightText(wxCommandEvent& event);

        // Methods responsible for dispalying gain property
        void PopulateGain(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderGainCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlGainText(wxCommandEvent& event);

        // Methods responsible for dispalying exposure property
        void PopulateAbsoluteExposureTime(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnSliderAbsoluteExposureTimeCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlAbsoluteExposureTimeText(wxCommandEvent& event);
        void OnCheckBoxExposureTimeAutoClick(wxCommandEvent& event);

        // Methods responsible for dispalying white balance property
        void PopulateWhiteBalanceComponent(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void OnAutoWhiteBalanceUpdateTimer(wxTimerEvent& event);
        void OnSliderWhiteBalanceBlueCmdScrollChanged(wxScrollEvent& event);
        void OnSliderWhiteBalanceRedCmdScrollChanged(wxScrollEvent& event);
        void OnTextCtrlWhiteBalanceBlueText(wxCommandEvent& event);
        void OnTextCtrlWhiteBalanceRedText(wxCommandEvent& event);
        void OnCheckBoxWhiteBalanceAutoClick(wxCommandEvent& event);

        // Methods responsible for firmware update
        void OnFilePickerCtrlFirmwareFileChanged(wxFileDirPickerEvent& event);
        void OnButtonCancelClick(wxCommandEvent& event);
        void OnButtonUpdateClick(wxCommandEvent& event);
        void CreateFirmwareDownloadEventListener();
        void OnCameraFirmwareDownloadEvent(wxCommandEvent& event);
        void ReleaseFirmwareDownloadEventListener();
        void OnButtonLaunchClick(wxCommandEvent& event);

        /**
        * Dispaly event logs
        * @param logMessage & * @param value
        * @return void function
        */
        void EventLog(const std::string& logMessage, int value);
        void EventLog(const std::string& logMessage);

        // Methods responsible for snapshot image event
        void OnSnapshotImageEvent(wxCommandEvent& event);
        void OnCaptureSnapshotEvent(wxCommandEvent& event);
        void OnButtonCaptureSnapshotClick(wxCommandEvent& event);
        void OnCheckBoxSnapshotEventsClick(wxCommandEvent& event);
        void QueueCaptureSnapshotEvent();

        //Method to retrive configuration
        void OnButtonRetriveConfigClick(wxCommandEvent& event);
        void OnButtonRetriveConfigToFileClick(wxCommandEvent& event);
        void OnDirPickerCtrlConfigDirChanged(wxFileDirPickerEvent& event);


        // Method to load configuration
        void OnButtonLoadConfigClick(wxCommandEvent& event);
        void OnButtonLoadConfigFromFileClick(wxCommandEvent& event);
        void OnFilePickerCtrlConfigFileChanged(wxFileDirPickerEvent& event);

        // Methods responsible for continuous image event
        void OnContinuousImageEvent(wxCommandEvent& event);
        void OnCheckBoxContinuousEventsClick(wxCommandEvent& event);

        // Methods to populate power user mode
        void PopulatePowerUserMode(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        
        //Method to disable and enable UVC properties when power user mode check box is clicked
        void OnPowerUserModeChange(bool mode);
        void OnChoicePowerUserModeSelection(wxCommandEvent& event);
        
        // Methods to populate device awake
        void PopulateDeviceAwake(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera);
        void SetDeviceAwake(VideoMode mode);
        void ClearDeviceAwakeInfo();


        // Save images of camera image events
        void SaveImage(ImageBuffer& image, std::string str_event_type);


        //*)
     
        int property_brightness;
        int property_contrast;
        int property_saturation;
        int property_sharpness;
        int property_gamma;
        int property_wb_blue;
        float property_wb_blue_in_float;
        int property_wb_red;
        float property_wb_red_in_float;
        int property_backlight;
        int property_gain;
        int property_abs_exposure_time;
        int property_auto_exposure_mode;
        int property_videomode;
        int property_illuminationmode;
        int property_powerusermode;

        wxTimer auto_white_balance_monitor_timer_;   
        wxLog* logger_;
        
        zebra::DeviceManager device_manager_;
        std::unique_ptr<zebra::camera_sdk::ZebraCameraManagerClient> camera_manager_client_;
        
        AttachedEventObserver *attached_listener_;
        DetachedEventObserver *detached_listener_;

     
        std::string save_image_directory_path_;
        std::string firmware_file_;
        
        DirectoryObserver *dir_observer_;
        bool listening_started_ = false;
        bool observer_created_ = false;

        bool firmware_update_completed = false;

        FirmwareDownloadEventObserver *firmware_download_event_listener_;
        SnapshotImageObserver *snapshot_image_listener_;
        ContinuousImageObserver *continuous_image_listener_;
    
        std::string load_config_file_="";
        std::string retrieve_config_file_="";
        std::string config_file_directory_path_ = "";
        std::string config_extension = ".bcccfg";
        ImageFileFormat image_file_format_;
   
    
        //(*Identifiers(bioptic_color_cameraFrame)
        static const long ID_STATICTEXT16;
        static const long ID_CHOICE5;
        static const long ID_STATICTEXT17;
        static const long ID_TEXTCTRL11;
        static const long ID_STATICTEXT18;
        static const long ID_TEXTCTRL12;
        static const long ID_STATICTEXT19;
        static const long ID_TEXTCTRL13;
        static const long ID_STATICTEXT20;
        static const long ID_TEXTCTRL14;
        static const long ID_BUTTON6;
        static const long ID_STATICTEXT21;
        static const long ID_TEXTCTRL15;
        static const long ID_BUTTON7;
        static const long ID_STATICTEXT22;
        static const long ID_TEXTCTRL16;
        static const long ID_BUTTON8;
        static const long ID_STATICTEXT23;
        static const long ID_TEXTCTRL17;
        static const long ID_BUTTON9;
        static const long ID_PANEL4;
        static const long ID_FILEPICKERCTRL1;
        static const long ID_BUTTON10;
        static const long ID_BUTTON11;
        static const long ID_GAUGE1;
        static const long ID_BUTTON12;
        static const long ID_PANEL5;
        static const long ID_TEXTCTRL18;
        static const long ID_PANEL6;
        static const long ID_STATICBOX2;
        static const long ID_STATICBOX3;
        static const long ID_STATICBOX4;
        static const long ID_PANEL12;
        static const long ID_PANEL13;
        static const long ID_NOTEBOOK1;
        static const long ID_PANEL2;
        static const long ID_STATICBOX1;
        static const long ID_STATICTEXT24;
        static const long ID_TEXTCTRL19;
        static const long ID_STATICTEXT25;
        static const long ID_TEXTCTRL20;
        static const long ID_STATICTEXT26;
        static const long ID_TEXTCTRL21;
        static const long ID_STATICTEXT27;
        static const long ID_TEXTCTRL22;
        static const long ID_STATICTEXT28;
        static const long ID_TEXTCTRL23;
        static const long ID_STATICTEXT29;
        static const long ID_TEXTCTRL24;
        static const long ID_STATICTEXT30;
        static const long ID_PANEL8;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_STATICTEXT15;
        static const long ID_DIRPICKERCTRL1;
        static const long ID_CHECKBOX9;
        static const long ID_BUTTON5;
        static const long ID_PANEL11;
        static const long ID_STATICTEXT1;
        static const long ID_SLIDER1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_SLIDER2;
        static const long ID_TEXTCTRL2;
        static const long ID_STATICTEXT3;
        static const long ID_SLIDER3;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT4;
        static const long ID_SLIDER4;
        static const long ID_TEXTCTRL4;
        static const long ID_STATICTEXT5;
        static const long ID_SLIDER5;
        static const long ID_TEXTCTRL5;
        static const long ID_STATICTEXT6;
        static const long ID_SLIDER6;
        static const long ID_TEXTCTRL6;
        static const long ID_CHECKBOX1;
        static const long ID_STATICTEXT7;
        static const long ID_SLIDER7;
        static const long ID_TEXTCTRL7;
        static const long ID_STATICTEXT8;
        static const long ID_SLIDER8;
        static const long ID_TEXTCTRL8;
        static const long ID_STATICTEXT9;
        static const long ID_SLIDER9;
        static const long ID_TEXTCTRL9;
        static const long ID_STATICTEXT10;
        static const long ID_SLIDER10;
        static const long ID_TEXTCTRL10;
        static const long ID_CHECKBOX2;
        static const long ID_PANEL9;
        static const long ID_STATICTEXT11;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT12;
        static const long ID_CHOICE2;
        static const long ID_STATICTEXT13;
        static const long ID_CHOICE3;
        static const long ID_STATICTEXT14;
        static const long ID_CHOICE4;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_PANEL10;
        static const long ID_PANEL7;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_CHECKBOX_CONTRAST_AUTO;
        static const long ID_PANEL20;
        static const long ID_TEXTCTRL25;
        static const long ID_FILEPICKERCTRL2;
        static const long ID_DIRPICKERCTRL2;
        static const long ID_LED2;

        //*)

        //(*Declarations(bioptic_color_cameraFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxButton* Button5;
        wxButton* button_cancel_fu;
        wxButton* button_launch_fw;
        wxButton* button_reboot;
        wxButton* button_set_default;
        wxButton* button_snaposhot;
        wxButton* button_update_firmware;
        wxButton* button_write_to_flash;
        wxCheckBox* CheckBoxWhiteBalanceAuto;
        wxCheckBox* CheckBoxExposureTimeAuto;
        wxCheckBox* CheckBoxContinuousEvents;
        wxCheckBox* CheckBoxSnapshotEvents;
        wxCheckBox* CheckBoxDecodeEvents;
        wxCheckBox* CheckBox6;
        wxCheckBox* CheckBox8;
        wxCheckBox* CheckBoxSaveImages;
        wxCheckBox* checkbox_decode_session;
        wxCheckBox* CheckBoxContrastAuto;
        wxChoice* ChoiceVideoMode;
        wxChoice* ChoiceIlluminationMode;
        wxChoice* Choice3;
        wxChoice* ChoicePowerUserMode;
        wxChoice* choice_camera_id;
        wxDirPickerCtrl* DirPickerCtrl1;
        wxFilePickerCtrl* filepicker_firmware_file;
        wxGauge* GaugeFirmwareDownloadProgress;
        wxNotebook* Notebook1;
        wxPanel* Panel1;
        wxPanel* Panel2;
        wxPanel* Panel3;
        wxPanel* Panel4;
        wxPanel* Panel5;
        wxPanel* Panel6;
        wxPanel* Panel7;
        wxPanel* Panel8;
        wxPanel* Panel_Firmware_update;
        wxPanel* Panel_camera_properties;
        wxPanel* Panel_left;
        wxPanel* Panel_main;
        wxPanel* Panel_right;
        wxPanel* PanelVideo;
        wxSlider* SliderAbsoluteExposureTime;
        wxSlider* SliderBrightness;
        wxSlider* SliderContrast;
        wxSlider* SliderSaturation;
        wxSlider* SliderSharpness;
        wxSlider* SliderGamma;
        wxSlider* SliderWhiteBalanceBlue;
        wxSlider* SliderWhiteBalanceRed;
        wxSlider* SliderBacklight;
        wxSlider* SliderGain;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxStaticBox* StaticBox3;
        wxStaticBox* StaticBox4;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;
        wxStaticText* StaticText12;
        wxStaticText* StaticText13;
        wxStaticText* StaticText14;
        wxStaticText* StaticText15;
        wxStaticText* StaticText16;
        wxStaticText* StaticText17;
        wxStaticText* StaticText18;
        wxStaticText* StaticText19;
        wxStaticText* StaticText1;
        wxStaticText* StaticText20;
        wxStaticText* StaticText21;
        wxStaticText* StaticText22;
        wxStaticText* StaticText23;
        wxStaticText* StaticText24;
        wxStaticText* StaticText25;
        wxStaticText* StaticText26;
        wxStaticText* StaticText27;
        wxStaticText* StaticText28;
        wxStaticText* StaticText29;
        wxStaticText* StaticText2;
        wxStaticText* StaticText30;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlAbsoluteExposureTime;
        wxTextCtrl* TextCtrlEventLog;
        wxTextCtrl* TextCtrlEventType;
        wxTextCtrl* TextCtrlBrightness;
        wxTextCtrl* TextCtrlFormat;
        wxTextCtrl* TextCtrlSize;
        wxTextCtrl* TextCtrlTimeStamp;
        wxTextCtrl* TextCtrlImageResolution;
        wxTextCtrl* TextCtrlDecodeData;
        wxTextCtrl* TextCtrlContrast;
        wxTextCtrl* TextCtrlSaturation;
        wxTextCtrl* TextCtrlSharpness;
        wxTextCtrl* TextCtrlGamma;
        wxTextCtrl* TextCtrlWhiteBalanceBlue;
        wxTextCtrl* TextCtrlWhiteBalanceRed;
        wxTextCtrl* TextCtrlBacklight;
        wxTextCtrl* TextCtrlGain;
        wxTextCtrl* text_dofp;
        wxTextCtrl* text_dom;
        wxTextCtrl* text_dos;
        wxTextCtrl* text_firmware_version;
        wxTextCtrl* text_hardware_version;
        wxTextCtrl* text_model_number;
        wxTextCtrl* text_serial_number;
        wxTextCtrl* TextCtrlConfiguration;
        VideoPanel* PanelVideoDisplay;
        wxFilePickerCtrl* filepicker_load_config;
        wxDirPickerCtrl* DirPickerCtrl2;
        wxLed* LedDeviceAwake;

        //*)

        DECLARE_EVENT_TABLE()
};

#endif  
