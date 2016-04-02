// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef SETWINDOW_H
#define SETWINDOW_H

#include <Window.h>
#include "SettingsClass.h"

class SetWindow : public BWindow
{

	 private:
 			BWindow 			*handler;
			BSlider 			*volume;
			BCheckBox 			*highlight;
			BTextControl 		*textlength;
			BTextView 			*textView;
			
			void 				MessageReceived(BMessage *message);
			void 				Quit();


	 public:
 			SetWindow(BWindow *hand);
 	
	
};
#endif