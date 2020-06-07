#ifndef _TTT_UTILS_H_
#define _TTT_UTILS_H_

#include <stdint.h>
#include <stdio.h>

// general definitions
#define MAX(a,b)                    ((a) > (b) ? a : b)
#define MIN(a,b)                    ((a) < (b) ? a : b)

#define BOARD_SIZE                  (9)
#define BOARD_MASK                  (0x01FF)  // lower 9 bits
#define OPP_PIECE(p)                (p == X ? O : p == O ? X : EMPTY)
#define PIECE_STR(p)                (p == X ? "X" : p == O ? "O" : "-")
#define GET_BIT(p_brd, cell)        (*p_brd & (1 << (BOARD_SIZE - cell)))
#define SET_BIT(p_brd, cell)        (*p_brd |= (1 << (BOARD_SIZE - cell)))
#define CLEAN_BOARD(brd)            { brd.x_board = 0x00; brd.o_board = 0x00; }

#define ROW_1_MASK                  ((uint16_t)0x01C0)
#define COL_1_MASK                  ((uint16_t)0x0124)
#define DIAGONAL_MASK               ((uint16_t)0x0111)
#define REVERSE_DIAGONAL_MASK       ((uint16_t)0x0054)
#define IS_ROW(brd, row)            ((brd & (ROW_1_MASK >> ((row-1) * 3))) == (ROW_1_MASK >> ((row-1) * 3)))
#define IS_COL(brd, col)            ((brd & (COL_1_MASK >> (col-1))) == (COL_1_MASK >> (col-1)))
#define IS_DIAGONAL(brd)            ((brd & DIAGONAL_MASK) == DIAGONAL_MASK)
#define IS_REV_DIAGONAL(brd)        ((brd & REVERSE_DIAGONAL_MASK) == REVERSE_DIAGONAL_MASK)
#define IS_ANY_ROW(brd)             (IS_ROW(brd, 1) || IS_ROW(brd, 2) || IS_ROW(brd, 3))
#define IS_ANY_COL(brd)             (IS_COL(brd, 1) || IS_COL(brd, 2) || IS_COL(brd, 3))
#define IS_ANY_DIAGONAL(brd)        (IS_DIAGONAL(brd) || IS_REV_DIAGONAL(brd))
#define IS_WON(brd)                 (IS_ANY_ROW(brd) || IS_ANY_COL(brd) || IS_ANY_DIAGONAL(brd))
#define IS_BOARD_FULL(x_brd, o_brd) (((x_brd) | (o_brd)) == BOARD_MASK)

typedef int8_t                      score_t;
#define MAX_SCORE                   INT8_MAX
#define MIN_SCORE                   INT8_MIN

typedef uint8_t                     bool;
#define true                        1
#define false                       0

/*
    Represents a Tic Tac Toe board.

    x_board represents the locations of the X pieces on the board.
    o_board represents the locations of the O pieces on the board.

    On each board, only the 9 lower bits are used.
*/
typedef struct _ttt_board
{
    uint16_t x_board;
    uint16_t o_board;
} ttt_board;

/*
    Represents a TicTacToe board piece.
*/
typedef enum _piece
{
    X       = 0,
    O       = 1,
    EMPTY   = 2
} piece;

/*
    Represents a minimax result computed for a single board state.

    child_index is the index of the child board of the given board that is recommended as next move.
    eval is the final evaluation for the given board.
*/
typedef struct _node_result
{
    uint8_t child_index;
    score_t eval;
} node_result;


void set_piece(ttt_board* board, uint8_t cell, piece piece);
piece get_piece(ttt_board* board, uint8_t cell);
void print_board(ttt_board* board);
bool is_game_over(ttt_board* board);


#endif  // _TTT_UTILS_H_