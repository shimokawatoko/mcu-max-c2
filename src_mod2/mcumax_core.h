#ifndef MCUMAX_CORE_H
#define MCUMAX_CORE_H

#include "mcumax_types.h"

// 指し手の実行と検証
bool mcumax_play_move(mcumax_move move);
bool mcumax_is_move_valid(mcumax_move move);
bool mcumax_is_move_legal(mcumax_move move);
void mcumax_undo_move(void);

// 指し手生成
void mcumax_generate_moves(mcumax_move *moves, uint32_t *num_moves);
void mcumax_generate_captures(mcumax_move *moves, uint32_t *num_moves);
void mcumax_generate_checks(mcumax_move *moves, uint32_t *num_moves);

// チェック関連
bool mcumax_is_in_check(uint8_t side);
bool mcumax_is_checkmate(void);
bool mcumax_is_stalemate(void);

// 駒の移動可能性チェック
bool mcumax_can_move_piece(mcumax_square from, mcumax_square to);
bool mcumax_is_square_attacked(mcumax_square square, uint8_t attacking_side);

// 特殊な指し手
bool mcumax_can_castle_kingside(uint8_t side);
bool mcumax_can_castle_queenside(uint8_t side);
bool mcumax_is_promotion_move(mcumax_move move);
bool mcumax_is_en_passant_move(mcumax_move move);

#endif