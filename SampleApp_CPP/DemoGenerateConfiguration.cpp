/***************************************************************
 * Name:      DemoGenerateConfiguration.cpp
 * Purpose:   Implementation of loading configurations from a file and from the configurations tab
 *             Implementation of retrieving configurations to a file and to the configurations tab 
 * Author:     ()
 * Created:   2021-03-22
 * Copyright: ©2022 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "BiopticColorCameraDemoMain.h"

// Method to retieve configurations to Load/Retrive configuration tab
void BiopticColorCameraDemoFrame::OnButtonRetriveConfigClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		std::string camera_config;

		try
		{
			camera_config = camera_manager_client_->RetrieveConfiguration(camera);
			TextCtrlConfiguration->SetValue(camera_config);
            EventLog("Configuration RETRIEVED");
		}
		catch (std::exception& e)
		{
			wxString msg;
			msg.Printf(wxT("%s"), e.what());
			wxMessageBox(msg, _("Retrieve configuration"), wxICON_ERROR);
		}
	}

}

// Method to load configurations from Load/Retrive configuration tab
void BiopticColorCameraDemoFrame::OnButtonLoadConfigClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		std::string camera_configuration = std::string(TextCtrlConfiguration->GetValue());
		if (camera_configuration.compare("") != 0 )
		{
			try
			{
				camera_manager_client_->LoadConfiguration(camera, camera_configuration);

				// Refresh UI controls
				PopulateProcessingUnitInfo(camera);
				// PopulateExtensionUnit1Info(camera);
				EventLog("Configuration LOADED");
			}
			catch (std::exception& e)
			{
				wxString msg;
				msg.Printf(wxT("%s"), e.what());
				wxMessageBox(msg, _("Load configuration into color camera"), wxICON_ERROR);
			}
		}
		else
		{
			wxString msg;
			msg.Printf(wxT("%s"), "load configuration into color camera failed: Empty configuration provided");
			wxMessageBox(msg, _("Load configuration"), wxICON_ERROR);
		}

	}

}

// Method to retieve configurations to a file in a selected folder
void BiopticColorCameraDemoFrame::OnButtonRetriveConfigToFileClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		if(config_file_directory_path_.empty())
		{
			wxMessageBox(_("File Location not SELECTED"),_("Configuration retrive"), wxICON_EXCLAMATION);
		}
		else
		{
		
			//Get current date and time
			auto current_time = std::time(nullptr);
    		auto time = *std::localtime(&current_time);

    		std::ostringstream oss;
    		oss << std::put_time(&time, "_%Y-%m-%d %H:%M:%S");
    		auto config_time = oss.str();

			std::string model_number = camera->GetModelNumber();
			retrieve_config_file_ = "/Config_file_" + model_number+ config_time +config_extension;
			std::string config_file_path = config_file_directory_path_ + retrieve_config_file_;

			try
			{
				camera_manager_client_->RetrieveConfigurationToFile(camera,config_file_path);
            	EventLog("Configuration RETRIEVED to file : " + retrieve_config_file_);
			}
			catch (std::exception& e)
			{
				wxString msg;
				msg.Printf(wxT("%s"), e.what());
				wxMessageBox(msg, _("Retrieve configuration"), wxICON_ERROR);
			}
		}
	}

}

// Method to load configurations from a file
void BiopticColorCameraDemoFrame::OnButtonLoadConfigFromFileClick(wxCommandEvent& event)
{

	(void)event;

	auto camera = GetCamera();
	if (camera)
	{
		if(load_config_file_.empty())
		{
			wxMessageBox(_("NO Configuration File Selected"),_("Configuration load"), wxICON_EXCLAMATION);
		}
		else
		{
			try
			{
				camera_manager_client_->LoadConfigurationFromFile(camera, load_config_file_);

				// Refresh UI controls
				PopulateProcessingUnitInfo(camera);
				// PopulateExtensionUnit1Info(camera);
				EventLog("Configuration LOADED from file");
			}
			catch (std::exception& e)
			{
				wxString msg;
				msg.Printf(wxT("%s"), e.what());
				wxMessageBox(msg, _("Load configuration into color camera"), wxICON_ERROR);
			}
		}

	}

}

void BiopticColorCameraDemoFrame::OnFilePickerCtrlConfigFileChanged(wxFileDirPickerEvent& event)
{
    (void)event;

    load_config_file_ = std::string(static_cast<const char*>(event.GetPath()));
    wxLogMessage("%s: path=%s", __func__, load_config_file_);
}

void BiopticColorCameraDemoFrame::OnDirPickerCtrlConfigDirChanged(wxFileDirPickerEvent& event)
{
    (void)event;

    config_file_directory_path_ = std::string(static_cast<const char*>(event.GetPath()));
    wxLogMessage("%s: path=%s", __func__, config_file_directory_path_);
}

