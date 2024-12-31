// mcumax_search.c
#include "mcumax_search.h"
#include "mcumax_board.h"
#include "mcumax_core.h"

static const int8_t mcumax_capture_values[] = {
    0, 2, 2, 7, -1, 8, 12, 23
};

static const int8_t mcumax_step_vectors_indices[] = {
    0, 7, -1, 11, 6, 8, 3, 6
};

static const int8_t mcumax_step_vectors[] = {
    // ポーン（上方向）
    -16, -15, -17, 0,
    // ルーク
    1, 16, 0,
    // キング、クイーン
    1, 16, 15, 17, 0,
    // ナイト
    14, 18, 31, 33, 0
};

static mcumax_search_info g_search_info;

static int32_t mcumax_search_internal(int32_t alpha, int32_t beta, int32_t score,
                                     uint8_t en_passant_square, uint8_t depth,
                                     enum mcumax_search_mode mode) {
    mcumax_state* state = (mcumax_state*)mcumax_get_state();
    
    if (g_search_info.time_up) {
        return 0;
    }
    
    g_search_info.node_count++;
    
    // 深さ0の場合は静的評価
    if (depth == 0) {
        return mcumax_evaluate_position();
    }
    
    mcumax_move moves[MCUMAX_VALID_MOVES_NUM];
    uint32_t num_moves = 0;
    mcumax_generate_moves(moves, &num_moves);
    
    // 合法手がない場合
    if (num_moves == 0) {
        if (mcumax_is_in_check(state->current_side)) {
            return -MCUMAX_SCORE_MAX; // チェックメイト
        }
        return 0; // ステイルメイト
    }
    
    int32_t best_score = -MCUMAX_SCORE_MAX;
    mcumax_move best_move = MCUMAX_MOVE_INVALID;
    
    // 全ての手を試す
    for (uint32_t i = 0; i < num_moves; i++) {
        mcumax_play_move(moves[i]);
        int32_t score = -mcumax_search_internal(-beta, -alpha, -score,
                                               state->en_passant_square,
                                               depth - 1, mode);
        mcumax_undo_move();
        
        if (score > best_score) {
            best_score = score;
            best_move = moves[i];
            
            if (score > alpha) {
                alpha = score;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }
    
    // 探索情報の更新
    if (depth == g_search_info.depth_max) {
        g_search_info.best_move = best_move;
        g_search_info.best_score = best_score;
    }
    
    return best_score;
}

mcumax_move mcumax_search_best_move(uint32_t node_max, uint32_t depth_max) {
    g_search_info.node_count = 0;
    g_search_info.node_max = node_max;
    g_search_info.depth_max = depth_max;
    g_search_info.time_up = false;
    
    mcumax_search_internal(-MCUMAX_SCORE_MAX, MCUMAX_SCORE_MAX, 0,
                          MCUMAX_SQUARE_INVALID, depth_max,
                          MCUMAX_SEARCH_BEST_MOVE);
    
    return g_search_info.best_move;
}

// ... 他のsearch関数の実装 ...