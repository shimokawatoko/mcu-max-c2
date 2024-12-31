/*
 * mcumax_board.h
 */
#ifndef MCUMAX_BOARD_H
#define MCUMAX_BOARD_H

#include "mcumax_types.h"

// 駒の配置と取得
mcumax_square mcumax_set_piece(mcumax_square square, mcumax_piece piece);
mcumax_piece mcumax_get_piece(mcumax_square square);
mcumax_piece mcumax_get_current_side(void);

void mcumax_init(void);

#endif