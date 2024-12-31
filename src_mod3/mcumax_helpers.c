/*
 * mcumax_helpers.c
 *
 * Auxiliary functions for the mcu-max chess engine.
 */

#include "mcumax_api.h"
#include "mcumax_constants.h"
#include "mcumax_types.h"
#include <stdbool.h>

/**
 * @brief Sets the user callback, which is called periodically during search.
 */
void mcumax_set_callback(mcumax_callback callback, void *userdata)
{
    mcumax.user_callback = callback;
    mcumax.user_data = userdata;
}

/**
 * @brief Stops the current search. To be called from the user callback.
 */
void mcumax_stop_search(void)
{
    mcumax.stop_search = true;
}