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

Output:

```shell
RAM:   [=         ]   5.6% (used 18456 bytes from 327680 bytes)
Flash: [=         ]   7.4% (used 248457 bytes from 3342336 bytes)
RAM:   [=         ]  13.5% (used 44388 bytes from 327680 bytes)
Flash: [===       ]  26.8% (used 894473 bytes from 3342336 bytes)
RAM:   [=         ]   8.9% (used 29088 bytes from 327680 bytes)
Flash: [=         ]  14.7% (used 489777 bytes from 3342336 bytes)
```
