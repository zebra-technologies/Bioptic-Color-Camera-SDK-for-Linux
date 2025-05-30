#ifndef CAMERA_IMAGE_EVENTS_H_
#define CAMERA_IMAGE_EVENTS_H_

#include <wx/wx.h>

#include "zebra_camera_client.h"

using namespace zebra::camera_sdk;

class BiopticColorCameraDemoFrame;



// Snapshot image event listener.

class SnapshotImageObserver: public SnapshotImageEventListener
{
public:
	SnapshotImageObserver(BiopticColorCameraDemoFrame *frame);

    //Method to convert color when a snapshot image is received
	void ImageReceived(ImageEventData image, ImageEventMetaData meta_data) override;

private:
    BiopticColorCameraDemoFrame *frame_;
};


// Continuous image event listener.

class ContinuousImageObserver: public ContinuousImageEventListener
{
public:
	ContinuousImageObserver(BiopticColorCameraDemoFrame *frame);

    //Method to convert color when a continuous image is received
	void ImageReceived(ImageEventData image, ImageEventMetaData meta_data) override;

private:
    BiopticColorCameraDemoFrame *frame_;
};


// Declaration of the CONTINUOUS_IMAGE_EVENT.
wxDECLARE_EVENT(CONTINUOUS_IMAGE_EVENT, wxCommandEvent);

// Declaration of the CAPTURE_SNAPSHOT_EVENT.
wxDECLARE_EVENT(CAPTURE_SNAPSHOT_EVENT, wxCommandEvent);

// Declaration of the PRODUCE_IMAGE_EVENT.
wxDECLARE_EVENT(PRODUCE_IMAGE_EVENT, wxCommandEvent);

// Declaration of the SNAPSHOT_IMAGE_EVENT.
wxDECLARE_EVENT(SNAPSHOT_IMAGE_EVENT, wxCommandEvent);

// Declaration of the DECODE_IMAGE_EVENT.
wxDECLARE_EVENT(DECODE_IMAGE_EVENT, wxCommandEvent);

// Declaration of the DECODE_SESSION_STATUS_CHANGE_EVENT.
wxDECLARE_EVENT(DECODE_SESSION_STATUS_CHANGE_EVENT, wxCommandEvent);

#endif // CAMERA_IMAGE_EVENTS_H_
