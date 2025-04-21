/***************************************************************
 * Name:      CameraFirmwareDownload.cpp
 * Purpose:   Implementation of firmware update , firmware update event listening and progress bar updation
 * Author:     ()
 * Created:   2021-03-10
 * Copyright: ©2021 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#include "CameraFirmwareDownload.h"

#include <wx/msgdlg.h>

#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"


// Definition of the CAMERA_FIRMWARE_DOWNLOAD_EVENT
wxDEFINE_EVENT(CAMERA_FIRMWARE_DOWNLOAD_EVENT, wxCommandEvent);

// Constructot
FirmwareDownloadEventObserver::FirmwareDownloadEventObserver(BiopticColorCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void FirmwareDownloadEventObserver::EventReceived(FirmwareDownloadEventsArgs event)
{
    frame_->QueueFirmwareDownloadEvent(event);
}

void BiopticColorCameraDemoFrame::CreateFirmwareDownloadEventListener()
{
    // Bind firmware download event listener
    Bind(CAMERA_FIRMWARE_DOWNLOAD_EVENT, &BiopticColorCameraDemoFrame::OnCameraFirmwareDownloadEvent, this);

    firmware_download_event_listener_ = new FirmwareDownloadEventObserver(this);
    camera_manager_client_->AddFirmwareDownloadEventListener(*firmware_download_event_listener_);
}

// Implemntation for releasing firmware download event listener
void BiopticColorCameraDemoFrame::ReleaseFirmwareDownloadEventListener()
{
    if (firmware_download_event_listener_)
    {
    	camera_manager_client_->RemoveFirmwareDownloadEventListener(*firmware_download_event_listener_);
        delete firmware_download_event_listener_;
    }

    Unbind(CAMERA_FIRMWARE_DOWNLOAD_EVENT, &BiopticColorCameraDemoFrame::OnCameraFirmwareDownloadEvent, this);
}

// Add firmware update event to the event queue
void BiopticColorCameraDemoFrame::QueueFirmwareDownloadEvent(FirmwareDownloadEventsArgs status)
{
    wxCommandEvent *event = new wxCommandEvent(CAMERA_FIRMWARE_DOWNLOAD_EVENT, GetId());
    event->SetClientData(new FirmwareDownloadEventsArgs(status));
    QueueEvent(event);
}

void BiopticColorCameraDemoFrame::OnCameraFirmwareDownloadEvent(wxCommandEvent& event)
{
    FirmwareDownloadEventsArgs *fwstatus = (FirmwareDownloadEventsArgs*)event.GetClientData();

    if (fwstatus)
    {
        wxLogMessage("%s: total=%d, current=%d, status=%d, opcode=%d",
                     __func__,
                     fwstatus->GetTotalRecords(), fwstatus->GetCurrentRecord(), fwstatus->GetStatus(), fwstatus->GetOperationCode());
        GaugeFirmwareDownloadProgress->SetRange(fwstatus->GetTotalRecords());
        
        if (FirmwareDownloadEventsArgs::Status::kSuccessful == fwstatus->GetStatus())
        {
            // Update the progress.
            GaugeFirmwareDownloadProgress->SetValue(fwstatus->GetCurrentRecord());
            EventLog("Firmware Update in PROGRESS");
        }
        else if (FirmwareDownloadEventsArgs::Status::kCanceled == fwstatus->GetStatus())
        {
           // Reset progress display.
            GaugeFirmwareDownloadProgress->SetValue(0);
        }

        if ((FirmwareDownloadEventsArgs::OperationCode::kSessionStop == fwstatus->GetOperationCode()) &&
            (fwstatus->GetTotalRecords() == fwstatus->GetCurrentRecord()))
        {
            firmware_update_completed = true;
            EventLog("Firmware Update ENDED & READY TO LAUNCH");
        }
    }
}
