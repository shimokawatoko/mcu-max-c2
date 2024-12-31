#ifndef MCUMAX_BOARD_H
#define MCUMAX_BOARD_H

#include "mcumax_types.h"

// ボードの初期化と操作
void mcumax_init(void);
void mcumax_clear_board(void);
void mcumax_reset_state(void);

// ピースの操作
mcumax_piece mcumax_get_piece(mcumax_square square);
mcumax_square mcumax_set_piece(mcumax_square square, mcumax_piece piece);
bool mcumax_is_square_valid(mcumax_square square);
bool mcumax_is_piece_color(mcumax_piece piece, uint8_t color);

// 手番関連
mcumax_piece mcumax_get_current_side(void);
void mcumax_switch_side(void);

// ボード状態の取得・設定
const mcumax_state* mcumax_get_state(void);
void mcumax_set_state(const mcumax_state* state);

// 評価値関連
int32_t mcumax_get_non_pawn_material(void);
int32_t mcumax_get_score(void);

#endif