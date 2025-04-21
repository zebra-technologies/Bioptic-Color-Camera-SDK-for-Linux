/***************************************************************
 * Name:      CameraFirmwareDownload.h
 * Purpose:   Defines Implementation of firmware download event
 * Author:     ()
 * Created:   2021-03-10
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#ifndef CAMERA_FIRMWARE_DOWNLOAD_H_
#define CAMERA_FIRMWARE_DOWNLOAD_H_

#include <wx/wx.h>

#include "zebra_camera_manager_client.h"

using namespace zebra::camera_sdk;

class BiopticColorCameraDemoFrame;

/*
    Firmware download event listener.
*/
class FirmwareDownloadEventObserver: public FirmwareDownloadEventListener
{
public:
    FirmwareDownloadEventObserver(BiopticColorCameraDemoFrame *frame);
	void EventReceived(FirmwareDownloadEventsArgs event) override;

private:
    BiopticColorCameraDemoFrame *frame_;
};

// Declaration of the CAMERA_FIRMWARE_DOWNLOAD_EVENT. Notify when a camera object is created.
wxDECLARE_EVENT(CAMERA_FIRMWARE_DOWNLOAD_EVENT, wxCommandEvent);

#endif // CAMERA_FIRMWARE_DOWNLOAD_H_
