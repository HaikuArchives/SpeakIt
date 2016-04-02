SpeakIt v0.4
=======================

This program reads the typed in text and searches a folder called 'words' for a sound file that corresponds to each individual word in the sentence. So the more sound files in the 'word' folder the more words that can be spoken from the input sentence. A sample collection of words can be downloaded from The Hailstone Web site (396kb)

## What's new in 0.4

- Source code now included.
- Cleaned up source a bit so should be easier to follow the code.


## Usage

 1.
  SpeakIt [-h] ["text"]

  Options:
    -h Does not show SpeakIt window
    "text" The text you want SpeakIt to say upon launch

  Example (in Terminal): SpeakIt -h "Welcome Be dude" &

 2.
  Click on the SpeakIt program

## Notes on source code

- The source is being released because Sean, the guy at Hailstone who wrote this app, does not have time to update it and does not want to see the app just die off.
- This program was originally written to learn the Be API and as such is not structured all that well.
- The PowerPC version would not compile with the cross platform tools, however the source is now available for someone to compile it on a PowerPC machine.

POSSIBLE ITEMS TO ADD:
   - Open plain text files and then speak.
   - A monitor mode that will import any new text put on the clipboard.
   - Drag and Drop support for text.
   - Allow user to change delay between words spoken.
   - Squash any bugs in the program.


## Source Code License

The included text and source code contained with this file may not be used for commercial purposes without prior authorization from Hailstone Software.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to use, copy, modify, merge, distribute, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software. Moreover, the name of any contributor to the Software shall remain unaltered in the source files.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL HAILSTONE SOFTWARE BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.




Hailstone Software
www.hailstonesoftware.com
send questions or comments to help@hailstonesoftware.com


