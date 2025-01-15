# GN10Mainboard

STM32マイコンとRNBD451PEというBluetooth-LEモジュールを組み合わせたNHK高専ロボコン用メイン基板です。

## 特徴

電源
- 5V-3A以上の電源をCANポートから供給可能
- 3.3V-1A以上の電源を内臓
インターフェイス
- BLE通信可能
- CAN通信用のポートx3搭載
- SPI通信ポートx1
- I2C通信ポートx1
- UART通信ポートx1
- USB-Serial変換経由STM32-UARTインターフェイスx1
その他
- BNO055モジュール搭載用のPCB搭載
- DIPスイッチ-4Pによってモードの切り替え可能
- デバッグ用インジケーター5つ搭載

## 主な部品

- [STM32G474RBT6](https://www.stmcu.jp/stm32/stm32g4/stm32g4x4/66799/)
- [RNBD451PE](https://www.microchip.com/en-us/product/rnbd451pe)
- [FT231XS](https://ftdichip.com/products/ft231xs/)
- [OKL-T/3-W5N-C](https://www.murata.com/ja-jp/products/productdetail?partno=OKL-T%2F3-W5N-C)
