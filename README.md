# GN10Mainboard

This is the main board for the NHK Robot Contest, combining an STM32 microcontroller and a Bluetooth-LE module called RNBD451PE.
Both automatic and manual control are envisaged.
If you want automatic control, connect it to a PC using USB, SPI, etc.
For manual control, use a controller equipped with RNBD451PE.

## Features

Power supply
- 5V-6A can be supplied from the CAN port
- Built-in power supply of 3.3V-1A

Interface
- BLE communication possible
- 2 CAN communication port
- 1 SPI communication port
- 1 I2C communication port
- 1 UART communication port
- 1 USB-type-C STM32-UART x2 interface via dual USB-Serial conversion

Other
- 1 gyro
- Mode can be switched by DIP switch-4P

Indicators
- 7segment LED for continuous data
- 3 LED (Red Green Blue) for program
- 4 LED for BLE module

## Main parts

- [STM32G474RCT6](https://www.stmcu.jp/stm32/stm32g4/stm32g4x4/66801/)
- [RNBD451PE](https://www.microchip.com/en-us/product/rnbd451pe)
- [FT231XS](https://ftdichip.com/products/ft231xs/)
- [OKL-T/6-W12N-C](https://www.murata.com/ja-jp/products/productdetail?partno=OKL-T%2F6-W12N-C)

## Reference

https://github.com/ararobo/mainboradv2
