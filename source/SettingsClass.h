// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef SETTINGSCLASS_H
#define SETTINGSCLASS_H

#include "Application.h"

class SettingsClass
{
	public:
		char				AppPath[B_PATH_NAME_LENGTH+B_FILE_NAME_LENGTH];
		char				AppLeaf[B_FILE_NAME_LENGTH];
		char				SoundPath[B_PATH_NAME_LENGTH+B_FILE_NAME_LENGTH];
		float 				Volume;
		int					Highlight; 
		int					FontSize;
		BPoint				TopLeft;
		rgb_color			FontColor;
		int					MaxTextLength;					

};

#endif