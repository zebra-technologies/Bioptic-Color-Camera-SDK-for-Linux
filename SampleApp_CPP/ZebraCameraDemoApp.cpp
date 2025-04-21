/***************************************************************
 * Name:      ZebraCameraDemoApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2019-08-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "ZebraCameraDemoApp.h"

#include <wx/image.h>

#include "wx_pch.h"
#include "BiopticColorCameraDemoMain.h"
//*)

IMPLEMENT_APP(ZebraCameraDemoApp);

bool ZebraCameraDemoApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	BiopticColorCameraDemoFrame* Frame = new BiopticColorCameraDemoFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
