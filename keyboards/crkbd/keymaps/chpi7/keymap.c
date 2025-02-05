/*
    chpi7's personal keymap and oled config.
*/

#include QMK_KEYBOARD_H
#include "keymap_german.h"

bool is_alt_tab_active = false;

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    _LOWER,
    _RAISE,
};

#define L_BASEW 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_BASEW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         DE_Z,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, DE_PLUS, KC_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    DE_Y,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, DE_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  _LOWER,  KC_SPC,LSFT_T(KC_ESC),_RAISE, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

  [L_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ALT_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, DE_HASH, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,    _______, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [L_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DE_CIRC, DE_EXLM, DE_DQUO, DE_SECT,  DE_DLR, DE_PERC,                      DE_AMPR, DE_SLSH, DE_LPRN, DE_RPRN,  DE_EQL, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, DE_LABK, DE_RABK, XXXXXXX, XXXXXXX, XXXXXXX,                      DE_QUOT, DE_BSLS, DE_LBRC, DE_RBRC, DE_QUES, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      DE_TILD, DE_PIPE, DE_LCBR, DE_RCBR,  DE_GRV, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,    _______, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [L_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,   DE_AT, XXXXXXX, DE_EURO,   KC_F4,   KC_F5,                        KC_F6, DE_UDIA, XXXXXXX, DE_ODIA,  KC_F12,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, DE_ADIA,   DE_SS, RGB_HUI, RGB_SAI, RGB_VAI,                      KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ESC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
#include "oled_stuff.h"
#endif



void stop_alt_tab(void) {
    if (!is_alt_tab_active) return;
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
#endif
    switch (keycode) {
        case _LOWER:
            if (record->event.pressed) {
                layer_on(L_LOWER);
            } else {
                layer_off(L_LOWER);
                stop_alt_tab();
            }
            update_tri_layer(L_LOWER, L_RAISE, L_ADJUST);
            return false;
        case _RAISE:
            if (record->event.pressed) {
                layer_on(L_RAISE);
            } else {
                layer_off(L_RAISE);
            }
            update_tri_layer(L_LOWER, L_RAISE, L_ADJUST);
            return false;
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}
