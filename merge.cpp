
#include "merge.h"

FwMerge::FwMerge(): 
    m_inputFWbinHeader(""),
    m_inputFWbinFull(""),
    m_inputConfigFile(""),
    m_outputFWbinFull(""),
    ini(CIni())
{
    memset(m_pBinBuffer, NULL, BUFFER_NUM * sizeof(char*));
    memset(m_bufferSize, 0, BUFFER_NUM * sizeof(int));
}

FwMerge::~FwMerge()
{
    if (NULL != m_pBinBuffer[FW_HEADER])
	{
		delete[] m_pBinBuffer[FW_HEADER];
		m_pBinBuffer[FW_HEADER] = NULL;
	}
    if (NULL != m_pBinBuffer[FW_FULL])
	{
		delete[] m_pBinBuffer[FW_FULL];
		m_pBinBuffer[FW_FULL] = NULL;
	}
    
}

void FwMerge::SetInputFWbinFile(std::string header, std::string fwbin)
{
    m_inputFWbinHeader = header;
    m_inputFWbinFull = fwbin;
}

void FwMerge::SetInputConfigFile(std::string file)
{
    m_inputConfigFile = file;
}

void FwMerge::SetOutputFWbinFile(std::string file)
{
    m_outputFWbinFull = file;
}


int FwMerge::ReadBinFile(std::string &file, char * &pbuffer, int &bufsize, int endian_swap)
{
    //ate: 打开时指针移到文件末尾，才可以tellg获得文件大小
    ifstream f(file.c_str(), ios::in | ios::binary | ios::ate);
    if (!f.is_open())
        return OPEN_FILE_ERROR;

    bufsize = f.tellg();
    cout << "ReadBinFile | bufsize = " << bufsize << endl;

    pbuffer = new char[bufsize];
    memset(pbuffer, '0', bufsize);

    f.seekg(0, ios::beg);
    f.read(pbuffer, bufsize);
    f.close();

    //FW bin file must be big-endian
    //For Linux, the FW header read out from flash, must do endian-swap to make DWORDs as big-endian format.
    if(endian_swap == DWORD_SWAP)
        EndianChangeForDwords(pbuffer, bufsize);

    return SUCCESS;
}

int FwMerge::ReadConfigFile(std::string &file)
{
    int ret = ini.OpenFile("./fw_param.ini", "r");
    if (ret)
        return ret;

    ParamFormat param;

    // single parameter test.
    // ini.GetInt("serial_number", "offset", param.m_offset);
    // ini.GetInt("serial_number", "length", param.m_length);
    //cout << "ReadBinFile | m_offset = " << param.m_offset  << ", m_length = " << param.m_length << endl;
    //push_back will call copy constructor of ParamFormat
    //m_vecParam.push_back(param);

    //check input ini parameters match the table's item or not.
    for(int i = 0; i < PARAM_MAX_NUM; ++i)
    {
        ret = ini.GetInt(parameter_table[i].name, "offset", param.m_offset);
        if(ret != INI_SUCCESS) continue;

        ret = ini.GetInt(parameter_table[i].name, "length", param.m_length);
        if(ret != INI_SUCCESS) continue;

        //make a copy of ParamFormat and push_back vector.
        if((param.m_offset == parameter_table[i].offset) && (param.m_length == parameter_table[i].length))
            m_vecParam.push_back(param);
    }

    return SUCCESS;
}

int FwMerge::OutputBinFile(std::string &file)
{
    ofstream f(file.c_str(), ios::out | ios::binary);
    if (!f.is_open())
        return OPEN_FILE_ERROR;

    //overwrite the original parameter to values that read from flash header.
    for (std::vector<ParamFormat>::iterator it = m_vecParam.begin(); it != m_vecParam.end(); ++it)
    {
        cout << "OutputBinFile | m_offset = " << it->m_offset  << ", m_length = " << it->m_length << endl;
        memcpy(m_pBinBuffer[FW_FULL] + it->m_offset, m_pBinBuffer[FW_HEADER] + it->m_offset, it->m_length);
    }

    //write output file
    //f.write(m_pBinBuffer[FW_FULL], strlen(m_pBinBuffer[FW_FULL])); //Cut-off! FW header is not a string!
    f.write(m_pBinBuffer[FW_FULL], m_bufferSize[FW_FULL]);
    f.close();

    return SUCCESS;
}

void FwMerge::EndianChangeForDwords(char *pbuffer, int bufsize)
{
    unsigned int *pdword = (unsigned int *)pbuffer;
    int dword = bufsize / 4;

    for (; dword > 0; --dword, pdword++, pbuffer += 4)
    {
        *pdword = ((*pdword & 0x000000ff) << 24) | ((*pdword & 0x0000ff00) << 8) | ((*pdword & 0x00ff0000) >> 8) | ((*pdword & 0xff000000) >> 24);
    }
}

int FwMerge::DoMergeProcess()
{

    int ret;

    //read fw-header and fw-full to buffer
    ret = ReadBinFile(m_inputFWbinHeader, m_pBinBuffer[FW_HEADER], m_bufferSize[FW_HEADER], DWORD_SWAP);
    if (ret != SUCCESS)
        return ret;

    ret = ReadBinFile(m_inputFWbinFull, m_pBinBuffer[FW_FULL], m_bufferSize[FW_FULL], NO_SWAP);
    if (ret != SUCCESS)
        return ret;

    //get what parameter to keep during merge. by ini config file
    ret = ReadConfigFile(m_inputConfigFile);
    if (ret != SUCCESS)
        return ret;

    //generate merged fw-full binfile
    ret = OutputBinFile(m_outputFWbinFull);
    if (ret != SUCCESS)
        return ret;

    return SUCCESS;
}