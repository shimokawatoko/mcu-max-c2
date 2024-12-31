#ifndef MCUMAX_TYPES_H
#define MCUMAX_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// バージョン情報
#define MCUMAX_ID "mcu-max 1.0.5"
#define MCUMAX_AUTHOR "Gissio"

// ボード関連の定数
#define MCUMAX_SQUARE_INVALID 0x80
#define MCUMAX_BOARD_MASK 0x88
#define MCUMAX_BOARD_WHITE 0x8
#define MCUMAX_BOARD_BLACK 0x10
#define MCUMAX_PIECE_MOVED 0x20

// 探索関連の定数
#define MCUMAX_SCORE_MAX 8000
#define MCUMAX_DEPTH_MAX 99
#define MCUMAX_VALID_MOVES_NUM 512

// ピースの種類の定義
enum mcumax_piece_type {
    MCUMAX_EMPTY,
    MCUMAX_PAWN_UPSTREAM,
    MCUMAX_PAWN_DOWNSTREAM,
    MCUMAX_KNIGHT,
    MCUMAX_KING,
    MCUMAX_BISHOP,
    MCUMAX_ROOK,
    MCUMAX_QUEEN,
    
    // 色の定義
    MCUMAX_BLACK = 0x8,
};

// 探索モードの定義
enum mcumax_search_mode {
    MCUMAX_INTERNAL_NODE,
    MCUMAX_SEARCH_VALID_MOVES,
    MCUMAX_SEARCH_BEST_MOVE,
    MCUMAX_PLAY_MOVE,
};

// 基本的な型定義
typedef uint8_t mcumax_square;
typedef uint8_t mcumax_piece;

// 指し手の構造体
typedef struct {
    mcumax_square from;  // 移動元の座標
    mcumax_square to;    // 移動先の座標
} mcumax_move;

// 無効な指し手の定義
#define MCUMAX_MOVE_INVALID \
    (mcumax_move) { MCUMAX_SQUARE_INVALID, MCUMAX_SQUARE_INVALID }

// コールバック関数の型定義
typedef void (*mcumax_callback)(void *);

// ボード状態の構造体
typedef struct {
    uint8_t board[0x80 + 1];        // ボード配列 (16x8 + ダミー)
    uint8_t current_side;           // 現在の手番
    int32_t score;                  // 評価値
    uint8_t en_passant_square;      // アンパッサンの対象となるマス
    int32_t non_pawn_material;      // ポーン以外の駒の材料値
    bool stop_search;               // 探索停止フラグ
} mcumax_state;

#endif