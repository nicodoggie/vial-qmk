/*
Copyright 2020 Pabile

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    DBLZERO = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DBLZERO:
        if (record->event.pressed) {
            tap_code(KC_P0);
            tap_code(KC_P0);
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x4(
        BL_TOGG, BL_BRTG, KC_PAST, KC_PMNS, 
        KC_P7,   KC_P8,   KC_P9,   KC_TAB, 
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS, 
        KC_P1,   KC_P2,   KC_P3,   KC_DEL, 
        KC_P0,   DBLZERO, KC_PDOT, KC_PENT)
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      backlight_decrease();
    } else {
      backlight_increase();
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
     tap_code16(C(KC_MINS)); /* zoom in */
    } else { 
     tap_code16(C(KC_EQL)); /* zoom out */
    }
  } else if (index == 2) { /* Third encoder */  
    if (clockwise) {
      tap_code(KC_WH_U); /* mouse wheel up */
    } else {
      tap_code(KC_WH_D); /* mouse wheel down */
    }
  } else if (index == 3) { /* Forth encoder */
    if (clockwise) {
      tap_code(KC_VOLU); /* volume up */
    } else {
      tap_code(KC_VOLD); /* volume down */
    }
  }
}
