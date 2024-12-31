/*
 * mcumax_engine_core.c
 *
 * Core engine functionality for the mcu-max chess engine.
 */

#include "mcumax_api.h"
#include "mcumax_constants.h"
#include "mcumax_types.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Recursive minimax search function.
 */
static int32_t mcumax_search(int32_t alpha,
                             int32_t beta,
                             int32_t score,
                             uint8_t en_passant_square,
                             uint8_t depth,
                             enum mcumax_mode mode)
{
    // Core recursive logic of the engine
    // Placeholder implementation
    if (depth == 0 || mcumax.stop_search)
        return score;

    int32_t best_score = -MCUMAX_SCORE_MAX;

    for (uint8_t move = 0; move < 64; move++)
    {
        int32_t eval = -mcumax_search(-beta, -alpha, score + 1, en_passant_square, depth - 1, mode);

        if (eval > best_score)
            best_score = eval;

        if (best_score > alpha)
            alpha = best_score;

        if (alpha >= beta)
            break;
    }

    return best_score;
}

/**
 * @brief Starts a search for a move.
 */
static int32_t mcumax_start_search(enum mcumax_mode mode,
                                   mcumax_move move,
                                   uint32_t depth_max,
                                   uint32_t node_max)
{
    mcumax.square_from = move.from;
    mcumax.square_to = move.to;

    mcumax.node_max = node_max;
    mcumax.node_count = 0;
    mcumax.depth_max = depth_max;

    mcumax.stop_search = false;

    return mcumax_search(-MCUMAX_SCORE_MAX,
                         MCUMAX_SCORE_MAX,
                         mcumax.score,
                         mcumax.en_passant_square,
                         3,
                         mode);
}

/**
 * @brief Searches valid moves.
 */
uint32_t mcumax_search_valid_moves(mcumax_move *valid_moves_buffer, uint32_t valid_moves_buffer_size)
{
    mcumax.valid_moves_num = 0;
    mcumax.valid_moves_buffer = valid_moves_buffer;
    mcumax.valid_moves_buffer_size = valid_moves_buffer_size;

    mcumax_start_search(MCUMAX_SEARCH_VALID_MOVES, MCUMAX_MOVE_INVALID, 0, 0);

    return mcumax.valid_moves_num;
}

/**
 * @brief Searches the best move.
 */
mcumax_move mcumax_search_best_move(uint32_t node_max, uint32_t depth_max)
{
    int32_t score = mcumax_start_search(MCUMAX_SEARCH_BEST_MOVE,
                                        MCUMAX_MOVE_INVALID, depth_max + 3, node_max);

    if (score == MCUMAX_SCORE_MAX)
        return (mcumax_move){mcumax.square_from, mcumax.square_to};
    else
        return MCUMAX_MOVE_INVALID;
}

/**
 * @brief Plays a move.
 */
bool mcumax_play_move(mcumax_move move)
{
    return mcumax_start_search(MCUMAX_PLAY_MOVE, move, 0, 0) == MCUMAX_SCORE_MAX;
}
