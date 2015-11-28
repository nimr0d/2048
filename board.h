#ifndef _BOARD_H_
#define _BOARD_H_

enum player {
	P1, P2
};

typedef unsigned short bitboard;
typedef unsigned char tile;
typedef unsigned char uint8_t;
typedef signed char int8_t;

uint8_t lsb(bitboard b);
bitboard unset_lsb(bitboard b);

namespace bitboards {
	void init();
	extern bitboard sqr[16];
}

/*Immutable board representation*/
class board {
public:
	board() = default;
	board(tile b[16]);
	board(const board &b) = default;
	int eval() const;
	bool left(board *n) const;
	bool right(board *n) const;
	bool up(board *n) const;
	bool down(board *n) const;
	void place(board *n, tile t, uint8_t pos) const;
	tile operator[](int i) const;
	bitboard space() const;
	int num_empty() const;
private:
	tile b_[16];
	bitboard space_;
	uint8_t num_empty_;
	void clear(); // Sets everything to 0. Not a usable board.
};
#endif // _BOARD_H_