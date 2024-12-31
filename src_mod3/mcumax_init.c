/*
 * mcumax_init.c
 *
 * Initialization and position setup for the mcu-max chess engine.
 */

#include "mcumax_api.h"
#include "mcumax_constants.h"
#include "mcumax_types.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief Resets the engine state.
 */
void mcumax_init()
{
    for (uint32_t x = 0; x < 8; x++)
    {
        // Setup pieces (left side)
        mcumax.board[0x10 * 0 + x] = MCUMAX_BOARD_BLACK | mcumax_board_setup[x];
        mcumax.board[0x10 * 1 + x] = MCUMAX_BOARD_BLACK | MCUMAX_PAWN_DOWNSTREAM;
        for (uint32_t y = 2; y < 6; y++)
            mcumax.board[0x10 * y + x] = MCUMAX_EMPTY;
        mcumax.board[0x10 * 6 + x] = MCUMAX_BOARD_WHITE | MCUMAX_PAWN_UPSTREAM;
        mcumax.board[0x10 * 7 + x] = MCUMAX_BOARD_WHITE | mcumax_board_setup[x];

        // Setup weights (right side)
        for (uint32_t y = 0; y < 8; y++)
            mcumax.board[16 * y + x + 8] = (x - 4) * (x - 4) + (y - 4) * (y - 3);
    }
    mcumax.current_side = MCUMAX_BOARD_WHITE;

    mcumax.score = 0;
    mcumax.en_passant_square = MCUMAX_SQUARE_INVALID;
    mcumax.non_pawn_material = 0;

#ifdef MCUMAX_HASHING_ENABLED
    mcumax.hash_key = 0;
    mcumax.hash_key2 = 0;

    memset(mcumax_hash_table, 0, sizeof(mcumax_hash_table));

    srand(1);
    for (uint32_t i = 0; i < MCUMAX_HASH_SCRAMBLE_TABLE_SIZE; i++)
        mcumax_scramble_table[i] =
            ((rand() & 0xff) << 0) |
            ((rand() & 0xff) << 8) |
            ((rand() & 0xff) << 16) |
            ((rand() & 0xff) << 24);
#endif
}

/**
 * @brief Sets position from a FEN string.
 *
 * @param fen_string The FEN string.
 */
void mcumax_set_fen_position(const char *fen_string)
{
    mcumax_init();

    uint32_t field_index = 0;
    uint32_t board_index = 0;

    char c;
    while ((c = *fen_string++))
    {
        if (c == ' ')
        {
            if (field_index < 4)
                field_index++;

            continue;
        }

        switch (field_index)
        {
        case 0:
            if (board_index < 0x80)
            {
                switch (c)
                {
                case '8':
                case '7':
                case '6':
                case '5':
                case '4':
                case '3':
                case '2':
                case '1':
                    for (int32_t i = 0; i < (c - '0'); i++)
                        board_index = mcumax_set_piece(board_index, MCUMAX_EMPTY);

                    break;

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

                case '/':
                    board_index = (board_index < 0x80) ? (board_index & 0xf0) + 0x10 : board_index;

                    break;
                }
            }
            break;

        case 1:
            switch (c)
            {
            case 'w':
                mcumax.current_side = MCUMAX_BOARD_WHITE;

                break;

            case 'b':
                mcumax.current_side = MCUMAX_BOARD_BLACK;

                break;
            }
            break;

        case 2:
            switch (c)
            {
            case 'K':
                mcumax.board[0x74] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x77] &= ~MCUMAX_PIECE_MOVED;

                break;

            case 'Q':
                mcumax.board[0x74] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x70] &= ~MCUMAX_PIECE_MOVED;

                break;

            case 'k':
                mcumax.board[0x04] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x07] &= ~MCUMAX_PIECE_MOVED;

                break;

            case 'q':
                mcumax.board[0x04] &= ~MCUMAX_PIECE_MOVED;
                mcumax.board[0x00] &= ~MCUMAX_PIECE_MOVED;

                break;
            }

            break;

        case 3:
            switch (c)
            {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
                mcumax.en_passant_square &= 0x7f;
                mcumax.en_passant_square |= (c - 'a');

                break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                mcumax.en_passant_square &= 0x7f;
                mcumax.en_passant_square |= 16 * ('8' - c);

                break;
            }

            break;
        }
    }
}
