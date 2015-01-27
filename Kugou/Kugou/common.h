#define _COMMON_H

#include <fmod/fmod.hpp>
#include <Windows.h>
#include <vector>

#define NUM_COLUMNS 50
#define NUM_ROWS 25
#define Kuhou_snprintf _snprintf
#define Kuhou_vsnprintf _vsnprintf
#define ERRCHECK(_result) ERRCHECK_fn(_result, __FILE__, __LINE__)


extern	FMOD::System	*KuhouSystem;		//sys����֪����ʲô
extern	FMOD::Sound *	MusicToPlay;		//����������
extern	FMOD::Channel *	Channel;			//Ƶ����
extern	FMOD_RESULT		Result;				//����FMOD���������ķ���

extern	HANDLE			ConsoleHandle = NULL; 
extern	CHAR_INFO		ConsoleBuffer[NUM_COLUMNS * NUM_ROWS] = {0};
extern	char			WriteBuffer[NUM_COLUMNS * NUM_ROWS] = {0};
extern	unsigned int	gYPos = 0;
extern	bool			Paused = false;
extern	std::vector<char *>	PathList;

extern	int Kuhou_Private_Argc;
extern	char** Kuhou_Private_Argv;

unsigned int			version;
void *					extradriverdata = 0;

void Fmod_init();
void Kuhou_Close();

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);