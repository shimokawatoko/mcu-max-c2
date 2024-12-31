/*
 * mcumax_core.h
 * チェスエンジンのコア探索アルゴリズムのヘッダ
 */

#ifndef MCUMAX_CORE_H
#define MCUMAX_CORE_H

#include "mcumax_types.h"

// 駒の捕獲価値テーブル
static const int8_t mcumax_capture_values[] = {
    0,   // 空マス
    2,   // ポーン
    2,   // ポーン
    7,   // ナイト
    -1,  // キング
    8,   // ビショップ
    12,  // ルーク
    23   // クイーン
};

// 駒の移動ベクトルインデックス
static const int8_t mcumax_step_vectors_indices[] = {
    0,   // ポーン
    7,   // ポーン
    -1,  // ナイト
    11,  // キング
    6,   // ビショップ
    8,   // ルーク
    3,   // クイーン
    6    // 予備
};

// 駒の移動ベクトル
static const int8_t mcumax_step_vectors[] = {
    // ポーン（上向き）
    -16, -15, -17, 0,
    // ルーク
    1, 16, 0,
    // キング、クイーン
    1, 16, 15, 17, 0,
    // ナイト
    14, 18, 31, 33, 0
};

/*
 * ミニマックス探索の実装
 * @param alpha: アルファ値
 * @param beta: ベータ値
 * @param score: 現在の評価値
 * @param en_passant_square: アンパッサンのマス
 * @param depth: 探索深さ
 * @param mode: 探索モード
 * @return: 探索結果の評価値
 */
int32_t mcumax_search(int32_t alpha,
                      int32_t beta,
                      int32_t score,
                      uint8_t en_passant_square,
                      uint8_t depth,
                      enum mcumax_mode mode);

#endif // MCUMAX_CORE_H