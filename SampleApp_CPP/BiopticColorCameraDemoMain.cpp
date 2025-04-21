/***************************************************************
 * Name:      BiopticColorCameraDemoMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2021-03-01
 * Copyright: ©2021 Zebra Technologies Corp. and/or its affiliates.  All rights reserved.
 * License:
 **************************************************************/

#include "BiopticColorCameraDemoMain.h"
#include "image_event_subscription_impl.h"
#include "directory_observer.h"
#include "image_creation_observer.h"
#include <wx/msgdlg.h>

#include <wx/valnum.h>  // For wxIntegerValidator.
#include <wx/valgen.h>  // For wxGenericValidator.
#include <math.h>

//(*InternalHeaders(BiopticColorCameraDemoFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

#include <iostream>
#include <fstream>
#include <exception>
#include "wx_pch.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(BiopticColorCameraDemoFrame)
const long BiopticColorCameraDemoFrame::ID_STATICTEXT16 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHOICE5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT17 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL11 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT18 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL12 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT19 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL13 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT20 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL14 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT21 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL15 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT22 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL16 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT23 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL17 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_FILEPICKERCTRL1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON10 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON11 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_GAUGE1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON12 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL18 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICBOX2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICBOX3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICBOX4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL12 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL13 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_NOTEBOOK1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICBOX1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT24 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL19 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT25 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL20 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT26 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL21 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT27 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL22 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT28 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL23 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT29 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL24 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT30 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT15 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_DIRPICKERCTRL1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL11 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL5 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL6 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL8 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT10 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_SLIDER10 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL10 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL9 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT11 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHOICE1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT12 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHOICE2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT13 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHOICE3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATICTEXT14 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHOICE4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_BUTTON4 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL10 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL7 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL3 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL1 = wxNewId();
const long BiopticColorCameraDemoFrame::idMenuQuit = wxNewId();
const long BiopticColorCameraDemoFrame::idMenuAbout = wxNewId();
const long BiopticColorCameraDemoFrame::ID_STATUSBAR1 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_CHECKBOX_CONTRAST_AUTO = wxNewId();
const long BiopticColorCameraDemoFrame::ID_PANEL20 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_TEXTCTRL25 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_FILEPICKERCTRL2= wxNewId();
const long BiopticColorCameraDemoFrame::ID_DIRPICKERCTRL2 = wxNewId();
const long BiopticColorCameraDemoFrame::ID_LED2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(BiopticColorCameraDemoFrame,wxFrame)
    //(*EventTable(BiopticColorCameraDemoFrame)
    //*)
END_EVENT_TABLE()

BiopticColorCameraDemoFrame::BiopticColorCameraDemoFrame(wxWindow* parent,wxWindowID id)
{
	(void)id;
    //(*Initialize(BiopticColorCameraDemoFrame)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer11;
    wxFlexGridSizer* FlexGridSizer12;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer17;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer19;
    wxFlexGridSizer* FlexGridSizer20;

    wxFlexGridSizer* FlexGridSizer_main;
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxStaticBoxSizer* StaticBoxSizer2;
    wxStaticBoxSizer* StaticBoxSizer3;
    wxStaticBoxSizer* StaticBoxSizer4;
    wxStaticBoxSizer* StaticBoxSizer5;
    wxStaticBoxSizer* StaticBoxSizer6;
    wxStaticBoxSizer* StaticBoxSizer7;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1360,864));
    SetMinSize(wxSize(1360,900));
    SetMaxSize(wxSize(1360,900));
    Panel_main = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer_main = new wxFlexGridSizer(0, 2, 0, 0);
    Panel_left = new wxPanel(Panel_main, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer1 = new wxFlexGridSizer(3, 1, 0, 0);
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_left, _("Camera Properties"));
    Panel_camera_properties = new wxPanel(Panel_left, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    FlexGridSizer10 = new wxFlexGridSizer(8, 3, 0, 0);
    StaticText16 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT16, _("Selected Camera"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT16"));
    FlexGridSizer10->Add(StaticText16, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    choice_camera_id = new wxChoice(Panel_camera_properties, ID_CHOICE5, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    FlexGridSizer10->Add(choice_camera_id, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10->Add(-1,-1,1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticText17 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT17, _("Serial Number"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT17"));
    FlexGridSizer10->Add(StaticText17, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 18);
    text_serial_number = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL11, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL11"));
    FlexGridSizer10->Add(text_serial_number, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText18 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT18, _("Model Number"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT18"));
    FlexGridSizer10->Add(StaticText18, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_model_number = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL12, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    FlexGridSizer10->Add(text_model_number, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText19 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT19, _("Date of Manufacture"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT19"));
    FlexGridSizer10->Add(StaticText19, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_dom = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL13, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
    FlexGridSizer10->Add(text_dom, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText20 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT20, _("Date of Service"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT20"));
    FlexGridSizer10->Add(StaticText20, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_dos = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL14, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL14"));
    FlexGridSizer10->Add(text_dos, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    button_snaposhot = new wxButton(Panel_camera_properties, ID_BUTTON6, _("Snapshot"), wxDefaultPosition, wxSize(110,30), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    FlexGridSizer10->Add(button_snaposhot, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    StaticText21 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT21, _("Date of First Program"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT21"));
    FlexGridSizer10->Add(StaticText21, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_dofp = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL15, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL15"));
    FlexGridSizer10->Add(text_dofp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    button_write_to_flash = new wxButton(Panel_camera_properties, ID_BUTTON7, _("Write to Flash"), wxDefaultPosition, wxSize(110,30), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    FlexGridSizer10->Add(button_write_to_flash, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    StaticText22 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT22, _("Firmware Version"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT22"));
    FlexGridSizer10->Add(StaticText22, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_firmware_version = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL16, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
    FlexGridSizer10->Add(text_firmware_version, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    button_set_default = new wxButton(Panel_camera_properties, ID_BUTTON8, _("Set Default"), wxDefaultPosition, wxSize(110,30), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    FlexGridSizer10->Add(button_set_default, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    StaticText23 = new wxStaticText(Panel_camera_properties, ID_STATICTEXT23, _("Hardware Version"), wxDefaultPosition, wxSize(150,20), 0, _T("ID_STATICTEXT23"));
    FlexGridSizer10->Add(StaticText23, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 18);
    text_hardware_version = new wxTextCtrl(Panel_camera_properties, ID_TEXTCTRL17, wxEmptyString, wxDefaultPosition, wxSize(200,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
    FlexGridSizer10->Add(text_hardware_version, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    button_reboot = new wxButton(Panel_camera_properties, ID_BUTTON9, _("Reboot"), wxDefaultPosition, wxSize(110,30), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    FlexGridSizer10->Add(button_reboot, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    Panel_camera_properties->SetSizer(FlexGridSizer10);
    FlexGridSizer10->Fit(Panel_camera_properties);
    FlexGridSizer10->SetSizeHints(Panel_camera_properties);
    StaticBoxSizer1->Add(Panel_camera_properties, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_left, _("Firmware Update"));
    Panel_Firmware_update = new wxPanel(Panel_left, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer11 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer12 = new wxFlexGridSizer(1, 3, 0, 0);
    filepicker_firmware_file = new wxFilePickerCtrl(Panel_Firmware_update, ID_FILEPICKERCTRL1, wxEmptyString, _("Select Firmware file"), wxEmptyString, wxDefaultPosition, wxSize(255,29), wxFLP_FILE_MUST_EXIST|wxFLP_OPEN, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
    FlexGridSizer12->Add(filepicker_firmware_file, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    button_update_firmware = new wxButton(Panel_Firmware_update, ID_BUTTON10, _("Update"), wxDefaultPosition, wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    FlexGridSizer12->Add(button_update_firmware, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 20);
    button_launch_fw = new wxButton(Panel_Firmware_update, ID_BUTTON11, _("Launch"), wxDefaultPosition, wxSize(100,30), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    FlexGridSizer12->Add(button_launch_fw, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 17);
    FlexGridSizer11->Add(FlexGridSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer13 = new wxFlexGridSizer(1, 2, 0, 0);
    GaugeFirmwareDownloadProgress = new wxGauge(Panel_Firmware_update, ID_GAUGE1, 100, wxDefaultPosition, wxSize(360,14), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    FlexGridSizer13->Add(GaugeFirmwareDownloadProgress, 1, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 15);
    button_cancel_fu = new wxButton(Panel_Firmware_update, ID_BUTTON12, _("Cancel"), wxDefaultPosition, wxSize(105,30), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    FlexGridSizer13->Add(button_cancel_fu, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 24);
    FlexGridSizer11->Add(FlexGridSizer13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_Firmware_update->SetSizer(FlexGridSizer11);
    FlexGridSizer11->Fit(Panel_Firmware_update);
    FlexGridSizer11->SetSizeHints(Panel_Firmware_update);
    StaticBoxSizer2->Add(Panel_Firmware_update, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_left, _("Event Log and Tower Platter Images"));
    Notebook1 = new wxNotebook(Panel_left, ID_NOTEBOOK1, wxDefaultPosition, wxSize(550,340), 0, _T("ID_NOTEBOOK1"));
    Panel6 = new wxPanel(Notebook1, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    FlexGridSizer14 = new wxFlexGridSizer(1, 1, 0, 0);
    TextCtrlEventLog = new wxTextCtrl(Panel6, ID_TEXTCTRL18, wxEmptyString, wxDefaultPosition, wxSize(550,300), wxTE_MULTILINE|wxVSCROLL|wxHSCROLL|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL18"));
    FlexGridSizer14->Add(TextCtrlEventLog, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel6->SetSizer(FlexGridSizer14);
    FlexGridSizer14->Fit(Panel6);
    FlexGridSizer14->SetSizeHints(Panel6);
    Panel7 = new wxPanel(Notebook1, ID_PANEL12, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL12"));
    FlexGridSizer17 = new wxFlexGridSizer(2, 2, 0, 0);
    StaticBox2 = new wxStaticBox(Panel7, ID_STATICBOX2, _("Tower Image"), wxDefaultPosition, wxSize(260,145), 0, _T("ID_STATICBOX2"));
    FlexGridSizer17->Add(StaticBox2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBox3 = new wxStaticBox(Panel7, ID_STATICBOX3, _("Decode Image"), wxDefaultPosition, wxSize(260,145), 0, _T("ID_STATICBOX3"));
    FlexGridSizer17->Add(StaticBox3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBox4 = new wxStaticBox(Panel7, ID_STATICBOX4, _("Platter Image"), wxDefaultPosition, wxSize(260,145), 0, _T("ID_STATICBOX4"));
    FlexGridSizer17->Add(StaticBox4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel7->SetSizer(FlexGridSizer17);
    FlexGridSizer17->Fit(Panel7);
    FlexGridSizer17->SetSizeHints(Panel7);
    Panel8 = new wxPanel(Notebook1, ID_PANEL13, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL13"));
    FlexGridSizer18 = new wxFlexGridSizer(1, 1, 0, 0);
    TextCtrlConfiguration = new wxTextCtrl(Panel8, ID_TEXTCTRL25, wxEmptyString, wxDefaultPosition, wxSize(550,300), wxTE_MULTILINE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL25"));
    FlexGridSizer18->Add(TextCtrlConfiguration, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel8->SetSizer(FlexGridSizer18);
    FlexGridSizer18->Fit(Panel8);
    FlexGridSizer18->SetSizeHints(Panel8);
    Notebook1->AddPage(Panel6, _("Event Log"), false);
    Notebook1->AddPage(Panel7, _("Tower Platter Images"), false);
    Notebook1->AddPage(Panel8, _("Configuration Retrieve/Load"), false);
    StaticBoxSizer3->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(StaticBoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_left->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel_left);
    FlexGridSizer1->SetSizeHints(Panel_left);
    FlexGridSizer_main->Add(Panel_left, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_right = new wxPanel(Panel_main, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    FlexGridSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
    StaticBoxSizer4 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_right, _("Event Viewer"));
    Panel2 = new wxPanel(Panel_right, ID_PANEL8, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL8"));
    FlexGridSizer15 = new wxFlexGridSizer(1, 3, 0, 0);
    PanelVideoDisplay = new VideoPanel(Panel2, ID_PANEL20, wxDefaultPosition, wxSize(458,269), wxTAB_TRAVERSAL, _T("ID_PANEL20"));
    FlexGridSizer15->Add(PanelVideoDisplay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer15->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer16 = new wxFlexGridSizer(9, 2, 0, 0);
    StaticText24 = new wxStaticText(Panel2, ID_STATICTEXT24, _("Event Type"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT24"));
    FlexGridSizer16->Add(StaticText24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlEventType = new wxTextCtrl(Panel2, ID_TEXTCTRL19, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL19"));
    FlexGridSizer16->Add(TextCtrlEventType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText25 = new wxStaticText(Panel2, ID_STATICTEXT25, _("Format"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT25"));
    FlexGridSizer16->Add(StaticText25, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlFormat = new wxTextCtrl(Panel2, ID_TEXTCTRL20, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL20"));
    FlexGridSizer16->Add(TextCtrlFormat, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText26 = new wxStaticText(Panel2, ID_STATICTEXT26, _("Size (Kb)"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT26"));
    FlexGridSizer16->Add(StaticText26, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSize = new wxTextCtrl(Panel2, ID_TEXTCTRL21, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL21"));
    FlexGridSizer16->Add(TextCtrlSize, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText27 = new wxStaticText(Panel2, ID_STATICTEXT27, _("Time Stamp"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT27"));
    FlexGridSizer16->Add(StaticText27, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlTimeStamp = new wxTextCtrl(Panel2, ID_TEXTCTRL22, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL22"));
    FlexGridSizer16->Add(TextCtrlTimeStamp, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText28 = new wxStaticText(Panel2, ID_STATICTEXT28, _("Image Resolution"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT28"));
    FlexGridSizer16->Add(StaticText28, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlImageResolution = new wxTextCtrl(Panel2, ID_TEXTCTRL23, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL23"));
    FlexGridSizer16->Add(TextCtrlImageResolution, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText29 = new wxStaticText(Panel2, ID_STATICTEXT29, _("Decode Data"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT29"));
    FlexGridSizer16->Add(StaticText29, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlDecodeData = new wxTextCtrl(Panel2, ID_TEXTCTRL24, wxEmptyString, wxDefaultPosition, wxSize(130,27), 0, wxDefaultValidator, _T("ID_TEXTCTRL24"));
    FlexGridSizer16->Add(TextCtrlDecodeData, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText30 = new wxStaticText(Panel2, ID_STATICTEXT30, _("Device Awake"), wxDefaultPosition, wxSize(122,17), 0, _T("ID_STATICTEXT30"));
    FlexGridSizer16->Add(StaticText30, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    LedDeviceAwake = new wxLed(Panel2,ID_LED2,wxColour(128,128,128),wxColour(0,255,0),wxColour(255,0,0),wxDefaultPosition,wxDefaultSize);
    LedDeviceAwake->SwitchOn();
    FlexGridSizer16->Add(LedDeviceAwake, 1, wxALL|wxEXPAND, 5);
    FlexGridSizer15->Add(FlexGridSizer16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer15);
    FlexGridSizer15->Fit(Panel2);
    FlexGridSizer15->SetSizeHints(Panel2);
    StaticBoxSizer4->Add(Panel2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer7 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_right, _("Camera Image Event Controllers"));
    Panel5 = new wxPanel(Panel_right, ID_PANEL11, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL11"));
    FlexGridSizer8 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer9 = new wxFlexGridSizer(3, 5, 0, 0);
    CheckBoxContinuousEvents = new wxCheckBox(Panel5, ID_CHECKBOX3, _("Continuous"), wxDefaultPosition, wxSize(170,24), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBoxContinuousEvents->SetValue(false);
    FlexGridSizer9->Add(CheckBoxContinuousEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxSnapshotEvents = new wxCheckBox(Panel5, ID_CHECKBOX4, _("Snapshot"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBoxSnapshotEvents->SetValue(false);
    FlexGridSizer9->Add(CheckBoxSnapshotEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxDecodeEvents = new wxCheckBox(Panel5, ID_CHECKBOX5, _("Decode"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBoxDecodeEvents->SetValue(false);
    FlexGridSizer9->Add(CheckBoxDecodeEvents, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox6 = new wxCheckBox(Panel5, ID_CHECKBOX6, _("Produce"), wxDefaultPosition, wxSize(145,24), 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    FlexGridSizer9->Add(CheckBox6, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    checkbox_decode_session = new wxCheckBox(Panel5, ID_CHECKBOX7, _("Decode Session"), wxDefaultPosition, wxSize(127,24), 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    checkbox_decode_session->SetValue(false);
    FlexGridSizer9->Add(checkbox_decode_session, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox8 = new wxCheckBox(Panel5, ID_CHECKBOX8, _("Detect Bounding Box"), wxDefaultPosition, wxSize(170,24), 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox8->SetValue(false);
    FlexGridSizer9->Add(CheckBox8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText15 = new wxStaticText(Panel5, ID_STATICTEXT15, _("Location"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT15"));
    FlexGridSizer9->Add(StaticText15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DirPickerCtrl1 = new wxDirPickerCtrl(Panel5, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    FlexGridSizer9->Add(DirPickerCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxSaveImages = new wxCheckBox(Panel5, ID_CHECKBOX9, _("Auto save images"), wxDefaultPosition, wxSize(137,24), 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBoxSaveImages->SetValue(false);
    FlexGridSizer9->Add(CheckBoxSaveImages, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button5 = new wxButton(Panel5, ID_BUTTON5, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    FlexGridSizer9->Add(Button5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 3);
    FlexGridSizer8->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel5->SetSizer(FlexGridSizer8);
    FlexGridSizer8->Fit(Panel5);
    FlexGridSizer8->SetSizeHints(Panel5);
    StaticBoxSizer7->Add(Panel5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticBoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer5 = new wxStaticBoxSizer(wxHORIZONTAL, Panel_right, _("Camera Configuration"));
    Panel1 = new wxPanel(Panel_right, ID_PANEL7, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
    Panel3 = new wxPanel(Panel1, ID_PANEL9, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL9"));
    FlexGridSizer4 = new wxFlexGridSizer(10, 4, 0, 0);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Brightness"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT1"));
    FlexGridSizer4->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderBrightness = new wxSlider(Panel3, ID_SLIDER1, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_brightness), _T("ID_SLIDER1"));
    FlexGridSizer4->Add(SliderBrightness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlBrightness = new wxTextCtrl(Panel3, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_brightness), _T("ID_TEXTCTRL1"));
    FlexGridSizer4->Add(TextCtrlBrightness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel3, ID_STATICTEXT2, _("Contrast"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT2"));
    FlexGridSizer4->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderContrast = new wxSlider(Panel3, ID_SLIDER2, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_contrast), _T("ID_SLIDER2"));
    FlexGridSizer4->Add(SliderContrast, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlContrast= new wxTextCtrl(Panel3, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_contrast), _T("ID_TEXTCTRL2"));
    FlexGridSizer4->Add(TextCtrlContrast, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(Panel3, ID_STATICTEXT3, _("Saturation"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT3"));
    FlexGridSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSaturation = new wxSlider(Panel3, ID_SLIDER3, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_saturation), _T("ID_SLIDER3"));
    FlexGridSizer4->Add(SliderSaturation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSaturation = new wxTextCtrl(Panel3, ID_TEXTCTRL3, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_saturation), _T("ID_TEXTCTRL3"));
    FlexGridSizer4->Add(TextCtrlSaturation, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel3, ID_STATICTEXT4, _("Sharpness"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT4"));
    FlexGridSizer4->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderSharpness = new wxSlider(Panel3, ID_SLIDER4, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_sharpness), _T("ID_SLIDER4"));
    FlexGridSizer4->Add(SliderSharpness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlSharpness = new wxTextCtrl(Panel3, ID_TEXTCTRL4, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_sharpness), _T("ID_TEXTCTRL4"));
    FlexGridSizer4->Add(TextCtrlSharpness, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText5 = new wxStaticText(Panel3, ID_STATICTEXT5, _("Gamma"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT5"));
    FlexGridSizer4->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderGamma = new wxSlider(Panel3, ID_SLIDER5, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_gamma), _T("ID_SLIDER5"));
    FlexGridSizer4->Add(SliderGamma, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlGamma = new wxTextCtrl(Panel3, ID_TEXTCTRL5, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_gamma), _T("ID_TEXTCTRL5"));
    FlexGridSizer4->Add(TextCtrlGamma, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText6 = new wxStaticText(Panel3, ID_STATICTEXT6, _("White Balance (Blue)"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT6"));
    FlexGridSizer4->Add(StaticText6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderWhiteBalanceBlue = new wxSlider(Panel3, ID_SLIDER6, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_wb_blue), _T("ID_SLIDER6"));
    FlexGridSizer4->Add( SliderWhiteBalanceBlue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlWhiteBalanceBlue = new wxTextCtrl(Panel3, ID_TEXTCTRL6, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxFloatingPointValidator<float>(&property_wb_blue_in_float, wxNUM_VAL_NO_TRAILING_ZEROES), _T("ID_TEXTCTRL6"));
    FlexGridSizer4->Add(TextCtrlWhiteBalanceBlue, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxWhiteBalanceAuto = new wxCheckBox(Panel3, ID_CHECKBOX1, _("Auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBoxWhiteBalanceAuto->SetValue(false);
    FlexGridSizer4->Add(CheckBoxWhiteBalanceAuto, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText7 = new wxStaticText(Panel3, ID_STATICTEXT7, _("White Balance (Red)"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT7"));
    FlexGridSizer4->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderWhiteBalanceRed = new wxSlider(Panel3, ID_SLIDER7, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_wb_red), _T("ID_SLIDER7"));
    FlexGridSizer4->Add(SliderWhiteBalanceRed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlWhiteBalanceRed = new wxTextCtrl(Panel3, ID_TEXTCTRL7, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxFloatingPointValidator<float>(&property_wb_red_in_float, wxNUM_VAL_NO_TRAILING_ZEROES), _T("ID_TEXTCTRL7"));
    FlexGridSizer4->Add(TextCtrlWhiteBalanceRed, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText8 = new wxStaticText(Panel3, ID_STATICTEXT8, _("Backlight"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT8"));
    FlexGridSizer4->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderBacklight = new wxSlider(Panel3, ID_SLIDER8, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_backlight), _T("ID_SLIDER8"));
    FlexGridSizer4->Add(SliderBacklight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlBacklight = new wxTextCtrl(Panel3, ID_TEXTCTRL8, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_backlight), _T("ID_TEXTCTRL8"));
    FlexGridSizer4->Add(TextCtrlBacklight, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText9 = new wxStaticText(Panel3, ID_STATICTEXT9, _("Gain"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT9"));
    FlexGridSizer4->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderGain = new wxSlider(Panel3, ID_SLIDER9, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_gain), _T("ID_SLIDER9"));
    FlexGridSizer4->Add(SliderGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlGain = new wxTextCtrl(Panel3, ID_TEXTCTRL9, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_gain), _T("ID_TEXTCTRL9"));
    FlexGridSizer4->Add(TextCtrlGain, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText10 = new wxStaticText(Panel3, ID_STATICTEXT10, _("Exposure"), wxDefaultPosition, wxSize(140,17), 0, _T("ID_STATICTEXT10"));
    FlexGridSizer4->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SliderAbsoluteExposureTime = new wxSlider(Panel3, ID_SLIDER10, 0, 0, 100, wxDefaultPosition, wxSize(150,27), 0, wxGenericValidator(&property_abs_exposure_time), _T("ID_SLIDER10"));
    FlexGridSizer4->Add(SliderAbsoluteExposureTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlAbsoluteExposureTime = new wxTextCtrl(Panel3, ID_TEXTCTRL10, wxEmptyString, wxDefaultPosition, wxSize(55,27), 0, wxIntegerValidator<int>(&property_abs_exposure_time), _T("ID_TEXTCTRL10"));
    FlexGridSizer4->Add(TextCtrlAbsoluteExposureTime, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckBoxExposureTimeAuto = new wxCheckBox(Panel3, ID_CHECKBOX2, _("Auto"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBoxExposureTimeAuto->SetValue(false);
    FlexGridSizer4->Add(CheckBoxExposureTimeAuto, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel3->SetSizer(FlexGridSizer4);
    FlexGridSizer4->Fit(Panel3);
    FlexGridSizer4->SetSizeHints(Panel3);
    FlexGridSizer3->Add(Panel3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel4 = new wxPanel(Panel1, ID_PANEL10, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL10"));
    FlexGridSizer5 = new wxFlexGridSizer(3, 1, 0, 0);
    FlexGridSizer6 = new wxFlexGridSizer(4, 2, 0, 0);
    StaticText11 = new wxStaticText(Panel4, ID_STATICTEXT11, _("Video Mode"), wxDefaultPosition, wxSize(130,17), 0, _T("ID_STATICTEXT11"));
    FlexGridSizer6->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceVideoMode = new wxChoice(Panel4, ID_CHOICE1, wxDefaultPosition, wxSize(130,31), 0, 0, 0, wxGenericValidator(&property_videomode), _T("ID_CHOICE1"));
    ChoiceVideoMode->Append(_("OFF"));
    ChoiceVideoMode->Append(_("WAKEUP"));
    ChoiceVideoMode->Append(_("CONTINUOUS"));
    FlexGridSizer6->Add(ChoiceVideoMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText12 = new wxStaticText(Panel4, ID_STATICTEXT12, _("Illumination Mode"), wxDefaultPosition, wxSize(130,17), 0, _T("ID_STATICTEXT12"));
    FlexGridSizer6->Add(StaticText12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoiceIlluminationMode = new wxChoice(Panel4, ID_CHOICE2, wxDefaultPosition, wxSize(130,31), 0, 0, 0, wxGenericValidator(&property_illuminationmode), _T("ID_CHOICE2"));
    ChoiceIlluminationMode->Append(_("Standard"));
    ChoiceIlluminationMode->Append(_("Always On"));
    ChoiceIlluminationMode->Append(_("Always Off"));
    FlexGridSizer6->Add(ChoiceIlluminationMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText13 = new wxStaticText(Panel4, ID_STATICTEXT13, _("Image Resolution"), wxDefaultPosition, wxSize(130,17), 0, _T("ID_STATICTEXT13"));
    FlexGridSizer6->Add(StaticText13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice3 = new wxChoice(Panel4, ID_CHOICE3, wxDefaultPosition, wxSize(130,31), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    FlexGridSizer6->Add(Choice3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText14 = new wxStaticText(Panel4, ID_STATICTEXT14, _("Power User Mode"), wxDefaultPosition, wxSize(130,17), 0, _T("ID_STATICTEXT14"));
    FlexGridSizer6->Add(StaticText14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChoicePowerUserMode = new wxChoice(Panel4, ID_CHOICE4, wxDefaultPosition, wxSize(130,31), 0, 0, 0, wxGenericValidator(&property_powerusermode), _T("ID_CHOICE4"));
    ChoicePowerUserMode->Append(_("DISABLE"));
    ChoicePowerUserMode->Append(_("ENABLE"));
    FlexGridSizer6->Add(ChoicePowerUserMode, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6 = new wxStaticBoxSizer(wxHORIZONTAL, Panel4, _("Load and Retrieve Configurations"));
    FlexGridSizer7 = new wxFlexGridSizer(4, 1, 0, 0);
    Button1 = new wxButton(Panel4, ID_BUTTON1, _("Retrieve Configuration"), wxDefaultPosition, wxSize(230,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel4, ID_BUTTON2, _("Load Configuration"), wxDefaultPosition, wxSize(230,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer20 = new wxFlexGridSizer(1, 2, 0, 0);
    DirPickerCtrl2 = new wxDirPickerCtrl(Panel4, ID_DIRPICKERCTRL2, wxEmptyString, wxEmptyString, wxDefaultPosition, wxSize(165,29), wxDIRP_DIR_MUST_EXIST, wxDefaultValidator, _T("ID_DIRPICKERCTRL2"));
    FlexGridSizer20->Add(DirPickerCtrl2, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 8);
    Button3 = new wxButton(Panel4, ID_BUTTON3, _("Retrieve to File"), wxDefaultPosition, wxSize(115,29), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer20->Add(Button3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer7->Add(FlexGridSizer20, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19 = new wxFlexGridSizer(1, 2, 0, 0);
    filepicker_load_config = new wxFilePickerCtrl(Panel4, ID_FILEPICKERCTRL2, wxEmptyString, _("Select Configuration File"),  wxEmptyString, wxDefaultPosition, wxSize(165,29), wxFLP_FILE_MUST_EXIST|wxFLP_OPEN, wxDefaultValidator, _T("ID_FILEPICKERCTRL2"));
    FlexGridSizer19->Add(filepicker_load_config, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    Button4 = new wxButton(Panel4, ID_BUTTON4, _("Load from File"), wxDefaultPosition, wxSize(115,29), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer19->Add(Button4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer7->Add(FlexGridSizer19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticBoxSizer6->Add(FlexGridSizer7, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer5->Add(StaticBoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel4->SetSizer(FlexGridSizer5);
    FlexGridSizer5->Fit(Panel4);
    FlexGridSizer5->SetSizeHints(Panel4);
    FlexGridSizer3->Add(Panel4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel1);
    FlexGridSizer3->SetSizeHints(Panel1);
    StaticBoxSizer5->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer2->Add(StaticBoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_right->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel_right);
    FlexGridSizer2->SetSizeHints(Panel_right);
    FlexGridSizer_main->Add(Panel_right, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel_main->SetSizer(FlexGridSizer_main);
    FlexGridSizer_main->Fit(Panel_main);
    FlexGridSizer_main->SetSizeHints(Panel_main);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);



    Connect(ID_CHOICE5,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnChoiceSelectedCameraSelect);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnClose);
    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderBrightnessCmdScrollChanged);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlBrightnessText);
    Connect(ID_SLIDER2,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderContrastCmdScrollChanged);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlContrastText);
    Connect(ID_SLIDER3,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderSaturationCmdScrollChanged);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlSaturationText);
    Connect(ID_SLIDER4,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderSharpnessCmdScrollChanged);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlSharpnessText);
    Connect(ID_SLIDER5,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderGammaCmdScrollChanged);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlGammaText);
    Connect(ID_SLIDER6,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderWhiteBalanceBlueCmdScrollChanged);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlWhiteBalanceBlueText);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnCheckBoxWhiteBalanceAutoClick);
    Connect(ID_SLIDER7,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderWhiteBalanceRedCmdScrollChanged);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlWhiteBalanceRedText);
    Connect(ID_SLIDER8,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderBacklightCmdScrollChanged);
    Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlBacklightText);
    Connect(ID_SLIDER9,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderGainCmdScrollChanged);
    Connect(ID_TEXTCTRL9,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlGainText);
    Connect(ID_SLIDER10,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnSliderAbsoluteExposureTimeCmdScrollChanged);
    Connect(ID_TEXTCTRL10,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnTextCtrlAbsoluteExposureTimeText);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnCheckBoxExposureTimeAutoClick);
    Connect(ID_FILEPICKERCTRL1,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnFilePickerCtrlFirmwareFileChanged);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonUpdateClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonLaunchClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonCancelClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonCaptureSnapshotClick);
    Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnCheckBoxSnapshotEventsClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonRetriveConfigClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonLoadConfigClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonRetriveConfigToFileClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnButtonLoadConfigFromFileClick);
    Connect(ID_FILEPICKERCTRL2,wxEVT_COMMAND_FILEPICKER_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnFilePickerCtrlConfigFileChanged);
    Connect(ID_DIRPICKERCTRL2,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnDirPickerCtrlConfigDirChanged);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnChoiceVideoModeSelect);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnChoiceIlluminationModeSelect);
    Connect(ID_CHOICE4,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnChoicePowerUserModeSelection);
    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&BiopticColorCameraDemoFrame::OnCheckBoxContinuousEventsClick);



    // Set logger to console.
    logger_ = new wxLogStream(&std::cout);
    logger_->SetLogLevel(wxLOG_FatalError);
    wxLog::SetActiveTarget(logger_);

    wxLogMessage("%s", __func__);

    camera_manager_client_ = zebra::camera_sdk::CreateZebraCameraManagerClient();

    ClearAllCameraProperties();

    // Create PnP listener.
    CreatePnpListeners();

    // Create firmware download event listener.
    CreateFirmwareDownloadEventListener();

    // Create image event listeners.
    CreateImageEventListeners();

    auto_white_balance_monitor_timer_.SetOwner(this);

    // Enumerate already attched cameras.
    QueueAlreadyAttachedCameraEvents();

}

BiopticColorCameraDemoFrame::~BiopticColorCameraDemoFrame()
{
    //(*Destroy(BiopticColorCameraDemoFrame)
    //*)

	wxLogMessage("%s", __func__);
}

void BiopticColorCameraDemoFrame::OnAbout(wxCommandEvent& event)
{
    (void)event;
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void BiopticColorCameraDemoFrame::OnChoiceSelectedCameraSelect(wxCommandEvent& event)
{

    unsigned int selected_camera = event.GetSelection();

    wxLogMessage("%s: selected=%d", __func__, selected_camera);

    for (unsigned int i = 0; i < choice_camera_id->GetCount(); i++)
    {
        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                            choice_camera_id->GetClientData(i);
        wxLogMessage("%s: vid=%x, pid=%x, sn=%s, path=%s, selected=%d, cam=%p",
        __func__,
        client_data->first.vid, client_data->first.pid, client_data->first.serial_number, client_data->first.device_path,
        selected_camera,
        client_data->second.get());

        if (i == selected_camera)
        {
            // Found the selected camera information. Create the camera.
            try
            {
                std::shared_ptr<ZebraCameraClient> camera = camera_manager_client_->CreateZebraCamera(client_data->first);  
                client_data->second = camera;

               
                ClearAllCameraProperties();

                //Populate the properties for the new camera.
                PopulateCameraProperties(camera);
            }
            catch (std::exception& e)
            {
                wxMessageBox(e.what(), "Error");
            }
        }
        else
        {
            // Any other camera will be released.
            client_data->second = nullptr;
        }
    }

}


std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> BiopticColorCameraDemoFrame::GetCamera()
{

    std::shared_ptr<ZebraCameraClient> camera = nullptr;

    int index = choice_camera_id->GetSelection();

    if (wxNOT_FOUND != index)
    {
        std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
            *client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
                            choice_camera_id->GetClientData(index);
        if (client_data)
        {
                camera = client_data->second;
            }
        }

    return camera;
}

void BiopticColorCameraDemoFrame::PopulateCameraProperties(std::shared_ptr<zebra::camera_sdk::ZebraCameraClient> camera)
{
    wxLogMessage("%s", __func__);

    if (camera)
    {
        PopulateCameraAssetTrackingInfo(camera);
        PopulateProcessingUnitInfo(camera);
        PopulateVideoProfiles(camera);
        PopulateExtensionUnit1Info(camera);
        PopulateDeviceAwake(camera);
    }
}

void BiopticColorCameraDemoFrame::ClearAllCameraProperties()
{

    ClearCameraAssetTrackingInfo();
    ClearProcessingUnitInfo();
    ClearVideoEvents();
    ClearExtensionUnit1Info();
    ClearDeviceAwakeInfo();

}
/** This method is responsible for reseting the progress bar of firmware update during camera detach and reboot events*/
void BiopticColorCameraDemoFrame::ResetFirmwareUpdateProgressBar()
{

    GaugeFirmwareDownloadProgress->SetValue(0);
}


void BiopticColorCameraDemoFrame::ReleaseCameras()
{
	for (unsigned int i = 0; i < choice_camera_id->GetCount(); i++)
	{
		std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>
			*client_data = (std::pair<zebra::DeviceInfo, std::shared_ptr<ZebraCameraClient>>*)
				choice_camera_id->GetClientData(i);
		client_data->second = nullptr;
	}
}

void BiopticColorCameraDemoFrame::OnClose(wxCloseEvent& event)
{

	(void)event;

    wxLogMessage("%s", __func__);

    // Release image event listeners.
    ReleaseImageEventListeners();

    // Release firmware download event listener.
    ReleaseFirmwareDownloadEventListener();

    // Release PnP listener.
    ReleasePnpListeners();

    // Release cameras so that claimed interfaces (control and streaming) are released.
    ReleaseCameras();

    //delete logger_;

    if (listening_started_)
    {
        // stop listening to directory monochrome
        dir_observer_->StopObserving();
    }

    Destroy();

}

void BiopticColorCameraDemoFrame::EventLog(const std::string& logMessage, int propertyValue)
{
    auto value = std::to_string(propertyValue);

    TextCtrlEventLog->WriteText(logMessage.c_str());
    TextCtrlEventLog->WriteText(value);
    TextCtrlEventLog->WriteText("\n");

}

void BiopticColorCameraDemoFrame::EventLog(const std::string& logMessage)
{
    TextCtrlEventLog->WriteText(logMessage.c_str());
    TextCtrlEventLog->WriteText("\n");
}