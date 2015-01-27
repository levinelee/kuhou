#include "common.h"
#include <conio.h>
#include <vector>
#include "common.h"
#include <fmod/fmod_errors.h>

void (*Kuhou_Private_Update)(unsigned int*);
void (*Kuhou_Private_Close)();
void (*Kuhou_Private_Error)(FMOD_RESULT, const char *, int);
static std::vector<char *> gPathList;
static unsigned int gYPos = 0;

void Kuhou_Update()
{
    /*
        Capture key input
    */
/*    unsigned int newButtons = 0;
    while (_kbhit())
    {
        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = 256 + _getch(); // Handle multi-char keys
        }

        if      (key == '1')    newButtons |= (1 << BTN_ACTION1);
        else if (key == '2')    newButtons |= (1 << BTN_ACTION2);
        else if (key == '3')    newButtons |= (1 << BTN_ACTION3);
        else if (key == '4')    newButtons |= (1 << BTN_ACTION4);
        else if (key == 256+75) newButtons |= (1 << BTN_LEFT);
        else if (key == 256+77) newButtons |= (1 << BTN_RIGHT);
        else if (key == 256+72) newButtons |= (1 << BTN_UP);
        else if (key == 256+80) newButtons |= (1 << BTN_DOWN);
        else if (key == 32)     newButtons |= (1 << BTN_MORE);
        else if (key == 27)     newButtons |= (1 << BTN_QUIT);
        else if (key == 112)    gPaused = !gPaused;
    }

    gPressedButtons = (gDownButtons ^ newButtons) & newButtons;
    gDownButtons = newButtons;
	*/
    /*
        Update the screen
    */
    if (!Paused)
    {
        for (unsigned int i = 0; i < NUM_COLUMNS * NUM_ROWS; i++)
        {
            ConsoleBuffer[i].Char.AsciiChar = WriteBuffer[i];
            ConsoleBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }

        COORD bufferSize = {NUM_COLUMNS, NUM_ROWS};
        COORD bufferCoord = {0, 0};
        SMALL_RECT writeRegion = {0, 0, NUM_COLUMNS - 1, NUM_ROWS - 1};
        WriteConsoleOutput(ConsoleHandle, ConsoleBuffer, bufferSize, bufferCoord, &writeRegion);
        fflush;(stdout);
    }

    /*
        Reset the write buffer
    */
    gYPos = 0;
    memset(WriteBuffer, ' ', sizeof(WriteBuffer));
/*
    if (Kuhou_Private_Update)
    {
        Kuhou_Private_Update(&PressedButtons);
    }
*/
}





void Kuhou_Draw(const char *format, ...)
{
	//draw函数
    char string[1024];
    char *stringPtr = string;
    
	va_list args;
    va_start(args, format);
    Kuhou_vsnprintf(string, 1024, format, args);	//vsnprintf,stdio里面的一个
    va_end(args);
    
	string[1023] = '\0';
	unsigned int length = (unsigned int)strlen(string);

    do
    {
        bool consumeNewLine = false;
        unsigned int copyLength = length;

        // Search for new line characters
        char *newLinePtr = strchr(stringPtr, '\n');
        if (newLinePtr)
        {
            consumeNewLine = true;
            copyLength = (unsigned int)(newLinePtr - stringPtr);
        }

        if (copyLength > NUM_COLUMNS)
        {
            // Hard wrap by default
            copyLength = NUM_COLUMNS;

            // Loop for a soft wrap
            for (int i = NUM_COLUMNS - 1; i >= 0; i--)
            {
                if (stringPtr[i] == ' ')
                {
                    copyLength = i + 1;
                    break;
                }
            }
        }

        // Null terminate the sub string temporarily by swapping out a char
        char tempChar = stringPtr[copyLength];
        stringPtr[copyLength] = 0;
        Kuhou_DrawText(stringPtr);
        stringPtr[copyLength] = tempChar;

        copyLength += (consumeNewLine ? 1 : 0);
        length -= copyLength;
        stringPtr += copyLength;
    } while (length > 0);
}


void Kuhou_Sleep(unsigned int ms)
{
    Sleep(ms);
}

void Kuhou_Exit(int returnCode)
{
    exit(returnCode);
}

void Kuhou_Format(char *buffer, int bufferSize, const char *formatString...)
{
    va_list args;

    va_start(args, formatString);

    Kuhou_vsnprintf(buffer, bufferSize, formatString, args);

    va_end(args);

    buffer[bufferSize-1] = '\0';

}

void Kuhou_DrawText(const char *text)
{
    if (gYPos < NUM_ROWS)
    {
        Kuhou_Format(&WriteBuffer[gYPos * NUM_COLUMNS], NUM_COLUMNS, "%s", text);
        gYPos++;
    }
}



void Kuhou_Fatal(const char *format, ...)
{
    char error[1024];

    va_list args;
    va_start(args, format);
    Kuhou_vsnprintf(error, 1024, format, args);
    va_end(args);
    error[1023] = '\0';

/*    do
    {*/
        Kuhou_Draw("A fatal error has occurred...");
        Kuhou_Draw("");
        Kuhou_Draw("%s", error);
        Kuhou_Draw("");
        Kuhou_Draw("It will quit");

        Kuhou_Update();
        Kuhou_Sleep(50);
 //   } while (!Kuhou_BtnPress(BTN_QUIT));

    Kuhou_Exit(0);
}


void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        if (Kuhou_Private_Error)
        {
            Kuhou_Private_Error(result, file, line);
        }
        Kuhou_Fatal("%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}


/*
void createmusic(char * FilePath)
{
	Result = FMOD::System_Create(&System);
	ERRCHECK(Result);

	gPathList.push_back(FilePath);

	return;
}
*/
void Fmod_init(void **)
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO	BufferInfo = {0};

	GetConsoleScreenBufferInfo(ConsoleHandle,&BufferInfo);

	unsigned int WindowWidth = BufferInfo.srWindow.Left + BufferInfo.srWindow.Right;

	BufferInfo.dwSize.X = NUM_COLUMNS;

	BufferInfo.srWindow.Right = BufferInfo.srWindow.Left + (NUM_COLUMNS - 1);

	if (NUM_COLUMNS > WindowWidth)
	{
		SetConsoleScreenBufferSize(ConsoleHandle,BufferInfo.dwSize);

		SetConsoleWindowInfo(ConsoleHandle,TRUE,&BufferInfo.srWindow);

	}
	else
	{
        SetConsoleWindowInfo(ConsoleHandle, TRUE, &BufferInfo.srWindow);
        
		SetConsoleScreenBufferSize(ConsoleHandle, BufferInfo.dwSize);
	}

    unsigned int windowHeight = BufferInfo.srWindow.Top + BufferInfo.srWindow.Bottom;
    
	BufferInfo.dwSize.Y = NUM_ROWS;
    
	BufferInfo.srWindow.Bottom = BufferInfo.srWindow.Top + (NUM_ROWS - 1);
    if (NUM_ROWS > windowHeight)
    {
        
		SetConsoleScreenBufferSize(ConsoleHandle, BufferInfo.dwSize);
        
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &BufferInfo.srWindow);
   
	}
    else
    {       
        
		SetConsoleWindowInfo(ConsoleHandle, TRUE, &BufferInfo.srWindow);
        
		SetConsoleScreenBufferSize(ConsoleHandle, BufferInfo.dwSize);
    
	}

	// Hide the cursor
    CONSOLE_CURSOR_INFO CursorInfo = {0};

    CursorInfo.bVisible = false;

    CursorInfo.dwSize = 100;

    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

	SetConsoleTitleA("FMOD Example");


}

void Kuhou_Close()
{
    for (std::vector<char *>::iterator item = gPathList.begin(); item != gPathList.end(); ++item)
    {
        free(*item);
    }
    if (Kuhou_Private_Close)
    {
        Kuhou_Private_Close();
    }
}