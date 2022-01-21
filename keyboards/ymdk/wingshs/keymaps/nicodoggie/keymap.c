/* Copyright 2021 alittlepeace
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warran 1ty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <time.h>
#include <stdlib.h>

// Custom Keycodes
enum custom_keycodes {
    KC_CUST_DF = SAFE_RANGE,
};

// Layer names
enum {
  LY_QWERTY,
  LY_NORMAN,
  LY_1,
  LY_2,
  LY_3
};

const uint8_t layout_layers[] = {LY_QWERTY, LY_NORMAN};

// Persistence
typedef union {
  uint32_t raw;
  struct {
    uint8_t default_layer :8;
  };
} user_config_t;

user_config_t user_config;

// Unicode mapping

enum unicode_names { BANG, IRONY, SNEK, THINKING, THUMBSUP, THUMBSDOWN, DEGREES, FUCK, LOL, MOAI };

const uint32_t PROGMEM unicode_map[] = {
    [BANG]       = 0x203D,   // ‽
    [IRONY]      = 0x2E2E,   // ⸮
    [SNEK]       = 0x1F40D,  // 🐍
    [THINKING]   = 0x1F914,  // 🤔
    [THUMBSUP]   = 0x1F44D,  // 👍
    [THUMBSDOWN] = 0x1F44E,  // 👎
    [DEGREES]    = 0x00B0,   // °
    [FUCK]       = 0x1F595,  // 🖕
    [LOL]        = 0x1F923,  // 🤣
    [MOAI]       = 0x1f5ff,  // 🗿
};

// Tap Dance declarations

enum {
    TD_ESC_KEYLOCK,
    TD_SHIFT_CAPS,
    TD_MENU_LAYER3,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_KEYLOCK] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_LOCK),
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS_LOCK),
    [TD_MENU_LAYER3] = ACTION_TAP_DANCE_LAYER_MOVE(KC_APPLICATION, LY_3 - 1),
};

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LY_QWERTY] = LAYOUT_all(
    KC_GRAVE,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_CUST_DF,        KC_PSCR,
    KC_TAB,    KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,        KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_MPLY,
    KC_LCTL,   KC_A,  KC_S,    KC_D,    KC_F,    KC_G,    KC_H,        KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ESC,                  DF(0),
    TD(TD_SHIFT_CAPS),   KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,        KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,           KC_VOLU,
    KC_LGUI,   KC_LALT,        LT(LY_1, KC_SPC),  LT(LY_2, KC_ENT),              KC_BACKSPACE, TD(TD_MENU_LAYER3),         KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [LY_NORMAN] = LAYOUT_all(
    KC_GRAVE,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_CUST_DF,        KC_PSCR,
    KC_TAB,    KC_Q,  KC_W,    KC_D,    KC_F,    KC_K,    KC_J,        KC_U,    KC_R,    KC_L,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,        KC_MPLY,
    KC_LCTL,   KC_A,  KC_S,    KC_E,    KC_T,    KC_G,    KC_Y,        KC_N,    KC_I,    KC_O,    KC_H,    KC_QUOT, KC_ESC,                  DF(0),
    TD(TD_SHIFT_CAPS),   KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_P,        KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,           KC_VOLU,
    KC_LGUI,   KC_LALT,        LT(LY_1, KC_SPC),  LT(LY_2, KC_ENT),              KC_BACKSPACE, TD(TD_MENU_LAYER3),         KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [LY_1] = LAYOUT_all(
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,  _______,        _______,
    KC_CAPS, KC_PGUP, KC_UP,   KC_PGDN,  KC_HOME, KC_INS, _______,     KC_CUT, KC_COPY, KC_PASTE, KC_FIND, _______, _______, KC_DEL,           _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,  KC_DEL, _______,     _______, _______, _______, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,          _______,
    _______,          _______,          _______, _______,              _______,          _______,                   _______, _______, _______
  ),

  [LY_2] = LAYOUT_all(
    _______, _______,       _______,        _______,       _______, _______,              _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, MEH(KC_LEFT),  SGUI(KC_LEFT),  MEH(KC_RIGHT), _______, _______,              _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, LCA(KC_LEFT),  SGUI(KC_RIGHT), LCA(KC_RIGHT), _______, _______,              X(THINKING), X(THUMBSUP), X(THUMBSDOWN), _______, _______, _______, _______,     _______,
    _______, LGUI(KC_LEFT), LGUI(KC_UP),   LGUI(KC_RIGHT), LGUI(KC_DOWN), _______,        X(DEGREES), X(FUCK), X(SNEK), _______, _______, _______,          _______,
    _______,          _______,          _______, _______,                                 _______, TO(LY_3),                                          _______, _______, _______
  ),
  [LY_3] = LAYOUT_all(
    _______, _______, _______, _______, _______, _______,          _______,    _______,    _______,     _______,       _______, _______, _______, _______,          _______,
    _______, _______, KC_UP,   _______, _______, _______,          KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  KC_MS_WH_UP,   _______, _______, _______, _______,          _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_MS_WH_DOWN, _______, _______, _______,                   _______,
    _______, _______, _______, _______, _______, _______,          _______, _______, _______,    _______,   _______,     _______,          _______,
    _______,          _______,          _______, _______,              _______,          TO(LY_QWERTY),                                   _______, _______, _______
  )
};

// RGB Backlight layers
#define HSV_CUST_PINK 236, 180, 250
#define HSV_CUST_SKYBLUE 119, 200, 240
#define HSV_CUST_MINT 106, 200, 240
#define HSV_CUST_LAVENDER 236, 255, 250

const rgblight_segment_t PROGMEM rgblight_capslock[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED}, {13, 2, HSV_RED}, {30, 1, HSV_RED});
const rgblight_segment_t PROGMEM rgblight_layer0[]   = RGBLIGHT_LAYER_SEGMENTS({2, 11, HSV_CUST_SKYBLUE}, {59, 1, HSV_CUST_PINK}, {60, 1, HSV_CUST_MINT});
const rgblight_segment_t PROGMEM rgblight_layer1[]   = RGBLIGHT_LAYER_SEGMENTS({2, 11, HSV_CUST_PINK});
const rgblight_segment_t PROGMEM rgblight_layer2[]   = RGBLIGHT_LAYER_SEGMENTS({2, 11, HSV_CUST_MINT}, {62, 1, HSV_CUST_LAVENDER});
const rgblight_segment_t PROGMEM rgblight_layer3[]   = RGBLIGHT_LAYER_SEGMENTS({2, 11, HSV_CUST_LAVENDER}, {62, 1, HSV_CUST_SKYBLUE});

const rgblight_segment_t* const PROGMEM wings_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(rgblight_capslock, rgblight_layer0, rgblight_layer1, rgblight_layer2, rgblight_layer3);

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.default_layer = LY_QWERTY;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    rgblight_layers = wings_rgblight_layers;
};

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_CUST_DF:
            if(record->event.pressed) {
                uint8_t size = sizeof(layout_layers)/sizeof(layout_layers[0]);
                #ifdef CONSOLE_ENABLE
                uprintf("default_layer: %d %d\n",user_config.default_layer, size);
                #endif
                user_config.default_layer = (user_config.default_layer+1)  % size;
                default_layer_set(user_config.default_layer);
                set_single_persistent_default_layer(user_config.raw);
            }
            return false;
            break;
    }
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, LY_QWERTY));
    rgblight_set_layer_state(0, layer_state_cmp(state, LY_NORMAN));

    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, LY_QWERTY));
    rgblight_set_layer_state(1, layer_state_cmp(state, LY_NORMAN));
    rgblight_set_layer_state(2, layer_state_cmp(state, LY_1));
    rgblight_set_layer_state(3, layer_state_cmp(state, LY_2));
    rgblight_set_layer_state(4, layer_state_cmp(state, LY_3));
    return state;
}

