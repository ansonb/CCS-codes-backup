################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SDCard.obj: ../SDCard.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/driverlib/MSP430F5xx_6xx" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/driverlib" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/fonts" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/LcdDriver" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/ECW" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/grlib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/HAL" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="SDCard.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/driverlib/MSP430F5xx_6xx" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/driverlib" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/fonts" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/LcdDriver" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/ECW" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/grlib" --include_path="C:/ti/msp430/MSP430ware_1_97_00_47/examples/boards/MSP-EXP430F5529/src/FatFs" --include_path="E:/Codes/CCS/workspace_v6_0/sdTest/HAL" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


