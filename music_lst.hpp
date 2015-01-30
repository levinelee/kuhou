#ifndef MUSIC_LST_HPP
#define MUSIC_LST_HPP

#include <fmod/fmod.hpp>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <fmod/fmod_errors.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <cstring>

#define NUM_COLUMNS 50
#define NUM_ROWS 25
#define Kuhou_snprintf _snprintf
#define Kuhou_vsnprintf _vsnprintf
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)

static std::vector<char *> PathList;
void (*Kuhou_Private_Update)(unsigned int*);
void (*Kuhou_Private_Close)();
void (*Kuhou_Private_Error)(FMOD_RESULT, const char *, int);

class music_lst
{
public:

	void Kuhou_Sleep(unsigned int ms);
	void Kuhou_Exit(int returnCode);
	void Kuhou_Format(char *buffer, int bufferSize, const char *formatString...);
	void Kuhou_Fatal(const char *format, ...);
	void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
//	void Fmod_init(void **);
	void Kuhou_Close();
	const char *Kuhou_MediaPath(const char *fileName);
	void CreateMusic(char * FileName);
	void Kuhou_Play();
	void Kuhou_End();
private:
	
	FMOD::System *			KuhouSystem;		//sys，不知道是什么
	FMOD::Sound *			MusicToPlay;		//待播放音乐
	FMOD::Channel *			Channel;			//频道？
	FMOD_RESULT				Result;				//部分FMOD函数操作的返回

};


void music_lst::Kuhou_Sleep(unsigned int ms)
{
    Sleep(ms);
}

void music_lst::Kuhou_Exit(int returnCode)
{
    exit(returnCode);
}

void music_lst::Kuhou_Format(char *buffer, int bufferSize, const char *formatString...)
{
    va_list args;

    va_start(args, formatString);

    Kuhou_vsnprintf(buffer, bufferSize, formatString, args);

    va_end(args);

    buffer[bufferSize-1] = '\0';

}

void music_lst::Kuhou_Fatal(const char *format, ...)		//错误信息
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


void music_lst::ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
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
void music_lst::Kuhou_Close()
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

const char * music_lst::Kuhou_MediaPath(const char *fileName)
{
    char *filePath = (char *)calloc(256, sizeof(char));

    strcat(filePath, "./media/");
    strcat(filePath, fileName);
    PathList.push_back(filePath);

    return filePath;
}

void music_lst::CreateMusic(char * FileName)
{
	Result = FMOD::System_Create(&KuhouSystem);
	ERRCHECK(Result);
	Result = KuhouSystem->init(32,FMOD_INIT_NORMAL,0);
	ERRCHECK(Result);
	Result = KuhouSystem->createSound(Kuhou_MediaPath(FileName),FMOD_DEFAULT,0,&MusicToPlay);

	return;
}

void music_lst::Kuhou_Play()
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
	printf ("xxxx");
	return ;
}
void music_lst::Kuhou_End()
{
	Result = MusicToPlay->release();
	ERRCHECK(Result);
	printf("XXXX");
	Kuhou_Close();
}

#endif
