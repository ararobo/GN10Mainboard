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
- [LM64460CPPQRYFRQ1](https://www.mouser.jp/ProductDetail/Texas-Instruments/LM64460CPPQRYFRQ1?qs=ST9lo4GX8V34fdE91%2FxUbQ%3D%3D)
- [BNO086](https://www.mouser.jp/ProductDetail/CEVA/BNO086?qs=ulEaXIWI0c%2FqTo1scjodAw%3D%3D)
- https://www.mouser.jp/ProductDetail/Diodes-Incorporated/B560C?qs=e5T%2FzGlhGObuwwV6I9BY7Q%3D%3D&srsltid=AfmBOorPlUXTR8UtZiDISGUChlSEy-OMWWhuqhgKjMJdPER_P_AT99Y-
- https://www.mouser.jp/ProductDetail/Texas-Instruments/TPS54560DDAR?qs=%2FA2SZCkL4Tlm1gC5t8ZNIg%3D%3D
- https://www.mouser.jp/ProductDetail/Murata-Electronics/BLM18AG601SN1D?qs=eh6oC%2F9l24oGGaJFkAJJAA%3D%3D&srsltid=AfmBOorajf2_pkvgIimFKCJByGK3rDwvzCRVmrebkCYJLDSUCe5lNOHh

## Reference

https://github.com/ararobo/mainboradv2

## Development tools

- KiCad 9
- STM32CubeMX
