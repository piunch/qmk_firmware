// Copyright 2022 Jorge Munoz (@Jorge Munoz)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define _BASE     0
#define _MEET     1
#define _GIT      2
#define _OBS      3
#define _MEDIA    4

// Tap Dance Declarations
enum {
    DIFF_LAYR
};

enum custom_keycodes {
    GITPUSH,
    GITADD,
    GITSTATUS,
    NEWBRANCH,
    COMASTER,
    GITCLONE,
    GITCOMMIT,
    RAGECOMM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* BASE
    * ,--------------------.
    * |   7  |   8  |  FN  |
    * |------+------+------|
    * |   4  |   5  |   6  |
    * |------+------+------|
    * |   1  |   2  |   3  |
    * `--------------------'
    */
    [_BASE] = LAYOUT(
        KC_7,       KC_8,       TD(DIFF_LAYR),
        KC_4,       KC_5,       KC_6,
        KC_1,       KC_2,       KC_3
    ),

    /* MEET
    * ,--------------------.
    * |  F5  | EXIT |  FN  |
    * |------+------+------|
    * | CHAT | ZOOM |  PIP |
    * |------+------+------|
    * | MUTE | WCAM | HAND |
    * `--------------------'
    */
    [_MEET] = LAYOUT(
        KC_F5,              LCTL(KC_W),         TD(DIFF_LAYR),
        LALT(LCTL(KC_C)),   LALT(LCTL(KC_M)),   LALT(KC_P),
        LCTL(KC_D),         LCTL(KC_E),         LALT(LCTL(KC_H))
    ),

    /* GIT
    * ,-----------------------------------.
    * | GITCLONE  | RAGECOMM  |     FN    |
    * |-----------+-----------+-----------|
    * | GITSTATUS | COMASTER  | NEWBRANCH |
    * |-----------+-----------+-----------|
    * |   GITADD  | GITCOMMIT |  GITPUSH  |
    * `-----------------------------------'
    */
    [_GIT] = LAYOUT(
        GITCLONE,     RAGECOMM,    TD(DIFF_LAYR),
        GITSTATUS,    COMASTER,    NEWBRANCH,
        GITADD,       GITCOMMIT,   GITPUSH
    ),

    /* OBS
    * ,-----------------------------------------.
    * | INITSTREAM |    ENDSTREAM   |     FN    |
    * |------------+----------------+-----------|
    * |    MAIN    |    DESKTOP     |  WEBCAM   |
    * |------------+----------------+-----------|
    * |  MUTE_MIC  |  MUTE_DESKTOP  |  INTRO    |
    * `-----------------------------------------'
    */
    [_OBS] = LAYOUT(
        KC_G,   KC_H,   TD(DIFF_LAYR),
        KC_D,   KC_E,   KC_F,
        KC_A,   KC_B,   KC_C
    ),

    /* MEDIA
    * ,---------------------------------------------.
    * |    SLEEP   |     WAKEUP     |       FN      |
    * |------------+----------------+---------------|
    * | PLAY/PAUSE |    PREVTRACK   |   NEXTTRACK   |
    * |------------+----------------+---------------|
    * |    MUTE    |   VOLUMEDOWN   |   NVOLUMEUP   |
    * `---------------------------------------------'
    */
    [_MEDIA] = LAYOUT(
        KC_SLEP,    KC_WAKE,    TD(DIFF_LAYR),
        KC_MPLY,    KC_MPRV,    KC_MNXT,
        KC_MUTE,    KC_VOLD,    KC_VOLU
    )
};

//MACRO ------------------------------------------------------- https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

    case GITPUSH:
        if (record->event.pressed) {
            SEND_STRING("git push");
            register_code(KC_ENTER);
        }else {
            unregister_code(KC_ENTER);
        }
        break;

    case GITADD:
        if (record->event.pressed) {
            SEND_STRING("git add --all");
            register_code(KC_ENTER);
        }else {
            unregister_code(KC_ENTER);
        }
        break;

    case GITCOMMIT:
        if (record->event.pressed) {
            SEND_STRING("git commit -m '");
        }
        break;

    case GITSTATUS:
        if (record->event.pressed) {
            SEND_STRING("git status");
            register_code(KC_ENTER);
        }else {
            unregister_code(KC_ENTER);
        }
        break;

    case NEWBRANCH:
        if (record->event.pressed) {
            SEND_STRING("git checkout -b ");
        }
        break;

    case COMASTER:
        if (record->event.pressed) {
            SEND_STRING("git checkout master");
            register_code(KC_ENTER);
            SEND_STRING("git pull");
            register_code(KC_ENTER);
        }else {
            unregister_code(KC_ENTER);
        }
        break;

    case GITCLONE:
        if (record->event.pressed) {
            SEND_STRING("git clone ");
        }
        break;

    case RAGECOMM:
        if (record->event.pressed) {
            SEND_STRING("git commit -m '(┛ಠ_ಠ)┛彡┻━┻'");
            register_code(KC_ENTER);
        }else {
            unregister_code(KC_ENTER);
        }
        break;

    }

    return true;
};

//TAPDANCE ------------------------------------------------------------------------- wan syazlina
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_TRIPLE_TAP,
    TD_FOUR_TAP,
    TD_FIVE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

//Tap Dance ----------------------------------------------------------------------

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
    }
    else if (state->count == 2) return TD_DOUBLE_TAP;
    else if (state->count == 3) return TD_TRIPLE_TAP;
    else if (state->count == 4) return TD_FOUR_TAP;
    else if (state->count == 5) {
        if (state->pressed) return TD_FIVE_HOLD;
    }
    return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);

//This allows the dumbpad to switch to other layers as it will turn off all active layer. I made it turn all possible layers.
//Not sure if there are better ways at handling this
            layer_off(0);
            layer_off(1);
            layer_off(2);
            layer_off(3);

    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:

            layer_on(0);
            break;
        case TD_DOUBLE_TAP:

            layer_on(1);
            break;

        case TD_TRIPLE_TAP:

            layer_on(2);
            break;

        case TD_FOUR_TAP:

            layer_on(3);
            break;

        case TD_FIVE_HOLD:
            reset_keyboard();
            break;

        default: break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {

  ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [DIFF_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};

// end of Tap Dance ----------------------------------------------------------------------