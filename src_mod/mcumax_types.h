/*
 * mcumax_types.h
 */
#ifndef MCUMAX_TYPES_H
#define MCUMAX_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// 型定義
typedef uint8_t mcumax_square;
typedef uint8_t mcumax_piece;
typedef void (*mcumax_callback)(void *);

// 駒の種類
enum {
    MCUMAX_EMPTY,
    MCUMAX_PAWN_UPSTREAM,
    MCUMAX_PAWN_DOWNSTREAM,
    MCUMAX_KNIGHT,
    MCUMAX_KING,
    MCUMAX_BISHOP,
    MCUMAX_ROOK,
    MCUMAX_QUEEN,
    MCUMAX_BLACK = 0x8,
};

// 定数定義
#define MCUMAX_BOARD_MASK 0x88
#define MCUMAX_BOARD_WHITE 0x8
#define MCUMAX_BOARD_BLACK 0x10
#define MCUMAX_PIECE_MOVED 0x20
#define MCUMAX_SCORE_MAX 8000
#define MCUMAX_DEPTH_MAX 99
#define MCUMAX_SQUARE_INVALID 0x80

typedef struct {
    mcumax_square from;
    mcumax_square to;
} mcumax_move;

#define MCUMAX_MOVE_INVALID \
    (mcumax_move) { MCUMAX_SQUARE_INVALID, MCUMAX_SQUARE_INVALID }

enum mcumax_mode {
    MCUMAX_INTERNAL_NODE,
    MCUMAX_SEARCH_VALID_MOVES,
    MCUMAX_SEARCH_BEST_MOVE,
    MCUMAX_PLAY_MOVE,
};

struct mcumax_state {
    uint8_t board[0x80 + 1];
    uint8_t current_side;
    int32_t score;
    uint8_t en_passant_square;
    int32_t non_pawn_material;
    
#ifdef MCUMAX_HASHING_ENABLED
    uint32_t hash_key;
    uint32_t hash_key2;
#endif

    uint8_t square_from;
    uint8_t square_to;
    uint32_t node_count;
    uint32_t node_max;
    uint32_t depth_max;
    bool stop_search;
    
    mcumax_callback user_callback;
    void *user_data;
    mcumax_move *valid_moves_buffer;
    uint32_t valid_moves_buffer_size;
    uint32_t valid_moves_num;
};

extern struct mcumax_state mcumax;

#endif