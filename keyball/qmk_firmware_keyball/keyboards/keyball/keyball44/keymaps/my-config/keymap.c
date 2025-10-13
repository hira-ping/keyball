/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include "quantum.h"

// 1. Define the keys for the combo.
const uint16_t PROGMEM enter_combo[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_I, KC_O, COMBO_END};


// 2. Define the combo key combination and the action it triggers.
combo_t key_combos[] = {
    COMBO(enter_combo, KC_ENT),
    COMBO(del_combo, KC_DEL),
};

// --- End of combo definitions ---


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // 0: 
  [0] = LAYOUT_universal(
    KC_NO,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_NO,
    KC_NO,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_BTN1,   KC_NO,
    MO(1),  MT(MOD_LSFT,KC_Z), MT(MOD_LGUI,KC_X) , MT(MOD_LCTL,KC_C),  KC_V,    KC_B,           KC_N,    KC_M,    MT(MOD_LCTL, KC_COMM), MT(MOD_RGUI,KC_DOT), MT(MOD_RSFT, KC_BTN2), KC_NO,
            KC_ESC,  KC_LALT, KC_BSPC, MO(2), KC_TAB ,         LT(1, KC_LNG2), LT(2,KC_SPC) , KC_NO, _______,   MO(3)
  ),

  // 1: 
  [1] = LAYOUT_universal(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_PMNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_NO,     KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_KP_0, KC_KP_4, KC_KP_5, KC_KP_6, KC_TRNS,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                                            KC_PDOT, KC_KP_1, KC_KP_2, KC_KP_3, KC_TRNS,   KC_NO,
             KC_NO,   KC_NO,   _______,   _______,   _______,                                      KC_TRNS, KC_TRNS, KC_NO ,_______,   _______
  ), 

  // 2: 
  [2] = LAYOUT_universal(
    KC_NO, KC_RCTL, KC_LBRC, KC_RBRC, KC_SCLN, S(KC_SCLN),                                       KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_NO,     KC_NO,
    KC_NO, KC_RCMD, S(KC_9), S(KC_0), KC_BSLS, S(KC_BSLS),                                       KC_NO,   KC_LEFT, KC_DOWN, KC_RGHT, KC_LALT,   KC_NO,
    KC_NO, KC_RSFT, S(KC_LBRC), S(KC_RBRC), S(KC_QUOT), KC_QUOT,                                 KC_NO, C(S(KC_TAB)), KC_NO, C(KC_TAB), KC_TRNS,   KC_NO,
                    S(KC_COMM), S(KC_DOT),KC_NO , _______,  _______,                             KC_TRNS, KC_TRNS, KC_NO , _______,   _______
  ),

  // 3: 
  [3] = LAYOUT_universal(
    S(KC_5), S(KC_5), S(KC_3), S(KC_6), S(KC_8), S(KC_EQL),                                        _______, KC_WH_U, C(KC_UP), KC_NO,   KC_NO,    KC_NO,
    S(KC_2), S(KC_2), S(KC_4), KC_MINS, KC_SLSH, KC_EQL,                                           KC_WH_L, KC_WH_D, KC_WH_R, _______, _______,   KC_NO,
    S(KC_GRV), S(KC_GRV), S(KC_7), S(KC_MINS), S(KC_SLSH), S(KC_1),                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,
               KC_GRV, KC_NO,  _______,   _______,    _______,                                     KC_LNG1, _______, KC_NO, _______,   _______
  ),
};
// clang-format on


#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    // Enable auto-scroll mode on Layer 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

    // First, always ensure the RGB light system is enabled
    rgblight_enable_noeeprom();

    switch (get_highest_layer(state)) {
        case 0: // Base layer
            // Turn off the light by setting brightness (value) to 0
            rgblight_sethsv_noeeprom(0, 0, 0);
            break;
        case 1: // Layer 1
            rgblight_sethsv_noeeprom(95, 255, 128);
            break;
        case 2: // Layer 2
            rgblight_sethsv_noeeprom(85, 255,	128);
            break;
        case 3: // Layer 3 (Scroll Mode)
            rgblight_sethsv_noeeprom(32, 255, 128);
            break;
    }
    return state;
}
#endif

// This function runs on every keyboard matrix scan.
void matrix_scan_user(void) {
  // This line calls led_update_user and passes the current LED state.
  led_update_user(host_keyboard_led_state()); 
}

bool led_update_user(led_t led_state) {
    uint8_t mods = get_mods();

   if (mods & MOD_MASK_SHIFT) { // while Shift is held
        rgblight_sethsv_noeeprom(128, 255, 128);
    } else if (mods & MOD_MASK_CTRL) { // while Ctrl is held
        rgblight_sethsv_noeeprom(0, 225, 255);
    } else if (mods & MOD_MASK_GUI) { // Command/Win key
        rgblight_sethsv_noeeprom(213, 255, 128);
    } else if (mods & MOD_MASK_ALT) { // Command/Win key
        rgblight_sethsv_noeeprom(0, 255, 128);
    } else {
        // If no modifier keys are pressed, revert to the layer color.
        layer_state_set_user(layer_state);
    }
    return true;
    
}