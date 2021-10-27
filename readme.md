# ST_GRBL
![Grbl Logo 250px](https://user-images.githubusercontent.com/42537573/131384819-1b6f93d4-67df-4933-aaee-5ba4f4d7ff07.png)

## 描述：

该项目主要是出于个人兴趣，将原生的GRBL的源码，移植到STM32的MCU上，移植的源码的地址：https://github.com/gnea/grbl。

目前该项目还未完善，主要原因是因为电机控制部分还未完全调试完成，其余完成的部分：

- GPIO，读写操作和中断，用于限位和Probe
- UART，用于上位机连接，目前与上位机正常连接
- EEPROM，在STM32F429IG上使用的是内部Flash模拟EEPROM，读写与保存正常
- W25qxx，驱动已经正常，后期可以针对GUI，用于图片存放和字库存放
- SDCard, 未加入， 用于脱机
- TFT_SPI，未完成，用于脱机显示和操作
- Spindle，未完成，激光或CNC的直流电机控制，输出的是PWM控制
- FreeRTOS, 已移植完成
- Fatfs, 已加入

## 测试过的MCU

测试方法是在保持工程结构不改变的前提下，只修改了底层接口，其余地方不改变，

|    内核    |                 MCU型号                 |
| :--------: | :-------------------------------------: |
| @Cortex-M0 |               STM32G070RB               |
| @Cortex-M3 |               STM32F103VE               |
| @Cortex-M4 |               STM32F429IG               |
| @Cortex-M7 | STM32H750XB/i.MX RT1064/i.MX RT1010-EVK |

目前在这以上的MCU上都进行跑过，效果基本是一样的，而本仓库只提供STM32F429IG的工程，其余的移植是很方便的，其次一个原因是因为，目前改项目的编译环境使用的是Keil MDK 5.34的环境进行编译，因此如果想直接兼容更多的MCU在同一个工程是，Keil MDK显然是很不方便的，并且MDK是收费的。后期的打算是将开发环境改为Vscoed+gcc+makefile的方式来编译，也可以vscode+platformIO的方式进行编译，但这都是都需移植完成后的事情了。

## 编译环境

- 编译器使用：Keil MDK 5.34
- 下载和调试工具使用：Jlink/DAPlink

