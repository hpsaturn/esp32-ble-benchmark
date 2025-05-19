# esp32-ble-benchmark

Tests around some Bluetooth LE libraries with Espressif and Arduino frameworks

## Results

| Tests | Version |  RAM used | Flash used |
|:---------|:------:|------:|------:|
| Arduino Framework (without BLE libs)   | 6.10.0 | 18456 | 248457 |
| Arduino Framework (internal library)   | 6.10.0 | 44388 | 894473 |
| Arduino Framework (NimBLE Arduino lib) | 6.10.0 | 29088 | 489777 |
| IDF NimBLE module | | WIP | WIP |
| IDF BlueDroid | | WIP | WIP |

## Run tests

```shell
git clone https://github.com/hpsaturn/esp32-ble-benchmark.git
cd esp32-ble-benchmark.git
pio run | grep -e "RAM:" -e "Flash:"
```
