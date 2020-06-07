#include <stdlib.h>
#include "ttt_utils.h"


void _assert(bool expression, char* file, uint32_t line)
{
    if(!expression)
    {
        printf("Assertion failed - File: %s - Line: %d", file, line);
        exit(1);
    }
}

#define assert(expression)      (_assert(!!(expression), __FILE__, __LINE__))


void test_is_row()
{
    ttt_board b = {0};
    ttt_board* pb = &b;

    set_piece(pb, 1, X);
    set_piece(pb, 2, X);
    set_piece(pb, 3, X);
    assert(IS_ROW(b.x_board, 1) == true);
    assert(IS_ROW(b.x_board, 2) == false);

    CLEAN_BOARD(b);
    set_piece(pb, 4, X);
    set_piece(pb, 5, X);
    set_piece(pb, 6, X);
    assert(IS_ROW(b.x_board, 1) == false);
    assert(IS_ROW(b.x_board, 2) == true);

    CLEAN_BOARD(b);
    set_piece(pb, 7, X);
    set_piece(pb, 8, X);
    set_piece(pb, 9, X);
    assert(IS_ROW(b.x_board, 1) == false);
    assert(IS_ROW(b.x_board, 3) == true);
}

void test_is_col()
{
    ttt_board b = {0};
    ttt_board* pb = &b;

    set_piece(pb, 1, O);
    set_piece(pb, 4, O);
    set_piece(pb, 7, O);
    assert(IS_COL(b.o_board, 1) == true);
    assert(IS_COL(b.o_board, 2) == false);

    CLEAN_BOARD(b);
    set_piece(pb, 2, O);
    set_piece(pb, 5, O);
    set_piece(pb, 8, O);
    assert(IS_COL(b.o_board, 1) == false);
    assert(IS_COL(b.o_board, 2) == true);

    CLEAN_BOARD(b);
    set_piece(pb, 3, O);
    set_piece(pb, 6, O);
    set_piece(pb, 9, O);
    assert(IS_COL(b.o_board, 1) == false);
    assert(IS_COL(b.o_board, 3) == true);
}

void test_is_diagonal()
{
    ttt_board b = {0};
    ttt_board* pb = &b;

    set_piece(pb, 1, X);
    set_piece(pb, 5, X);
    set_piece(pb, 9, X);
    assert(IS_DIAGONAL(b.x_board) == true);

    CLEAN_BOARD(b);
    set_piece(pb, 3, O);
    set_piece(pb, 5, O);
    set_piece(pb, 7, O);
    assert(IS_REV_DIAGONAL(b.o_board) == true);

    CLEAN_BOARD(b);
    assert(IS_DIAGONAL(b.x_board) == false);
    assert(IS_REV_DIAGONAL(b.x_board) == false);
}

void test_is_board_full()
{
    ttt_board b = {0};
    ttt_board* pb = &b;

    b.x_board = BOARD_MASK;
    b.o_board = 0x0000;
    assert(IS_BOARD_FULL(b.x_board, b.o_board) == true);

    CLEAN_BOARD(b);
    assert(IS_BOARD_FULL(b.x_board, b.o_board) == false);

    b.x_board = 0b0000000101010101;
    b.o_board = 0b0000000010101000;
    assert(IS_BOARD_FULL(b.x_board, b.o_board) == false);

    b.o_board = 0b0000000010101010;
    assert(IS_BOARD_FULL(b.x_board, b.o_board) == true);
}

void test_is_game_over()
{
    ttt_board b = {0};
    ttt_board* pb = &b;

    b.x_board = BOARD_MASK;
    b.o_board = 0x0000;
    assert(is_game_over(pb) == true);

    CLEAN_BOARD(b);
    assert(is_game_over(pb) == false);

    CLEAN_BOARD(b);
    set_piece(pb, 1, X);
    set_piece(pb, 2, X);
    set_piece(pb, 3, O);
    set_piece(pb, 4, O);
    set_piece(pb, 5, X);
    set_piece(pb, 6, X);
    set_piece(pb, 7, X);
    set_piece(pb, 8, O);
    set_piece(pb, 9, EMPTY);
    assert(is_game_over(pb) == false);

    set_piece(pb, 9, O);
    assert(is_game_over(pb) == true);
}

void run_tests()
{
    test_is_row();
    test_is_col();
    test_is_diagonal();
    test_is_board_full();
    test_is_game_over();
}
