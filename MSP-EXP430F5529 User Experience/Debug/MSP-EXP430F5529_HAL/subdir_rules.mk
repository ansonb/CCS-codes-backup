################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
MSP-EXP430F5529_HAL/HAL_AppUart.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_AppUart.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_AppUart.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Board.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Board.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Board.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Buttons.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Buttons.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Buttons.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Cma3000.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Cma3000.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Cma3000.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Dogs102x6.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Dogs102x6.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Dogs102x6.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Menu.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Menu.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Menu.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_SDCard.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_SDCard.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_SDCard.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP-EXP430F5529_HAL/HAL_Wheel.obj: C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL/HAL_Wheel.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=coffabi --data_model=restricted -O2 --opt_for_speed=4 --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/F5xx_F6xx_Core_Lib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/MSP-EXP430F5529_HAL" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/CTS" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_CDC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_config" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_Common" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_HID_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_API/USB_MSC_API" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/USB/USB_User" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/UserExperienceDemo/Puzzle" -g --gcc --define=__MSP430F5529__ --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --large_memory_model --printf_support=minimal --preproc_with_compile --preproc_dependency="MSP-EXP430F5529_HAL/HAL_Wheel.pp" --obj_directory="MSP-EXP430F5529_HAL" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


