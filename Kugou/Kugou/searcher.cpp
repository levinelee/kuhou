#include "music_lst.hpp"
#include <sys\stat.h>
#include <sys\types.h>


music_lst::music_lst()
{
	music_num=0;
}

void music_lst::Kuhou_Addlist(char name[MAX_NAME_LENGTH],char path[MAX_PATH_LENGTH])
{
	lst * temp;
	temp = new lst;
	strcpy((*temp).name,name);
	strcpy((*temp).path,path);
	music[music_num]=temp;
	music_num++;
}

void music_lst::Kuhou_Getnum()
{
	printf("%d",music_num);
}

void music_lst::Kuhou_Getlist()
{
	int i;
	for (i=0;i<music_num;i++)
		printf("[%d]\t\t<%s>\t\t\t<%s>\n",i,(*music[i]).name,(*music[i]).path);
}

void music_lst::Kuhou_Search(char * fp)
{
	char filepath[260];
	char fp_temp[260];
	HANDLE temp;
	WIN32_FIND_DATA temp_data;
	strcpy(filepath,fp);
	strcpy(fp_temp,fp);
	strcat(filepath,"\\*.ogg");
	temp = FindFirstFile(filepath,&temp_data);
	if (temp!=INVALID_HANDLE_VALUE)
//		printf("%s\\%s\n",fp,temp_data.cFileName);
		Kuhou_Addlist(temp_data.cFileName,fp_temp);
	while (FindNextFile(temp,&temp_data))
//		printf("%s\\%s\n",fp,temp_data.cFileName);
		Kuhou_Addlist(temp_data.cFileName,fp_temp);
	FindClose(temp);
}

void music_lst::Kuhou_Scan(char * fp)
{
	int x;
	char filepath[260];
	struct _stat temp_buf;
	HANDLE temp;
	WIN32_FIND_DATA temp_data;
	strcpy(filepath,fp);
	Kuhou_Search(filepath);
	strcat(filepath,"\\*.*");
	temp = FindFirstFile(filepath,&temp_data);
	FindNextFile(temp,&temp_data);
	while (FindNextFile(temp,&temp_data))
	{
		strcpy(filepath,fp);
		strcat(filepath,"\\");
		strcat(filepath,temp_data.cFileName);
		x=_stat(filepath,&temp_buf) ;
		if (S_IFDIR & temp_buf.st_mode )
		{
//			printf("%s\n",filepath);
			Kuhou_Scan(filepath);
		}

	}
	FindClose(temp);
}



music_lst::~music_lst()
{
	int i;
	for (i=0;i<music_num;i++)
		delete[] music[i];
	printf("ended");
}