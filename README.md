# What's this
0. Update the NVMe controller's Firmware through NVMe Commands. the 'nvme-cli' tool support basic update function.

1. For some Firmware header parameters, customer request keep the original value in Flash where Firmware stored during Firmware update.
	For example, Serial Number(SN), this parameter differs on each NVMe controller, Firmware update process should not overwrite it.

2. This tool support below procedure:
	a. read out the Firmware header data from Flash, through 'nvme-cli' tool's get-log-page command. The firmware side implement the vendor specific command to response the firmware head data to host driver.
	b. merge the read out header and original firmware header to be updated, generate a new firmware, and some parameters keep its value(e.g. SN)
	c. do firmware update process, through 'nvme-cli' tool's fw-download & fw-commit command

# How to use
0. Linux OS: Ubuntu Suggested
	For other Linux OS(CentOS, ...) you must manually install "build-essential" for gcc/g++/make tool, and "nvme-cli" tool

1. please check below files are in this folder:
	fw_sys_edit.bin (firmware to be merged before fw-update.)
	fw_param.ini (what parameters need to keep during merge. the parameters are read out from flash and output to log_page_c0.raw.)
	
2. Connect Internet, and run script: run.sh by:
	sh run.sh
	During script run, input '/dev/nvmeX' to select which nvme device to do fw-update.

3. After fw-update, use 'nvme id_ctrl /dev/nvmeX' to check parameter changes. 
	For example, Serial Number that defined in fw_param.ini