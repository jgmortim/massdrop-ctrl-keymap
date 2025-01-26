# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [2.3.0] - 2025-01-25

### Changed

- RGB layout

### Fixed

- Bug in RGB timeout function which prevented the timer from counting above 255 seconds.

## [2.2.0] - 2025-01-24

### Added

- RGB timeout after 5 minutes.

### Fixed

- matthewrobo keymap link in README

## [2.1.1] - 2025-01-24

### Fixed

- Bug in LED layer transparency that caused LEDs that are off on all active layers to match the LED options of FN layer.

## [2.1.0] - 2025-01-24

### Added

- LED layer transparency. If an LED is off/transparent at a given layer `n`, it will be set to the value of the first
  active layer checking from `n-1` to `0`. For example, if `LED[6]` is off on `layer[3]`, but its red on `layer[2]`, 
  then if both layers `2` and `3` are active, `LED[6]` will be red.

### Changed

- Give layers aliases and other minor organizational improvements

## [2.0.0] - 2025-01-21

### Added

- Cyan indicator LED on left ALT to indicate that the Spanish layer is active

### Changed

- Spanish layers merged into a single layer
- Spanish layer is no longer toggled by holding `CAPS LOCK`. Instead, the Spanish layer is turned on and off by
  double tapping left ALT.
- The Spanish layer is automatically turned off after typing a Spanish letter
- README to reflect changes

## [1.3.0] - 2025-01-20

### Added

- Custom LED programming

### Changed

- README to reflect changes

## [1.2.0] - 2025-01-19

### Added

- Inverted question mark and exclamation point to Spanish layers
- README

### Fixed

- v1.1.0 link in CHANGELOG

## [1.1.0] - 2025-01-19

### Added

- Layers for upper and lowercase Spanish letters with accents: á, é, í, ó, ú, ñ

## [1.0.0] - 2025-01-19

### Added

- Numpad layer

## [0.0.1] - 2025-01-19

### Added

- A keymap initialized with a copy of the default for massdrop/ctrl
- This CHANGELOG file
- gitignore

[2.3.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v2.2.0...v2.3.0
[2.2.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v2.1.1...v2.2.0
[2.1.1]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v2.1.0...v2.1.1
[2.1.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v2.0.0...v2.1.0
[2.0.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v1.3.0...v2.0.0
[1.3.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v1.2.0...v1.3.0
[1.2.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v1.1.0...v1.2.0
[1.1.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v1.0.0...v1.1.0
[1.0.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v0.0.1...v1.0.0
[0.0.1]: https://github.com/jgmortim/massdrop-ctrl-keymap/releases/tag/v0.0.1
