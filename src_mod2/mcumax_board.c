// mcumax_board.c
#include <string.h>
#include "mcumax_board.h"

// 初期配置用の定数
static const int8_t mcumax_board_setup[] = {
    MCUMAX_ROOK,
    MCUMAX_KNIGHT,
    MCUMAX_BISHOP,
    MCUMAX_QUEEN,
    MCUMAX_KING,
    MCUMAX_BISHOP,
    MCUMAX_KNIGHT,
    MCUMAX_ROOK,
};

static mcumax_state g_state;

void mcumax_init(void) {
    // ボード初期化
    for (uint32_t x = 0; x < 8; x++) {
        // 黒側の配置
        g_state.board[0x10 * 0 + x] = MCUMAX_BOARD_BLACK | mcumax_board_setup[x];
        g_state.board[0x10 * 1 + x] = MCUMAX_BOARD_BLACK | MCUMAX_PAWN_DOWNSTREAM;
        
        // 空マス
        for (uint32_t y = 2; y < 6; y++) {
            g_state.board[0x10 * y + x] = MCUMAX_EMPTY;
        }
        
        // 白側の配置
        g_state.board[0x10 * 6 + x] = MCUMAX_BOARD_WHITE | MCUMAX_PAWN_UPSTREAM;
        g_state.board[0x10 * 7 + x] = MCUMAX_BOARD_WHITE | mcumax_board_setup[x];

        // 駒の重み付け (右側8x8部分)
        for (uint32_t y = 0; y < 8; y++) {
            g_state.board[16 * y + x + 8] = (x - 4) * (x - 4) + (y - 4) * (y - 3);
        }
    }

    // 状態初期化
    g_state.current_side = MCUMAX_BOARD_WHITE;
    g_state.score = 0;
    g_state.en_passant_square = MCUMAX_SQUARE_INVALID;
    g_state.non_pawn_material = 0;
    g_state.stop_search = false;
}

mcumax_piece mcumax_get_piece(mcumax_square square) {
    if (square & MCUMAX_BOARD_MASK) {
        return MCUMAX_EMPTY;
    }
    return g_state.board[square];
}

mcumax_square mcumax_set_piece(mcumax_square square, mcumax_piece piece) {
    if (square & MCUMAX_BOARD_MASK) {
        return square;
    }
    g_state.board[square] = piece;
    return square + 1;
}

const mcumax_state* mcumax_get_state(void) {
    return &g_state;
}

void mcumax_set_state(const mcumax_state* state) {
    memcpy(&g_state, state, sizeof(mcumax_state));
}

// ... 他のboard関数の実装 ...