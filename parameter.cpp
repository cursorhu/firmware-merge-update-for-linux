#include "parameter.h"

ParamFormat::ParamFormat(): m_offset(0), m_length(0)
{ 
}

ParamFormat::~ParamFormat()
{ 
}

ParamFormat::ParamFormat(const ParamFormat& obj)
{
    this->m_offset = obj.m_offset;
    this->m_length = obj.m_length;
}

ParamFormat& ParamFormat::operator=(const ParamFormat& obj)
{
    this->m_offset = obj.m_offset;
    this->m_length = obj.m_length;
    return *this; 
}


parameter_tbl_format_t parameter_table[PARAM_MAX_NUM] =
{
	/*{param_name, bytes offset, byte length}*/

	//Bootloader vendor parameters
	{"spi_page_program",			 34, 1},//DWORD8(Byte1)
	{"spi_ctrl_io_timing",			 36, 4},//DWORD9(Byte0~4)
	{"spi_erase_cfg_reg1",			 40, 4},//DWORD10(Byte0~4)
	{"spi_erase_cfg_data1",			 44, 4},//DWORD11(Byte0~4)
	{"spi_erase_cfg_reg2",			 48, 4},//DWORD12(Byte0~4)
	{"spi_erase_cfg_data2",			 52, 4},//DWORD13(Byte0~4)
	{"spi_erase_cfg_reg3",			 56, 4},//DWORD14(Byte0~4)
	{"spi_erase_cfg_data3",			 60, 4},//DWORD15(Byte0~4)
	{"spi_erase_cfg_reg4",			 64, 4},//DWORD16(Byte0~4)
	{"spi_erase_cfg_data4",			 68, 4},//DWORD17(Byte0~4)
	{"spi_erase_cfg_reg5",			 72, 4},//DWORD18(Byte0~4)
	{"spi_erase_cfg_data5",			 76, 4},//DWORD19(Byte0~4)

	
	//Device Information
	{"dev_vendor_id",				    192, 4}, //DWORD48(Byte0~4)--->DWORD33(Byte0~4)

	{"hssdr_clkout_delay",			    211, 1},//DWORD52(Byte3 bit[31:24])
	{"legacy_clkout_delay",			    210, 1},//DWORD52(Byte2 bit[23:16])

    {"spi_frq_div",					    35, 1},//DWORD8(Byte0)


	//Device Information
	{"subsys_dev_vendor_id",			196, 4},//DWORD49(Byte0~4)
	{"serial_number",				    268, 20},//DWORD67~DWORD71(20 Bytes)
	{"model_number",					288, 40},//DWORD72 ~ DWORD81(40bytes)
	{"model_number_field_enable",		328, 1}, //DWORD82(Byte0 bit[7:0])
	{"model_number_oem_name",	    	332, 8}, //DW 83 ~ 84(8bytes)
	{"model_number_emmc_mid_name",		340, 8}, //DW 85~86 (8bytes)

	{"hs200_input_tuning_fix_phase",		385, 1},//DWORD96 Byte1[8:15]
	{"hs200_output_tuning_fix_phase",		384, 1},//DWORD96 Byte0[0:7]

	{"host_drive_strength",				392, 4},//DWORD98(0~3 Bytes)
	{"emmc_drive_strength",				396, 1},//DWORD99(Byte0)

};
