/***************************************************************
 * Name:      CameraImageEvents.cpp
 * Purpose:   Implementation of image frame handling and listener implementation
 * Author:     ()
 * Created:   2021-03-18
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#include "CameraImageEvents.h"
#include "BiopticColorCameraDemoMain.h"
#include <cstring>
#include <fstream>
#include <sys/time.h> 
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>


#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/imgproc/imgproc.hpp>

// Definition of the CAPTURE_SNAPSHOT_EVENT
wxDEFINE_EVENT(CAPTURE_SNAPSHOT_EVENT, wxCommandEvent);

// Definition of the CONTINUOUS_IMAGE_EVENT
wxDEFINE_EVENT(CONTINUOUS_IMAGE_EVENT, wxCommandEvent);

// Definition of the PRODUCE_IMAGE_EVENT.
wxDEFINE_EVENT(PRODUCE_IMAGE_EVENT, wxCommandEvent);

// Definition of the SNAPSHOT_IMAGE_EVENT.
wxDEFINE_EVENT(SNAPSHOT_IMAGE_EVENT, wxCommandEvent);

// Definition of the DECODE_IMAGE_EVENT.
wxDEFINE_EVENT(DECODE_IMAGE_EVENT, wxCommandEvent);

// Definition of the DECODE_SESSION_STATUS_CHANGE_EVENT.
wxDEFINE_EVENT(DECODE_SESSION_STATUS_CHANGE_EVENT,wxCommandEvent);

// Definition of the TOWER_PLATTER_IMAGE_EVENT.
wxDEFINE_EVENT(TOWER_PLATTER_IMAGE_EVENT, wxCommandEvent);

#define IMAGE_SAVE_TIME_STR_LEN 128

void BiopticColorCameraDemoFrame::CreateImageEventListeners()
{

    // Bind image-event listeners
  
    Bind(SNAPSHOT_IMAGE_EVENT, &BiopticColorCameraDemoFrame::OnSnapshotImageEvent, this);
    Bind(CAPTURE_SNAPSHOT_EVENT, &BiopticColorCameraDemoFrame::OnCaptureSnapshotEvent, this);
    Bind(CONTINUOUS_IMAGE_EVENT, &BiopticColorCameraDemoFrame::OnContinuousImageEvent, this);
   

    snapshot_image_listener_ = new SnapshotImageObserver(this);
    continuous_image_listener_ = new ContinuousImageObserver(this);
}

SnapshotImageObserver::SnapshotImageObserver(BiopticColorCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

// Method to convert color in received snapshot images
void SnapshotImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData meta_data)
{
    (void)image;
	(void)meta_data;

	zebra::image::ColorConverter converter;

	switch (image.format)
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

    // Primary_image is a RGB image
	zebra::camera_sdk::Image primary_image_ = zebra::image::ConvertColor(converter, image.image);
    frame_->snapshot_image_.CopyToBuffer(primary_image_.Data(), primary_image_.Length());
    
    frame_->last_saved_image_.CopyToBuffer(primary_image_.Data(), primary_image_.Length());
    
    frame_-> image_event_type_ = "_s";

    frame_->QueueSnapshotImageEvent();
}

// Method to update event viewer when a snapshot image event is received by application's snapshot button click
void BiopticColorCameraDemoFrame::OnCaptureSnapshotEvent(wxCommandEvent& event)
{
    (void)event;

    image_buffer_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();
    
    SaveImage(image_buffer_, "_cs");
    UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"");

}

// Method to update event viewer when a snapshot image event is received by scanner's snapshot button click
void BiopticColorCameraDemoFrame::OnSnapshotImageEvent(wxCommandEvent& event)
{
    (void)event;

    snapshot_image_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();

    SaveImage(snapshot_image_, "_s");
    UpdateEventInformation("Snapshot","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"");
   
}

// Method to uodate image event information
void BiopticColorCameraDemoFrame::UpdateEventInformation(string event_type_,string image_format_,string image_size_,string time_stamp_, string image_resolution_,string decode_data_){
   
    TextCtrlEventType->SetValue(event_type_);
    TextCtrlTimeStamp->SetValue(time_stamp_);
    TextCtrlDecodeData->SetValue(decode_data_);
    TextCtrlFormat->SetValue(image_format_);
    TextCtrlImageResolution->SetValue(image_resolution_);
    TextCtrlSize->SetValue(image_size_);
    
}

// Get current date and time
std::string BiopticColorCameraDemoFrame::GetDateAndTime(){
     //calculate date time	
    std::time_t t = std::time(nullptr);
    char mbstr[128];
    std::strftime(mbstr, sizeof(mbstr), "%Y_%m_%d_%H:%M:%S", std::localtime(&t));

    //calculate milli seconds	
    timeval current_time;
    gettimeofday(&current_time, 0);
    int milli_seconds = current_time.tv_usec / 1000;
    char milli_string[128];
    sprintf(milli_string, "_%03d", milli_seconds);
    
    std::string date_time = std::string(mbstr) + std::string(milli_string);
    return date_time;
}

// Method to create capture snapshot event and add to event queue
void BiopticColorCameraDemoFrame::QueueCaptureSnapshotEvent()
{
    wxCommandEvent *event = new wxCommandEvent(CAPTURE_SNAPSHOT_EVENT, GetId());
    event->SetString("Frame Ready");
    QueueEvent(event);
}

void BiopticColorCameraDemoFrame::ReleaseImageEventListeners()
{

    auto camera = GetCamera();

    StopCameraVideo(camera);

  
    Unbind(SNAPSHOT_IMAGE_EVENT, &BiopticColorCameraDemoFrame::OnSnapshotImageEvent, this);
    Unbind(CAPTURE_SNAPSHOT_EVENT, &BiopticColorCameraDemoFrame::OnCaptureSnapshotEvent, this);
    Unbind(CONTINUOUS_IMAGE_EVENT, &BiopticColorCameraDemoFrame::OnContinuousImageEvent, this);    

}

// Method to stop  image event listeners
void BiopticColorCameraDemoFrame::StopCameraVideo(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        camera->RemoveSnapshotImageEventListener(*snapshot_image_listener_);
        camera->RemoveContinuousImageEventListener(*continuous_image_listener_);
 
    }
}

// Method to create  snapshot image event and add to queue
void BiopticColorCameraDemoFrame::QueueSnapshotImageEvent()
{
    wxCommandEvent *event = new wxCommandEvent(SNAPSHOT_IMAGE_EVENT, GetId());
    QueueEvent(event);
}

// Method to recieve continuous images to event viewer
void BiopticColorCameraDemoFrame::OnContinuousImageEvent(wxCommandEvent& event)
{
    (void)event;

    image_buffer_.CopyFromBuffer(PanelVideoDisplay->image_data_,
                                 PanelVideoDisplay->image_data_size_);
    PanelVideoDisplay->DrawFrame();
    PanelVideoDisplay->Refresh();
    PanelVideoDisplay->Update();
    
    SaveImage(image_buffer_, "_c");
    UpdateEventInformation("Continuous","RGB", std::to_string((PanelVideoDisplay->image_data_size_)/1000),GetDateAndTime(),image_resolution_,"");
   
}

ContinuousImageObserver::ContinuousImageObserver(BiopticColorCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

// Method to convert colors of received continuous images
void ContinuousImageObserver::ImageReceived(ImageEventData image, ImageEventMetaData meta_data)
{
	(void)meta_data;

	zebra::image::ColorConverter converter;

	switch (image.format)
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

    wxLogMessage("%s: wxh: %d x %d", __func__, image.image.width, image.image.height);

	zebra::camera_sdk::Image rgb_image = zebra::image::ConvertColor(converter, image.image);

    frame_->image_buffer_.CopyToBuffer(rgb_image.Data(), rgb_image.Length());

    frame_->QueueContinuousImageEvent();

    frame_ ->continuous_image_received_ = true ;
}

// Create continuous image event and add to event queue
void BiopticColorCameraDemoFrame::QueueContinuousImageEvent()
{
    wxCommandEvent *event = new wxCommandEvent(CONTINUOUS_IMAGE_EVENT, GetId());
    event->SetString("Frame Ready");
    QueueEvent(event);
    
}

/*
 Generates image file name with given postfix : image_YYYYMMDD_HHMMSS_MILLISec_postfix
 @param file_postfix Postfix to add to file name at the end (one of _c, _s, _p, _d, _sb)
 @return Generated file name as a std::string
*/
std::string GetFileName(std::string file_postfix)
{
    std::string file_prefix = "image_";

    //calculate date time	
    std::time_t t = std::time(nullptr);
    char mbstr[128];
    std::strftime(mbstr, sizeof(mbstr), "%Y%m%d_%H%M%S", std::localtime(&t));

    //calculate milli seconds	
    timeval current_time;
    gettimeofday(&current_time, 0);
    int milli_seconds = current_time.tv_usec / 1000;
    char milli_string[128];
    sprintf(milli_string, "_%03d", milli_seconds);

    //generate file name
    std::string file_name = file_prefix + std::string(mbstr) + std::string(milli_string) + file_postfix;
    return file_name;
}

// Save images
void BiopticColorCameraDemoFrame::SaveImage(ImageBuffer& image, std::string str_event_type)
{
    if (!save_image_directory_path_.empty() && CheckBoxSaveImages->GetValue())
    {
        std::time_t t = std::time(nullptr);
        char save_time[IMAGE_SAVE_TIME_STR_LEN];
        std::strftime(save_time, sizeof(save_time), "%c", std::localtime(&t));

         std::string filepath = save_image_directory_path_ + std::string("/") + GetFileName(str_event_type);
        switch (image_file_format_)
        {
        case ImageFileFormat::JPG:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        case ImageFileFormat::BMP:
            image.SaveAsBmp(filepath + std::string(".bmp"));
            break;
        default:
            image.SaveAsJpeg(filepath + std::string(".jpg"));
            break;
        }
    }
}
