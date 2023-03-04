/* Copyright 2022 DZTECH <moyi4681@Live.cn>
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

enum layers {
    _LAYER0,
    _LAYER1,
    _LAYER2,
    _LAYER3,
};

enum custom_keycodes {
    WINLOCKON = SAFE_RANGE, 
    WINLOCKOFF
};

int winLockSentinel = 0; // 0 for WINLOCKON, 1 for WINLOCKOFF

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 
    switch (keycode) {
        case WINLOCKON: //when pressed, turns winlock and the LED on. LED located at default scroll lock location
            if (record->event.pressed) {
                // when keycode WINLOCKON is pressed
                process_magic(QK_MAGIC_GUI_OFF, record);
                if (winLockSentinel == 0) { //Only changes LED if winlock changes from on to off.
                    SEND_STRING(SS_TAP(X_SCROLL_LOCK));
                    winLockSentinel++;
                }            
            } else {
                // when keycode WINLOCKON is released
            }
            break;
        case WINLOCKOFF:    //when pressed, turns winlock and the LED OFF. LED located at default scroll lock location
            if (record->event.pressed) {
                // when keycode WINLOCKOFF is pressed          
                 process_magic(QK_MAGIC_GUI_ON, record);
                if (winLockSentinel == 1) { // Only changes LED if winlock changes from off to on.
                    SEND_STRING(SS_TAP(X_SCROLL_LOCK));
                    winLockSentinel--;
                }

            } else {
                // when keycode WINLOCKOFF is released
            }
            break;

    }
    return true;
};




    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE,    KC_PSCR, WINLOCKON, KC_MPLY,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_VOLD,   KC_VOLU,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,    KC_MYCM,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, MO(1),   KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LAYER1] = LAYOUT_tkl_f13_ansi_tsangan(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      BL_TOGG, WINLOCKOFF, RGB_TOG,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      BL_STEP, RGB_RMOD,  RGB_MOD,
        KC_NO,   RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,      BL_BRTG, KC_NO,  KC_NO,
        KC_NO,   RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO,   KC_NO,   KC_NO,   KC_K,    KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,               KC_NO,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                                       KC_NO,   KC_NO,   KC_NO,      KC_NO,   KC_NO, KC_NO
    ),
};
