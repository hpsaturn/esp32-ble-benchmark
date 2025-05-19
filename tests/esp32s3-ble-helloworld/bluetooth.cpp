#ifndef DISABLE_BLE
#include "bluetooth.hpp"

BLEServer* pServer = NULL;
BLECharacteristic* pCharactData = NULL;
BLECharacteristic* pCharactConfig = NULL;
BLECharacteristic* pCharactStatus = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

/*************************************************************************
*   B L U E T O O T H   P A Y L O A D
*************************************************************************/

String getNotificationData() {
    return "";
}

/*************************************************************************
*   B L U E T O O T H   M E T H O D S
*************************************************************************/

// Config BLE callbacks
class MyConfigCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
    };

    void onRead(BLECharacteristic* pCharacteristic) {
    }
};

// Status BLE callbacks
class MyStatusCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* pCharacteristic) {
        std::string value = pCharacteristic->getValue();
    }
};

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    };
};  // BLEServerCallbacks



void bleServerInit() {
    // Create the BLE Device
    BLEDevice::init("CanAirIO_ESP32");
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    // Create the BLE Service
    BLEService* pService = pServer->createService(SERVICE_UUID);
    // Create a BLE Characteristic for PM 2.5
    pCharactData = pService->createCharacteristic(
        CHARAC_DATA_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
    // Create a BLE Characteristic for Sensor mode: STATIC/MOVIL
    pCharactConfig = pService->createCharacteristic(
        CHARAC_CONFIG_UUID,
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
    // Create a BLE Characteristic for Sensor mode: STATIC/MOVIL
    pCharactStatus = pService->createCharacteristic(
        CHARAC_STATUS_UUID,
        BLECharacteristic::PROPERTY_WRITE);
    // Config callback
    pCharactConfig->setCallbacks(new MyConfigCallbacks());
    // Status callback
    pCharactStatus->setCallbacks(new MyStatusCallbacks());
    // Set callback data:
    // Create a Data Descriptor (for notifications)
    pCharactData->addDescriptor(new BLE2902());
    // Start the service
    pService->start();
    // Start advertising
    pServer->getAdvertising()->start();
    Serial.println("-->[BTLE] Bluetooth GATT \t: ready for config client!");
}

void bleLoop() {
    static uint_fast64_t bleTimeStamp = 0;
    // notify changed value
    if (deviceConnected && (millis() - bleTimeStamp > 5 * 1000)) {  // each 5 secs
        bleTimeStamp = millis();
        pCharactData->setValue(getNotificationData().c_str());  // small payload for notification
        pCharactData->notify();
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(250);                   // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising();  // restart advertising
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}

bool bleIsConnected(){
    return deviceConnected;
}
#endif