#ifndef CHPI7_OLED_STUFF_H
#define CHPI7_OLED_STUFF_H

#include QMK_KEYBOARD_H

#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_90;  // flips the display (270 for arasaka) 180 degrees if offhand
  }
  return rotation;
}

#define BIT_BASEW (0)
#define BIT_LOWER (1 << L_LOWER)
#define BIT_RAISE (1 << L_RAISE)
#define BIT_ADJUST (1 << L_ADJUST)

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case BIT_BASEW:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case BIT_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case BIT_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case BIT_ADJUST: case BIT_ADJUST|BIT_LOWER:
        case BIT_ADJUST|BIT_RAISE:
        case BIT_ADJUST|BIT_LOWER|BIT_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}
// ================================= KEYLOG END ====================

// Arasaka glitch gist: https://gist.github.com/aleksbrgt/48a8eb932dc1b6aa8f4b36ecd7c380d0

#define frame_size 512

static const char PROGMEM text_clean[frame_size] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f, 
  0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0, 
  0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x7f, 0xfe, 0xf9, 0xf1, 0xc3, 0x83, 0x03, 0x03, 
  0x03, 0x83, 0xc3, 0xf1, 0xf9, 0xfc, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78, 0x7b, 0x7f, 0x7f, 0x7f, 0x7e, 0x7c, 
  0x3e, 0x1f, 0x7f, 0x7f, 0x7b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0x7c, 0x3e, 0x1f, 0x1f, 0x1f, 
  0x1c, 0x1e, 0x1f, 0x1f, 0x1f, 0x9f, 0xdf, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3f, 0xff, 0xff, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0, 
  0xc0, 0xc0, 0xe0, 0xf8, 0xff, 0xff, 0x3f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xe1, 0x01, 0x03, 0x03, 0x07, 0x07, 
  0x87, 0xc3, 0xf3, 0xf9, 0xf9, 0xf8, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe, 
  0x3f, 0x1f, 0x07, 0x07, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x8f, 0xc3, 0xc1, 0xc0, 
  0x00, 0x9e, 0xde, 0xde, 0xdf, 0xdf, 0xcf, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xfe, 0x1f, 0x0f, 0x07, 0x07, 0x07, 
  0x07, 0x07, 0x07, 0x07, 0xc7, 0xe7, 0xf7, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x7f, 0x7e, 0xf8, 0xf0, 0xf0, 0xf0, 
  0xf0, 0xf0, 0xf8, 0x7e, 0x7f, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x3c, 0x3c, 0x01, 0x01, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x80, 
  0xc0, 0xf0, 0xf8, 0xfe, 0x7f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xcf, 0xef, 0xef, 0xef, 
  0x87, 0xc3, 0xef, 0xef, 0xef, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xff, 0x0f, 0x07, 0x03, 0x03, 0x03, 
  0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 0xfb, 0xf3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x3f, 0x3f, 0x7c, 0x78, 0xf8, 0xf8, 
  0xf8, 0x78, 0x7c, 0x3f, 0x3f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// static const char PROGMEM logo_clean[frame_size] = {
//   0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0xc3, 0xe3, 0xf3, 0xfb, 0xfb, 
//   0xfb, 0xfb, 0xf3, 0xe3, 0xc3, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 
//   0xf8, 0xfe, 0x07, 0xe1, 0xf0, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf3, 0xe7, 0x0f, 0x1f, 0xff, 
//   0xff, 0x1f, 0x0f, 0xe7, 0xf3, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf0, 0xe1, 0x07, 0xfe, 0xf8, 
//   0x1f, 0x7f, 0xe0, 0x81, 0x03, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x0f, 0x1d, 0x38, 0x70, 0xff, 
//   0xff, 0x70, 0x38, 0x1d, 0x0f, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x07, 0x03, 0x81, 0xe0, 0x7f, 0x1f, 
//   0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x60, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xdf, 
//   0xdf, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x60, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0xc0, 0x00, 0xe0, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0xe0, 0x00, 0x20, 0x20, 0x20, 0xe0, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x07, 0x00, 0x09, 0x09, 0x09, 0x06, 0x80, 0x80, 0x81, 
//   0x81, 0x80, 0x80, 0x00, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
//   0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0xc0, 0xc3, 0x43, 0xc7, 0xc7, 0xc7, 
//   0xc7, 0x47, 0xc7, 0x43, 0x43, 0x40, 0xc0, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 
//   0x00, 0xff, 0x40, 0x5f, 0xd1, 0x51, 0xd1, 0xdf, 0x40, 0x7f, 0x84, 0xf2, 0x86, 0x3f, 0x43, 0xee, 
//   0x0c, 0xe2, 0xca, 0xa4, 0x86, 0xad, 0xdc, 0xff, 0x40, 0x5f, 0x51, 0xd1, 0x51, 0x5f, 0xc0, 0xff, 
//   0x00, 0xff, 0xee, 0x42, 0x48, 0x3d, 0x14, 0x25, 0x55, 0x19, 0xb1, 0xca, 0x53, 0x80, 0x78, 0x12, 
//   0x9e, 0xab, 0x9c, 0x04, 0x9a, 0x25, 0x14, 0x47, 0xb4, 0x6b, 0xfb, 0x94, 0xd9, 0x11, 0xd6, 0xff, 
//   0x00, 0xff, 0x15, 0xde, 0x5d, 0x56, 0x5d, 0xd3, 0x15, 0xfe, 0xc3, 0x43, 0x82, 0xed, 0x78, 0xa7, 
//   0xd5, 0xf3, 0xbe, 0x4b, 0x9e, 0xeb, 0x05, 0x75, 0x50, 0x74, 0x07, 0xbe, 0xa7, 0xc9, 0xa8, 0xff, 
//   0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x17, 0x10, 0x1f, 0x12, 0x1e, 0x1c, 0x16, 0x10, 0x13, 
//   0x12, 0x17, 0x13, 0x11, 0x15, 0x1c, 0x13, 0x1d, 0x1e, 0x17, 0x10, 0x1c, 0x1c, 0x12, 0x1d, 0x1f, 
//   0x00, 0x00, 0x00, 0x00, 0x06, 0xc6, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0xc6, 0xc6, 0x46, 
//   0xc6, 0x46, 0x46, 0xc6, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0x46, 0xc6, 0x06, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x40, 0x5f, 0x51, 0xd1, 0x51, 0x5f, 0x40, 0x7f, 0x1d, 0x38, 
//   0x56, 0x38, 0x85, 0x7f, 0x40, 0xdf, 0xd1, 0xd1, 0x51, 0xdf, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x13, 0xd1, 0x52, 0x53, 0x5c, 0xd2, 0x15, 0xf9, 0x03, 0xff, 
//   0xb1, 0x0f, 0xb5, 0x0f, 0x52, 0x0f, 0xb5, 0xae, 0x54, 0xc5, 0x5a, 0xff, 0x00, 0x00, 0x00, 0x00, 
//   0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 0x14, 0x17, 0x10, 0x1f, 0x11, 0x17, 
//   0x1a, 0x1f, 0x15, 0x1f, 0x12, 0x1f, 0x15, 0x1f, 0x12, 0x1e, 0x15, 0x1f, 0x00, 0x00, 0x00, 0x00
// };

// void arasaka_logo_clean(void) {
//     oled_write_raw_P(logo_clean, frame_size);
// }

void arasaka_text_clean(void) {
    oled_write_raw_P(text_clean, frame_size);
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        arasaka_text_clean();
    }
    return false;
}

#endif // CHPI7_OLED_STUFF_H