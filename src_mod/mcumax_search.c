/*
 * mcumax_search.c
 * 探索機能の実装
 */

#include "mcu-max.h"
#include "mcumax_types.h"
#include "mcumax_core.h"

/*
 * 探索の開始処理
 * @param mode: 探索モード
 * @param move: 実行する手
 * @param depth_max: 最大探索深さ
 * @param node_max: 最大探索ノード数
 * @return: 探索結果のスコア
 */
static int32_t mcumax_start_search(enum mcumax_mode mode,
                                   mcumax_move move,
                                   uint32_t depth_max,
                                   uint32_t node_max) {
    // 探索パラメータの設定
    mcumax.square_from = move.from;
    mcumax.square_to = move.to;
    mcumax.node_max = node_max;
    mcumax.node_count = 0;
    mcumax.depth_max = depth_max;
    mcumax.stop_search = false;

    // コア探索処理の呼び出し
    return mcumax_search(-MCUMAX_SCORE_MAX,
                         MCUMAX_SCORE_MAX,
                         mcumax.score,
                         mcumax.en_passant_square,
                         3,
                         mode);
}

/*
 * 有効な手の探索
 * @param valid_moves_buffer: 有効手を格納するバッファ
 * @param valid_moves_buffer_size: バッファサイズ
 * @return: 見つかった有効手の数
 */
uint32_t mcumax_search_valid_moves(mcumax_move *valid_moves_buffer, uint32_t valid_moves_buffer_size) {
    mcumax.valid_moves_num = 0;
    mcumax.valid_moves_buffer = valid_moves_buffer;
    mcumax.valid_moves_buffer_size = valid_moves_buffer_size;

    mcumax_start_search(MCUMAX_SEARCH_VALID_MOVES, MCUMAX_MOVE_INVALID, 0, 0);
    return mcumax.valid_moves_num;
}

/*
 * 最善手の探索
 * @param node_max: 最大探索ノード数
 * @param depth_max: 最大探索深さ
 * @return: 見つかった最善手（見つからない場合はMCUMAX_MOVE_INVALID）
 */
mcumax_move mcumax_search_best_move(uint32_t node_max, uint32_t depth_max) {
    int32_t score = mcumax_start_search(MCUMAX_SEARCH_BEST_MOVE,
                                        MCUMAX_MOVE_INVALID, depth_max + 3, node_max);

    if (score == MCUMAX_SCORE_MAX)
        return (mcumax_move){mcumax.square_from, mcumax.square_to};
    else
        return MCUMAX_MOVE_INVALID;
}

/*
 * 指定された手の実行
 * @param move: 実行する手
 * @return: 手が実行可能だったかどうか
 */
bool mcumax_play_move(mcumax_move move) {
    return mcumax_start_search(MCUMAX_PLAY_MOVE, move, 0, 0) == MCUMAX_SCORE_MAX;
}

/*
 * コールバック関数の設定
 * @param callback: コールバック関数
 * @param userdata: コールバック用データ
 */
void mcumax_set_callback(mcumax_callback callback, void *userdata) {
    mcumax.user_callback = callback;
    mcumax.user_data = userdata;
}

/*
 * 探索の停止
 */
void mcumax_stop_search(void) {
    mcumax.stop_search = true;
}