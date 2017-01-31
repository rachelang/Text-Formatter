# Text-Formatter
#Introduction
C++ program to clean up text by using token input and alignment, such as right and left justified, centered and ragged left or right. It also contains many printing options.
#Functions
Extra spaces/lines in the input do not matter.
The program receives the following input; the alignment and printing commands can be called as many times as desired but the printing will follow the last-called command or default selection if not specified.
1. Number N (desired character limit per line)
2. First command: 
   - rr (ragged right alignment which is default)
   - j (right and left justify)
   - rl (ragged left alignment)
   - c (center alignment)
3. Second command:
   - f (forward printing direction)
   - r (reverse printing direction)
   - p (print lines with set settings, default is forward)
   - k M (print Mth line where M is an integer>=0)
   - s N (prints lines containing N where N is a string)
   - q (quits command input and begins file-reading)
