#include QMK_KEYBOARD_H // компиляция по QMK qmk compile -kb xd75 -km leo

#define L_OSNOVA 0 // слой 0 (основной)

#define SVIT(bt1, s1, bt2, s2, bt3, s3, bt4, s4) \
if (record->event.pressed) { \
  if (shift_held) { \
     if (alt_held) { \
      unregister_code(KC_F15); \
      if (s4 == 0) { \
        unregister_code(KC_LSFT); \
        tap_code(bt4); \
      } else { \
        tap_code(bt4); \
        unregister_code(KC_LSFT); \
       } \
    } else { \
      if (s2 == 0) { \
        unregister_code(KC_LSFT); \
        tap_code(bt2); \
      } else { \
        tap_code(bt2); \
        unregister_code(KC_LSFT); \
      } \
    } \
  } else { \
    if (alt_held) { \
      if (s3 == 0) { \
        tap_code(bt3); \
      } else { \
        register_code(KC_LSFT); \
        tap_code(bt3); \
        unregister_code(KC_LSFT); \
      } \
      unregister_code(KC_F15); \
    } else { \
      if (s1 == 0) { \
        tap_code(bt1); \
      } else { \
        register_code(KC_LSFT); \
        tap_code(bt1); \
        unregister_code(KC_LSFT); \
      } \
    } \
  } \
} \
return false;

#define CTRINS LCTL(KC_INS)
#define ALTBS LALT(KC_BSPC)
#define ALTYY LALT(KC_P2)
#define SFTINS LSFT(KC_INS)
#define KYO ALT_1

bool shift_held = false;
bool alt_held = false;

typedef struct { //назначение структуры нажатий https://docs.qmk.fm/#/feature_tap_dance?id=how-to-use
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    VYH, // Вых / альт+Ф4
    TABB, // таб / альт+таб
    WEMO, // окно / окно+точка
    LEV, // влево / домой
    PRAV, // вправо / в конец
    RU_AN, // кнопка Р/А
};

enum custom_keycodes {      
  ALT_1 = SAFE_RANGE,
  SL_1,
  KOP1,
  VST1,
  ALT_3,
  ALT_2,
  KCC_1,
  KCC_2,
  KCC_3,
  KCC_4,
  KCC_5,
  KCC_6,
  KCC_7,
  KCC_8,
  KCC_9,
  KCC_0,
  KCC_10,
}; 

enum combo_events { // обозначение комбо-команд
comb_TOCH,
comb_ZAP,
comb_TZ,
comb_DT,
comb_DEF,
comb_TIRE,
comb_VOS,
comb_VOP,
comb_REG1,
comb_REG2,
comb_PROB1,
comb_PROB2,
comb_NACH,
comb_KON,
comb_LEV,
comb_PRAV,
comb_VERH,
comb_VNIZ,
comb_VSH,
comb_VVOD,
comb_UDL,
comb_TAB,
comb_VIH,
comb_KOP1,
comb_VST1,
comb_UPR1,
comb_OTM,
comb_N1,
comb_N2,
comb_N3,
comb_N4,
comb_N5,
comb_N6,
comb_N7,
comb_N8,
comb_N9,
comb_N0,
comb_VSH2,
comb_INS,
comb_VYR,
comb_PER1,
comb_PER2,
comb_OCH,
comb_VVOD2,
comb_PER3,
comb_SOYI,
comb_BUKTZ,
};

uint8_t cur_dance(qk_tap_dance_state_t *state); // общая функция нажатий
void ql_finished(qk_tap_dance_state_t *state, void *user_data); //индивидуальные функции двойных нажатий
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { // определение матриц
/* Основа
 * ,-----------------------------------------------------------------------------------.
 * | КОП  | ВСТ  |  ,%# |  ;:₽ |  ?!& |  "'  |        /\| |  +=  | -_—  | .$   | («[{ | )»]} | 
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   C  |   X  |   U  |   ~  |   [  |  ВЫХ |        *@^  |   H  |   P  |   L  |   M  |   J  |счгчгшфуiaeiae
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   I  |   A  |   E  |   O  |   S  |  ТАБ |          ]  |   K  |   N  |   T  |   W  |   R  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |   /  |      |   Q  |   Y  |   \  |  Б/Ц |          F  |   G  |   D  |   B  |   V  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | УПР  | РЕГ  | ДОП  |  ГИП | ВВОД |  УД  |         ВШ  |пробел|  Р/А |  ОТМ |  ←   |   →  |
 * `-----------------------------------------------------------------------------------'
ц ь у ч ш ъ х п л м й
и а е о с щ к н т в р
э ё ы я ю ф г д б ж з
УПР ← НАЧ
УПР → КОН
УПР ↑ ВЕРХ      TD(WEMO),
УПР ↓ НИЗ
РЕГ ВШ  Отмена
 */
[L_OSNOVA] = LAYOUT_ortho_5x15( \
  KOP1,          VST1,         KCC_1,  KCC_2,    KCC_3,   KCC_4,    KC_F2,   KC_F4,  KC_F9,   KCC_5,   KCC_6,  KCC_7,    KCC_8,   KCC_9,   KCC_0, \
  KC_C,          KC_X,         KC_U,   KC_GRV,   KC_LBRC, TD(VYH),  KC_7,    KC_8,   KC_9,    KCC_10,  KC_H,   KC_P,     KC_L,    KC_M,    KC_J, \
  KC_I,          KC_A,         KC_E,   KC_O,     KC_S,    TD(TABB), KC_4,    KC_5,   KC_6,    KC_RBRC, KC_K,   KC_N,     KC_T,    KC_W,    KC_R, \
  KC_BSLS,       KYO,          KC_Q,   KC_Y,     KC_NUBS, KC_UP,    KC_1,    KC_2,   KC_3,    KC_F,    KC_G,   KC_D,     KC_B,    KC_V,    KC_Z, \
  KC_LCTL,       KC_LSFT,      KC_F15, KC_ENT,   KC_LEFT, KC_DOWN,  KC_RGHT, KC_0,   TD(WEMO),KC_SPC,  KC_SPC, TD(RU_AN),ALTBS,   KC_DEL,  KC_BSPC \
)
}; 

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        capslock_led_off();
    } else {
        capslock_led_on();
    }

    return false;
};


// задаем сочитание клавиш (комбо). Прописать их количество в файле config
const uint16_t PROGMEM TOCH_combo[] = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM ZAP_combo[] = {KC_U, KC_GRV, COMBO_END};
const uint16_t PROGMEM TZ_combo[] = {KC_E, KC_N, COMBO_END};
const uint16_t PROGMEM DT_combo[] = {KC_O, KC_T, COMBO_END};
const uint16_t PROGMEM DEF_combo[] = {KC_A, KC_W, COMBO_END};
const uint16_t PROGMEM TIRE_combo[] = {KC_I, KC_R, COMBO_END};
const uint16_t PROGMEM VOS_combo[] = {KC_U, KC_L, COMBO_END};
const uint16_t PROGMEM VOP_combo[] = {KC_X, KC_M, COMBO_END};
const uint16_t PROGMEM REG1_combo[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM REG2_combo[] = {KC_GRV, KC_S, COMBO_END};
const uint16_t PROGMEM PROB1_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM PROB2_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM NACH_combo[] = {KC_D, KC_B, COMBO_END};
const uint16_t PROGMEM KON_combo[] = {KC_V, KC_Z, COMBO_END};
const uint16_t PROGMEM LEV_combo[] = {KC_W, KC_T, COMBO_END};
const uint16_t PROGMEM PRAV_combo[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM VERH_combo[] = {KC_L, KC_M, COMBO_END};
const uint16_t PROGMEM VNIZ_combo[] = {KC_B, KC_V, COMBO_END};
const uint16_t PROGMEM VSH_combo[] = {KC_I, KC_A, COMBO_END};
const uint16_t PROGMEM VVOD_combo[] = {KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM UDL_combo[] = {KC_C, KC_X, COMBO_END};
const uint16_t PROGMEM TAB_combo[] = {KC_N, KC_R, COMBO_END};
const uint16_t PROGMEM VIH_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM KOP1_combo[] = {KC_X, KC_O, COMBO_END};
const uint16_t PROGMEM VST1_combo[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM UPR1_combo[] = {KC_E, KC_Y, COMBO_END};
const uint16_t PROGMEM OTM_combo[] = {KC_X, KC_U, COMBO_END};
const uint16_t PROGMEM N1_combo[] = {KC_Y, KC_N, COMBO_END};
const uint16_t PROGMEM N2_combo[] = {KC_Y, KC_T, COMBO_END};
const uint16_t PROGMEM N3_combo[] = {KC_Y, KC_W, COMBO_END};
const uint16_t PROGMEM N4_combo[] = {KC_Y, KC_R, COMBO_END};
const uint16_t PROGMEM N5_combo[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM N6_combo[] = {KC_Y, KC_P, COMBO_END};
const uint16_t PROGMEM N7_combo[] = {KC_Y, KC_L, COMBO_END};
const uint16_t PROGMEM N8_combo[] = {KC_Y, KC_M, COMBO_END};
const uint16_t PROGMEM N9_combo[] = {KC_Y, KC_J, COMBO_END};
const uint16_t PROGMEM N0_combo[] = {KC_Y, KC_K, COMBO_END};
const uint16_t PROGMEM VSH2_combo[] = {KC_EQL, KYO, COMBO_END};
const uint16_t PROGMEM INS_combo[] = {KC_X, KC_E, COMBO_END};
const uint16_t PROGMEM VYR_combo[] = {KYO, KC_O, COMBO_END};
const uint16_t PROGMEM PER1_combo[] = {KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM PER2_combo[] = {KC_D, KC_W, COMBO_END};
const uint16_t PROGMEM OCH_combo[] = {KC_Q, KC_Y, COMBO_END};
const uint16_t PROGMEM VVOD2_combo[] = {KC_O, KC_S, COMBO_END};
const uint16_t PROGMEM PER3_combo[] = {KC_N, KC_V, COMBO_END};
const uint16_t PROGMEM SOYI_combo[] = {KC_I, KC_N, COMBO_END};
const uint16_t PROGMEM BUKTZ_combo[] = {KC_I, KC_X, COMBO_END};
//const uint16_t PROGMEM DOP_combo[] = {KC_D, KC_T, COMBO_END};  // АЛЬТ



//связываем комбо с функциональными клавишами и действиями
combo_t key_combos[COMBO_COUNT] = { 
[comb_TOCH] = COMBO_ACTION(TOCH_combo),
[comb_ZAP] = COMBO_ACTION(ZAP_combo),
[comb_TZ] = COMBO_ACTION(TZ_combo),
[comb_DT] = COMBO_ACTION(DT_combo),
[comb_DEF] = COMBO(DEF_combo, KC_PMNS),
[comb_TIRE] = COMBO_ACTION(TIRE_combo),
[comb_VOS] = COMBO_ACTION(VOS_combo),
[comb_VOP] = COMBO_ACTION(VOP_combo),
  [comb_REG1] = COMBO_ACTION(REG1_combo), 
  [comb_REG2] = COMBO_ACTION(REG2_combo),
  [comb_PROB1] = COMBO(PROB1_combo, KC_SPC),
  [comb_PROB2] = COMBO(PROB2_combo, KC_SPC),
  [comb_NACH] = COMBO(NACH_combo, KC_HOME),
  [comb_KON] = COMBO(KON_combo, KC_END),
  [comb_LEV] = COMBO(LEV_combo, KC_LEFT),
  [comb_PRAV] = COMBO(PRAV_combo, KC_RGHT),
  [comb_VERH] = COMBO(VERH_combo, KC_UP),
  [comb_VNIZ] = COMBO(VNIZ_combo, KC_DOWN),
  [comb_VSH] = COMBO(VSH_combo, KC_BSPC),
[comb_VVOD] = COMBO(VVOD_combo, KC_ENT),
  [comb_UDL] = COMBO(UDL_combo, KC_DEL),
  [comb_TAB] = COMBO(TAB_combo, KC_TAB),
  [comb_VIH] = COMBO(VIH_combo, KC_ESC),
[comb_KOP1] = COMBO(KOP1_combo, CTRINS),
[comb_VST1] = COMBO(VST1_combo, SFTINS),
  [comb_UPR1] = COMBO_ACTION(UPR1_combo),
[comb_OTM] = COMBO(OTM_combo, ALTBS),
[comb_N1] = COMBO(N1_combo, KC_P1),
[comb_N2] = COMBO(N2_combo, KC_P2),
[comb_N3] = COMBO(N3_combo, KC_P3),
[comb_N4] = COMBO(N4_combo, KC_P4),
[comb_N5] = COMBO(N5_combo, KC_P5),
[comb_N6] = COMBO(N6_combo, KC_P6),
[comb_N7] = COMBO(N7_combo, KC_P7),
[comb_N8] = COMBO(N8_combo, KC_P8),
[comb_N9] = COMBO(N9_combo, KC_P9),
[comb_N0] = COMBO(N0_combo, KC_P0),
[comb_VSH2] = COMBO_ACTION(VSH2_combo),
[comb_INS] = COMBO(INS_combo, KC_INS),
[comb_VYR] = COMBO_ACTION(VYR_combo),
[comb_PER1] = COMBO_ACTION(PER1_combo),
[comb_PER2] = COMBO_ACTION(PER2_combo),
[comb_OCH] = COMBO_ACTION(OCH_combo),
[comb_VVOD2] = COMBO_ACTION(VVOD2_combo),
[comb_PER3] = COMBO_ACTION(PER3_combo),
[comb_SOYI] = COMBO_ACTION(SOYI_combo),
[comb_BUKTZ] = COMBO_ACTION(BUKTZ_combo),

};

// действия для комбо
void process_combo_event(uint16_t combo_index, bool pressed) { 
  switch(combo_index) {
    case comb_ZAP: // запятая
      if (pressed) {
        register_code(KC_3);
        unregister_code(KC_3);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
    case comb_TOCH: // точка
      if (pressed) {
        register_code(KC_8);
        unregister_code(KC_8);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        set_oneshot_mods (MOD_LSFT);
      }
      break;
    case comb_TZ: // точка c запятой
      if (pressed) {
        register_code(KC_4);
        unregister_code(KC_4);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
    case comb_DT: // двоеточие
      if (pressed) {
        register_code(KC_6);
        unregister_code(KC_6);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
    case comb_TIRE: // тире
      if (pressed) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        register_code(KC_LSFT);
        register_code(KC_5);
        unregister_code(KC_5);
        unregister_code(KC_LSFT);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
      }
      break;
    case comb_VOS: // !
      if (pressed) {
        register_code(KC_1);
        unregister_code(KC_1);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        set_oneshot_mods (MOD_LSFT);
      }
      break;
     case comb_VOP: // ?
      if (pressed) {
        register_code(KC_7);
        unregister_code(KC_7);
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        set_oneshot_mods (MOD_LSFT);
      }
      break;
    case comb_VSH2: // удалить целиком
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_BSPC);
        unregister_code(KC_BSPC);
        unregister_code(KC_LCTL);
      }
      break;
    case comb_VYR: // вырезать
      if (pressed) {
        tap_code16(LCTL(KC_X));
      }
      break;
    case comb_PER1: // alt shift таб
      if (pressed) {
        register_code(KC_LALT);
        register_code(KC_LSFT);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
        unregister_code(KC_LALT);
      }
      break;
    case comb_PER2: // ctr PGDN
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
        unregister_code(KC_LCTL);
      }
      break;
    case comb_OCH: // очистить строку
      if (pressed) {
        register_code(KC_END);
        unregister_code(KC_END);
        register_code(KC_LSFT);
        register_code(KC_HOME);
        unregister_code(KC_HOME);
        unregister_code(KC_LSFT);
        register_code(KC_DEL);
        unregister_code(KC_DEL);
      }
      break;    
    case comb_UPR1: // залипший упр (левый)
      if (pressed) {
        set_oneshot_mods (MOD_LCTL);
      }
      break;        
    case comb_REG1: // залипший Рег (левый)
      if (pressed) {
        set_oneshot_mods (MOD_LSFT);
      }
      break;    
    case comb_REG2: // пробел и залипший Рег (правый)
      if (pressed) {
        register_code(KC_SPC);
        unregister_code(KC_SPC);
        set_oneshot_mods (MOD_LSFT);
      }
      break;
    case comb_VVOD2: // контр ввод
      if (pressed) {
        tap_code16(LCTL(KC_ENT));
      }
      break;
    case comb_PER3: // ctr PGDN
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
        unregister_code(KC_LCTL);
      }
      break;
    case comb_SOYI: // ctr PGDN
      if (pressed) {
        tap_code(KC_SPC);
        tap_code(KC_I);
        tap_code(KC_SPC);
      }
      break;
    case comb_BUKTZ: // ctr PGDN
      if (pressed) {
        register_code(KC_LALT);
        tap_code(KC_P2);
        tap_code(KC_P3);
        tap_code(KC_P4);
        unregister_code(KC_LALT);
      }
      break;
  }
}

uint8_t cur_dance(qk_tap_dance_state_t *state) { // определение состояния двойного нажатия
    if (state->count == 1) { //если нажата один раз
        if (!state->pressed) return SINGLE_TAP; // если не удерживается, то Одиночное нажатие
        else return SINGLE_HOLD; // иначе Одиночное удержание
    } else if (state->count == 2) return DOUBLE_TAP; // если нажата два раза, то Двойное нажатие
    else return 8; // магическое число (на будущее)
}
static tap ql_tap_state = { // Инициализация двойного нажатия
    .is_press_action = true,
    .state = 0 // обнуление состояния
};
 

void x_finished(qk_tap_dance_state_t *state, void *user_data) { // функция реакции двойного нажатия Р/А. Действие при нажатии
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case SINGLE_TAP: register_code(KC_CAPS); break; // нажатие КАПС
        case SINGLE_HOLD: register_code(KC_CAPS); break; // нажатие КАПС
    }
}
void x_reset(qk_tap_dance_state_t *state, void *user_data) { // Действие при отпускании (то отключить слой)
    switch (ql_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_CAPS); break; // снятие КАПС
        case SINGLE_HOLD: register_code(KC_CAPS); break; // нажатие КАПС
    }
    ql_tap_state.state = 0; // обнуление состояния
};

qk_tap_dance_action_t tap_dance_actions[] = { // связка кнопок с функциями двойного нажатия
    [VYH] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, LALT(KC_F4)), // выход или альт+ф4
    [TABB] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LALT(KC_TAB)), // таб или альт+таб https://docs.qmk.fm/#/feature_macros?id=super-alt%e2%86%aftab
    [WEMO] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_DOT)), // вин или эмодзи
    [LEV] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME), // влево или домой
    [PRAV] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END), // вправо или в конец
    [RU_AN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset), // Р/А
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) { // https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions#programming-the-behavior-of-any-keycode-id-programming-the-behavior-of-any-keycode
  switch (keycode) { 
    case ALT_1:
      if (record->event.pressed) { //if (pressed) {
        register_code(KC_LALT); // SEND_STRING(SS_LALT("D83D+DC4D")); SEND_STRING(":yellow_yoshi:");
        tap_code(KC_P1);
        tap_code(KC_P3);
        tap_code(KC_P4);
        unregister_code(KC_LALT);
      }
      break;
    case KC_LSFT:
        shift_held = record->event.pressed;
    return true;
    break;
    case KC_F15:
        alt_held = record->event.pressed; // записать, что УПР нажат
    return true;
    break;
    case KCC_1:
      SVIT(KC_COMM, 0, KC_5, 1,  KC_3, 1, KC_INT1, 0)
    case KCC_2:
      SVIT(KC_SCLN, 0, KC_SCLN, 1,  KC_PDOT, 0, KC_3, 1)
    case KCC_3:
      SVIT(KC_SLSH, 1, KC_1, 1,  KC_7, 1, KC_3, 1)
    case KCC_4:
      SVIT(KC_QUOT, 1, KC_QUOT, 0,  KC_NUHS, 0, KC_NUHS, 1) //KC_NUHS, 0,
    case KCC_5:
      SVIT(KC_PSLS, 0, KC_BSLS, 0,  KC_BSLS, 1, KC_GRV, 1)
    case KCC_6:
      SVIT(KC_EQL, 1, KC_EQL, 0,  KC_INT4, 0, KC_ZKHK, 1)
    case KCC_7:
      SVIT(KC_PMNS, 0, KC_MINS, 1,  KC_INT5, 0, KC_3, 1)
    case KCC_8:
      SVIT(KC_DOT, 0, KC_4, 1,  KC_3, 1, KC_3, 1)
    case KCC_9:
      SVIT(KC_9, 1, KC_5, 1,  KC_3, 1, KC_3, 1)
    case KCC_0:
      SVIT(KC_0, 1, KC_5, 1,  KC_3, 1, KC_3, 1)
    case KCC_10:
      SVIT(KC_PAST, 0, KC_2, 1,  KC_6, 1, KC_3, 1)
    case ALT_3:
      SVIT(KC_SLSH, 0, KC_8, 1,  KC_COMM, 1, KC_DOT, 1)
    case SL_1: {
            if (record->event.pressed) {
        if (shift_held) {
                    //unregister_code(KC_LSFT);
                    register_code(KC_BSLS);
                } else {
          //register_code(KC_LSFT);
          register_code(KC_PSLS);
        }
              } else { // Release the key // https://www.reddit.com/r/olkb/comments/4u36wk/qmk_question_how_do_i_make_backspace_send_delete/d5mh93e/
          unregister_code(KC_LSFT); // https://github.com/qmk/qmk_firmware/issues/7840
          unregister_code(KC_PSLS); // https://github.com/qmk/qmk_firmware/blob/master/users/spacebarracecar/spacebarracecar.h
          unregister_code(KC_BSLS); // https://github.com/jeherve/qmk_firmware/blob/06206a9d5bfcbf96d65394b8bed495dc7b0ddf70/keyboards/redox/keymaps/jeherve/keymap.c#L64-L109
          }
          return false;
          break;
              }
    case KOP1:
            if (record->event.pressed) {
        if (shift_held) {
          unregister_code(KC_LSFT);
          tap_code16(LCTL(KC_DEL));
                } else {
          tap_code16(LCTL(KC_INS));
        }
        }
          break;
    case VST1:
            if (record->event.pressed) {
        if (shift_held) {
                    unregister_code(KC_LSFT);
                    tap_code(KC_INS);
                } else {
          tap_code16(LSFT(KC_INS));
        }
        }
          break;
  }
  return true;
}