Keil工程文件配置(固件库en.stsw-stm32054_v3-6-0_v3.6.0.zip)：

一、文件夹目录结构

```html
STM32F103C8T6/
|-- Doc
|   `-- README.md
|-- Libraries
|   |-- CMSIS
|   |   `-- CM3
|   |       |-- CoreSupport
|   |       |   |-- core_cm3.c
|   |       |   `-- core_cm3.h
|   |       `-- DeviceSupport
|   |           `-- ST
|   |               `-- STM32F10x
|   |                   |-- startup
|   |                   |   `-- arm
|   |                   |       `-- startup_stm32f10x_md.s
|   |                   |-- stm32f10x.h
|   |                   |-- system_stm32f10x.c
|   |                   `-- system_stm32f10x.h
|   `-- STM32F10x_StdPeriph_Driver
|       |-- inc
|       |   |-- misc.h
|       |   |-- stm32f10x_adc.h
|       |   |-- stm32f10x_bkp.h
|       |   |-- stm32f10x_can.h
|       |   |-- stm32f10x_cec.h
|       |   |-- stm32f10x_crc.h
|       |   |-- stm32f10x_dac.h
|       |   |-- stm32f10x_dbgmcu.h
|       |   |-- stm32f10x_dma.h
|       |   |-- stm32f10x_exti.h
|       |   |-- stm32f10x_flash.h
|       |   |-- stm32f10x_fsmc.h
|       |   |-- stm32f10x_gpio.h
|       |   |-- stm32f10x_i2c.h
|       |   |-- stm32f10x_iwdg.h
|       |   |-- stm32f10x_pwr.h
|       |   |-- stm32f10x_rcc.h
|       |   |-- stm32f10x_rtc.h
|       |   |-- stm32f10x_sdio.h
|       |   |-- stm32f10x_spi.h
|       |   |-- stm32f10x_tim.h
|       |   |-- stm32f10x_usart.h
|       |   `-- stm32f10x_wwdg.h
|       `-- src
|           |-- misc.c
|           |-- stm32f10x_adc.c
|           |-- stm32f10x_bkp.c
|           |-- stm32f10x_can.c
|           |-- stm32f10x_cec.c
|           |-- stm32f10x_crc.c
|           |-- stm32f10x_dac.c
|           |-- stm32f10x_dbgmcu.c
|           |-- stm32f10x_dma.c
|           |-- stm32f10x_exti.c
|           |-- stm32f10x_flash.c
|           |-- stm32f10x_fsmc.c
|           |-- stm32f10x_gpio.c
|           |-- stm32f10x_i2c.c
|           |-- stm32f10x_iwdg.c
|           |-- stm32f10x_pwr.c
|           |-- stm32f10x_rcc.c
|           |-- stm32f10x_rtc.c
|           |-- stm32f10x_sdio.c
|           |-- stm32f10x_spi.c
|           |-- stm32f10x_tim.c
|           |-- stm32f10x_usart.c
|           `-- stm32f10x_wwdg.c
|-- MDK-ARM
|   |-- DebugConfig
|   |-- STM32F103C8T6.uvguix.iu
|   |-- STM32F103C8T6.uvoptx
|   `-- STM32F103C8T6.uvprojx
|-- Output
|   |-- Listings
|   `-- Objects
|       `-- STM32F103C8T6.hex
|-- User
|   |-- bsp_systick.c
|   |-- bsp_systick.h
|   |-- main.c
|   |-- main.h
|   |-- stm32f10x_conf.h
|   |-- stm32f10x_it.c
|   `-- stm32f10x_it.h
`-- keilkill.bat

19 directories, 65 files

```



二、Keil工程目录结构

```html
STM32F103C8T6/
|-- Startup
|   `-- startup_stm32f10x_md.s
|-- CMSIS
|   |-- core_cm3.c
|   `-- system_stm32f10x.c
|-- StdPeriph_Driver
|    `-- src
|    |-- misc.c
|    |-- stm32f10x_adc.c
|    |-- stm32f10x_bkp.c
|    |-- stm32f10x_can.c
|    |-- stm32f10x_cec.c
|    |-- stm32f10x_crc.c
|    |-- stm32f10x_dac.c
|    |-- stm32f10x_dbgmcu.c
|    |-- stm32f10x_dma.c
|    |-- stm32f10x_exti.c
|    |-- stm32f10x_flash.c
|    |-- stm32f10x_fsmc.c
|    |-- stm32f10x_gpio.c
|    |-- stm32f10x_i2c.c
|    |-- stm32f10x_iwdg.c
|    |-- stm32f10x_pwr.c
|    |-- stm32f10x_rcc.c
|    |-- stm32f10x_rtc.c
|    |-- stm32f10x_sdio.c
|    |-- stm32f10x_spi.c
|    |-- stm32f10x_tim.c
|    |-- stm32f10x_usart.c
|    `-- stm32f10x_wwdg.c
|-- User
|   |-- stm32f10x_it.c
|   |-- bsp_systick.c
|   `-- main.c
`-- Doc
    `-- README.md

```



三、Keil配置

Options for Target 'STM32F103C8T6':

| Device      | Target            | Output          | Listing       | User | C/C++                                                        | Asm  | Linker | Debug                 | Utilities |
| ----------- | ----------------- | --------------- | ------------- | ---- | ------------------------------------------------------------ | ---- | ------ | --------------------- | --------- |
| STM32F103C8 | Xtal(MHz): 8.0    | Change Floder   | Change Floder |      | Define: STM32F10X_MD,USE_STDPERIPH_DRIVER                    |      |        | Use: ST-Link Debugger |           |
|             | ARM Compiler: AC5 | Create HEX File |               |      | Include Paths: ..\Libraies\CMSIS\CM3\CoreSupport ..\Libraies\CMSIS\CM3\DeviceSupport\ST\STM32F10x ..\Libraies\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm ..\Libraies\STM32F10x_StdPeriph_Driver\inc ..\User |      |        | Flash Download        |           |
|             |                   |                 |               |      | Misc Controls: -Wno-invalid-source-encoding                  |      |        |                       |           |



四、文件

```bash
::keilkill.bat

del *.bak /s
del *.ddk /s
del *.edk /s
del *.lst /s
del *.lnp /s
del *.mpf /s
del *.mpj /s
del *.obj /s
del *.omf /s
::del *.opt /s	::不允许删除JLINK的设置
del *.plg /s
del *.rpt /s
del *.tmp /s
del *.__i /s
del *.crf /s
del *.o /s
del *.d /s
del *.axf /s
del *.tra /s
del *.dep /s
del JLINKLog.txt /s

del *.iex /s
del *.htm /s
del *.sct /s
del *.map /s

del *.dbgconf /s
del *.LINGZHUNING /s
del *.Administrator /s
exit

```

