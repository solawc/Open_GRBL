# Middleware

## 简介

什么是Middleware？在我的项目看来，他应该是用于隔离APP层和HAL层的东西。HAL层的接口按照Middleware层已经写好的Template，通过改写HAL层的相关接口来衔接，App层应该调用的是Middleware的接口，而不是HAL层的接口，这样的话不管HAL是如何改变，只要对应的HAL层是可以按照标准正常工作的，那对于APP层来说他也是可以正常工作的。当然如果使用不同的主频的MCU，性能也会产生相关的差异，不仅仅是执行速度的问题，还包含设备传输速度等等。

## Middleware包含的部分

- 通用的GPIO的接口
- 通用定时器的接口
- EEPROM的接口
- W25QXX的接口
- UART的接口
- ...更多

这些需要通过不断的测试、补充。