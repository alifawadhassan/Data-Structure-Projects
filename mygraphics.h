/*---------------------------------------*/
/*          Graphics LIBRARY            */
/*  Compiled By: Muhammad saif ul Islam   */
/*              President BUDEPS         */
/*        Desktop Programming Society    */
/*             Bahria University         */
/*  Time:       17/12/16 9:40 AM         */
/*---------------------------------------*/

/*-------------------------------------------------*/
/*  Functionality:                                 */
/*------------------------------------------------ */
/*  1) setColor - graphics.h library function      */
/*                to set the color of text         */
/*                or drawing                       */
/*  2)  gotoxy   - graphics.h library function     */
/*                used to set cursor position      */
/*  3)  xbar     - function to create a            */
/*                horizontal bar                   */
/*  4)  ybar     - function to create a            */
/*                vertical bar                     */
/*  5)  xbar -    overloaded function to create a  */
/*                horizontal bar with              */
/*                specified  position (3 args)     */
/*  6)  ybar -    overloaded function to create a  */
/*                vertical bar with                */
/*                specified position (3 args)      */
/*  7)  box       draw a box with given width and  */
/*                height (4 args)
/*  8) pause     - to pause the time               */
/*_________________________________________________*/



#include<iostream>
#include<windows.h>
#include<string>
#include <time.h>


//funtion to set color
void setColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

//funtion to set BG color
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

//Defines gotoxy() for dev C compiler to set cursor position

void gotoxy(short x, short y) {
COORD pos = {x, y};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//Defined function for "time pause" 
void pause(int dur)
{
int temp = time(NULL) + dur;
while(temp > time(NULL));
}

//draw a bar along x axix
int xbar(int range)  {
 for(int i=0;i<range;i++)
    {
    std::cout<<"\xDB"; //prints solid boxes
    }  
}

//defining a function for creating a solid bar including cursor positioning 
//with x increment
 void xbar(int len,int x,int y)
{
for(int i=0;i<len;i++)
    {
    gotoxy(x++,y);
    std::cout<<"\xDB";
    } 
}

//draw a bar along y axis
int ybar(int range)  {
 for(int i=0;i<range;i++)
    {
    std::cout<<"\xDB\n"; //prints solid boxes
    }  
}

//defining a function for creating a solid bar including cursor positioning
//with y increment
void ybar(int len,int x,int y)
{
for(int i=0;i<len;i++)
    {
      gotoxy(x,y++);  
    std::cout<<"\xDB";
}
}



//defined function for timepause
void beep(int time) {
for(int i=0;i<time;i++)
  {
        std::cout<<"\a"; //beep sound
  }
  
}

//defined function for square
void box(int height, int width, int x, int y){
xbar(width,x,y);
xbar(width,x,y+height);
ybar(height, x,y);
ybar(height+1, x+width,y);
}

//change fonts
void setFonts(int size){
	
	CONSOLE_FONT_INFOEX cfi;
cfi.cbSize = sizeof(cfi);
cfi.nFont = 0;
cfi.dwFontSize.X = 1;                   // Width of each character in the font
cfi.dwFontSize.Y = size;                  // Height
cfi.FontFamily = FF_DONTCARE;
cfi.FontWeight = FW_NORMAL;
std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
}

