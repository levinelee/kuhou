#include "music_lst.hpp"

int		Kuhou_Private_Argc;
char **	Kuhou_Private_Argv;
void *	extradriverdata =0;

int main(int argc , char * argv[])
{
	lst a;
    Kuhou_Private_Argc = argc;
    Kuhou_Private_Argv = argv;
	music_lst kuhou;
	kuhou.Kuhou_Scan("f:");
	kuhou.Kuhou_Getlist();
	a = kuhou.Kuhou_Getmusic(7);
	kuhou.Kuhou_Play(a);
	return 1;
}