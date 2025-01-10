#ifndef MCUMAX_STATE_H
#define MCUMAX_STATE_H

struct mcumax_state {
    // Board: first half of 16x8 + dummy
    uint8_t board[0x80 + 1];
    uint8_t current_side;
    int32_t score;
    uint8_t en_passant_square;
    int32_t non_pawn_material;

#ifdef MCUMAX_HASHING_ENABLED
    uint32_t hash_key;
    uint32_t hash_key2;
#endif

    // Interface
    uint8_t square_from; // Selected move
    uint8_t square_to;

    uint32_t node_count;
    uint32_t node_max;
    uint32_t depth_max;
    uint32_t current_depth;  // 実際の現在の探索深さ

    bool stop_search;

    // Extra
    mcumax_callback user_callback;
    void *user_data;

    mcumax_move *valid_moves_buffer;
    uint32_t valid_moves_buffer_size;
    uint32_t valid_moves_num;
};

extern struct mcumax_state mcumax;

#endif