// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <Window.h>

class ColorWindow : public BWindow
{

	 private:
	 		BWindow 			*handler;
 			BWindow 			*colorWin;
 			BColorControl   	*colorControl;
	
			void 				MessageReceived(BMessage *message);
			void 				Quit();


	 public:
 			ColorWindow(BWindow *hand,BRect frame);
 	
	
};
#endif