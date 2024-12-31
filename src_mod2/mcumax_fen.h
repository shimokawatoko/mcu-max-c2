#ifndef MCUMAX_FEN_H
#define MCUMAX_FEN_H

#include "mcumax_types.h"

// FEN文字列関連の操作
void mcumax_set_fen_position(const char *fen_string);
char* mcumax_get_fen_position(char *buffer, size_t size);
bool mcumax_validate_fen_string(const char *fen_string);

// FEN文字列のパース用補助関数
void mcumax_parse_piece_placement(const char *fen_part);
void mcumax_parse_active_color(const char *fen_part);
void mcumax_parse_castling(const char *fen_part);
void mcumax_parse_en_passant(const char *fen_part);

#endif