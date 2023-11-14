# meteo-board
My Code and Notes all throughout the competition https://code-envision.ro (achieved 2nd place)

## Task

Methods of monitoring, centralizing/decentralizing(preferrably) and democratizing the data of the air around us. Task: Design an entire pipeline with the provided hardware to achieve a valuable application to monitor urban air quality and not limited.

## Short Summary

This repository contains more than just the code, it contains a version history of my entire thought process tackling the proposed problems. i.e. There are many personal statements in the `.md` files and code comments.

## Requirements

The actual hardware, specific, well, hardware.
- ESP32 30-pins  - main board - contains a WiFi module
- DHT Sensor     - temperature and humidity sensor
- MQ135 Sensor   - aerosols / smog / greenhouse gas sensors
                 - i.e. can handle measurements of parts per
                   million in various molecule configurations
                   (CO2, CO, NO2, etc)
- DSM501A Sensor - dust and smoke detector
                 - provides messy but qualitatve data points

Software-wise, a standard installation of Arduino IDE (a complete cesspit) should suffice. Do yourself a favor and use arduino-cli if you can as for me the IDE broke many times. You also need a Dart/Flutter installation to be present and available in your PATH as well as the automatic components it will pull after an initial `pub get` of the client_app_flutter.

Firebase was used to handle a small but reliable Real Time Database in the CRUD (Create, Read, Update and Delete) paradigm.

Everything except the Arduino IDE (again, cesspit) was run under my build of Void Linux but should all be fine for pretty much all environments, albeit your milleage may varry.

## Usage

IDE's should cover pretty much all that is needed in this section, but as a general rule of thought, for Android Studio especially:
1. Make sure to have the Flutter SDK installed and pointed at by your IDE.
2. Open the repository with your IDE, go to pubspec.yaml and perform `pub get`
3. Select a mobile/web device to run the application on.
4. Hit Run.
4. ???
5. Profit.

### Contributing

Any contributions are welcome. I have no idea if this has been mentioned but IT ISN T FULLY FUNCTIONAL:) yet.
