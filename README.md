# ESP32 RadonEye RD200 BLE for Arduino Core

This library provides a simple software interface for an ESP32 to read radon levels from a [RadonEye RD200](http://radonftlab.com/radon-sensor-product/radon-detector/rd200/) via BLE (Bluetooth Low Energy).

__Be aware that the interface to the RD200 is not documented or guaranteed to work. It could change at any time and without warning. You obtain an RD200 to use with this library at your own risk.__

The RadonEye app maintains a constant connection to the sensor. In order for this library to work with the sensor it also maintains a constant connection, in order to lock out the app. If the app reconnects, this software will no longer be able to connect. While it would be easy for this library to connect, take a reading and disconnect, that would leave it open to be locked out. __This  means you can use the RadonEye app or you can use this library, but not both, to access the sensor.__

This library is based on [code published on Github by spikeygg](https://github.com/spikeygg/esphome_radoneye_rd200/tree/fe7284d05b19f84446f0bcfb21a45b67d4846dff), which was originally written by "wettermann" and published on the [Home Assistant discussion groups](https://community.home-assistant.io/t/radoneye-ble-interface/94962/33). Neither of these locations has any copyright notice with the code. I offer my changes in the public domain. __Use at your own risk.__

## Find the RadonEye's Bluetooth MAC address

You'll need to figure out the Bluetooth MAC address of the RadonEye in order to use this software. Unfortunately the packaging, unit and app do not provide this address.

If you've already configured the RadonEye app to access the sensor, you'll need to disable it. It keeps a connection to the sensor active whenever within range, which prevents the sensor from responding to scans or being used by other devices. Killing the RadonEye app may be sufficient to disconnect, otherwise you may need to put the device in airplane mode.

If you have a Raspberry Pi or other Linux system with Bluetooth LE hardware handy, you can use `hcitool` to search for the sensor. Run:
```
sudo hcitool lescan
```
You should see a continually refreshing list of MAC addresses and device names. Many may be `(unknown)` - this is normal. Look for one with a name with the word "Radon" in it. The 17 character string before the name is the MAC address.

If you don't have a Pi or similar hardware, you'll need to find a Bluetooth LE scanner that can run on your computer, phone or tablet.

## Usage

See `examples/simple/simple.ino`.

The ESP32 Bluetooth stack is very large. You may find that when you link this library into a program that does any other network access that the firmware `.bin` is too large. In this case you'll need to use a different partition for your ESP32's flash memory. You'll want to use "Huge app" types of schemes, which may not maintain space for OTA (over-the-air) updates.

Be warned that changing the partition table on an ESP32 will likely lose access to any data already stored in NVS and SPIFFS.

You can find information on how to do this with the [Arduino IDE](https://robotzero.one/arduino-ide-partitions/)  and [PlatformIO](https://docs.platformio.org/en/latest/platforms/espressif32.html#partition-tables). Doing this is beyond the scope of documentation for this library. If you need help, search for resources related to the build environment you're using.

## FAQ

1. How about an ESP8266, Arduino or Nordic nrf version?

The ESP8266 and most Arduinos do not have built-in Bluetooth. You may be able to get an external Bluetooth adapter to work. The Nordic CPUs do have Bluetooth support but their Bluetooth API is different from the ESP32's. Feel free to fork this library and adapt it to other processors.

2. Why can't the code connect to the RD200?

Both the RD200 and the ESP32 have very short range on Bluetooth. Try placing the ESP32 within a few feet of the RD200.

Also, the RD200 app stays connected to the RD200 whenever possible. Try killing the app and/or disabling Bluetooth on your phone for long enough for the ESP32 to connect. You may need to remove the app entirely to prevent it from reconnecting and locking out the ESP32.
