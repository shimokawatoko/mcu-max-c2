/*
 * mcumax_types.h
 * チェスエンジンの基本型定義と定数
 */

#ifndef MCUMAX_TYPES_H
#define MCUMAX_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// ボード関連の定数
#define MCUMAX_BOARD_MASK 0x88      // ボード範囲チェック用マスク
#define MCUMAX_BOARD_WHITE 0x8      // 白駒の識別子
#define MCUMAX_BOARD_BLACK 0x10     // 黒駒の識別子
#define MCUMAX_PIECE_MOVED 0x20     // 移動済み駒の識別子
#define MCUMAX_SCORE_MAX 8000       // 最大評価値
#define MCUMAX_DEPTH_MAX 99         // 最大探索深さ

// 基本データ型の定義
typedef uint8_t mcumax_square;      // マス目を表す型
typedef uint8_t mcumax_piece;       // 駒を表す型

// 探索モードの列挙型
enum mcumax_mode {
    MCUMAX_INTERNAL_NODE,           // 内部ノード探索
    MCUMAX_SEARCH_VALID_MOVES,      // 有効手の探索
    MCUMAX_SEARCH_BEST_MOVE,        // 最善手の探索
    MCUMAX_PLAY_MOVE,              // 指し手の実行
};

// エンジンの状態を管理する構造体
struct mcumax_state {
    // ボード状態
    uint8_t board[0x80 + 1];        // 盤面配列
    uint8_t current_side;           // 現在の手番
    int32_t score;                  // 現在の評価値
    uint8_t en_passant_square;      // アンパッサンのマス
    int32_t non_pawn_material;      // ポーン以外の駒の材料値
    
    // ハッシュ関連（オプション）
#ifdef MCUMAX_HASHING_ENABLED
    uint32_t hash_key;              // ハッシュキー1
    uint32_t hash_key2;             // ハッシュキー2
#endif

    // 探索制御
    uint8_t square_from;            // 移動元マス
    uint8_t square_to;              // 移動先マス
    uint32_t node_count;            // 探索ノード数
    uint32_t node_max;              // 最大探索ノード数
    uint32_t depth_max;             // 最大探索深さ
    bool stop_search;               // 探索停止フラグ
    
    // コールバック関連
    mcumax_callback user_callback;   // ユーザーコールバック関数
    void *user_data;                // コールバック用データ
    
    // 有効手バッファ
    mcumax_move *valid_moves_buffer;// 有効手格納バッファ
    uint32_t valid_moves_buffer_size;// バッファサイズ
    uint32_t valid_moves_num;       // 有効手の数
};

extern struct mcumax_state mcumax;  // グローバル状態変数

#endif // MCUMAX_TYPES_H