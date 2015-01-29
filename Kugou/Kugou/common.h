#ifndef _COMMON_H
#define _COMMON_H

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


extern	FMOD::System	*KuhouSystem;		//sys，不知道是什么
extern	FMOD::Sound *	MusicToPlay;		//待播放音乐
extern	FMOD::Channel *	Channel;			//频道？
extern	FMOD_RESULT		Result;				//部分FMOD函数操作的返回

extern	HANDLE			ConsoleHandle; 
extern	CHAR_INFO		ConsoleBuffer[NUM_COLUMNS * NUM_ROWS];
extern	char			WriteBuffer[NUM_COLUMNS * NUM_ROWS];
extern	unsigned int	gYPos;
extern	bool			Paused;
static std::vector<char *> PathList;

extern	int Kuhou_Private_Argc;
extern	char** Kuhou_Private_Argv;

extern	unsigned int	version;
extern	void *	extradriverdata;

void Fmod_init(void **);
void Kuhou_Close();


void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);

void Kuhou_Update();
void Kuhou_Draw(const char *format, ...);
void Kuhou_Sleep(unsigned int);
void Kuhou_Exit(int );
void Kuhou_Format(char *buffer, int bufferSize, const char *formatString...);
void Kuhou_DrawText(const char *text);
void Kuhou_Fatal(const char *format, ...);

void CreateMusic(char * );
void Kuhou_Play();
void Kuhou_End();

#endif