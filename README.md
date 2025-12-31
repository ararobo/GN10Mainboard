# GN10Mainboard

This is the main board for the NHK Robot Contest, combining an STM32 microcontroller and W5500.
It can connnect PC using Ethernet.

![PCB](GN10Mainboard.png)

## Features

Power supply
- MAX+36V input
- 5V-6A can be supplied from the CAN port
- Built-in power supply of 3.3V-1A

Interface
- 3 CAN-communication port
- RJ45 Ethernet W5500
- UART communication port
- USB-type-C for STM32-UART and STM32-OTA

Sensors
- Gyro BNO086
- 3 external switch
- 2 Incremental encoder

Indicators
- 1 LED for 5V power
- 2 LED for USB Serial
- 3 LED (Red Green Blue) for MCU debug

## Main parts

- [STM32G474RET6](https://www.stmcu.jp/stm32/stm32g4/stm32g4x4/66804/)
- [FT2232HQ](https://ftdichip.com/products/ft2232hq/)
- [BNO086](https://www.mouser.jp/ProductDetail/CEVA/BNO086?qs=ulEaXIWI0c%2FqTo1scjodAw%3D%3D)
- https://www.mouser.jp/ProductDetail/Texas-Instruments/TPS54560DDAR?qs=%2FA2SZCkL4Tlm1gC5t8ZNIg%3D%3D

## Reference

https://github.com/ararobo/mainboradv2

## Development tools

- KiCad 9
- STM32CubeMX
