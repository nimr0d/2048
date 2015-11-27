#ifndef _BOARD_H_
#define _BOARD_H_
typedef unsigned short bitboard;

char lsb(bitboard b);
char unset_lsb(bitboard b);

namespace bitboards {
	bitboard sqr[16];
	void init();
}

/*Immutable board representation*/
class board {
public:
	board();
	board(char b[16]);
	board(const board &b) = default;
	int eval() const;
	board *left() const;
	board *right() const;
	board *up() const;
	board *down() const;
	board *place(char tile, char pos) const;
	bitboard space() const;

private:
	char b_[16];
	bitboard space_;
	char num_empty_;
};
#endif // _BOARD_H_