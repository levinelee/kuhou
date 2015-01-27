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

static	HANDLE			ConsoleHandle = NULL; 
static	CHAR_INFO		ConsoleBuffer[NUM_COLUMNS * NUM_ROWS] = {0};
static	char			WriteBuffer[NUM_COLUMNS * NUM_ROWS] = {0};
static	unsigned int	gYPos = 0;
static	bool			Paused = false;
static	std::vector<char *>	PathList;

int Kuhou_Private_Argc;
char** Kuhou_Private_Argv;

unsigned int			version;
void *					extradriverdata = 0;

void Fmod_init();
void Kuhou_Close();

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);