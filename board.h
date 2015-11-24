#ifndef _BOARD_H_
#define _BOARD_H_

typedef unsigned short bitboard;

char lsb(bitboard b);
char unset_lsb(bitboard b);

namespace bitboards {
	bitboard sqr[16];
}

/*Immutable board representation*/
class board {
public:
	board() = default;
	board(const board &b) = default;
	board(char b[16]);
	int eval() const;
	board *left() const;
	board *right() const;
	board *up() const;
	board *down() const;
	board *place(char tile, char pos) const;
	bitboard space() const;

private:
	bitboard tiles_[17];
	bitboard space_;
	int num_empty_;
};
#endif