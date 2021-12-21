#include "ini.h"

CIni::CIni()
{
    m_fp = NULL;
}

CIni::~CIni()
{
    m_Map.clear();
}

INI_RES CIni::OpenFile(const char *pathName, const char *type)
{
    string szLine, szMainKey, szLastMainKey, szSubKey;
    char strLine[CONFIGLEN] = {0};
    KEYMAP mLastMap;
    std::size_t iIndexPos = -1;
    std::size_t iLeftPos = -1;
    std::size_t iRightPos = -1;
    m_fp = fopen(pathName, type);
    if (!m_fp)
    {
        printf("open ini file %s error!\n", pathName);
        return INI_OPENFILE_ERROR;
    }
    m_Map.clear();

    while (fgets(strLine, CONFIGLEN, m_fp))
    {
        //cout << szLine << endl;
        szLine.assign(strLine);
        iLeftPos = szLine.find("\n");
        if (string::npos != iLeftPos)
        {
            szLine.erase(iLeftPos, 1);
        }
        iLeftPos = szLine.find("\r");
        if (string::npos != iLeftPos)
        {
            szLine.erase(iLeftPos, 1);
        }

        iLeftPos = szLine.find("[");
        iRightPos = szLine.find("]");
        if (iLeftPos != string::npos && iRightPos != string::npos)
        {
            szLine.erase(iLeftPos, 1);
            iRightPos--;
            szLine.erase(iRightPos, 1);
            m_Map[szLastMainKey] = mLastMap;
            mLastMap.clear();
            szLastMainKey = szLine;
        }
        else
        {
            if (iIndexPos = szLine.find("="), string::npos != iIndexPos)
            {
                string szSubKey, szSubValue;
                szSubKey = szLine.substr(0, iIndexPos);
                szSubValue = szLine.substr(iIndexPos + 1, szLine.length() - iIndexPos - 1);
                //cout << "szSubValue:" << szSubValue << endl;
                mLastMap[szSubKey] = szSubValue;
            }
            else
            {
            }
        }
    }
    m_Map[szLastMainKey] = mLastMap;

    return INI_SUCCESS;
}

INI_RES CIni::CloseFile()
{
    if (!m_fp)
    {
        fclose(m_fp);
        m_fp = NULL;
    }
    return INI_SUCCESS;
}

INI_RES CIni::GetKey(const char *mAttr, const char *cAttr, char *pValue)
{
    KEYMAP mKey = m_Map[mAttr];
    string sTemp = mKey[cAttr];
    strcpy(pValue, sTemp.c_str());
    //cout << "pValue:" << pValue << endl;
    return INI_SUCCESS;
}

//和windows的ini方法GetPrivateInt格式一致
int CIni::GetInt(const char *mAttr, const char *cAttr)
{
    char szKey[CONFIGLEN];
    memset(szKey, 0, sizeof(szKey));
    if (INI_SUCCESS == GetKey(mAttr, cAttr, szKey))
    {
        return atoi(szKey);
    }
    return 0;
}

//另一种实现：和GetKey格式一致
INI_RES CIni::GetInt(const char* mAttr, const char* cAttr, int &iValue)
{
        char szKey[CONFIGLEN];
        memset(szKey, 0, sizeof(szKey));
        if(INI_SUCCESS == GetKey(mAttr, cAttr, szKey))
        {
                iValue = atoi(szKey);
                return INI_SUCCESS;
        }
        return INI_ERROR;
}

INI_RES CIni::GetStr(const char *mAttr, const char *cAttr, char *szValue)
{
    if (INI_SUCCESS != GetKey(mAttr, cAttr, szValue))
    {
        strcpy(szValue, "NULL");
        return INI_ERROR;
    }
    //cout << "szValue:" << szValue << endl;
    return INI_SUCCESS;
}