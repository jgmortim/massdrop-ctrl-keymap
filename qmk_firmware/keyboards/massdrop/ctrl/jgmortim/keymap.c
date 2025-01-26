#include QMK_KEYBOARD_H

#define MILLISECONDS_IN_SECOND 1000

#define CYAN {HSV_CYAN}
#define DIM_RED {0, 255, 100}
#define DIM_WHITE {0, 0, 100}
#define ______ {HSV_BLACK} // 5 underscores instead of the 6 used by the KC_TRNS alias.

#define RGB_TIME_OUT 300  // 300 seconds (5 minutes).

extern rgb_config_t rgb_matrix_config;

bool rgb_enabled_flag;                  // Current LED state flag. If false then LED is off.
bool rgb_time_out_enable;               // Idle LED toggle enable. If false then LED will not turn off after idle timeout.
bool rgb_time_out_user_value;           // This holds the toggle value set by user with ROUT_TG. It's necessary as RGB_TOG changes timeout enable.
uint16_t rgb_time_out_seconds;          // Idle LED timeout value, in seconds not milliseconds
led_flags_t rgb_time_out_saved_flag;    // Store LED flag before timeout so it can be restored when LED is turned on again.

enum tapdance_keycodes {
    TD_ALT_SL = 0 // Tap dance key to switch to Spanish layer
};

enum layout_names {
    _KL=0,       // Keys Layout: The main keyboard layout that has all the characters
    _FL,         // Function Layout: The function key activated layout with default functions
    _NL,         // Numpad Layout: Adds a numpad
    _SL          // Spanish Layout: Spanish accented letter macros
};

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};

enum custom_keycodes {
    // The start of this enum should always be equal to end of ctrl_keycodes + 1
    A_ACUTE = MD_BOOT + 1, // A with acute accent
    E_ACUTE,               // E with acute accent
    I_ACUTE,               // I with acute accent
    O_ACUTE,               // O with acute accent
    U_ACUTE,               // U with acute accent
    ENE,                   // N with tilde accent
    INV_EXC,               // Inverted exclamation point
    INV_QUS                // Inverted question mark
};

static uint16_t idle_timer;             // Idle LED timeout timer
static uint16_t idle_second_counter;    // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;       // This counter is used to check if any keys are being held

/* Associate tap dance key with its functionality */
tap_dance_action_t tap_dance_actions[] = {
    [TD_ALT_SL] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LALT, 3)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_KL] = LAYOUT(
        KC_ESC,       KC_F1,   KC_F2,         KC_F3, KC_F4, KC_F5,  KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUS,
        LT(2,KC_GRV), KC_1,    KC_2,          KC_3,  KC_4,  KC_5,   KC_6,  KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,       KC_Q,    KC_W,          KC_E,  KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS,      KC_A,    KC_S,          KC_D,  KC_F,  KC_G,   KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,      KC_Z,    KC_X,          KC_C,  KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                            KC_UP,
        KC_LCTL,      KC_LGUI, TD(TD_ALT_SL),               KC_SPC,                        KC_RALT, MO(1),   KC_APP,  KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FL] = LAYOUT(
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MUTE, _______, _______,
        _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MSTP, KC_VOLU,
        _______, RGB_SPD,  RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,
        _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG,  _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                            _______,
        _______, _______,  _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
    ),
    [_NL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_KP_7, KC_KP_8, KC_KP_9,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
    ),
    [_SL] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, INV_EXC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, E_ACUTE, _______, _______, _______, U_ACUTE, I_ACUTE, O_ACUTE, _______, _______, _______, _______, _______, _______, _______,
        _______, A_ACUTE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, ENE,     _______, _______, _______, INV_QUS, _______,                            _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,          _______, _______, _______
    )
};

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [_KL] = {
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,                         ______,
        ______, ______, ______,                 ______,                         ______, ______, ______, ______,         ______, ______, ______,
        /* Boarder; starts bottom right and moves clockwise */
        DIM_RED, DIM_RED,   DIM_WHITE, DIM_RED, DIM_RED, DIM_RED, DIM_WHITE, DIM_RED, DIM_RED, DIM_RED, DIM_WHITE, DIM_RED, DIM_RED,
        DIM_RED, DIM_WHITE, DIM_RED,
        DIM_RED, DIM_RED,   DIM_WHITE, DIM_RED, DIM_RED, DIM_RED, DIM_WHITE, DIM_RED, DIM_RED, DIM_RED, DIM_WHITE, DIM_RED, DIM_RED,
        DIM_RED, DIM_WHITE, DIM_RED
    },
    [_FL] = {
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,                         ______,
        ______, ______, ______,                 ______,                         ______, ______, ______, ______,         ______, ______, ______
    },
    [_NL] = {
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         CYAN,    CYAN,   CYAN,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, CYAN,    CYAN,   CYAN,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, CYAN,   CYAN,    CYAN,   CYAN,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, CYAN,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,                          ______,
        ______, ______, ______,                 ______,                         ______, ______, ______, ______,          ______, ______, ______,
        /* Boarder; starts bottom right and moves clockwise */
        CYAN,   CYAN,   CYAN,   ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, CYAN,   CYAN,   CYAN,
        CYAN,   CYAN,   CYAN
    },
    [_SL] = {
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,
        ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,                         ______,
        ______, ______, CYAN,                   ______,                         ______, ______, ______, ______,         ______, ______, ______
    }
};

/* Runs just one time when the keyboard initializes. */
void matrix_init_user(void) {
    idle_second_counter = 0;                            // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                              // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_TIME_OUT;                // RGB timeout initialized to its default.
    rgb_time_out_enable = true;                         // Enable RGB timeout by default.
    rgb_enabled_flag = true;                            // Initially, keyboard RGB is enabled.
    rgb_time_out_saved_flag = rgb_matrix_get_flags();   // Save RGB matrix state for when keyboard comes back from ide.
};

/* Runs just one time after everything else has initialized. */
void keyboard_post_init_user(void) {
    rgb_matrix_enable();
}

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {
    if(rgb_time_out_enable && rgb_enabled_flag) {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter) {
            idle_second_counter = 0;
        } else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND) {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds) {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
};

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

void send_string_without_mods(const char *string) {
    uint8_t mod_state = get_mods(); // Gets the current mods
    unregister_mods(mod_state);     // Turns all active mods off
    SEND_STRING(string);            // Sends the string
    register_mods(mod_state);       // And restores the mods to their original state
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    // Increment key event counter for every press and decrement for every release.
    if (record->event.pressed) {
        key_event_counter++;
    } else {
        key_event_counter--;
    }

    if (rgb_time_out_enable) {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag) {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    switch (keycode) {
        case A_ACUTE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase A with acute accent: ALT + 0193
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_3)));
                } else {          // Lowercase a with acute accent: ALT + 0225
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_5)));
                }
            }
            layer_off(3);
            return false;
        case E_ACUTE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase E with acute accent: ALT + 0201
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_1)));
                } else {          // Lowercase e with acute accent: ALT + 0233
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_3)));
                }
            }
            layer_off(3);
            return false;
        case I_ACUTE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase I with acute accent: ALT + 0205
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_5)));
                } else {          // Lowercase i with acute accent: ALT + 0237
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_7)));
                }
            }
            layer_off(3);
            return false;
        case O_ACUTE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase O with acute accent: ALT + 0211
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_1)));
                } else {          // Lowercase o with acute accent: ALT + 0243
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_3)));
                }
            }
            layer_off(3);
            return false;
        case U_ACUTE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase U with acute accent: ALT + 0218
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_8)));
                } else {          // Lowercase u with acute accent: ALT + 0250
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_5) SS_TAP(X_KP_0)));
                }
            }
            layer_off(3);
            return false;
        case ENE:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Uppercase N with tilde accent: ALT + 0209
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_0) SS_TAP(X_KP_9)));
                } else {          // Lowercase n with tilde accent: ALT + 0241
                    SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_1)));
                }
            }
            layer_off(3);
            return false;
        case INV_EXC:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Inverted exclamation point: ALT + 161
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_6) SS_TAP(X_KP_1)));
                } else {
                    SEND_STRING("1");
                }
            }
            layer_off(3);
            return false;
        case INV_QUS:
            if (record->event.pressed) {
                if (MODS_SHIFT) { // Inverted question mark: ALT + 191
                    send_string_without_mods(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_1)));
                } else {
                    SEND_STRING("/");
                }
            }
            layer_off(3);
            return false;
        // DEFAULTS BELOW
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

void set_layer_color(int layer) {
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer != _FL) {
            // Only read lower layer LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            bool is_undefined = true;
            // Attempt to get HSV values from a lower active layer, working down from the current layer.
            for (int lower_layer_j = layer - 1; lower_layer_j >= 0; lower_layer_j--) {
                // IS_LAYER_ON(_KL) returns false for some reason, might have something to do with it being the default
                // layer. For my purposes, _KL is always active so I added "|| lower_layer_j == _KL".
                if (IS_LAYER_ON(lower_layer_j) || lower_layer_j == _KL) {
                    HSV lower_hsv = {
                        .h = pgm_read_byte(&ledmap[lower_layer_j][i][0]),
                        .s = pgm_read_byte(&ledmap[lower_layer_j][i][1]),
                        .v = pgm_read_byte(&ledmap[lower_layer_j][i][2]),
                    };
                    if (lower_hsv.h || lower_hsv.s || lower_hsv.v) {
                        RGB rgb = hsv_to_rgb(lower_hsv);
                        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
                        rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
                        is_undefined = false;
                        break;
                    }
                }
            }

            if (is_undefined) {
                // If the values are all false then it's a transparent key and deactivate LED at this layer
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return true;
        }
    set_layer_color(get_highest_layer(layer_state));
    return false;
}