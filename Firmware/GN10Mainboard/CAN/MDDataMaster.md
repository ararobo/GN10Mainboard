# MDDataMaster クラス API ドキュメント

`MDDataMaster` クラスは、モータードライバ（MD）のデータを管理し、CAN通信を通じてデータの送受信を行うためのクラスです。このドキュメントでは、`MDDataMaster` クラスの各メソッドについて説明します。

---

## コンストラクタ

### `MDDataMaster::MDDataMaster()`
`MDDataMaster` オブジェクトを初期化し、すべてのデータフラグをリセットします。

---

## パブリックメソッド

### データ受信

#### `void MDDataMaster::receive(uint16_t id, uint8_t *data, uint8_t len)`
CAN通信で受信したデータを処理し、内部バッファやフラグを更新します。

- **パラメータ**:
  - `id` (uint16_t): 受信パケットのCAN ID。
  - `data` (uint8_t*): 受信データへのポインタ。
  - `len` (uint8_t): 受信データの長さ。

---

### データ送信

#### `void MDDataMaster::send_init(uint8_t id, md_config_t *config)`
指定したMDに初期化データを送信します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `config` (md_config_t*): MDの設定データへのポインタ。

#### `void MDDataMaster::send_target(uint8_t id, int16_t target)`
指定したMDに目標値データを送信します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `target` (int16_t): 送信する目標値。

#### `void MDDataMaster::send_gain(uint8_t id, uint8_t gain_type, float gain)`
指定したMDにゲインデータを送信します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `gain_type` (uint8_t): 送信するゲインの種類。
  - `gain` (float): 送信するゲイン値。

---

### データ取得

#### `bool MDDataMaster::get_init(uint8_t id, uint8_t *md_type)`
指定したMDの初期化データを取得します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `md_type` (uint8_t*): 取得したMDタイプを格納するポインタ。

- **戻り値**:
  - データが利用可能な場合は `true`、それ以外は `false`。

#### `bool MDDataMaster::get_encoder(uint8_t id, int16_t *encoder)`
指定したMDのエンコーダデータを取得します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `encoder` (int16_t*): 取得したエンコーダ値を格納するポインタ。

- **戻り値**:
  - データが利用可能な場合は `true`、それ以外は `false`。

#### `bool MDDataMaster::get_limit_switch(uint8_t id, uint8_t *limit_switch)`
指定したMDのリミットスイッチデータを取得します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `limit_switch` (uint8_t*): 取得したリミットスイッチ値を格納するポインタ。

- **戻り値**:
  - データが利用可能な場合は `true`、それ以外は `false`。

#### `bool MDDataMaster::get_gain(uint8_t id, uint8_t gain_type, float *gain)`
指定したMDのゲインデータを取得します。

- **パラメータ**:
  - `id` (uint8_t): 対象MDのID。
  - `gain_type` (uint8_t): 取得するゲインの種類。
  - `gain` (float*): 取得したゲイン値を格納するポインタ。

- **戻り値**:
  - データが利用可能な場合は `true`、それ以外は `false`。

---

## 注意事項

- `MDDataMaster` クラスは、ハードウェア固有の `CANDriver` クラスを継承して使用することを前提としています。
- `get_*` メソッドを使用してデータを取得すると、対応するフラグは自動的にリセットされます。
- マルチスレッド環境で共有データにアクセスする場合は、適切な同期処理を行ってください。

---

## 使用例

```cpp
#include "md_data_master.hpp"

MDDataMaster md_master;

// 初期化データの送信
md_config_t md_config;
// MDの設定
md_config[0].control_period = 10;           // 制御周期
md_config[0].encoder_period = 10;           // エンコーダ周期
md_config[0].encoder_type = 0;              // エンコーダの種類
md_config[0].limit_switch_behavior = 0;     // リミットスイッチの動作
md_config[0].max_acceleration = 100;        // 最大加速度
md_config[0].max_output = 3199;             // 最大出力
md_config[0].option = 0;                    // オプション

md_master.init(0, 0);                   // CAN通信開始
md_master.send_init(1, &config);        // MD初期化


// 目標値データの送信
md_master.send_target(1, 1000);

// エンコーダデータの取得
int16_t encoder;
if (md_master.get_encoder(1, &encoder)) {
    std::cout << "Encoder value: " << encoder << std::endl;
}
```
