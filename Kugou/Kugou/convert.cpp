#include <afx.h>
#include <atlconv.h>
#include <winnls.h>
#include <malloc.h>

LPCSTR AnsiToUtf8(LPCSTR Ansi)
{
  int WLength = MultiByteToWideChar(CP_ACP, 0, Ansi, -1, NULL, 0);
  LPWSTR pszW = (LPWSTR) _alloca((WLength+1) * sizeof(WCHAR));
  MultiByteToWideChar(CP_ACP, 0, Ansi, -1, pszW, WLength);
  
  int ALength = WideCharToMultiByte(CP_UTF8, 0, pszW, -1, NULL, 0, NULL, NULL);
  LPSTR pszA = (LPSTR)_alloca( ALength + 1);
  WideCharToMultiByte(CP_UTF8, 0, pszW, -1, pszA, ALength, NULL, NULL);  
  pszA[ALength] = 0;
  
  return pszA;
}

int main()
{
//测试代码
	FILE * fp;
	fp = fopen("d:/a","w+");
	TCHAR szBuf[1204] = { "你好.mp3" };
	strcpy(szBuf,AnsiToUtf8(szBuf));
	fwrite(szBuf,1024,1,fp);
	fclose(fp);

}
