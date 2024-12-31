/*
 * mcumax_types.h
 *
 * Definitions of data types and structures for mcu-max.
 */

#ifndef MCUMAX_TYPES_H
#define MCUMAX_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * Square and piece types.
 */
typedef uint8_t mcumax_square;
typedef uint8_t mcumax_piece;

/**
 * Move structure.
 */
typedef struct
{
    mcumax_square from;
    mcumax_square to;
} mcumax_move;

/**
 * User callback type.
 */
typedef void (*mcumax_callback)(void *);

#ifdef __cplusplus
}
#endif

#endif /* MCUMAX_TYPES_H */
