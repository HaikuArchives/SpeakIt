// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef APP_H
#define APP_H

#include "ColorWindow.h"
#include "SetWindow.h"
#include "AppWindow.h"
#include "Application.h"


class App : public BApplication 
{
	private:
		AppWindow			*appWindow;			//Main window
		SetWindow			*setWindow;			//window for settings
		ColorWindow			*colorWindow;		//window for color selection
			
		void				MessageReceived(BMessage *message);
		void 				AboutRequested();
		bool            	QuitRequested();
		bool 				LoadConfigurationFile(char *filename);
		bool				SaveConfigurationFile(char *filename);
	
	public:
		App(char *STARTUP_TEXT,bool HIDE);
		

};


#endif