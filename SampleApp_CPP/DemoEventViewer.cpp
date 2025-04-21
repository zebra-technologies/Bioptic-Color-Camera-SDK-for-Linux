/***************************************************************
 * Name:      DemoEventViewer.cpp
 * Purpose:   Implementatiion to view and update camera video in event view UI
 * Author:     ()
 * Created:   2021-03-20
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/


#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"
#define FRAME_DATA_SIZE 64

// Method to populate camera video during camera attachment
void BiopticColorCameraDemoFrame::PopulateVideoProfiles(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    std::vector<FrameType> frame_types= camera->GetSupportedFrameTypes();

    for (FrameType& item: frame_types)
    {
        char str_item[FRAME_DATA_SIZE];
        sprintf(str_item, "%s, %d x %d, @%d fps",
                FrameDataFormat::YUY2 == item.format ? "YUY2" : (FrameDataFormat::UYVY == item.format ? "UYVY" : "UNKNOWN"),
                item.width, item.height, item.framerate);
        
        image_resolution_ = std::to_string(frame_types[0].width)+"x"+std::to_string(frame_types[0].height);
    }

    
        int selected_index = 0;
        ChangeCameraVideoProfile(camera, frame_types[selected_index]);
    
}

// Method to update event viewer video
void BiopticColorCameraDemoFrame::ChangeCameraVideoProfile(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera, const FrameType& frame_type)
{
    if (CheckBoxContinuousEvents->GetValue())
    {
        camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
    }   
    if (CheckBoxSnapshotEvents->GetValue())
    {
        camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
    }

    image_buffer_.AllocateBuffer(frame_type.width, frame_type.height);
    snapshot_image_.AllocateBuffer(frame_type.width, frame_type.height);
    PanelVideoDisplay->AllocateImageBuffer(frame_type.width, frame_type.height);
    last_saved_image_.AllocateBuffer(frame_type.width, frame_type.height);
    
    // Set camera frame profile.
    camera->SetCurrentFrameType(frame_type);
    if (CheckBoxSnapshotEvents->GetValue())
    {
        camera->AddSnapshotImageEventListener(*snapshot_image_listener_);
    }
    if (CheckBoxContinuousEvents->GetValue())
    {
        camera->AddContinuousImageEventListener(*continuous_image_listener_);
    }
}