#include <fmod/fmod.hpp>
#include <stdlib.h>
#include <fmod/fmod_errors.h>
#include <fmod/fmod_common.h>
#include "common.h"
#include "play.h"

int main(int argc , char * argv[])
{
    Kuhou_Private_Argc = argc;
    Kuhou_Private_Argv = argv;
	Fmod_init();
	CreateMusic("drumloop.wav");
	Kuhou_Play();
	Kuhou_End();
	return 1;
}