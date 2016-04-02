// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef APPWINDOW_H
#define APPWINDOW_H

#include "SettingsClass.h"
#include <Window.h>
#include "SetWindow.h"

//#define NUMBER_OF_CHAR			100


class AppWindow : public BWindow 
{
	private:
		BView 			*appView;
		BFont       	textfont;
		BMenuBar  		*MenuBar;
		BTextView		*textview;
		BScrollView		*scrollview;
		BButton			*button;
		BRect       	MenuRect;
		BRect 			TextFrame;
		BRect			TextRect;
		BRect			ButtonRect;
		BRect			VolumeRect;

		
		char 			totalpath[B_PATH_NAME_LENGTH+B_FILE_NAME_LENGTH];
		char 			CDpath[B_PATH_NAME_LENGTH];
		
		bool			QuitRequested();
		void			MessageReceived(BMessage *message);
		void			Work();
		void			FrameResized(float x, float y);
		

	public:
			AppWindow(char *StartText,bool Hide,BRect Frame);
};

#endif