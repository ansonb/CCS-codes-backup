################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
USB/USB_API/USB_PHDC_API/UsbPHDC.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_PHDC_API/UsbPHDC.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="USB/USB_API/USB_PHDC_API/UsbPHDC.pp" --obj_directory="USB/USB_API/USB_PHDC_API" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


