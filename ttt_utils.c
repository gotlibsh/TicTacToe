#include "ttt_utils.h"


void set_piece(ttt_board* board, uint8_t cell, piece piece)
{
    if (piece == X)
        SET_BIT(&board->x_board, cell);
    else
        SET_BIT(&board->o_board, cell);
}

piece get_piece(ttt_board* board, uint8_t cell)
{
    if (GET_BIT(&board->x_board, cell)) return X;
    if (GET_BIT(&board->o_board, cell)) return O;

    return EMPTY;
}

void print_board(ttt_board* board)
{
    printf("%s %s %s\n", PIECE_STR(get_piece(board, 1)), PIECE_STR(get_piece(board, 2)), PIECE_STR(get_piece(board, 3)));
    printf("%s %s %s\n", PIECE_STR(get_piece(board, 4)), PIECE_STR(get_piece(board, 5)), PIECE_STR(get_piece(board, 6)));
    printf("%s %s %s\n", PIECE_STR(get_piece(board, 7)), PIECE_STR(get_piece(board, 8)), PIECE_STR(get_piece(board, 9)));
}

bool is_game_over(ttt_board* board)
{
    bool is_board_full = (board->x_board | board->o_board) == BOARD_MASK;

    if (is_board_full)
    {
        return true;
    }

    if (IS_WON(board->x_board) || IS_WON(board->o_board))
    {
        return true;
    }

    return false;
}