#include <iostream>
#include <map>
#include <string>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strcpy

using namespace std;

#define CONFIGLEN       256

enum INI_RES
{
        INI_SUCCESS,
        INI_ERROR,
        INI_OPENFILE_ERROR,
        INI_NO_ATTR
};

typedef map<std::string, std::string> KEYMAP;
typedef map<std::string, KEYMAP> MAINKEYMAP;

class CIni
{
public:
        CIni();
        virtual ~CIni();

public:
        int GetInt(const char* mAttr, const char* cAttr);
        INI_RES GetInt(const char* mAttr, const char* cAttr, int &iValue);
        INI_RES GetStr(const char* mAttr, const char* cAttr, char* szValue);
        INI_RES OpenFile(const char* pathName, const char* type);
        INI_RES CloseFile();

protected:
        INI_RES GetKey(const char* mAttr, const char* cAttr, char* value);

        FILE *m_fp;
        MAINKEYMAP m_Map;
};