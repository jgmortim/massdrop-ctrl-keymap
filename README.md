# massdrop-ctrl-keymap

This repo is for keeping track of the changes I make to the firmware running on my Massdrop CTRL keyboard as well as
all other aspects of the keyboard.

An approximate rendering of my keyboard is below:

<details>
<summary>Click to expand image</summary>

![keyboard render](resources/images/keyboard.png)
</details>

## Hardware

[Drop CTRL V1 High-Profile](https://drop.com/buy/drop-ctrl-high-profile-mechanical-keyboard) TKL Mechanical Keyboard
* Case: [Bronze Replacement Case](https://drop.com/buy/drop-ctrl-high-profile-aluminum-case?defaultSelectionIds=966025)
* PCB: Stock CTRL V1
* LED Diffuser: Stock [CTRL LED Diffuser](https://drop.com/buy/drop-mechanical-keyboard-led-diffusers?defaultSelectionIds=989038)
* Switches: [Halo Clear](https://drop.com/buy/drop-halo-switch-pack?defaultSelectionIds=986078)
* Stabilizers: Stock Plate-mounted Cherry-style
* Keycaps: [KeyGeak Rome PBT - SA profile](https://keygeak.com/products/rome-pbt-ansi-iso-keycaps-set-sa-profile)
* Foam: [StupidFish Designs](https://stupidfish.design/products/drop-ctrl-high-profile-case-and-plate-foam-set)

## Layers

### L0 \ Base

The base, or default, layer is a pretty standard QWERTY layout. A few of the key caps are different, as shown in the 
render above, but the layout works as one would expect.

### L1 \ Function

Holding down the `FN` key activates the function layer, which features the following functions brought in from the 
default keymap:

| Key | Function                                                                           |
|-----|------------------------------------------------------------------------------------|
| B   | Put the keyboard into DFU (Device Firmware Update) mode after hold timeout (500ms) |
| I   | USB Toggle Automatic GCR control                                                   |
| N   | Toggle keyboard 6KRO/NKRO (Default state 6KRO)                                     |
| U   | USB Extra Port Toggle Auto Detect                                                  |

### L2 \ Numpad

A numpad layer is activated by holding down the grave mark (tilde) key while on any other layer. The numpad is located 
on the upper right of the keyboard like so:

<details>
<summary>Click to expand image</summary>

![numpad layout](resources/images/numpad.png)
</details>

While the numpad layer is active, the numpad keys are backlit with copper LEDs. All other keys are transparent.

### L3 \ Spanish

The Spanish layer can be turned on and off by double tapping `LEFT ALT` while on any other layer. While the Spanish
layer is active, the `LEFT ALT` key will be backlit with a cyan LED. The Spanish layer is automatically turned off 
after typing a Spanish letter or punctuation mark. All keys other than `A`, `E`, `I`, `O`, `U`, `N`, `?`, and `!`
are transparent.

<details>
<summary>Click to expand image</summary>

![Spanish layout](resources/images/spanish.png)
</details>

#### Letters with Accents

While the Spanish layer is active, type the corresponding letter to get an accented letter. For example, pressing
`a` will produce `á`, `e` will produce `é`, `n` will produce `ñ` and so on. To get capital letters, hold `SHIFT` at
the same time as pressing the corresponding letter.

#### Inverted Punctuation Marks

For `¡` and `¿`,  use `SHIFT`+`1` and `SHIFT`+`/`, respectively.

Note that `SHIFT`+`1` is `!` and `SHIFT`+`/` is `?`, so effectively, you could also think of these as
just pressing `!` and `?`, while the Spanish layer is active.

## Other Features

### LED Timeout

After 5 minutes of inactivity, the LEDs will turn off. Pressing any key will turn them back on. 

### Custom Shortcuts

| Shortcut | Function      | Macro                          |
|----------|---------------|--------------------------------|
| Win + c  | Calculator    | Win + r, "calc", ENTER         |
| Win + s  | Snipping Tool | Win + r, "SnippingTool", ENTER |

#### Notes
* Calculator replaces Cortana. I have Cortana disable so a calculator shortcut is much more useful.
* Snipping Tool replaces search. Pressing the `Win` key followed by typing anything will open search already, 
 so using `Win` + `s` to open search has always seemed like a waste of a shortcut.

### LED Layer Transparency

The LED configuration on each layer features transparency. That is to say, if an LED is off/transparent at a given
layer `n`, it will be set to the value of the first active layer checking from `n-1` to `0`. For example, if `LED[6]`
is off on `layer[3]`, but its red on `layer[2]`, then if both layers `2` and `3` are active, `LED[6]` will be red.

## Compiling

This firmware cannot be compiled with the official [qmk_firmware](https://github.com/qmk/qmk_firmware), but instead 
needs to be compiled using [Massdrop's fork](https://github.com/Massdrop/qmk_firmware) of the QMK repo. 
Specifically, using the [feature/riot_xap](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap) branch.

### Windows

I wasn't able to compile this using [QMK MSYS](https://msys.qmk.fm/). When I tried, I got an error stating that
Massdrop's fork of qmk_firmware "exists but is not a qmk_firmware clone!"

So instead, I used [MSYS2](https://www.msys2.org/) and followed the instructions for 
"[Building a keyboard firmware](https://matt3o.com/building-a-keyboard-firmware/)" on Matt3o.com. 
Specifically, the instructions for setting up MSYS2 and downloading QMK. 

Notes:
* The git clone will be `git clone -b feature/riot_xap https://github.com/Massdrop/qmk_firmware` instead of 
  `git clone https://github.com/qmk/qmk_firmware`.
* I had to run `pacman -S $MINGW_PACKAGE_PREFIX-python-pip` before I could run `make git-submodule`.

Next copy all the files from the `qmk_firmware/keyboards/massdrop/ctrl/jgmortim` directory in this repo and place
them into the `qmk_firmware/keyboards/massdrop/ctrl/jgmortim` directory of the repo you cloned.

You can then use MSYS2 MINGW64 to compile this keymap using `qmk compile -kb massdrop/ctrl -km jgmortim`.

### Other OS

I'm currently only using Windows 10, so if you try to use this on Linux or Mac, you'll be figuring that out on your own.

## Flashing

Once you have your .bin, you can flash it using [mdloader](https://github.com/Massdrop/mdloader).
Use the command `mdloader --first --download massdrop_ctrl_jgmortim.bin --restart`.

## See Also

* [The QMK Tutorial](https://docs.qmk.fm/newbs)
  * [Setting Up Your QMK Environment](https://docs.qmk.fm/newbs_getting_started)
  * [Building Your First Firmware](https://docs.qmk.fm/newbs_building_firmware)
  * [Flashing Your Keyboard](https://docs.qmk.fm/newbs_flashing)

## Troubleshooting

### LEDs not turning on
If the LED are not turning on or if they turn off after being on for a second, it most likely means your keyboard is
not getting enough power. This is especially common if you're using a USB hub as they can struggle to deliver enough
power to all connected devices.

## Credits

* LED config code was mostly transferred from [matthewrobo keymap](https://github.com/Massdrop/qmk_firmware/tree/master/keyboards/massdrop/ctrl/keymaps/matthewrobo).
* RGB timeout code is based on the implementation in [endgame keymap](https://github.com/Massdrop/qmk_firmware/tree/feature/riot_xap/keyboards/massdrop/ctrl/keymaps/endgame)

## Misc

* The JSON files under `/resources/json/` are compatible with https://www.keyboard-layout-editor.com/ and were used
  to generate the images in this README.