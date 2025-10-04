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

/*
#include "qk_tap_dance.h" 
// --- タップダンスの定義ここから ---

// 1. タップダンスに名前を付けます
enum {
  TD_LAYER_ONE_TWO = 0
};

// 2. タップダンスの動作を定義する関数
void layer_tilde_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // 1回タップの時の動作: Escキーを送信
    register_code(MO(2));
  } else if (state->count == 2) {
    // 2回タップの時の動作: Shift + ` (チルダ) を送信
    register_code(MO(1));
  }
}

void layer_tilde_reset(qk_tap_dance_state_t *state, void *user_data) {
  // キーを離したときに、押したキーを離す処理
  unregister_code(MO(1));
  unregister_code(MO(2));
}

// 3. 上記の動作を、付けた名前に紐付けます
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_LAYER_ONE_TWO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layer_tilde_finished, layer_tilde_reset)
};

// --- タップダンスの定義ここまで ---
*/


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_BTN1  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , MT(MOD_LCTL, KC_COMM), MT(MOD_RGUI,KC_DOT), MT(MOD_RSFT, KC_BTN2)  ,
    MO(1)  , KC_ESC , KC_LALT  ,MT(MOD_LGUI,KC_BSPC),LT(2,KC_SPC),MT(MOD_LSFT,KC_TAB),  LT(2, KC_LNG2), KC_ENT, KC_NO, KC_NO ,KC_NO, MO(3)
  ),

  [1] = LAYOUT_universal(
    KC_NO    , KC_NO    , KC_NO    ,KC_NO    , KC_NO  ,                            KC_PMNS   , KC_KP_7    , KC_KP_8    , KC_KP_9    , KC_NO   ,
    KC_NO    , KC_NO    , KC_NO    ,KC_NO    , KC_NO  ,                            KC_KP_0   , KC_KP_4    , KC_KP_5    , KC_KP_6  , KC_TRNS  ,
    KC_NO    , KC_NO    , KC_NO    ,KC_NO    , KC_NO,                              KC_PDOT   , KC_KP_1    , KC_KP_2    , KC_KP_3  , KC_TRNS  ,
    KC_NO    , KC_NO    , KC_NO    , _______  , _______  , _______  ,              KC_TRNS   , KC_TRNS    , _______    , KC_NO    , KC_NO    , KC_NO
  ),

  [2] = LAYOUT_universal(
    KC_RCTL   , KC_LBRC    , KC_RBRC     , KC_SCLN    ,S(KC_SCLN)  ,               KC_NO  , KC_HOME  , KC_UP   , KC_END , KC_NO  ,
    KC_RCMD   , S(KC_9)    , S(KC_0)     , KC_BSLS    ,S(KC_BSLS)  ,               KC_NO  , KC_LEFT  , KC_DOWN , KC_RGHT, KC_TRNS  ,
    KC_RSFT   , S(KC_LBRC) , S(KC_RBRC)  , S(KC_QUOT) ,KC_QUOT     ,               KC_NO  , KC_NO    , KC_NO   , KC_NO  , KC_TRNS  ,
    KC_ESC    , S(KC_COMM) , S(KC_DOT)   , KC_TRNS   , KC_TRNS   , KC_TRNS  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    S(KC_5)  , S(KC_3)   , S(KC_6)  , S(KC_8)  , S(KC_EQL)  ,                            _______  , KC_WH_U , C(KC_UP) , KC_NO , KC_NO,
    S(KC_2)  , S(KC_4)   , KC_MINS  , KC_SLSH  , S(KC_EQL) ,                            KC_WH_L  , KC_WH_D , KC_WH_R  , _______  , _______  ,
    S(KC_GRV), S(KC_7)  , S(KC_MINS)  , S(KC_SLSH)  , S(KC_1) ,                            KC_NO  , KC_NO , KC_NO , KC_NO  , KC_NO ,
    KC_NO  , KC_NO  , _______  , _______  , _______  , _______  ,      KC_LNG1  , _______  , _______  , _______  , KC_NO  , KC_NO
  ),
};
// clang-format on

/*
layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}
*/

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
            rgblight_sethsv_noeeprom(HSV_BLUE);
            break;
        case 2: // Layer 2
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case 3: // Layer 3 (Scroll Mode)
            rgblight_sethsv_noeeprom(HSV_GOLD);
            break;
        case 4: // Shift+Cmd Mode Layer
            // Enable modifier keys on this layer
            add_mods(MOD_LSFT | MOD_LGUI);
            rgblight_sethsv_noeeprom(HSV_MAGENTA);
            break;
        default:
            // On any layer other than the Shift+Cmd one, make sure to clear the modifier keys
            del_mods(MOD_LSFT | MOD_LGUI);
            break;
    }
    return state;
}
#endif
