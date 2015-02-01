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

#define MAX_NAME_LENGTH		40
#define MAX_PATH_LENGTH		260
#define MAX_MUSIC_NUM		1500

struct lst
{
	char name[MAX_NAME_LENGTH];
	char path[MAX_PATH_LENGTH];
};

class music_lst
{
public:
	void Kuhou_Scan(char *);
	void Kuhou_Getnum();
	void Kuhou_Sleep(unsigned int ms);
	lst Kuhou_Getmusic(int);
	void Kuhou_Play(lst);
	void Kuhou_End();
	void Kuhou_Getlist();
	music_lst();
	~music_lst();

private:
	lst * music[MAX_MUSIC_NUM];
	
	int music_num;

	FMOD::System *			KuhouSystem;		//sys，不知道是什么
	FMOD::Sound *			MusicToPlay;		//待播放音乐
	FMOD::Channel *			Channel;			//频道？
	FMOD_RESULT				Result;				//部分FMOD函数操作的返回
	const char *Kuhou_MediaPath(lst);
	void Kuhou_Exit(int returnCode);
	void Kuhou_Format(char *buffer, int bufferSize, const char *formatString...);
	void Kuhou_Fatal(const char *format, ...);
	void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
//	void Fmod_init(void **);
	void Kuhou_Close();
	void Kuhou_Search(char *);
	void Kuhou_Addlist(char name[MAX_NAME_LENGTH],char path[MAX_PATH_LENGTH]);
	void Kuhou_Create(lst);

};


#endif