// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000


#include <Alert.h>			//For AboutBox
#include <Application.h>
#include <Path.h>

#include <stdio.h>
#include <string.h>

#include "Colors.h"
#include "MsgVals.h"		
#include "Constants.h"		//For AboutBox text

#include "App.h"
#include "SetWindow.h"
#include "ColorWindow.h"

#include "SettingsClass.h"

//Global settings
SettingsClass		settings;

		
/////////////////////////////////////////////////////////////////

App::App(char *STARTUP_TEXT,bool HIDE)
		  : BApplication("application/x-vnd.Hailstone-SpeakIt")
{

	BEntry			entry;	
	BPath			path;
	app_info		info;
	
	unsigned int	loop=0;
	
	//Find path of program
	
	be_app->GetAppInfo(&info);
	entry.SetTo(&info.ref);
	entry.GetPath(&path);
	strcpy(settings.AppPath,path.Path());
	strcpy(settings.AppLeaf,path.Leaf());

	for(loop=0;loop < strlen(settings.AppPath)-strlen(settings.AppLeaf);loop++)
		settings.AppPath[loop] = settings.AppPath[loop];
	
	settings.AppPath[loop] = (char)NULL;
	
	//Initialize global settings
	if(LoadConfigurationFile("config.file") ==false)
	{
		//Use generic settings if the config.file is missing	
		settings.Volume          = .5;
		settings.Highlight       = false;
		settings.FontSize        = 12;
		settings.TopLeft.x       = 6;
		settings.TopLeft.y       = 25;
		settings.FontColor.red   = 0;
		settings.FontColor.green = 0;
		settings.FontColor.blue  = 0;		
		settings.FontColor.alpha = 0;	
		settings.MaxTextLength	 = 200;
	}
	
	strcpy(settings.SoundPath,settings.AppPath);	
	strcat(settings.SoundPath,"words/");	
	
	appWindow = new AppWindow(STARTUP_TEXT,HIDE,BRect(6,25,350,160));

	if(HIDE == false)			//Do not show window if running in non-visible mode
	appWindow->Show();
	
	setWindow = NULL;
	colorWindow = NULL;

	
}//end App

/////////////////////////////////////////////////////////////////



void App::MessageReceived(BMessage *message)
{

	BRect		colorFrame;
	BRect		colorRect;

	switch(message->what)
	{

		case SPEAKIT_SETTINGS:
			 if(setWindow != NULL) 
			 	break;			 	

	         setWindow = new SetWindow(appWindow);		
			 break;
				
		case SPEAKIT_COLOR_OTHER:
			 if(colorWindow != NULL)
			 	break;
		 
			 colorFrame = appWindow->Frame();
			 
			 colorRect.Set( (colorFrame.right+colorFrame.left)/2 , 
			 				(colorFrame.top  +colorFrame.bottom)/2,
			 				(colorFrame.right+colorFrame.left)/2 + 268,
							(colorFrame.top  +colorFrame.bottom)/2 + 53 );
			 
			 colorWindow = new ColorWindow(appWindow,colorRect);

			 break;
			 
	    case B_ABOUT_REQUESTED:
	    	 AboutRequested();
			 break;
		
		case SPEAKIT_SETWIN_QUIT:
			 setWindow = NULL;
       	 	 break;
       	 	 
       	case SPEAKIT_COLORWIN_QUIT:
			 colorWindow = NULL;
       	 	 break;
       	 	 	
		case B_QUIT_REQUESTED:
			 be_app->PostMessage(B_QUIT_REQUESTED);
			 break;
		
   		default:
			 BApplication::MessageReceived(message);
			 break;
     
	}

}//end MessageRecieved



/////////////////////////////////////////////////////////////////

void App::AboutRequested()
{
	(new BAlert(STR_ABOUT_TITLE,STR_ABOUT_DESC, STR_ABOUT_BUTTON))->Go();

}//end AboutRequested

/////////////////////////////////////////////////////////////////

bool App::QuitRequested()
{
	SaveConfigurationFile("config.file");
	PostMessage(B_QUIT_REQUESTED);
	return(true);
}

/////////////////////////////////////////////////////////////////

bool App::LoadConfigurationFile(char *filename)
{

//Load general configuration file from disk

	FILE				*fp;			
	char				tmpstr[100];	//holding string for labels within the config file
	char 				*configpath = new char[strlen(settings.AppPath)+strlen(filename)+1];

	strcpy(configpath,settings.AppPath);
	strcat(configpath,filename);

	//open the disk file
	if(!(fp=fopen(configpath,"rb")))
	{	
		delete configpath;
		return false;	
	}

	fscanf(fp,"%s%f\n",tmpstr,&settings.Volume);
	fscanf(fp,"%s%d\n",tmpstr,&settings.Highlight);
	fscanf(fp,"%s%d %d %d %d\n",tmpstr,&settings.FontColor.red,&settings.FontColor.green,
								&settings.FontColor.blue,&settings.FontColor.alpha);
	fscanf(fp,"%s%d\n",tmpstr,&settings.FontSize);
	fscanf(fp,"%s%f %f\n",tmpstr,&settings.TopLeft.x,&settings.TopLeft.y);
	fscanf(fp,"%s%d",tmpstr,&settings.MaxTextLength);

	if(settings.FontSize > 36)
		settings.FontSize = 36;
	else if(settings.FontSize < 36 && settings.FontSize > 24)
		settings.FontSize = 24;
		else if(settings.FontSize < 24 && settings.FontSize > 18)
			settings.FontSize = 18;
			else if(settings.FontSize < 18 && settings.FontSize > 14)
				settings.FontSize = 14;
					else if(settings.FontSize < 14 && settings.FontSize > 12)
						settings.FontSize = 12;
					else if(settings.FontSize < 12)
							settings.FontSize = 10;

	//close the file, free ram and return success
	fclose(fp);
	delete configpath;
	return true;

}//end LoadConfigurationFile

/////////////////////////////////////////////////////////////////

bool App::SaveConfigurationFile(char *filename)
{

//Save general configuration file to disk


	FILE				*fp;			
	char 				*configpath = new char[strlen(settings.AppPath)+strlen(filename)+1];
	
	strcpy(configpath,settings.AppPath);
	strcat(configpath,filename);

	//open the disk file
	if(!(fp=fopen(configpath,"wb")))
	{	
		(new BAlert("File load ERROR","ERROR SAVING config.file", STR_ABOUT_BUTTON))->Go();
		delete configpath;
		return false;
	}

	fprintf(fp,"%s %.2f\n","[Volume]",settings.Volume);
	fprintf(fp,"%s %d\n","[HighLight]",settings.Highlight);
	fprintf(fp,"%s %d %d %d %d\n","[ColorRGBA]",settings.FontColor.red,settings.FontColor.green,
												settings.FontColor.blue,settings.FontColor.alpha);
	fprintf(fp,"%s %d\n","[FontSize]",settings.FontSize);
	fprintf(fp,"%s %.0f %.0f\n","[WinPos]",settings.TopLeft.x,settings.TopLeft.y);
	fprintf(fp,"%s %d","[MaxTextLength]",settings.MaxTextLength);
	
	//close the file, free ram and return success
	fclose(fp);
	delete configpath;
	return true;

}//end SaveConfigurationFile
