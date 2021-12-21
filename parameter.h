//#include <string>

using namespace std;

class ParamFormat
{
public:
	ParamFormat();
    ~ParamFormat();

    // ParamFormat(ParamFormat& b);
	ParamFormat(const ParamFormat& obj);
	ParamFormat& operator=(const ParamFormat& obj);

public:
    //std::string m_name;
	int m_offset; //offset of byte
	int m_length; //length of bytes 
};

#define PARAM_MAX_NUM 26
#define NAME_MAX_LEN 128

typedef struct PARAMETER_TABLE_FORMAT
{
	char name[NAME_MAX_LEN]; //parameter_name
	int offset;		//offset of byte
	int length;		//length of bytes
}parameter_tbl_format_t, *parameter_tbl_format_p;

extern parameter_tbl_format_t parameter_table[PARAM_MAX_NUM];