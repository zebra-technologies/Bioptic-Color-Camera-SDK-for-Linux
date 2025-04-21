/***************************************************************
 * Name:      CameraPlugAndPlay.h
 * Purpose:   Defines Plug and Play listeners during camera attachment and detachment.
 * Author:     ()
 * Created:   2021-03-01
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#ifndef CAMERA_PLUGANDPLAY_H_
#define CAMERA_PLUGANDPLAY_H_

#include <wx/wx.h>

#include "device_manager.h"

class BiopticColorCameraDemoFrame;

// Defines AttachedEventObserver class
class AttachedEventObserver: public zebra::DeviceAttachedListener
{
public:
    // Constructor
    AttachedEventObserver(BiopticColorCameraDemoFrame *frame);

    // Get attached camera info  and add camera to camera arrived queue and creates CAMERA_SELECTED_EVENT.
	void Attached(zebra::DeviceInfo info) override;

private:
    BiopticColorCameraDemoFrame *frame_;
};

// Defines DetachedEventObserver class
class DetachedEventObserver: public zebra::DeviceDetachedListener
{
public:
    // Constructor
    DetachedEventObserver(BiopticColorCameraDemoFrame *frame);

    // Get detached camera , reset the progress bar of firmware update and add camera to camera left queue and creates CAMERA_DESELECTED_EVENT.
	void Detached(zebra::DeviceInfo info) override;

private:
    BiopticColorCameraDemoFrame *frame_;    
};

// Declaration of the CAMERA_SELECTED_EVENT. Notify when a camera object is created.
wxDECLARE_EVENT(CAMERA_SELECTED_EVENT, wxCommandEvent);

// Declaration of the CAMERA_DESELECTED_EVENT. Notify when a selected camera object is deselected.
wxDECLARE_EVENT(CAMERA_DESELECTED_EVENT, wxCommandEvent);

#endif // CAMERA_PLUGANDPLAY_H_
