#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _NUMPD 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  NUMPD,
  LOWER,
  RAISE,
  ADJUST,

};


/*
Send a keydown for alt, then keydown/up for tab, wait a bit to see if the key is pressed again (and if so send only tab but not change alt's status) then after some timeout send keyup for alt

↑↑ - Keyup (key release)
↓↓ - Keydown (key hold)
↓↑ - Keydown, Keyup (key press)
#  - Physical action
↘  - Transition

CASE 1:
  #LOWER↓↓
  ...
  #TAB↓↑ ↘
            ALT↓↓ ↘
                    TAB↓↑
  ...
  #TAB↓↑ ↘
          TAB↓↑
  ...
  ...
  ...
  ...
  ALT↑↑
  ...
  #LOWER↑↑

CASE 2: 
  #LOWER↓↓
  ...
  #TAB↓↑ ↘
            ALT↓↓ ↘
                    TAB↓↑
  ...
  #TAB↓↑ ↘
          TAB↓↑
  ...
  ...
  #LOWER↑↑
  ALT↑↑

WHILE(LOWER↓↓) {
    IF(TAB↓↑) {
      SEND ALT↓↓;
      START TIMER;
      SEND TAB↓↑;
    }
    WHILE (TIMER) {
      IF(TAB↓↑) {
        SEND TAB↓↑;
      }
    }
    IF(ALT↓↓ && !TIMER) {SEND ALT↑↑;}
}
IF(TIMER) {STOP TIMER;}



bool process_record_user(uint16_t keycode keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        // do something
      } else {
        // do something else
      }
      return false;
    default:
      return true;
  }
}


*/

#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_XXXX KC_NO
#define KC_QWER QWERTY
#define KC_GAM1 GAME1
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_NUMP NUMPD
#define KC_ADJS ADJUST
#define KC_SHUP S(KC_UP)
#define KC_SHDN S(KC_DOWN)
#define KC_SLFT S(KC_LEFT)
#define KC_SRGT S(KC_RGHT)
#define KC_SHOM S(KC_HOME)
#define KC_SEND S(KC_END)
#define KC_SPGU S(KC_PGUP)
#define KC_SPGD S(KC_PGDN)
#define KC_SMIN S(KC_MINS)
#define KC_SEQL S(KC_EQL)
#define KC_SBLS S(KC_BSLS)
#define KC_LRSP LT(_LOWER, KC_SPC)
#define KC_RSGU LT(_RAISE, KC_LGUI)
#define KC_RSBS LT(_RAISE, KC_BSPC)
#define KC_SENT SFT_T(KC_ENT)
#define KC_SESC SFT_T(KC_ESC)
#define KC_CESC CLT_T(KC_ESC)
#define KC_ATAB LALT(KC_TAB)
#define KC_AENT LALT(KC_ENT)
#define KC_NUMD MO(_NUMPD)
#define KC_RSET RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI // hue
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI // saturation
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI // brightness
#define KC_RVAD RGB_VAD
#define KC_RSPI RGB_SPI
#define KC_RSPD RGB_SPD
#define KC_RM_P RGB_M_P // static
#define KC_RM_B RGB_M_B // breathing
#define KC_RM_R RGB_M_R // rainbow
#define KC_RM_K RGB_M_K // knight rider
#define KC_RM_G RGB_M_G // static gradient
#define KC_RM_X RGB_M_X // christmas
#define KC_RMSN RGB_M_SN // snake
#define KC_RMSW RGB_M_SW // swirl

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
    GESC, 1   , 2   , 3   , 4   , 5   ,                   6   , 7   , 8   , 9   , 0   , BSPC,
    TAB , Q   , W   , E   , R   , T   ,                   Y   , U   , I   , O   , P   , DEL ,
    CESC, A   , S   , D   , F   , G   ,                   H   , J   , K   , L   , SCLN, QUOT,
    LSFT, Z   , X   , C   , V   , B   , LALT,       LGUI, N   , M   , COMM, DOT , SLSH, SENT,
                            LCTL, LOWR, SPC ,       SPC , RASE, LALT
  ),

  [_NUMPD] = LAYOUT_kc( 
    GESC, XXXX, XXXX, XXXX, XXXX, XXXX,                   SLCK, NLCK, PSLS, PAST, BSPC, BSPC,
    TAB , XXXX, XXXX, XXXX, XXXX, XXXX,                   PIPE, P7  , P8  , P9  , PMNS, DEL ,
    CESC, XXXX, XXXX, XXXX, XXXX, XXXX,                   COMM, P4  , P5  , P6  , PPLS, ENT ,
    LSFT, XXXX, XXXX, XXXX, XXXX, XXXX,     ,           , PDOT, P1  , P2  , P3  , PEQL, SENT,
                            LCTL, LALT,     ,           , P0  , ENT
  )

  [_LOWER] = LAYOUT_kc(
    GRV , XXXX, XXXX, XXXX, XXXX, XXXX,                   XXXX, XXXX, XXXX, XXXX, XXXX, BSPC,
    ATAB, PGUP, HOME, UP  , END , PGUP,                   SPGU, SHOM, SHUP, SEND, SPGU, DEL ,
    CESC, PGDN, LEFT, DOWN, RGHT, PGDN,                   SPGD, SLFT, SHDN, SRGT, SPGD, QUOT,
    LSFT, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,           , XXXX, XXXX, LEFT, UP  , DOWN, RGHT,
                            LCTL,     ,     ,           , RASE, LALT
  ),

  [_RAISE] = LAYOUT_kc(
    TILD, EXLM, AT  , HASH, DLR , PERC,                   CIRC, AMPR, ASTR, LPRN, RPRN, BSPC,
    ATAB, F1  , F2  , F3  , F4  , F5  ,                   XXXX, SMIN, SEQL, LCBR, RCBR, BSLS,
    CESC, F6  , F7  , F8  , F9  , F10 ,                   XXXX, MINS, EQL , LBRC, RBRC, SBLS,
    LSFT, F11 , F12 , XXXX, XXXX, XXXX, XXXX,           , XXXX, XXXX, MNXT, MPRV, MUTE, MPLY,
                            LCTL, LOWR,     ,           ,     , LALT
  ),

  [_ADJUST] = LAYOUT_kc(
    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,                   RM_P, RM_B, RM_R, RM_K, RM_G, RM_X, 
    RTOG, RMOD, RHUI, RSAI, RVAI, RSPI,                   XXXX, XXXX, XXXX, XXXX, RMSN, RMSW, 
    XXXX, BL_S, RHUD, RSAD, RVAD, RSPD,                   XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, 
    XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX,       DBUG, QWER, QWER, QWER, QWER, QWER, QWER,
                            XXXX,     , XXXX,       XXXX,     , RSET
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
/*
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  rgblight_disable();
  switch(layer) {
    case _QWERTY:
      rgblight_mode(14);
      break;

    case _LOWER:
      rgblight_mode(23);
      // rgblight_setrgb (0xFF, 0xFF, 0xFF);
      break;

    case _RAISE:
      rgblight_mode(20);
      // rgblight_setrgb (0x00, 0x00, 0xFF);
      break;

    case _ADJUST:
      rgblight_mode(1);
      // rgblight_setrgb (0x00, 0xFF, 0x00);
      break;
  }
}
*/



//  [_GAME1] = LAYOUT_kc(
//    GESC, F1  , F2  , F3  , F4  , F5  ,                   F6  , F7  , F8  , F9  , F10 , BSPC,
//    GRV , 1   , 2   , 3   , 4   , 5   ,                   6   , 7   , 8   , 9   , 0   , DEL ,
//    TAB , Q   , W   , E   , R   , T   ,                   Y   , U   , I   , O   , UP  , ENT ,
//    SESC, A   , S   , D   , F   , G   , B   ,       ADJS, H   , J   , K   , LEFT, DOWN, RGHT,
//                            LCTL, LALT, SPC ,       SPC , LGUI, LALT  
//  ),


//    case GAME1:
//      if (record->event.pressed) {
//        persistent_default_layer_set(1UL<<_GAME1);
//      }
//      return false;
//      break;
