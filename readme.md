![Build Status](https://img.shields.io/github/license/solawc/ST_GRBL)
![Build Status](https://img.shields.io/badge/build-GRBL--1.1h-green)
![Build Status](https://img.shields.io/badge/platform-vscode--PlatformIO-yellowgreen)

![Grbl Logo 250px](https://user-images.githubusercontent.com/42537573/131384819-1b6f93d4-67df-4933-aaee-5ba4f4d7ff07.png)

## 描述：

该项目主要是出于个人兴趣，将原生的GRBL的源码，移植到STM32的MCU上，移植的源码的地址：https://github.com/gnea/grbl

## 测试过的MCU

测试方法是在保持工程结构不改变的前提下，只修改了底层接口，其余地方不改变，

|    内核    |   MCU型号   |
| :--------: | :---------: |
| @Cortex-M0 | STM32G070RB |
| @Cortex-M0 | STM32G0B0CE |
| @Cortex-M3 | STM32F103VE |
| @Cortex-M4 | STM32F429IG |

目前Vscode+PlatformIO的环境已经搭建完成，抛弃了Keil的环境，Keil环境的代码将会移植到PIO中执行。

## 参数配置

参数与标准GRBL一致

| $0   | Step pulse time                 | 10       | microseconds | Sets time length per step. Minimum 3usec.                    |
| ---- | ------------------------------- | -------- | ------------ | ------------------------------------------------------------ |
| $1   | Step idle delay                 | 25       | milliseconds | Sets a short hold delay when stopping to let dynamics settle before disabling steppers. Value 255 keeps motors enabled with no delay. |
| $2   | Step pulse invert               | 0        | mask         | Inverts the step signal. Set axis bit to invert (00000ZYX).  |
| $3   | Step direction invert           | 0        | mask         | Inverts the direction signal. Set axis bit to invert (00000ZYX). |
| $4   | Invert step enable pin          | 0        | boolean      | Inverts the stepper driver enable pin signal.                |
| $5   | Invert limit pins               | 0        | boolean      | Inverts the all of the limit input pins.                     |
| $6   | Invert probe pin                | 0        | boolean      | Inverts the probe input pin signal.                          |
| $10  | Status report options           | 1        | mask         | Alters data included in status reports.                      |
| $11  | Junction deviation              | 0.010    | millimeters  | Sets how fast Grbl travels through consecutive motions. Lower value slows it down. |
| $12  | Arc tolerance                   | 0.002    | millimeters  | Sets the G2 and G3 arc tracing accuracy based on radial error. Beware: A very small value may effect performance. |
| $13  | Report in inches                | 0        | boolean      | Enables inch units when returning any position and rate value that is not a settings value. |
| $20  | Soft limits enable              | 0        | boolean      | Enables soft limits checks within machine travel and sets alarm when exceeded. Requires homing. |
| $21  | Hard limits enable              | 1        | boolean      | Enables hard limits. Immediately halts motion and throws an alarm when switch is triggered. |
| $22  | Homing cycle enable             | 1        | boolean      | Enables homing cycle. Requires limit switches on all axes.   |
| $23  | Homing direction invert         | 0        | mask         | Homing searches for a switch in the positive direction. Set axis bit (00000ZYX) to search in negative direction. |
| $24  | Homing locate feed rate         | 25.000   | mm/min       | Feed rate to slowly engage limit switch to determine its location accurately. |
| $25  | Homing search seek rate         | 500.000  | mm/min       | Seek rate to quickly find the limit switch before the slower locating phase. |
| $26  | Homing switch debounce delay    | 250      | milliseconds | Sets a short delay between phases of homing cycle to let a switch debounce. |
| $27  | Homing switch pull-off distance | 1.000    | millimeters  | Retract distance after triggering switch to disengage it. Homing will fail if switch isn't cleared. |
| $30  | Maximum spindle speed           | 1000     | RPM          | Maximum spindle speed. Sets PWM to 100% duty cycle.          |
| $31  | Minimum spindle speed           | 0        | RPM          | Minimum spindle speed. Sets PWM to 0.4% or lowest duty cycle. |
| $32  | Laser-mode enable               | 0        | boolean      | Enables laser mode. Consecutive G1/2/3 commands will not halt when spindle speed is changed. |
| $100 | X-axis travel resolution        | 80.000   | step/mm      | X-axis travel resolution in steps per millimeter.            |
| $101 | Y-axis travel resolution        | 80.000   | step/mm      | Y-axis travel resolution in steps per millimeter.            |
| $102 | Z-axis travel resolution        | 80.000   | step/mm      | Z-axis travel resolution in steps per millimeter.            |
| $110 | X-axis maximum rate             | 6000.000 | mm/min       | X-axis maximum rate. Used as G0 rapid rate.                  |
| $111 | Y-axis maximum rate             | 6000.000 | mm/min       | Y-axis maximum rate. Used as G0 rapid rate.                  |
| $112 | Z-axis maximum rate             | 6000.000 | mm/min       | Z-axis maximum rate. Used as G0 rapid rate.                  |
| $120 | X-axis acceleration             | 500.000  | mm/sec^2     | X-axis acceleration. Used for motion planning to not exceed motor torque and lose steps. |
| $121 | Y-axis acceleration             | 500.000  | mm/sec^2     | Y-axis acceleration. Used for motion planning to not exceed motor torque and lose steps. |
| $122 | Z-axis acceleration             | 500.000  | mm/sec^2     | Z-axis acceleration. Used for motion planning to not exceed motor torque and lose steps. |
| $130 | X-axis maximum travel           | 200.000  | millimeters  | Maximum X-axis travel distance from homing switch. Determines valid machine space for soft-limits and homing search distances. |
| $131 | Y-axis maximum travel           | 200.000  | millimeters  | Maximum Y-axis travel distance from homing switch. Determines valid machine space for soft-limits and homing search distances. |
| $132 | Z-axis maximum travel           | 200.000  | millimeters  | Maximum Z-axis travel distance from homing switch. Determines valid machine space for soft-limits and homing search distances. |

## 编译环境

- 编译器使用：Vscode+PlatformIO
- 下载和调试工具使用：Jlink/DAPlink(OpenOCD)

