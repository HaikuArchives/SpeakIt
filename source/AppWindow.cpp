// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#include <Application.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <Button.h>
#include <ScrollView.h>
#include <TextView.h>

//For string manipulation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MsgVals.h"
#include "Colors.h"
#include "AppWindow.h"
#include "SoundWork.h"

#include "SettingsClass.h"

//Global settings
extern SettingsClass		settings;


AppWindow::AppWindow(char *StartText,bool Hide,BRect Frame)
			: BWindow(Frame, "SpeakIt", B_DOCUMENT_WINDOW, B_NOT_ZOOMABLE,B_CURRENT_WORKSPACE)
{			

	BMenu 			*tempMenu;
	BMenu 			*sizemenu;
	BMenuItem 		*tempMenuItem;
	BMenuItem 		*font,*color;
	
	MoveTo(settings.TopLeft);
	
	appView = new BView(Bounds(), "SpeakItView", B_FOLLOW_ALL, B_WILL_DRAW);
	appView->SetViewColor(BeBackgroundGrey);
	AddChild(appView);

	
	strcpy(totalpath,settings.SoundPath);
	//not currently used for anything
	strcpy(CDpath,"/SPEAKIT/WORDS/");
	

	// creating and adding menu bar
	MenuRect = Bounds();
	MenuRect.bottom = 19;
	MenuBar = new BMenuBar(MenuRect, "Menu", B_FOLLOW_LEFT_RIGHT|B_FOLLOW_TOP, B_ITEMS_IN_ROW, true);


	//Layout the File menu
	tempMenu = new BMenu("File");
	
	tempMenuItem = new BMenuItem("About SpeakIt", new BMessage(B_ABOUT_REQUESTED));
    tempMenuItem->SetTarget(be_app); 
	tempMenu->AddItem(tempMenuItem);
	tempMenu->AddSeparatorItem();
	tempMenuItem = new BMenuItem("Quit", new BMessage(B_QUIT_REQUESTED),'Q');
	tempMenuItem->SetTarget(be_app); 
	tempMenu->AddItem(tempMenuItem);
	MenuBar->AddItem(tempMenu);

	//Layout the Edit menu
	tempMenu = new BMenu("Edit");

	tempMenuItem = new BMenuItem("Cut", new BMessage(B_CUT),'X');
	tempMenu->AddItem(tempMenuItem);
	tempMenuItem = new BMenuItem("Copy", new BMessage(B_COPY),'C');
	tempMenu->AddItem(tempMenuItem);
	tempMenuItem = new BMenuItem("Paste", new BMessage(B_PASTE),'V');
	tempMenu->AddItem(tempMenuItem);
	tempMenuItem = new BMenuItem("Clear", new BMessage(SPEAKIT_CLEAR));
	tempMenu->AddItem(tempMenuItem);
	tempMenu->AddSeparatorItem();
	tempMenuItem = new BMenuItem("Select All", new BMessage(B_SELECT_ALL),'A');
	tempMenu->AddItem(tempMenuItem);
	MenuBar->AddItem(tempMenu);
	
	//Layout the Font menu
	tempMenu = new BMenu("Font");	
	tempMenu->AddItem(new BMenuItem(sizemenu = new BMenu("Size"), NULL));
	
	sizemenu->AddItem(font = new BMenuItem("10", new BMessage(SPEAKIT_FONT_10)));
	if(settings.FontSize == 10)
		font->SetMarked(true);
	sizemenu->AddItem(font = new BMenuItem("12", new BMessage(SPEAKIT_FONT_12)));
	if(settings.FontSize == 12)
		font->SetMarked(true);
	sizemenu->AddItem(font = new BMenuItem("14", new BMessage(SPEAKIT_FONT_14)));
	if(settings.FontSize == 14)
		font->SetMarked(true);
	sizemenu->AddItem(font = new BMenuItem("18", new BMessage(SPEAKIT_FONT_18)));
	if(settings.FontSize == 18)
		font->SetMarked(true);
	sizemenu->AddItem(font = new BMenuItem("24", new BMessage(SPEAKIT_FONT_24)));
	if(settings.FontSize == 24)
		font->SetMarked(true);
	sizemenu->AddItem(font = new BMenuItem("36", new BMessage(SPEAKIT_FONT_36)));
	if(settings.FontSize == 36)
		font->SetMarked(true);
	sizemenu->SetRadioMode(true);

	tempMenu->AddSeparatorItem();
	color = new BMenuItem("Color", new BMessage(SPEAKIT_COLOR_OTHER));
	color->SetTarget(be_app);
	tempMenu->AddItem(color);
	MenuBar->AddItem(tempMenu);
	
	//Layout the Window menu
	tempMenu = new BMenu("Window");	
	tempMenuItem = new BMenuItem("Settings", new BMessage(SPEAKIT_SETTINGS));
	tempMenuItem->SetTarget(be_app); 
	tempMenu->AddItem(tempMenuItem);
	MenuBar->AddItem(tempMenu);
	
	//Now create the menu
	appView->AddChild(MenuBar);
	
	// Add the CUT button	//1 is a spacer  //40 is width of the button  
	ButtonRect.Set(0,MenuRect.bottom+1,40,MenuRect.bottom+25);	
	appView->AddChild(button = new BButton(ButtonRect, "Cut", "Cut", new BMessage(B_CUT), B_FOLLOW_NONE));	
	// Add the COPY button	  
	ButtonRect.Set(ButtonRect.right +1,MenuRect.bottom+1,ButtonRect.right +40,MenuRect.bottom+25);
	appView->AddChild(button = new BButton(ButtonRect, "Copy", "Copy", new BMessage(B_COPY), B_FOLLOW_NONE));	
	// Add the PASTE button	
	ButtonRect.Set(ButtonRect.right +1,MenuRect.bottom+1,ButtonRect.right +40,MenuRect.bottom+25);
	appView->AddChild(button = new BButton(ButtonRect, "Paste", "Paste", new BMessage(B_PASTE), B_FOLLOW_NONE));	
	// Add the CLEAR button	 
	ButtonRect.Set(ButtonRect.right +1,MenuRect.bottom+1,ButtonRect.right +40,MenuRect.bottom+25);
	appView->AddChild(button = new BButton(ButtonRect, "Clear", "Clear", new BMessage(SPEAKIT_CLEAR), B_FOLLOW_NONE));		
	// Add the SELECT ALL button  						60 is width of the button  
	ButtonRect.Set(ButtonRect.right +1,MenuRect.bottom+1,ButtonRect.right +60,MenuRect.bottom+25);
	appView->AddChild(button = new BButton(ButtonRect, "Select All", "Select All", new BMessage(B_SELECT_ALL), B_FOLLOW_NONE));			
	// Add the SPEAK button	  
	ButtonRect.Set(Frame.right-50,MenuRect.bottom+1,Frame.right-6,MenuRect.bottom+25);
	appView->AddChild(button = new BButton(ButtonRect, "Speak", "Speak", new BMessage(SPEAKIT_WORK), B_FOLLOW_RIGHT));	
	
	// Add the text view
	textfont.SetSize(settings.FontSize);				// 25 is height of menu
	TextFrame.Set(0,ButtonRect.bottom+3,Frame.right-20,Frame.bottom-25);
	TextRect.Set(0,0,Frame.right-B_V_SCROLL_BAR_WIDTH-3,Frame.bottom);		
	textview = new BTextView(TextFrame, "text_view", TextRect, B_FOLLOW_ALL_SIDES, B_WILL_DRAW);	
	textview->SetDoesUndo(true);

	textview->SetFontAndColor(&textfont,B_FONT_ALL,&settings.FontColor);

	textview->SetMaxBytes(settings.MaxTextLength);
	
				
	// Add the scroll view
	appView->AddChild(scrollview = new BScrollView("scroll_view", textview, B_FOLLOW_ALL_SIDES, B_FRAME_EVENTS, false, true, B_FANCY_BORDER));
	scrollview->AttachedToWindow();

	textview->MakeFocus(true);
	
	textview->SetText(StartText);
		
	//Say start up text if it is pressent
	Work();
	if(Hide==true)
		be_app->PostMessage(B_QUIT_REQUESTED);

}// end SpeakItWindow

//////////////////////////////////////////////////////////////////////////

void AppWindow::MessageReceived(BMessage *message)
{
	
	int32			insertstart,insertfinish;

	
	switch ( message->what )
	{

//App specific messages
		case SPEAKIT_WORK:
			 Work();
			 break;
		case SPEAKIT_CLEAR:
			 textview->SetText("");
			 break;	
		case B_SELECT_ALL:
			 textview->SelectAll();
			 break;				
		case SPEAKIT_FONT_10:		
			 textfont.SetSize(10.0);
			 textview->SetFontAndColor(&textfont);
			 break;	
		case SPEAKIT_FONT_12:
			 textfont.SetSize(12.0);
			 textview->SetFontAndColor(&textfont);
			 break;
		case SPEAKIT_FONT_14:
			 textfont.SetSize(14.0);
			 textview->SetFontAndColor(&textfont);
			 break;
		case SPEAKIT_FONT_18:
			 textfont.SetSize(18.0);
			 textview->SetFontAndColor(&textfont);
			 break;
		case SPEAKIT_FONT_24:
			 textfont.SetSize(24.0);
			 textview->SetFontAndColor(&textfont);
			 break;
		case SPEAKIT_FONT_36:
			 textfont.SetSize(36.0);
			 textview->SetFontAndColor(&textfont);
		     break;
		 
		case SPEAKIT_COLORWIN_CHANGE:		 
			 //Gets currnet selection and the turns text into new color and reselects anything selected
			 textview->GetSelection(&insertstart,&insertfinish);
			 textview->SetFontAndColor(&textfont,B_FONT_ALL,&settings.FontColor);
			 textview->SetText(textview->Text());
			 textview->Select(insertstart,insertfinish);		
			 break;
			 
		case SPEAKIT_CHAR_LEN_CHANGE:
			 textview->SetMaxBytes(settings.MaxTextLength);
			 break;
			 
//General messages	
		case B_CUT:
			 textview->Cut(be_clipboard);
			 break;
		case B_COPY:
			 textview->Copy(be_clipboard);
			 break;
		case B_PASTE:
			 textview->Paste(be_clipboard);
			 break;
		case B_QUIT_REQUESTED:			 
			 be_app->PostMessage(B_QUIT_REQUESTED);
			 break;
		
   		default:
			 BWindow::MessageReceived(message);
			 break;
	}
		
	
}// end MessageReceived

//////////////////////////////////////////////////////////////////////////


bool AppWindow::QuitRequested()
{	
	
	BRect			top_left;
	
	//Setting the font size	
	settings.FontSize = (int8) textfont.Size();
	
	//Setting the top left hand point of the current window position
	top_left = Frame();
	settings.TopLeft.x = top_left.left;
	settings.TopLeft.y = top_left.top;

	be_app -> PostMessage(B_QUIT_REQUESTED);
		
	return(true);

}


//////////////////////////////////////////////////////////////////////////


void AppWindow::Work()
{
// Function where all the text to wav stuff is done
	char *word;
	
	char *sentance;
	
	char tmppath[B_FILE_NAME_LENGTH+B_FILE_NAME_LENGTH];
	int isnumber=false;
	int index=0;
	int32 currentoff=0;
	int32 startoff=0;
	int32 endoff=0;
	int32 previousstart=0,previousfinish=0;	
	
	textview->SetMaxBytes(settings.MaxTextLength);
	
	sentance = new char[textview->TextLength()]; 
	
	strcpy(sentance,textview->Text());
	
	word = strtok(sentance," ");
	//say word
	if(word) //only run if text entered
	do
	{
		isnumber = false;
		//say word
	
		for(index=0;index <(signed)strlen(word);index++)
		{
			word[index]=tolower(word[index]);		//make lower case
		
			//Turn on the isnumber flag if word is a number (or contains a number)
			switch (word[index])
			{
				case '0':	
				case '1': 
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9': isnumber=true;
						  break;
				default : break;
			}//end switch			
	
		}

		if(settings.Highlight)
		{
			//get start and end offest of current word
			//highlight that word
			textview->FindWord(currentoff,&startoff,&endoff);
			
			textview->Highlight(previousstart,previousfinish);
			textview->Draw(TextRect);
			textview->Highlight(startoff,endoff);
			textview->Draw(TextRect);
			currentoff = endoff + 1;
			previousstart = startoff; 
			previousfinish= endoff;
		
		}
		
		if(isnumber ==false)
		{	
			RemovePuncFromWord(word,strlen(word));
			//Try playing the sound from the local words dir
			strcpy(tmppath,totalpath);
			strcat(tmppath,word);			
			if(playsound(tmppath,settings.Volume) == false )
			{
				//Play from the CD if word not in local dir
				strcpy(tmppath,CDpath);
							
				//make path UPPER case for CD
				for(index=0;index< (signed)strlen(word);index++)
					word[index]=toupper(word[index]);
							
				strcat(tmppath,word);		
								
				playsound(tmppath,settings.Volume);
						
			}
		
		}
		else
		{
			//word IS numeric so process it	
			RemovePuncFromWord(word,strlen(word));	//removes $ , .

			strcpy(tmppath,totalpath);
			ProcessNum(tmppath,atoi(word),strlen(word),settings.Volume);
					
		}
					
		
	}while((word = strtok(NULL," ")));
	
	//clean up any leftover highlihting
	textview->Invalidate();
	
	delete sentance;

}//end Work()

//////////////////////////////////////////////////////////////////////////

void AppWindow::FrameResized(float w, float h)
{
	if(w!=-1 && h!=-1) BWindow::FrameResized(w,h);

		BRect rect;
		if(w==-1 && h==-1)
		{
			rect = Bounds();
			h = rect.bottom;
			w = rect.right;
		}
		else
		{
		rect = textview->Frame();
		rect.bottom = rect.top + h -B_H_SCROLL_BAR_HEIGHT;
		rect.right = rect.left + w -B_V_SCROLL_BAR_WIDTH-1;
		textview->SetTextRect(rect);
		}
	
}

//////////////////////////////////////////////////////////////////////////
