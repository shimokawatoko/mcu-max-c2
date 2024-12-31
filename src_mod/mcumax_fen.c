/*
 * mcumax_fen.c
 * FEN形式の盤面表現の処理
 */

#include "mcumax.h"
#include "mcumax_types.h"

/*
 * FEN文字列から盤面を設定
 * FEN形式: 
 * - 1フィールド目: 駒の配置
 * - 2フィールド目: 手番
 * - 3フィールド目: キャスリング権
 * - 4フィールド目: アンパッサン
 * @param fen_string: FEN形式の文字列
 */
void mcumax_set_fen_position(const char *fen_string) {
    mcumax_init();

    uint32_t field_index = 0;    // 現在処理中のFENフィールド
    uint32_t board_index = 0;    // ボード上の位置

    char c;
    while ((c = *fen_string++)) {
        if (c == ' ') {
            if (field_index < 4)
                field_index++;
            continue;
        }

        switch (field_index) {
        case 0:  // 駒の配置フィールド
            if (board_index < 0x80) {
                switch (c) {
                case '8': case '7': case '6': case '5':
                case '4': case '3': case '2': case '1':
                    // 空マスの処理
                    for (int32_t i = 0; i < (c - '0'); i++)
                        board_index = mcumax_set_piece(board_index, MCUMAX_EMPTY);
                    break;

                // 白駒の配置
                case 'P':
                    board_index = mcumax_set_piece(board_index, MCUMAX_PAWN_UPSTREAM | MCUMAX_BOARD_WHITE);
                    break;
                case 'N':
                    board_index = mcumax_set_piece(board_index, MCUMAX_KNIGHT | MCUMAX_BOARD_WHITE);
                    break;
                case 'B':
                    board_index = mcumax_set_piece(board_index, MCUMAX_BISHOP | MCUMAX_BOARD_WHITE);
                    break;
                case 'R':
                    board_index = mcumax_set_piece(board_index, MCUMAX_ROOK | MCUMAX_BOARD_WHITE);
                    break;
                case 'Q':
                    board_index = mcumax_set_piece(board_index, MCUMAX_QUEEN | MCUMAX_BOARD_WHITE);
                    break;
                case 'K':
                    board_index = mcumax_set_piece(board_index, MCUMAX_KING | MCUMAX_BOARD_WHITE);
                    break;

                // 黒駒の配置
                case 'p':
                    board_index = mcumax_set_piece(board_index, MCUMAX_PAWN_DOWNSTREAM | MCUMAX_BOARD_BLACK);
                    break;
                case 'n':
                    board_index = mcumax_set_piece(board_index, MCUMAX_KNIGHT | MCUMAX_BOARD_BLACK);
                    break;
                case 'b':
                    board_index = mcumax_set_piece(board_index, MCUMAX_BISHOP | MCUMAX_BOARD_BLACK);
                    break;
                case 'r':
                    board_index = mcumax_set_piece(board_index, MCUMAX_ROOK | MCUMAX_BOARD_BLACK);
                    break;
                case 'q':
                    board_index = mcumax_set_piece(board_index, MCUMAX_QUEEN | MCUMAX_BOARD_BLACK);
                    break;
                case 'k':
                    board_index = mcumax_set_piece(board_index, MCUMAX_KING | MCUMAX_BOARD_BLACK);
                    break;

                case '/':  // 次の行へ
                    board_index = (board_index < 0x80) ? (board_index & 0xf0) + 0x10 : board_index;
                    break;
                }
            }
            break;

        case 1:  // 手番フィールド
            switch (c) {
            case 'w':
                mcumax.current_side = MCUMAX_BOARD_WHITE;
                break;
            case 'b':
                mcumax.current_side = MCUMAX_BOARD_BLACK;
                break;
            }
            break;

        case 2:  // キャスリング権フィールド
            switch (c) {
            case 'K':  // 白のキングサイドキャスリング
                mcumax.board[0x74] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x77] &= ~MCUMAX_PIECE_MOVED;
                break;
            case 'Q':  // 白のクイーンサイドキャスリング
                mcumax.board[0x74] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x70] &= ~MCUMAX_PIECE_MOVED;
                break;
            case 'k':  // 黒のキングサイドキャスリング
                mcumax.board[0x04] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x07] &= ~MCUMAX_PIECE_MOVED;
                break;
            case 'q':  // 黒のクイーンサイドキャスリング
                mcumax.board[0x04] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x00] &= ~MCUMAX_PIECE_MOVED;
                break;
            }
            break;

        case 3:  // アンパッサンフィールド
            switch (c) {
            // ファイル（a-h）
            case 'a': case 'b': case 'c': case 'd':
            case 'e': case 'f': case 'g': case 'h':
                mcumax.en_passant_square &= 0x7f;
                mcumax.en_passant_square |= (c - 'a');
                break;
            // ランク（1-8）
            case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8':
                mcumax.en_passant_square &= 0x7f;
                mcumax.en_passant_square |= 16 * ('8' - c);
                break;
            }
            break;
        }
    }
}