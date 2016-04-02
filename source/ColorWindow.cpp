// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#include <Application.h>
#include <ColorControl.h>

#include "Colors.h"
#include "ColorWindow.h"
#include "MsgVals.h"


#include "SettingsClass.h"

//Global settings
extern SettingsClass		settings;


ColorWindow::ColorWindow(BWindow *hand,BRect frame)
	: BWindow(frame, "Color Settings",B_FLOATING_WINDOW,B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_WILL_ACCEPT_FIRST_CLICK)
{
	BRect		MainAppFrame;
	handler = hand;
	
    MainAppFrame =	handler->Frame();
	MoveTo(MainAppFrame.left - 2,MainAppFrame.top + handler->Bounds().Height() + 9);
				 		 
	colorControl = new BColorControl(BPoint(1,1),B_CELLS_32x8,6,"Color Selector",
			 						 new BMessage(SPEAKIT_COLORWIN_CHANGE),false);

	colorControl->SetViewColor(BeBackgroundGrey);
	
	colorControl->SetValue(settings.FontColor);
	
	AddChild(colorControl);
	
	Show();
}

//////////////////////////////////////////////////////////////////////////////////

void ColorWindow::MessageReceived(BMessage *message)
{
	rgb_color	color;

	switch(message->what)
	{
	
	 case SPEAKIT_COLORWIN_CHANGE:
		color = colorControl->ValueAsColor();
		
		settings.FontColor.red   = color.red;
		settings.FontColor.green = color.green;
		settings.FontColor.blue  = color.blue;
		settings.FontColor.alpha = color.alpha;						
		handler->PostMessage(message);	 	
	 	break;
	 	
	 default:
	 	BWindow::MessageReceived(message);
	 	break;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void ColorWindow::Quit() 
{
	// alert the application of our impending demise 
	be_app->PostMessage(SPEAKIT_COLORWIN_QUIT);
	BWindow::Quit();
}
