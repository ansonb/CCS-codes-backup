################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
UserExperience.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperience.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --large_memory_model -g -O2 --gcc --define=__MSP430F5529__ --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" --diag_warning=225 --silicon_errata=CPU22 --silicon_errata=CPU21 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="UserExperience.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

system_pre_init.obj: ../system_pre_init.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --large_memory_model -g -O2 --gcc --define=__MSP430F5529__ --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" --diag_warning=225 --silicon_errata=CPU22 --silicon_errata=CPU21 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="system_pre_init.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

