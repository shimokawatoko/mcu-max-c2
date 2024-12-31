// mcumax_fen.c
#include <string.h>
#include "mcumax_fen.h"
#include "mcumax_board.h"

void mcumax_set_fen_position(const char *fen_string) {
    mcumax_init();
    mcumax_state* state = (mcumax_state*)mcumax_get_state();
    uint32_t field_index = 0;
    uint32_t board_index = 0;
    
    for (const char* ptr = fen_string; *ptr; ptr++) {
        char c = *ptr;
        
        if (c == ' ') {
            field_index++;
            continue;
        }
        
        switch (field_index) {
            case 0:  // Piece placement
                if (board_index >= 0x80) break;
                
                if (c >= '1' && c <= '8') {
                    board_index += (c - '0');
                } else if (c == '/') {
                    board_index = (board_index & 0xf0) + 0x10;
                } else {
                    mcumax_piece piece = MCUMAX_EMPTY;
                    uint8_t color = (c >= 'a') ? MCUMAX_BOARD_BLACK : MCUMAX_BOARD_WHITE;
                    
                    switch (c | 0x20) {  // Convert to lowercase
                        case 'p': piece = MCUMAX_PAWN_UPSTREAM; break;
                        case 'n': piece = MCUMAX_KNIGHT; break;
                        case 'b': piece = MCUMAX_BISHOP; break;
                        case 'r': piece = MCUMAX_ROOK; break;
                        case 'q': piece = MCUMAX_QUEEN; break;
                        case 'k': piece = MCUMAX_KING; break;
                    }
                    
                    if (piece != MCUMAX_EMPTY) {
                        mcumax_set_piece(board_index, piece | color);
                        board_index++;
                    }
                }
                break;
                
            case 1:  // Active color
                if (c == 'w') state->current_side = MCUMAX_BOARD_WHITE;
                if (c == 'b') state->current_side = MCUMAX_BOARD_BLACK;
                break;
                
            case 2:  // Castling
                switch (c) {
                    case 'K': 
                        state->board[0x74] &= ~MCUMAX_PIECE_MOVED;
                        state->board[0x77] &= ~MCUMAX_PIECE_MOVED;
                        break;
                    case 'Q':
                        state->board[0x74] &= ~MCUMAX_PIECE_MOVED;
                        state->board[0x70] &= ~MCUMAX_PIECE_MOVED;
                        break;
                    case 'k':
                        state->board[0x04] &= ~MCUMAX_PIECE_MOVED;
                        state->board[0x07] &= ~MCUMAX_PIECE_MOVED;
                        break;
                    case 'q':
                        state->board[0x04] &= ~MCUMAX_PIECE_MOVED;
                        state->board[0x00] &= ~MCUMAX_PIECE_MOVED;
                        break;
                }
                break;
                
            case 3:  // En passant
                if (c >= 'a' && c <= 'h') {
                    state->en_passant_square = (c - 'a');
                } else if (c >= '1' && c <= '8') {
                    state->en_passant_square |= 16 * ('8' - c);
                }
                break;
        }
    }
}

char* mcumax_get_fen_position(char *buffer, size_t size) {
    if (!buffer || size < 90) return NULL;
    
    const mcumax_state* state = mcumax_get_state();
    char* ptr = buffer;
    int empty = 0;
    
    // Piece placement
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            mcumax_piece piece = mcumax_get_piece(rank * 0x10 + file);
            
            if (piece == MCUMAX_EMPTY) {
                empty++;
            } else {
                if (empty) {
                    *ptr++ = '0' + empty;
                    empty = 0;
                }
                
                char c;
                switch (piece & 0x7) {
                    case MCUMAX_PAWN_UPSTREAM: c = 'P'; break;
                    case MCUMAX_KNIGHT: c = 'N'; break;
                    case MCUMAX_BISHOP: c = 'B'; break;
                    case MCUMAX_ROOK: c = 'R'; break;
                    case MCUMAX_QUEEN: c = 'Q'; break;
                    case MCUMAX_KING: c = 'K'; break;
                    default: c = '?'; break;
                }
                
                if (piece & MCUMAX_BOARD_BLACK) {
                    c |= 0x20;  // Convert to lowercase
                }
                *ptr++ = c;
            }
        }
        
        if (empty) {
            *ptr++ = '0' + empty;
            empty = 0;
        }
        
        if (rank < 7) *ptr++ = '/';
    }
    
    // Active color
    ptr += sprintf(ptr, " %c", (state->current_side == MCUMAX_BOARD_WHITE) ? 'w' : 'b');
    
    // Castling
    *ptr++ = ' ';
    bool hasCastling = false;
    if (!(state->board[0x74] & MCUMAX_PIECE_MOVED) && !(state->board[0x77] & MCUMAX_PIECE_MOVED)) {
        *ptr++ = 'K';
        hasCastling = true;
    }
    if (!(state->board[0x74] & MCUMAX_PIECE_MOVED) && !(state->board[0x70] & MCUMAX_PIECE_MOVED)) {
        *ptr++ = 'Q';
        hasCastling = true;
    }
    if (!(state->board[0x04] & MCUMAX_PIECE_MOVED) && !(state->board[0x07] & MCUMAX_PIECE_MOVED)) {
        *ptr++ = 'k';
        hasCastling = true;
    }
    if (!(state->board[0x04] & MCUMAX_PIECE_MOVED) && !(state->board[0x00] & MCUMAX_PIECE_MOVED)) {
        *ptr++ = 'q';
        hasCastling = true;
    }
    if (!hasCastling) *ptr++ = '-';
    
    // En passant
    if (state->en_passant_square == MCUMAX_SQUARE_INVALID) {
        ptr += sprintf(ptr, " -");
    } else {
        ptr += sprintf(ptr, " %c%c",
            'a' + (state->en_passant_square & 0x7),
            '8' - ((state->en_passant_square >> 4) & 0x7));
    }
    
    // Half move clock and full move number (defaults)
    ptr += sprintf(ptr, " 0 1");
    *ptr = '\0';
    
    return buffer;
}

bool mcumax_validate_fen_string(const char *fen_string) {
    if (!fen_string) return false;
    
    // Count fields
    int fields = 1;
    for (const char* p = fen_string; *p; p++) {
        if (*p == ' ') fields++;
    }
    if (fields < 4) return false;
    
    // Validate piece placement
    int rank = 0, file = 0;
    const char* p = fen_string;
    
    while (*p && *p != ' ') {
        if (*p == '/') {
            if (file != 8) return false;
            rank++;
            file = 0;
        }
        else if (*p >= '1' && *p <= '8') {
            file += (*p - '0');
        }
        else if (strchr("pnbrqkPNBRQK", *p)) {
            file++;
        }
        else return false;
        
        if (file > 8) return false;
        p++;
    }
    
    if (rank != 7 || file != 8) return false;
    
    // Basic validation of other fields
    if (!strchr(" wb ", p[1])) return false;
    if (!strchr("-KQkq", p[3])) return false;
    if (!strchr("-abcdefgh", p[5])) return false;
    
    return true;
}