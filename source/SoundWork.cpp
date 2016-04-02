// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#include "SoundWork.h"
#include <SimpleGameSound.h>

//For a wav
bool playsound(char *path,float VolumeLevel) 
{ 
	entry_ref	ref;
	BEntry		entry(path,true);
	if(entry.InitCheck()  == B_OK)
	{
		if(entry.GetRef(&ref) == B_OK)
		{
			BSimpleGameSound *sound = new BSimpleGameSound(&ref);
			
			if(sound->InitCheck() == B_OK)
			{
				sound->SetGain(VolumeLevel);
				sound->StartPlaying();
	 
				while (sound->IsPlaying()==true)
				{
					;
				}
				sound->StopPlaying();
				delete sound;
				//snooze(10000);  // Wait a bit
			}
			else
			{
				delete sound;
				return false;
			}
		}
		else
			return false;
	}
	else
		return false;

	return true;
              		
// OLD CODE BELOW
	
/*
      BSound 		*sound; 
      BSoundPlayer 	*player; 
      
      entry_ref 	ref;
      BEntry 		entry(path, true);

      BSoundPlayer::play_id id; 
   
      if (entry.InitCheck() == B_OK) 
      { 
         if (entry.GetRef(&ref) == B_OK) 
         { 
            sound = new BSound(&ref); 
            
            media_raw_audio_format	fmt = sound->Format();
            if (sound->InitCheck() == B_OK) 
            { 		              
               player = new BSoundPlayer( &fmt, ref.name );
               player->Start(); 
               player->SetVolume(VolumeLevel);
               id = player->StartPlaying(sound); 
               
               sound->ReleaseRef();
               player->WaitForSound(id);                
               
               player->Stop();
               delete player;
            }
            else
            	return false; 
         }
         else
            	return false; 
      } 
      else
            	return false;


      return true;
*/

}//end playsound

////////////////////////////////////////////////////////////////////////

void RemovePuncFromWord(char *string,int length)
{
//CURRENTLY Removes $ , . from a word 

	int count=0;
	int loop=0;
	
    	char *tmpstr = new char[length];
		
		count=0;
		for(loop=0;loop < length;loop++)
		{

			if(string[loop] == '~')	;
			else if(string[loop] == '`') ;	
			else if(string[loop] == '!') ;	
			else if(string[loop] == '@') ;	
			else if(string[loop] == '#') ;
			else if(string[loop] == '$') ;
			else if(string[loop] == '%') ;
			else if(string[loop] == '^') ;		
			else if(string[loop] == '&') ;
			else if(string[loop] == '*') ;				
			else if(string[loop] == '(') ;
			else if(string[loop] == ')') ;				
			else if(string[loop] == '{') ;
			else if(string[loop] == '}') ;														
			else if(string[loop] == '[') ;	
			else if(string[loop] == ']') ;	
			else if(string[loop] == 92)  ;  //the \ char ASCII dec form, '\' would not work
			else if(string[loop] == '/') ;
			else if(string[loop] == '|') ;	
			else if(string[loop] == ':') ;	
			else if(string[loop] == ';') ;	
			else if(string[loop] == '"') ;	
			else if(string[loop] == 39)  ;  //the ' char ASCII dec form, ''' would not work
			else if(string[loop] == '<') ;
			else if(string[loop] == ',') ;
			else if(string[loop] == '>') ;	
			else if(string[loop] == '.') ;	
			else if(string[loop] == '?') ;
			else if(string[loop] == '-') ;	
			else if(string[loop] == '+') ;					
			else if(string[loop] == '_') ;	
			else if(string[loop] == '=') ;
			else if(string[loop] == 10)  ;  //line feed		
			else if(string[loop] == 13)  ;  //carriage return	
					 	
			else
			{
			   	tmpstr[count] = string[loop];
		 	    count++; 
			}
			
		}//end for loop
		tmpstr[count]= (char) '\0';

		strcpy(string,tmpstr);
		
		delete tmpstr;


}//end RemovePuncFromWord

////////////////////////////////////////////////////////////////////////

void ProcessNum(char *totalpath,long num,int length,float VolumeLevel)
{
//Currently only processes numbers 0 - 9,999,999
	
	char backpath[B_PATH_NAME_LENGTH+B_FILE_NAME_LENGTH];
	
	int zeroflag =0;

	long tenmillions=0;
	long millions=0;
	long hunthousands=0;
	long tenthousands=0;
	long thousands=0;
	long hundreds=0;
	long tens=0;
	long ones=0;
	long temp=0;
	
	temp = num;
	tenmillions=millions=hunthousands=tenthousands=thousands=hundreds=tens=ones=0;
	
	strcpy(backpath,totalpath);
	
	//separate all the digits of the number
	switch (length)
	{
	
		case 8: tenmillions = num / 10000000;
				temp = num % 10000000;
		        millions = temp / 1000000;
				temp = temp % 1000000;				
		        hunthousands = temp / 100000;	
				temp = temp % 100000;									
		        tenthousands = temp / 10000;		
				temp = temp % 10000;											
		        thousands = temp / 1000;			
				temp = temp % 1000;												
		        hundreds = temp / 100;
				temp = temp % 100;								
		        tens = temp / 10; 				        		  
		     	ones = temp % 10;
				break; 
		case 7: millions = num / 1000000;
				temp = num % 1000000;				
		 		hunthousands = temp / 100000;	
				temp = temp % 100000;									
		 		tenthousands = temp / 10000;		
				temp = temp % 10000;											
		 		thousands = temp / 1000;			
				temp = temp % 1000;												
		 		hundreds = temp / 100;
				temp = temp % 100;								
		 		tens = temp / 10; 				        		  
				ones = temp % 10;
				break;
		case 6: hunthousands = num / 100000;	
				temp = num % 100000;									
		 		tenthousands = temp / 10000;		
				temp = temp % 10000;											
		 		thousands = temp / 1000;			
				temp = temp % 1000;												
				hundreds = temp / 100;
				temp = temp % 100;								
		 		tens = temp / 10; 				        		  
				ones = temp % 10;
				break;
		case 5: tenthousands = num / 10000;		
				temp = num % 10000;											
		 		thousands = temp / 1000;			
				temp = temp % 1000;												
		 		hundreds = temp / 100;
				temp = temp % 100;								
		 		tens = temp / 10; 				        		  
				ones = temp % 10;
				break;
		case 4: thousands = num / 1000;			
				temp = num % 1000;												
		 		hundreds = temp / 100;
				temp = temp % 100;								
		 		tens = temp / 10; 				        		  
				ones = temp % 10;
				break; 
		case 3: hundreds = num / 100;
				temp = num % 100;								
				tens = temp / 10; 				        		  
				ones = temp % 10;
				break;
		case 2: tens = num / 10; 				        		  
				ones = num % 10;
				break;
		case 1:	ones = num % 10;
				break;
	/*
	
		case 8: tenmillions = num / 10000000;
				temp = num % 10000000;
		case 7: millions = temp / 1000000;
				temp = temp % 1000000;				
		case 6: hunthousands = temp / 100000;	
				temp = temp % 100000;									
		case 5: tenthousands = temp / 10000;		
				temp = temp % 10000;											
		case 4: thousands = temp / 1000;			
				temp = temp % 1000;												
		case 3: hundreds = temp / 100;
				temp = temp % 100;								
		case 2: tens = temp / 10; 				        		  
		case 1:	ones = temp % 10;
				break;        
	*/
			
	}//end switch
			
	//testing if the number is zero
	num = num - 1;
	if(num < 0)
		zeroflag =1;
	else
		zeroflag =0;

	switch (length)
	{
		case 8: strcpy(totalpath,backpath);
				switch (tenmillions)
				{
					case 0: break;
					case 1: strcpy(totalpath,backpath);
					       	switch (millions)
							{
								case 0: strcat(totalpath,"ten");		break;
								case 1: strcat(totalpath,"eleven");		break;
								case 2: strcat(totalpath,"twelve");		break;
								case 3: strcat(totalpath,"thirteen"); 	break;
								case 4: strcat(totalpath,"fourteen");	break;
								case 5: strcat(totalpath,"fifteen");	break;
								case 6: strcat(totalpath,"sixteen");	break;
								case 7: strcat(totalpath,"seventeen");	break;
								case 8: strcat(totalpath,"eighteen");	break;
								case 9: strcat(totalpath,"nineteen");	break;
							}//end swtich (ones)
						    playsound(totalpath,VolumeLevel);
								    
						    strcpy(totalpath,backpath);
							strcat(totalpath,"million");
							playsound(totalpath,VolumeLevel);
								    
							goto skip2;						    
							
					case 2: strcat(totalpath,"twenty");	break;
					case 3: strcat(totalpath,"thirty"); break;
					case 4: strcat(totalpath,"forty");	break;
					case 5: strcat(totalpath,"fifty");	break;
					case 6: strcat(totalpath,"sixty");	break;
					case 7: strcat(totalpath,"seventy");break;
					case 8: strcat(totalpath,"eighty");	break;
					case 9: strcat(totalpath,"ninety");	break;
				}//end swtich (tenmillions)
				playsound(totalpath,VolumeLevel);
						
				if(tenmillions > 1 && millions == 0)
				{
					strcpy(totalpath,backpath);
					strcat(totalpath,"million");
					playsound(totalpath,VolumeLevel);
					goto skip2;
				}
	
		case 7: strcpy(totalpath,backpath);
				switch (millions)
				{
					case 0: break;
					case 1: strcat(totalpath,"one");	break;
					case 2: strcat(totalpath,"two");	break;
					case 3: strcat(totalpath,"three"); 	break;
					case 4: strcat(totalpath,"four");	break;
					case 5: strcat(totalpath,"five");	break;
					case 6: strcat(totalpath,"six");	break;
					case 7: strcat(totalpath,"seven");	break;
					case 8: strcat(totalpath,"eight");	break;
					case 9: strcat(totalpath,"nine");	break;
				}//end millions switch
				playsound(totalpath,VolumeLevel);
						
				if(millions != 0)
				{
					strcpy(totalpath,backpath);
					strcat(totalpath,"million");
					playsound(totalpath,VolumeLevel);
				}
				
				skip2:
						
		case 6: strcpy(totalpath,backpath);
				switch (hunthousands)
				{
					case 0: break;
		 			case 1: strcat(totalpath,"one");	break;
					case 2: strcat(totalpath,"two");	break;
					case 3: strcat(totalpath,"three"); 	break;
					case 4: strcat(totalpath,"four");	break;
					case 5: strcat(totalpath,"five");	break;
					case 6: strcat(totalpath,"six");	break;
					case 7: strcat(totalpath,"seven");	break;
					case 8: strcat(totalpath,"eight");	break;
					case 9: strcat(totalpath,"nine");	break;
				}//end hunthousands switch
				playsound(totalpath,VolumeLevel);
						
				if(hunthousands!=0)
				{
			 		strcpy(totalpath,backpath);
					strcat(totalpath,"hundred");
					playsound(totalpath,VolumeLevel);
					if (thousands == 0)
					{
						strcpy(totalpath,backpath);
						strcat(totalpath,"thousand");
						playsound(totalpath,VolumeLevel);
					}
				}
				
		case 5: strcpy(totalpath,backpath);
				switch (tenthousands)
				{
					case 0: break;
					case 1: strcpy(totalpath,backpath);
					       	switch (thousands)
							{
								case 0: strcat(totalpath,"ten");		break;
								case 1: strcat(totalpath,"eleven");		break;
								case 2: strcat(totalpath,"twelve");		break;
								case 3: strcat(totalpath,"thirteen"); 	break;
								case 4: strcat(totalpath,"fourteen");	break;
								case 5: strcat(totalpath,"fifteen");	break;
								case 6: strcat(totalpath,"sixteen");	break;
								case 7: strcat(totalpath,"seventeen");	break;
								case 8: strcat(totalpath,"eighteen");	break;
								case 9: strcat(totalpath,"nineteen");	break;
							}//end swtich (ones)
						    playsound(totalpath,VolumeLevel);
								    
						    strcpy(totalpath,backpath);
							strcat(totalpath,"thousand");
							playsound(totalpath,VolumeLevel);
								    
							goto skip;						    
							
					case 2: strcat(totalpath,"twenty");	break;
					case 3: strcat(totalpath,"thirty"); break;
					case 4: strcat(totalpath,"forty");	break;
					case 5: strcat(totalpath,"fifty");	break;
					case 6: strcat(totalpath,"sixty");	break;
					case 7: strcat(totalpath,"seventy");break;
					case 8: strcat(totalpath,"eighty");	break;
					case 9: strcat(totalpath,"ninety");	break;
				}//end swtich (tenthousands)
				playsound(totalpath,VolumeLevel);
						
				if(tenthousands > 1 && thousands == 0)
				{
					strcpy(totalpath,backpath);
					strcat(totalpath,"thousand");
					playsound(totalpath,VolumeLevel);
					goto skip;
				}
			
		case 4: strcpy(totalpath,backpath);
				switch (thousands)
				{
					case 0: break;
					case 1: strcat(totalpath,"one");	break;
					case 2: strcat(totalpath,"two");	break;
					case 3: strcat(totalpath,"three"); 	break;
					case 4: strcat(totalpath,"four");	break;
					case 5: strcat(totalpath,"five");	break;
					case 6: strcat(totalpath,"six");	break;
					case 7: strcat(totalpath,"seven");	break;
					case 8: strcat(totalpath,"eight");	break;
					case 9: strcat(totalpath,"nine");	break;
				}//end swtich (thousands)
				playsound(totalpath,VolumeLevel);
						
				if(thousands !=0)
				{
					strcpy(totalpath,backpath);
					strcat(totalpath,"thousand");
					playsound(totalpath,VolumeLevel);
				}
		
				skip:
		
		case 3: strcpy(totalpath,backpath);
				switch (hundreds)
				{
					case 0: break;
					case 1: strcat(totalpath,"one");	break;
					case 2: strcat(totalpath,"two");	break;
					case 3: strcat(totalpath,"three"); 	break;
					case 4: strcat(totalpath,"four");	break;
					case 5: strcat(totalpath,"five");	break;
					case 6: strcat(totalpath,"six");	break;
					case 7: strcat(totalpath,"seven");	break;
					case 8: strcat(totalpath,"eight");	break;
					case 9: strcat(totalpath,"nine");	break;
				}//end swtich (hundreds)
				playsound(totalpath,VolumeLevel);
						
				if(hundreds !=0)
				{
					strcpy(totalpath,backpath);
					strcat(totalpath,"hundred");
					playsound(totalpath,VolumeLevel);
				}
				
		case 2:	switch (tens)
				{
					case 0: break;
					case 1:	strcpy(totalpath,backpath);
							switch (ones)
							{
								case 0: strcat(totalpath,"ten");		break;
								case 1: strcat(totalpath,"eleven");		break;
								case 2: strcat(totalpath,"twelve");		break;
								case 3: strcat(totalpath,"thirteen"); 	break;
								case 4: strcat(totalpath,"fourteen");	break;
								case 5: strcat(totalpath,"fifteen");	break;
								case 6: strcat(totalpath,"sixteen");	break;
								case 7: strcat(totalpath,"seventeen");	break;
								case 8: strcat(totalpath,"eighteen");	break;
								case 9: strcat(totalpath,"nineteen");	break;
							}//end swtich (ones)
							playsound(totalpath,VolumeLevel);
							goto end;
								    
					case 2:	strcpy(totalpath,backpath);
							strcat(totalpath,"twenty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 3:	strcpy(totalpath,backpath);
							strcat(totalpath,"thirty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 4:	strcpy(totalpath,backpath);
							strcat(totalpath,"forty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 5:	strcpy(totalpath,backpath);
							strcat(totalpath,"fifty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 6:	strcpy(totalpath,backpath);
							strcat(totalpath,"sixty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 7:	strcpy(totalpath,backpath);
							strcat(totalpath,"seventy");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 8: strcpy(totalpath,backpath);
							strcat(totalpath,"eighty");
							playsound(totalpath,VolumeLevel); 
							if(ones==0) 
								goto end;
							break;
					case 9:	strcpy(totalpath,backpath);
							strcat(totalpath,"ninety");
							playsound(totalpath,VolumeLevel);
							if(ones==0) 
								goto end;
							break;	    	    	    	    	    
								   					
			 	}//end switch (tens)

		case 1:	strcpy(totalpath,backpath);
				switch (ones)
				{		
					case 0: if(zeroflag)
								strcat(totalpath,"zero");   
							break;
					case 1: strcat(totalpath,"one");	break;
					case 2: strcat(totalpath,"two");	break;
					case 3: strcat(totalpath,"three"); 	break;
					case 4: strcat(totalpath,"four");	break;
					case 5: strcat(totalpath,"five");	break;
					case 6: strcat(totalpath,"six");	break;
					case 7: strcat(totalpath,"seven");	break;
					case 8: strcat(totalpath,"eight");	break;
					case 9: strcat(totalpath,"nine");	break;
				}//end swtich (ones)
				playsound(totalpath,VolumeLevel);
					
				end:
				break;				
		
	}//end switch (length)


}//end ProcessNum




