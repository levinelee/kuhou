#include "common.h"
#include "play.h"
#include <fmod\fmod_errors.h>


FMOD::System *			KuhouSystem;		//sys，不知道是什么
FMOD::Sound *			MusicToPlay;		//待播放音乐
FMOD::Channel *			Channel;			//频道？
FMOD_RESULT				Result;				//部分FMOD函数操作的返回



void (*Kuhou_Private_Update)(unsigned int*);
void (*Kuhou_Private_Close)();
void (*Kuhou_Private_Error)(FMOD_RESULT, const char *, int);
/*
HANDLE	ConsoleHandle = NULL; 
CHAR_INFO		ConsoleBuffer[NUM_COLUMNS * NUM_ROWS] = {0};
char			WriteBuffer[NUM_COLUMNS * NUM_ROWS] = {0};

*/

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
/*
void Kuhou_DrawText(const char *text)
{
    if (gYPos < NUM_ROWS)
    {
        Kuhou_Format(&WriteBuffer[gYPos * NUM_COLUMNS], NUM_COLUMNS, "%s", text);
        gYPos++;
    }
}
*/


void Kuhou_Fatal(const char *format, ...)		//错误信息
{
    char error[1024];
    va_list args;
    va_start(args, format);
    Kuhou_vsnprintf(error, 1024, format, args);
    va_end(args);
    error[1023] = '\0';
	printf("%s",error);
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

	SetConsoleTitleA("Kuhou Player");


}
*/
void Kuhou_Close()
{
    for (std::vector<char *>::iterator item = PathList.begin(); item != PathList.end(); ++item)
    {
        free(*item);
    }
    if (Kuhou_Private_Close)
    {
        Kuhou_Private_Close();
    }
}

const char *Kuhou_MediaPath(const char *fileName)
{
    char *filePath = (char *)calloc(256, sizeof(char));

    strcat(filePath, "./media/");
    strcat(filePath, fileName);

	printf("%s\n",filePath);
    
	PathList.push_back(filePath);

    return filePath;
}

void CreateMusic(char * FileName)
{
	Result = FMOD::System_Create(&KuhouSystem);
	ERRCHECK(Result);
	Result = KuhouSystem->init(32,FMOD_INIT_NORMAL,0);
	ERRCHECK(Result);
	const char * xx = "./media/你好.mp3";
	Result = KuhouSystem->createSound(xx,FMOD_DEFAULT,0,&MusicToPlay);
	ERRCHECK(Result);
	printf("ok'n\n");
	return;
}

void Kuhou_Play()
{
	
	unsigned int ms = 0;
	int playing = 0;;
	Result = MusicToPlay->setMode(FMOD_LOOP_OFF);
	ERRCHECK(Result);
	do
	{
		if(playing ==0)
		{
			Result = KuhouSystem->playSound(MusicToPlay,0,false,&Channel); 
			ERRCHECK(Result);
		}
		KuhouSystem->update();
		{
			int   channelsplaying = 0;
			KuhouSystem->getChannelsPlaying(&channelsplaying);
			playing = channelsplaying;
		}
	}
	while(playing);
	return ;
}
void Kuhou_End()
{
	Result = MusicToPlay->release();
	ERRCHECK(Result);
	Kuhou_Close();
}
