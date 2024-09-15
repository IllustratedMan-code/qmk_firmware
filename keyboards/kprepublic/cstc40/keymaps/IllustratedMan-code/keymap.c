/* Copyright 2023
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum cstc40_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _PLOVER,
    _ADJUST
}
enum cstc40_keycodes {
    QWERTY = SAFE_RANGE,
    Plover,
    EXT_PLV
}
#define LOWER TL_LOWR
#define RAISE TL_UPPR

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    ESCCTRL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, QUOTALT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHFTENT,
    KC_LCTL,  PLOVER, KC_LGUI, KC_LALT,  LOWER, KC_SPC,    RAISE,   KC_RCTL, KC_VOLD, KC_VOLU, KC_KB_MUTE
),

[_LOWER] = LAYOUT_planck_mit(
    _______, _______, KC_PGUP, KC_UP,    KC_PGDN, _______, _______, KC_7,    KC_8,    KC_9,   _______, _______,
    _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_LPRN, KC_RPRN, KC_4,    KC_5,    KC_6,   KC_PLUS, _______,
    _______, _______, _______, KC_LBRC,  KC_RBRC, KC_EQL, _______, KC_1,    KC_2,    KC_3,   _______, _______,
    _______, _______, _______, _______,  _______, _______, _______, KC_0,    KC_DOT, _______, _______, _______
),

[_RAISE] = LAYOUT_planck_mit(
    KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINUS, KC_BSLS, KC_PIPE,
    _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______, _______, _______, KC_UNDS,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______
),

[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),

[_ADJUST] = LAYOUT_planck_grid(
    QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PLOVER:
      if (record->event.pressed) {
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _PLOVER:
            rgb_matrix_set_color(led_min, RGB_GREEN);
            break;
        default:
            break;
    }
    return false;
}