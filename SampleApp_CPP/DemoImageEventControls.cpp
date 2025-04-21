/***************************************************************
 * Name:      DemoImageEventControls.cpp
 * Purpose:   Implementation of button click and checkbox click events for image events
 * Author:     ()
 * Created:   2021-03-22
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/


#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"


// Method to handle snapshot image event listener when the snapshot image checkbox is clicked
void BiopticColorCameraDemoFrame::OnCheckBoxSnapshotEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddSnapshotImageEventListener(*snapshot_image_listener_);
        }
        else
        {
            camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
        }
    }

}

// Method to handle capture snapshot event when the snapshot button clicked in application
void BiopticColorCameraDemoFrame::OnButtonCaptureSnapshotClick(wxCommandEvent& event)
{
    

    (void)event;

    auto camera = GetCamera();
    if (camera)
    {
        Image snapshot = camera->CaptureSnapshot();

        if(snapshot.Data()){
            EventLog("Capture snapshot WORK");
        }else{
            EventLog("Capture snapshot DO NOT WORK");
        }
        zebra::image::ColorConverter converter;

        switch (snapshot.Format())
        {
        case ImageFormat::YUY2:
            converter = zebra::image::ColorConverter::YUY2_TO_RGB;
            break;
        case ImageFormat::UYVY:
            converter = zebra::image::ColorConverter::UYVY_TO_RGB;
            break;
        default:
            return;
        }

        wxLogMessage("%s: wxh: %d x %d", __func__, snapshot.Width(), snapshot.Height());
        EventLog("Snapshot CAPTURED");

        // Convert to RGB.
        ImageData image = {snapshot.Width(), snapshot.Height(), snapshot.Stride(), snapshot.Length(), snapshot.Data()};
        zebra::camera_sdk::Image rgb = zebra::image::ConvertColor(converter, image);
        // Save snapshot image.
        image_buffer_.CopyToBuffer(rgb.Data(), rgb.Length());
        last_saved_image_.CopyToBuffer(rgb.Data(), rgb.Length());
        image_event_type_= "_cs";
        UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"");

        QueueCaptureSnapshotEvent();
    }

}

// Method to handle continuous image event listeners when the continuous check box is clicked
void BiopticColorCameraDemoFrame::OnCheckBoxContinuousEventsClick(wxCommandEvent& event)
{

    wxLogMessage("%s: check status=%d", __func__, event.IsChecked());

    auto camera = GetCamera();
    if (camera)
    {
        if (event.IsChecked())
        {
            camera->AddContinuousImageEventListener(*continuous_image_listener_);
             EventLog("Continuous image event STARTED");
        }
        else
        {
            camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
            continuous_image_received_ = false ;
            EventLog("Continuous image event ENDED");
        }
    }

}

// Clear image event checkboxes
void BiopticColorCameraDemoFrame::ClearVideoEvents()
{
    wxLogMessage("%s", __func__);

    // Clear image event checkboxes. 
    CheckBoxSnapshotEvents->SetValue(false);
    CheckBoxContinuousEvents->SetValue(false);
}