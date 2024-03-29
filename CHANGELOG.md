# Changelog
All notable changes to SigmonLED will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
SigmonLED uses [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

[comment]: # (This is a comment, it will not be included)

## 0.4.1 - 2022-01-02
### Fixed
- Layout issues with color picker and palette editor

## 0.4.0 - 2021-04-09

**THIS VERSION WILL NOT WORK WITH ANY SIGMONLED ARDUINOS UNDER VERSION 0.3.0**

### Added
- Custom Palette Creation.
- Palette stretching.

### Changed
- Palette delay step from 10 to 5.
- Maximum palette delay from 9,999 to 4,095, a consequence of going hexadecimal.
- Decreased transmission delay from 35 ms to 15 ms. Only stable with latest version of SigmonLED.
- The app now sends the reset command state signal whenever it attempts to change the color.
- Palette and Static Color settings now instantly apply.

### Fixed
- Palette mode taking forever to update if the delay was set to a very high number.
- Last palette mode not saving.

### Known Issues
- (#1) Android app has no icon.

## [0.2.0] - 2021-02-22
### Added
- This Changelog :)
- JavaDoc-style documentation for source code.
- Dark mode setting. Off by default.
- Auto-reconnect, will automatically connect to a previous device on app boot. On by default.
- Solid Palette mode functionality.
### Fixed
- Android icons missing (#2). No longer icons, but text. Temporary solution until this Qt bug can be fixed. Unfortunately looks to be out of my control currently.
- Potential bug that would cause Arduino to lock if a device lost connection while communicating.
