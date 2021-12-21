#include "merge.h"

int main(int argc, char* argv[])
{
    // input args: 
    // ./headermerge 
    // input-fwbin-file(FW header read out from flash) 
    // input-fwbin-file(release full FW) 
    // input-cfg-file(which parameter to keep during merge) 
    // output-fwbin-file(full FW after merge)

    if(argc < 5){
        std::cout << "wrong input arguments, use below format:" << std::endl;
        std::cout << "./headermerge input-fwbin-file(FW header) input-fwbin-file(full FW) input-cfg-file output-fwbin-file" << std::endl;
        return -1;
    }
        
    FwMerge merge;
    merge.SetInputFWbinFile(argv[1], argv[2]);
    merge.SetInputConfigFile(argv[3]);
    merge.SetOutputFWbinFile(argv[4]);

    int ret = merge.DoMergeProcess();
    if(ret != SUCCESS)
        std::cout << "error ret code: %d" << ret << std::endl;

    return ret;
}