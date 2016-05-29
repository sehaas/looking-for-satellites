looking for satellites
=================

Displays GPS coordinates, altitude and number of connected satellites.

Startup:

     looking for
     satellites...

GPS Fix:

    N48 18.594  255m
    E14 17.086  5sat

Hardware
--------
 - esp8266 / nodemcu clone
 - LCD HD44780 (16x2)
 - I2C Serial Interface Adapter
 - uBlox neo-6m GPS module

The esp8266 is not required, you could use any other controller (Arduino, etc...), but I had this hardware lying around. 

Software:
---------
 - TinyGPS++
 - LiquidCrystal_I2C

Wiring
------
|nodemcu|i2c adapter|gps|
|-------|-----------|---|
|D1     |SCL        |   |
|D2     |SDA        |   |
|3v3    |3v3        |   |
|GND    |GND        |   |
|RX     |           |TX |
|TX     |           |RX |
|3v3    |           |3v3|
|GND    |           |GND|

Caveat
------
 - The layout may break for longitudes > 99 degrees.
 - Leading blanks or zeros are manually added; sprintf may be a better option.
 - I could not get SoftwareSerial working. You have to unplug the gps TX to flash a new program.
