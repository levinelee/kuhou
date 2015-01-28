#include <Windows.h>
#include <iostream>
#include <sys\stat.h>
#include <sys\types.h>
#include <time.h>

using namespace std;

void showdefind(const char * fp)
{
	char filepath[260];
	HANDLE temp;
	WIN32_FIND_DATA temp_data;
	strcpy(filepath,fp);
	strcat(filepath,"\\*.lua");
	temp = FindFirstFile(filepath,&temp_data);
	if (temp!=INVALID_HANDLE_VALUE)
		cout<<fp<<'\\'<<temp_data.cFileName<<endl;
	while (FindNextFile(temp,&temp_data))
		cout<<fp<<'\\'<<temp_data.cFileName<<endl;
	FindClose(temp);
}


void showdedir(const char * fp)
{
	int x;
	char filepath[260];
	struct _stat temp_buf;
	HANDLE temp;
	WIN32_FIND_DATA temp_data;
	strcpy(filepath,fp);
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
			showdedir(filepath);
		}

	}
	FindClose(temp);
}



int main()
{
//	clock_t a;
	
	char path[260];
	cin>>path;

	showdefind(path);
	showdedir(path);
//	a=clock();
//	cout<<double(a / CLK_TCK)<<endl;
	

}
