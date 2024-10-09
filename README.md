# WindQX Library
[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/McOrts/WindQX_Library?include_prereleases)](https://github.com/McOrts/WindQX_Library/releases) [![Arduino Registry](https://www.ardu-badge.com/badge/WindQX_Library.svg)](https://www.arduinolibraries.info/libraries/WindQX_Library) [![Framework](https://img.shields.io/badge/Framework-Arduino-blue)](https://www.arduino.cc/) ![GitHub](https://img.shields.io/github/license/McOrts/WindQX_Library) ![GitHub last commit](https://img.shields.io/github/last-commit/McOrts/WindQX_Library)

It measures the wind speed and the temperature from IoT devices made by [ECD (e.g. SA.01)](https://ecdsl.com/en/producto/sa-01-2/). The library is designed to be used with the Arduino IDE. Compatible with most Arduino and ESP boards.

## List of response statuses
| Message | Description |
|-----------|-----------|
| OK | Correct reading |
| Reading error | Incorrect reading due to corrupt or incomplete data frame |
| Wet sensor | The internal sensor of the anemometer is wet |
| Not connected | Sensor not conected |

## Sample sensor device
<img src="https://github.com/ElectronicCircuitDesing/solid_state_anemometer_wifi/blob/main/img/IMG_7342.png" width="300" align="center"/>
