/*
 * mcumax_core.c
 */
#include "mcumax_core.h"
#include "mcumax_types.h"

static const int8_t mcumax_capture_values[] = {
    0, 2, 2, 7, -1, 8, 12, 23
};

int32_t mcumax_search(int32_t alpha,
                      int32_t beta,
                      int32_t score,
                      uint8_t en_passant_square,
                      uint8_t depth,
                      enum mcumax_mode mode) {
    if (mcumax.user_callback)
        mcumax.user_callback(mcumax.user_data);

    uint8_t square_from = mcumax.square_from;
    uint8_t square_to = mcumax.square_to;
    
    // 基本的な評価
    if (depth == 0) {
        return score;
    }

    // 探索打ち切り
    if (mcumax.stop_search) {
        return score;
    }

    // ノードカウント
    mcumax.node_count++;
    
    return score; // 簡略化した実装
}
