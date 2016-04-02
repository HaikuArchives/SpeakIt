// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#include <Application.h>
#include <TextControl.h>
#include <TextView.h>
#include <CheckBox.h>
#include <Box.h>
#include <Slider.h>

#include <stdio.h>
#include <stdlib.h>

#include "Colors.h"
#include "SetWindow.h"
#include "MsgVals.h"

#include "SettingsClass.h"

//Global settings
extern SettingsClass		settings;


SetWindow::SetWindow(BWindow *hand)
	: BWindow(BRect(600,50,770,200), "Settings", B_FLOATING_WINDOW, 
			  B_NOT_RESIZABLE | B_NOT_ZOOMABLE | B_WILL_ACCEPT_FIRST_CLICK)
{
	BRect		MainAppFrame;
	char 		buf[3];
	handler = hand;
	
    MainAppFrame =	handler->Frame();
	MoveTo(MainAppFrame.right - 70,MainAppFrame.top + handler->Bounds().Height() + 9);
	
	BView *sv = new BView(Bounds(), "settingview", B_FOLLOW_ALL, B_WILL_DRAW);

	// fancy border box 
	BBox *bb = new BBox(BRect(5,10,Bounds().Width()-5,Bounds().Height()-10));
	sv->AddChild(bb);
	
	// create sliders for mass, drag, etc... 
	volume = new BSlider(BRect(5,20,155,50), "Volume", "Volume",new BMessage(SPEAKIT_VOL_CHANGE), 0, 10);
	
	rgb_color blue ={5,5,255,55};
	
	volume->UseFillColor(true,&blue);
	volume->SetStyle(B_BLOCK_THUMB);
	volume->SetLimitLabels("Min", "Max");
	volume->SetValue(settings.Volume * 10);
	bb->AddChild(volume);


	// create checkbox for highlight
	highlight = new BCheckBox(BRect(5,70,100,100), "Highlight", "Highlight Word",new BMessage(SPEAKIT_HIGHLIGHT_CHANGE));
	highlight->SetValue(settings.Highlight);
	bb->AddChild(highlight);
	
	//Create textcontrol to input number of characters of text
	textlength = new BTextControl(BRect(5,105,115,135),"maxtext","Max Characters","",new BMessage(SPEAKIT_CHAR_LEN_CHANGE),B_FOLLOW_NONE);
	sprintf(buf,"%d",settings.MaxTextLength);
	textlength->SetText(buf);
	textView = textlength->TextView();
	textView->SetMaxBytes(4);
	textlength->SetDivider(75);
	bb->AddChild(textlength);
	

	// set the color to gray, add the child, and show the window 
	sv->SetViewColor(216,216,216);
	AddChild(sv);
	
	Show();
}

//////////////////////////////////////////////////////////////////////////////////

void SetWindow::MessageReceived(BMessage *message)
{

	float val;

	switch(message->what)
	{
	 case SPEAKIT_VOL_CHANGE:
	 	val = volume->Value();
	 	settings.Volume = val / 10;
	 	break;	
	 	
	 case SPEAKIT_HIGHLIGHT_CHANGE:
	 	settings.Highlight = highlight->Value();
	 	break;		
	 
	 case SPEAKIT_CHAR_LEN_CHANGE:
	 	settings.MaxTextLength = atoi(textlength->Text());
	 	handler->PostMessage(message);
	 	break;	
	 
	 default:
	 	BWindow::MessageReceived(message);
	 	break;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void SetWindow::Quit() 
{
	// alert the application of our impending demise 
	be_app->PostMessage(SPEAKIT_SETWIN_QUIT);
	BWindow::Quit();
}
