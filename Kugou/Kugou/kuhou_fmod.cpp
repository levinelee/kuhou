#include "music_lst.hpp"

static std::vector<char *> PathList;
void (*Kuhou_Private_Update)(unsigned int*);
void (*Kuhou_Private_Close)();
void (*Kuhou_Private_Error)(FMOD_RESULT, const char *, int);

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

void music_lst::Kuhou_Fatal(const char *format, ...)		//´íÎóÐÅÏ¢
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

const char * music_lst::Kuhou_MediaPath(lst list)
{
    char *filePath = (char *)calloc(256, sizeof(char));

	strcat(filePath, list.path);
	strcat(filePath, "/");
	strcat(filePath, list.name);
    PathList.push_back(filePath);

    return filePath;
}

void music_lst::Kuhou_Create(lst list)
{
	Result = FMOD::System_Create(&KuhouSystem);
	ERRCHECK(Result);
	Result = KuhouSystem->init(32,FMOD_INIT_NORMAL,0);
	ERRCHECK(Result);
	Result = KuhouSystem->createSound(Kuhou_MediaPath(list),FMOD_DEFAULT,0,&MusicToPlay);
}

lst music_lst::Kuhou_Getmusic(int num)
{
	return *music[num];
}

void music_lst::Kuhou_Play(lst list)
{
	Kuhou_Create(list);
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
			Channel->getPosition(&ms,FMOD_TIMEUNIT_MS);
			printf("Time %02d:%02d:%02d\n", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100);
		}
		Kuhou_Sleep(2);
	}
	while(playing);
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
void music_lst::Kuhou_End()
{
	Result = MusicToPlay->release();
	ERRCHECK(Result);
	Kuhou_Close();
}


