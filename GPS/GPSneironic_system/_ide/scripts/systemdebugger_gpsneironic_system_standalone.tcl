# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\Jabbah\workspace\GPSneironic_system\_ide\scripts\systemdebugger_gpsneironic_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\Jabbah\workspace\GPSneironic_system\_ide\scripts\systemdebugger_gpsneironic_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Basys3 210183736504A" && level==0 && jtag_device_ctx=="jsn-Basys3-210183736504A-0362d093-0"}
fpga -file C:/Users/Jabbah/workspace/GPSneironic/_ide/bitstream/download.bit
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
loadhw -hw C:/Users/Jabbah/workspace/design_1_wrapper_1/export/design_1_wrapper_1/hw/design_1_wrapper.xsa -regs
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
rst -system
after 3000
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
dow C:/Users/Jabbah/workspace/GPSneironic/Debug/GPSneironic.elf
targets -set -nocase -filter {name =~ "*microblaze*#0" && bscan=="USER2" }
con
