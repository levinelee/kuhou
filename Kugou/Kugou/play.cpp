#include <vector>
#include "common.h"
#include <fmod/fmod_errors.h>

FMOD::System	*KuhouSystem;		//sys����֪����ʲô
FMOD::Sound *	MusicToPlay;		//����������
FMOD::Channel *	Channel;			//Ƶ����
FMOD_RESULT		Result;				//����FMOD���������ķ���



const char *Kuhou_MediaPath(const char *fileName)
{
    char *filePath = (char *)calloc(256, sizeof(char));

    strcat(filePath, "./media/");
    strcat(filePath, fileName);
    PathList.push_back(filePath);

    return filePath;
}

void CreateMusic(char * FileName)
{
	Result = FMOD::System_Create(&KuhouSystem);
	ERRCHECK(Result);
	
	Result = KuhouSystem->getVersion(&version);
	ERRCHECK(Result);

	Result = KuhouSystem->init(32,FMOD_INIT_NORMAL,extradriverdata);
	ERRCHECK(Result);

	Result = KuhouSystem->createSound(Kuhou_MediaPath(FileName),FMOD_DEFAULT,0,&MusicToPlay);


	return;
}

void Kuhou_Play()
{
	Result = KuhouSystem->playSound(MusicToPlay,0,false,&Channel); 
	ERRCHECK(Result);
}
void Kuhou_End()
{
	Result = MusicToPlay->release();
	ERRCHECK(Result);
	Kuhou_Close();
}