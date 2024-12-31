// mcumax_core.c
#include <string.h>
#include "mcumax_core.h"
#include "mcumax_board.h"
#include "mcumax_search.h"

static mcumax_state g_state;
static mcumax_callback g_callback;
static void* g_userdata;

bool mcumax_play_move(mcumax_move move) {
    if (!mcumax_is_move_valid(move)) {
        return false;
    }

    mcumax_piece piece = mcumax_get_piece(move.from);
    mcumax_piece captured = mcumax_get_piece(move.to);

    // 駒の移動
    mcumax_set_piece(move.to, piece | MCUMAX_PIECE_MOVED);
    mcumax_set_piece(move.from, MCUMAX_EMPTY);

    // キャスリング処理
    if ((piece & 0x7) == MCUMAX_KING) {
        if (move.to - move.from == 2) { // キングサイド
            mcumax_set_piece(move.from + 3, MCUMAX_EMPTY);
            mcumax_set_piece(move.from + 1, piece & MCUMAX_BOARD_WHITE ? 
                MCUMAX_ROOK | MCUMAX_BOARD_WHITE : 
                MCUMAX_ROOK | MCUMAX_BOARD_BLACK);
        } else if (move.from - move.to == 2) { // クイーンサイド
            mcumax_set_piece(move.from - 4, MCUMAX_EMPTY);
            mcumax_set_piece(move.from - 1, piece & MCUMAX_BOARD_WHITE ? 
                MCUMAX_ROOK | MCUMAX_BOARD_WHITE : 
                MCUMAX_ROOK | MCUMAX_BOARD_BLACK);
        }
    }

    // アンパッサン処理
    if (mcumax_is_en_passant_move(move)) {
        mcumax_set_piece(g_state.en_passant_square, MCUMAX_EMPTY);
    }

    // 状態更新
    g_state.en_passant_square = MCUMAX_SQUARE_INVALID;
    g_state.non_pawn_material += (captured & 0x7) >= MCUMAX_KNIGHT ? 1 : 0;
    
    return true;
}

bool mcumax_is_move_valid(mcumax_move move) {
    if (move.from & MCUMAX_BOARD_MASK || move.to & MCUMAX_BOARD_MASK) {
        return false;
    }

    mcumax_piece piece = mcumax_get_piece(move.from);
    if (!(piece & g_state.current_side)) {
        return false;
    }

    return mcumax_can_move_piece(move.from, move.to);
}

void mcumax_set_callback(mcumax_callback callback, void* userdata) {
    g_callback = callback;
    g_userdata = userdata;
}

// ... 他のcore関数の実装 ...