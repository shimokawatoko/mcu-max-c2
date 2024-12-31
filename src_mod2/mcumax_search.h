#ifndef MCUMAX_SEARCH_H
#define MCUMAX_SEARCH_H

#include "mcumax_types.h"

// 探索関連の構造体
typedef struct {
    uint32_t node_count;        // 探索ノード数
    uint32_t node_max;          // 最大探索ノード数
    uint32_t depth_max;         // 最大探索深さ
    int32_t best_score;         // 最善手の評価値
    mcumax_move best_move;      // 最善手
    bool time_up;               // 時間切れフラグ
} mcumax_search_info;

// 探索関連の関数
uint32_t mcumax_search_valid_moves(mcumax_move *buffer, uint32_t buffer_size);
mcumax_move mcumax_search_best_move(uint32_t node_max, uint32_t depth_max);
int32_t mcumax_evaluate_position(void);
void mcumax_set_callback(mcumax_callback callback, void *userdata);
void mcumax_stop_search(void);

// 探索情報の取得
const mcumax_search_info* mcumax_get_search_info(void);

// 探索パラメータの設定
void mcumax_set_search_params(uint32_t node_max, uint32_t depth_max);

#ifdef MCUMAX_HASHING_ENABLED
// トランスポジションテーブル関連
void mcumax_init_hash_table(void);
void mcumax_clear_hash_table(void);
bool mcumax_probe_hash_table(int32_t alpha, int32_t beta, int32_t depth, 
                            mcumax_move *best_move, int32_t *score);
void mcumax_store_hash_table(int32_t alpha, int32_t beta, int32_t depth,
                            mcumax_move best_move, int32_t score);
#endif

#endif