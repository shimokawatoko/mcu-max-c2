/*
 * mcumax_board.c
 * ボード操作の実装
 */

#include "mcumax.h"
#include "mcumax_types.h"

// 初期配置の駒の配列
static const int8_t mcumax_board_setup[] = {
    MCUMAX_ROOK,      // ルーク
    MCUMAX_KNIGHT,    // ナイト
    MCUMAX_BISHOP,    // ビショップ
    MCUMAX_QUEEN,     // クイーン
    MCUMAX_KING,      // キング
    MCUMAX_BISHOP,    // ビショップ
    MCUMAX_KNIGHT,    // ナイト
    MCUMAX_ROOK,      // ルーク
};

// グローバル状態変数の実体定義
struct mcumax_state mcumax;

/*
 * エンジンの初期化
 * - 駒の初期配置を設定
 * - 評価値の重みを設定
 * - 状態変数の初期化
 */
void mcumax_init(void) {
    for (uint32_t x = 0; x < 8; x++) {
        // 駒の初期配置（左側）
        mcumax.board[0x10 * 0 + x] = MCUMAX_BOARD_BLACK | mcumax_board_setup[x];
        mcumax.board[0x10 * 1 + x] = MCUMAX_BOARD_BLACK | MCUMAX_PAWN_DOWNSTREAM;
        for (uint32_t y = 2; y < 6; y++)
            mcumax.board[0x10 * y + x] = MCUMAX_EMPTY;
        mcumax.board[0x10 * 6 + x] = MCUMAX_BOARD_WHITE | MCUMAX_PAWN_UPSTREAM;
        mcumax.board[0x10 * 7 + x] = MCUMAX_BOARD_WHITE | mcumax_board_setup[x];

        // 評価値の重み設定（右側）
        for (uint32_t y = 0; y < 8; y++)
            mcumax.board[16 * y + x + 8] = (x - 4) * (x - 4) + (y - 4) * (y - 3);
    }
    
    // 状態変数の初期化
    mcumax.current_side = MCUMAX_BOARD_WHITE;
    mcumax.score = 0;
    mcumax.en_passant_square = MCUMAX_SQUARE_INVALID;
    mcumax.non_pawn_material = 0;

#ifdef MCUMAX_HASHING_ENABLED
    // ハッシュテーブルの初期化
    mcumax.hash_key = 0;
    mcumax.hash_key2 = 0;
    memset(mcumax_hash_table, 0, sizeof(mcumax_hash_table));

    // ハッシュ用乱数テーブルの初期化
    srand(1);
    for (uint32_t i = 0; i < 1035; i++)
        mcumax_scramble_table[i] =
            ((rand() & 0xff) << 0) |
            ((rand() & 0xff) << 8) |
            ((rand() & 0xff) << 16) |
            ((rand() & 0xff) << 24);
#endif
}

/*
 * 指定マスに駒を配置
 * @param square: 配置するマス
 * @param piece: 配置する駒
 * @return: 次のマスの位置
 */
mcumax_square mcumax_set_piece(mcumax_square square, mcumax_piece piece) {
    if (square & MCUMAX_BOARD_MASK)
        return square;

    mcumax.board[square] = piece ? (piece | MCUMAX_PIECE_MOVED) : piece;
    return square + 1;
}

/*
 * 指定マスの駒を取得
 * @param square: 取得するマス
 * @return: マスにある駒
 */
mcumax_piece mcumax_get_piece(mcumax_square square) {
    if (square & MCUMAX_BOARD_MASK)
        return MCUMAX_EMPTY;

    return (mcumax.board[square] & 0xf) ^ MCUMAX_BLACK;
}

/*
 * 現在の手番を取得
 * @return: 現在の手番（白/黒）
 */
mcumax_piece mcumax_get_current_side(void) {
    return mcumax.current_side;
}
