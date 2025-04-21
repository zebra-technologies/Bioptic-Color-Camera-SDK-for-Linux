/***************************************************************
 * Name:      DemoFirmwareControls.cpp
 * Purpose:   Implementation of button click events - firmware update , cancel firmware update and install firmware.
 * Author:     ()
 * Created:   2021-03-12
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved
 * License:
 **************************************************************/



#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"
#include <iostream>

void BiopticColorCameraDemoFrame::OnFilePickerCtrlFirmwareFileChanged(wxFileDirPickerEvent& event)
{
    (void)event;

    firmware_file_ = std::string(static_cast<const char*>(event.GetPath()));
    wxLogMessage("%s: path=%s", __func__, firmware_file_);
}

// Implementationtation for firmware download
void BiopticColorCameraDemoFrame::OnButtonUpdateClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera && !firmware_file_.empty())
    {
        try
        {
            EventLog("Firmware Update STARTED");
        	camera_manager_client_->DownloadFirmware(camera, firmware_file_);
        }
        catch (std::exception& e)
        {
            wxString msg;
            std::cout<<"Firmware update error" <<std::endl;
            msg.Printf(wxT("%s"), e.what());
            wxMessageBox(msg, _("Firmware Update"), wxICON_ERROR);
        }
    }

}

// Implementation for firmware dowload cancel during download
void BiopticColorCameraDemoFrame::OnButtonCancelClick(wxCommandEvent& event)
{

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        if(!firmware_update_completed&&!firmware_file_.empty()){
            try
            {
        	    camera_manager_client_->CancelFirmwareDownload(camera);
                EventLog("Firmware download CANCELED ");
                firmware_update_completed = false;

            }
            catch (std::exception& e)
            {
                wxString msg;
                msg.Printf(wxT("%s"), e.what());
                wxMessageBox(msg, _("Firmware Update"), wxICON_ERROR);
            }

        }else
        {
                wxString msg;
                msg.Printf(wxT("NO Firmware Update in Progress "));
                wxMessageBox(msg, _("Firmware Install"), wxICON_WARNING);
        }

    }

}

// Implemetation to install loaded firmware to device
void BiopticColorCameraDemoFrame::OnButtonLaunchClick(wxCommandEvent& event)
{
    (void)event;

    auto camera = GetCamera();
 
    if(camera)
    {

        if(firmware_update_completed){

            EventLog("Firmware LAUNCH STARTED");
            try
                {
                    
            	    camera_manager_client_->InstallFirmware(camera);
                    EventLog("Firmware INSTALL : SUCCESS");
                    firmware_update_completed = false;
                }
                catch (std::exception& e)
                {
                    wxString msg;
                    msg.Printf(wxT("%s"), e.what());
                    wxMessageBox(msg, _("Firmware Install"), wxICON_ERROR);
                }

        }
        else
        {
                wxString msg;
                msg.Printf(wxT("Firmware Update is not completed"));
                wxMessageBox(msg, _("Firmware Install"), wxICON_WARNING);

        }

                
    }
         

}
