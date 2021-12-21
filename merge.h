
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ini.h"
#include "parameter.h"

using namespace std;

enum MergeErrorCode{
    SUCCESS = 0,
    OPEN_FILE_ERROR,
};

class FwMerge
{
public:
	FwMerge();
	~FwMerge();

	void SetInputFWbinFile(std::string header, std::string fwbin);
	void SetInputConfigFile(std::string file);
	void SetOutputFWbinFile(std::string file);

    int ReadBinFile(std::string& file, char * &pbuffer, int &bufsize, int endian_swap);
    int ReadConfigFile(std::string& file);
    int OutputBinFile(std::string& file);

    void EndianChangeForDwords(char *pbuffer, int bufsize);

    int DoMergeProcess();

private:
    enum bufferType{
        FW_HEADER = 0,
        FW_FULL,
        BUFFER_NUM,
    };

    enum endianSwapType{
        NO_SWAP = 0,
        DWORD_SWAP,
    };

    //存输入参数
    std::string m_inputFWbinHeader;
    std::string m_inputFWbinFull;
	std::string m_inputConfigFile;
	std::string m_outputFWbinFull;

    //指针数组，指向 FW header 和 FW full的buffer
    char *m_pBinBuffer[BUFFER_NUM];
    int m_bufferSize[BUFFER_NUM];

    //.ini配置文件的参数对象，表示merge过程中，要"keep the value"的参数
    CIni ini;

    //存.ini解析出的参数属性
    std::vector<ParamFormat> m_vecParam;

};

