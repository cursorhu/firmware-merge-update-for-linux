##########################################################################################################
# Description: keep some paremeter value during merge of original full firmware and read out firmware header, 
# Author: Thomas.hu
# Date: 2021/12/17
#########################################################################################################

#!/bin/bash

sudo chmod +x *.sh

nvme_cli_path=`which nvme`

if [ "$nvme_cli_path" = "/usr/sbin/nvme" ]
then
    echo "find nvme-cli tool, path: " "$nvme_cli_path"
else
    echo "please install nvme-cli tool by command: "
    echo "sudo apt-get install nvme-cli"
    exit 0
fi


mergeheader=`ls | grep mergeheader`
if [ -z "$mergeheader" ]
then
    #check make exist
    make_path=`which make`
    if [ -z "$make_path" ]
    then
        echo "please install 'make' by command: "
        echo "sudo apt update"
        echo "sudo apt-get install -y build-essential"
        exit 0
    fi

    echo "building the tool: mergeheader"
    make clean && make
fi

fw_sys_edit=`ls | grep fw_sys_edit.bin`
if [ -z "$fw_sys_edit" ]
then
    echo "please put the firmware bin file: fw_sys_edit.bin to current path"
    exit 0
fi

#config_file=`ls | grep fw_param.ini`
#if [ -z "$configfile" ]
if [ ! -f "fw_param.ini" ]
then
    echo "please put the config file: fw_param.ini to current path"
    exit 0
fi

echo "find nvme device:" 
df -h | grep /dev/nvme

if read -p "please select target nvme device by entering: '/dev/nvme#', # = 0,1,2... an example: /dev/nvme0: " devname
then 
    echo "use $devname"
else
    devname=/dev/nvme0
    echo "use default: /dev/nvme0"
fi

nvme get-log $devname -log-id=0xC0 --log-len=1024 --raw-binary > log_page_c0.raw

echo " *** generated firmware header dumpfile: log_page_c0.raw *** "
echo "use 'hexdump log_page_c0.raw' to check it"


./mergeheader log_page_c0.raw fw_sys_edit.bin fw_param.ini out_fw.bin 

echo " *** generated firmware file: out_fw.bin *** "
echo "use 'hexdump -n 1024 out_fw.bin' to check firmware header"


echo " *** update firmware: out_fw.bin to flash *** "
nvme fw-download /dev/nvme0n1 -f out_fw.bin
nvme fw-commit /dev/nvme0n1 -s 3 -a 0
nvme reset /dev/nvme0