/*
 * mcumax_constants.h
 *
 * Definitions of constants and macros for mcu-max.
 */

#ifndef MCUMAX_CONSTANTS_H
#define MCUMAX_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MCUMAX_ID "mcu-max 1.0.5"
#define MCUMAX_AUTHOR "Gissio"

#define MCUMAX_SQUARE_INVALID 0x80

#define MCUMAX_MOVE_INVALID \
    (mcumax_move) { MCUMAX_SQUARE_INVALID, MCUMAX_SQUARE_INVALID }

/**
 * Piece types
 */
enum
{
    // Bits 0-2: piece
    MCUMAX_EMPTY,
    MCUMAX_PAWN_UPSTREAM,
    MCUMAX_PAWN_DOWNSTREAM,
    MCUMAX_KNIGHT,
    MCUMAX_KING,
    MCUMAX_BISHOP,
    MCUMAX_ROOK,
    MCUMAX_QUEEN,

    // Bits 3: color
    MCUMAX_BLACK = 0x8,
};

#ifdef __cplusplus
}
#endif

#endif /* MCUMAX_CONSTANTS_H */
