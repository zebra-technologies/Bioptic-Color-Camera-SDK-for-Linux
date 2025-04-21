/***************************************************************
 * Name:      CameraPlugAndPlay.cpp
 * Purpose:   Implementation for plug and play event listeners.
              Implementation to add camera to camera arrived queue during attachement and create camera selected event.
              Implementation to dd camera to camera left queue during detachement and create camera deselected event.
 * Author:     ()
 * Created:   2021-03-01
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved
 * License:
 **************************************************************/




#include "CameraPlugAndPlay.h"

#include <string>

#include "BiopticColorCameraDemoMain.h"

// Definition of the CAMERA_SELECTED_EVENT
wxDEFINE_EVENT(CAMERA_SELECTED_EVENT, wxCommandEvent);

// Definition of the CAMERA_DESELECTED_EVENT
wxDEFINE_EVENT(CAMERA_DESELECTED_EVENT, wxCommandEvent);


AttachedEventObserver::AttachedEventObserver(BiopticColorCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void AttachedEventObserver::Attached(zebra::DeviceInfo info)
{
    wxLogMessage("%s: SN: %s, (%s)", __func__, info.serial_number, info.device_path);

    frame_->QueueCameraArrivedEvent(info);
}

DetachedEventObserver::DetachedEventObserver(BiopticColorCameraDemoFrame *frame):
    frame_(frame)
{
    wxLogMessage("%s", __func__);
}

void DetachedEventObserver::Detached(zebra::DeviceInfo info)
{
    wxLogMessage("%s: SN: %s, (%s)", __func__, info.serial_number, info.device_path);
    frame_->ResetFirmwareUpdateProgressBar();
    frame_->QueueCameraLeftEvent(info);
}

void BiopticColorCameraDemoFrame::CreatePnpListeners()
{
    wxLogMessage("%s", __func__);

    // Bind camera-selected listener
    Bind(CAMERA_SELECTED_EVENT, &BiopticColorCameraDemoFrame::OnCameraArrivedEvent, this);

    // Bind camera-deselected listener
    Bind(CAMERA_DESELECTED_EVENT, &BiopticColorCameraDemoFrame::OnCameraLeftEvent, this);

    attached_listener_ = new AttachedEventObserver(this);
    detached_listener_ = new DetachedEventObserver(this);

    device_manager_.AddDeviceAttachedListener(*attached_listener_);
    device_manager_.AddDeviceDetachedListener(*detached_listener_);
}


void BiopticColorCameraDemoFrame::ReleasePnpListeners()
{
    wxLogMessage("%s", __func__);

    if (attached_listener_)
    {
        device_manager_.RemoveDeviceAttachedListener(*attached_listener_);
        delete attached_listener_;
    }
    if (detached_listener_)
    {
        device_manager_.RemoveDeviceDetachedListener(*detached_listener_);
        delete detached_listener_;
    }

    // Unbind camera-selected listener
    Unbind(CAMERA_SELECTED_EVENT, &BiopticColorCameraDemoFrame::OnCameraArrivedEvent, this);

    // Unbind camera-deselected listener
    Unbind(CAMERA_DESELECTED_EVENT, &BiopticColorCameraDemoFrame::OnCameraLeftEvent, this);
}

void BiopticColorCameraDemoFrame::QueueCameraArrivedEvent(zebra::DeviceInfo info)
{
    wxLogMessage("%s", __func__);

    wxCommandEvent *event = new wxCommandEvent(CAMERA_SELECTED_EVENT, GetId());
    event->SetClientData(new zebra::DeviceInfo(info));
    QueueEvent(event);
}

void BiopticColorCameraDemoFrame::QueueCameraLeftEvent(zebra::DeviceInfo info)
{
    wxLogMessage("%s", __func__);
    ResetFirmwareUpdateProgressBar();
    wxCommandEvent *event = new wxCommandEvent(CAMERA_DESELECTED_EVENT, GetId());
    event->SetClientData(new zebra::DeviceInfo(info));
    QueueEvent(event);
}

//Get device information of attached camera devices
void BiopticColorCameraDemoFrame::QueueAlreadyAttachedCameraEvents()
{
	wxLogMessage("%s", __func__);

	std::vector<zebra::DeviceInfo> existing_dev_info = device_manager_.EnumerateDevices();
	for (zebra::DeviceInfo& info: existing_dev_info)
	{
		QueueCameraArrivedEvent(info);
	}
}

void BiopticColorCameraDemoFrame::OnCameraArrivedEvent(wxCommandEvent& event)
{

    wxLogMessage("%s", __func__);

    zebra::DeviceInfo *info = (zebra::DeviceInfo*)event.GetClientData();
    if (info)
    {
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s", __func__, info->vid, info->pid, info->serial_number, info->device_path);

        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = new std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            (*info, nullptr);

        std::string item_name = client_data->first.device_path;
        choice_camera_id->Append(wxString(item_name.c_str()), client_data);

        if (wxNOT_FOUND == choice_camera_id->GetSelection())
        {
            // Select the newly arrived camera.
            try
            {
                client_data->second = camera_manager_client_->CreateZebraCamera(client_data->first);    
                choice_camera_id->SetSelection(choice_camera_id->GetCount() - 1);      

                PopulateCameraProperties(client_data->second);
                EventLog("Camera ATTACHED ");
            }
            catch (std::exception& e)
            {
                wxMessageBox(e.what(), "Error");
            }
        }
    }

}

void BiopticColorCameraDemoFrame::OnCameraLeftEvent(wxCommandEvent& event)
{

    wxLogMessage("%s", __func__);

    zebra::DeviceInfo *info = (zebra::DeviceInfo*)event.GetClientData();
    unsigned int selected = choice_camera_id->GetSelection();

    if (info)
    {
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s, selected=%d",
        __func__, info->vid, info->pid, info->serial_number, info->device_path, selected);

        for (unsigned int i = 0; i < choice_camera_id->GetCount(); i++)
        {
            std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
                *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                                choice_camera_id->GetClientData(i);
            if (client_data->first.device_path == info->device_path)
            {
                wxLogMessage("%s: camera left %d", __func__, i);
                EventLog("Camera DETACHED ");

                // Release currently selected camera
                if (i == selected)
                {
                    
                    /**
                     * stopping image/video is handled in client library itself when
                     * detaching a camera. StopCameraVideo(client_data->second); was using 
                     * for stopping.
					 * Delete the client. Unlike in single-client camera, multi-client client is still valid if this is a reboot.
                	 * So, if we do this last (i.e. before ClearAllCameraProperties), old values will be set to the camera
                	 * if the detach cause is a reboot.
                     */
                    ResetFirmwareUpdateProgressBar();
                    ClearAllCameraProperties();

                    client_data->second = nullptr;
                }
                choice_camera_id->Delete(i);
                break;
            }
        }
    }
    
}
