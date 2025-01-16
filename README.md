# GN10Mainboard

This is the main board for the NHK Robot Contest, combining an STM32 microcontroller and a Bluetooth-LE module called RNBD451PE.

## Features

Power supply
- 5V-3A can be supplied from the CAN port
- Built-in power supply of 3.3V-1A

Interface
- BLE communication possible
- Equipped with 3 ports for CAN communication
- 1 SPI communication port
- 1 I2C communication port
- 1 UART communication port
- 1 STM32-UART interface via USB-Serial conversion

Other
- Equipped with PCB for mounting BNO055 module
- Mode can be switched by DIP switch-4P
- Equipped with 5 debug indicators

## Main parts

- [STM32G474RCT6](https://www.stmcu.jp/stm32/stm32g4/stm32g4x4/66801/)
- [RNBD451PE](https://www.microchip.com/en-us/product/rnbd451pe)
- [FT231XS](https://ftdichip.com/products/ft231xs/)
- [OKL-T/3-W5N-C](https://www.murata.com/ja-jp/products/productdetail?partno=OKL-T%2F3-W5N-C)

## Reference

https://github.com/ararobo/mainboradv2
