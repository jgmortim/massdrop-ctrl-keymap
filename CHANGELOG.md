# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [4.3.0] - 2025-09-17

### Added

- Windows shortcut to toggle the audio output device.
  - <kbd>Win</kbd>+<kbd>a</kbd> triggers the following macro: <kbd>Win</kbd>+<kbd>Ctrl</kbd>+<kbd>v</kbd>, 
    <kbd>Down</kbd>×`n`, <kbd>Enter</kbd>, <kbd>Esc</kbd>.

### Changed

- Overhaul README section on custom shortcuts.

## [4.2.2] - 2025-09-17

### Fixed

- <kbd>Caps Lock</kbd> now correctly effects Spanish layer

## [4.2.1] - 2025-09-16

### Added

- Colored preview squares to README (e.g., ![#11CAC4](https://placehold.co/10x10/11CAC4/11CAC4))

### Changed

- Refactor Windows and Linux specific functions to own files
- Refactor accented letter functionality
- Other refactoring

### Fixed

* `TAP_DANCE_ENABLE = yes` was missing from `rules.mk`

## [4.2.0] - 2025-05-15

### Added

- Caps Lock indicator LED
- Scroll Lock indicator LED
- Additional details to the README

### Changed

- Standardized formatting of keys in README and CHANGELOG

## [4.1.0] - 2025-03-12

### Added

- Linux compiling instructions to README
- OS mode toggle on <kbd>fn</kbd>+<kbd>Win</kbd>
- OS indicator led to <kbd>Win</kbd> key
- Full Spanish layer support in Linux mode via the Unicode-entry mode (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>u</kbd>)
- Custom shortcuts in Linux mode:
  - Pressing <kbd>Win</kbd>+<kbd>c</kbd> will now open the calculator. The specific macro that runs is: 
    <kbd>Alt</kbd>+<kbd>F2</kbd> to open the `run` dialog, typing in the string "gnome-calculator" and then pressing
    <kbd>Enter</kbd>.
- Num Lock is automatically turned on when activating the numpad layer

## [4.0.1] - 2025-02-27

### Changed

- Extracted alt code logic to own method
- Extracted Windows Run shortcut logic to own function

## [4.0.0] - 2025-02-20

### Changed

- Numpad layer is now activated via tap dance

### Fixed

- Speed issue with custom <kbd>Win</kbd>+<kbd>r</kbd> shortcuts (#13)

## [3.1.0] - 2025-02-01

### Added

- Troubleshooting section to README

### Changed

- LED layout to copper themed
- README images to have the new bronze case 
- Updated hardware listing in README

## [3.0.1] - 2025-01-26

### Added

- License header to keymap

## [3.0.0] - 2025-01-26

### Added

- Shortcuts for Windows Calculator and Snipping Tool
  - Pressing <kbd>Win</kbd>+<kbd>c</kbd> will now open the calculator instead of Cortana. The specific macro that runs
    is: <kbd>Win</kbd>+<kbd>r</kbd> to open the `run` dialog, typing in the string "calc" and then pressing 
    <kbd>Enter</kbd>.
  - Pressing <kbd>Win</kbd>+<kbd>s</kbd> will now open Snipping Tool instead of search. The specific macro that runs 
    is: <kbd>Win</kbd>+<kbd>r</kbd> to open the `run` dialog, typing in the string "SnippingTool" and then pressing
    <kbd>Enter</kbd>.
- Backlight to FN layer keys while the FN layer is active
- Additional details to the README

### Removed

- Unused RGB controls from FN layer as this keymap uses its own hard-coded LED configuration

## [2.3.0] - 2025-01-25

### Changed

- RGB layout

### Fixed

- Bug in RGB timeout function which prevented the timer from counting above 255 seconds

## [2.2.0] - 2025-01-24

### Added

- RGB timeout after 5 minutes

### Fixed

- matthewrobo keymap link in README

## [2.1.1] - 2025-01-24

### Fixed

- Bug in LED layer transparency that caused LEDs that are off on all active layers to match the LED options of FN layer

## [2.1.0] - 2025-01-24

### Added

- LED layer transparency. If an LED is off/transparent at a given layer `n`, it will be set to the value of the first
  active layer checking from `n-1` to `0`. For example, if `LED[6]` is off on `layer[3]`, but it's red on `layer[2]`, 
  then if both layers `2` and `3` are active, `LED[6]` will be red.

### Changed

- Give layers aliases and other minor organizational improvements

## [2.0.0] - 2025-01-21

### Added

- Cyan indicator LED on <kbd>Left Alt</kbd> to indicate that the Spanish layer is active

### Changed

- Spanish layers merged into a single layer
- Spanish layer is no longer toggled by holding <kbd>Caps Lock</kbd>. Instead, the Spanish layer is turned on and off
  by double tapping <kbd>Left Alt</kbd>.
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

[4.3.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.2.2...v4.3.0
[4.2.2]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.2.1...v4.2.2
[4.2.1]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.2.0...v4.2.1
[4.2.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.1.0...v4.2.0
[4.1.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.0.1...v4.1.0
[4.0.1]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v4.0.0...v4.0.1
[4.0.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v3.1.0...v4.0.0
[3.1.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v3.0.1...v3.1.0
[3.0.1]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v3.0.0...v3.0.1
[3.0.0]: https://github.com/jgmortim/massdrop-ctrl-keymap/compare/v2.3.0...v3.0.0
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
