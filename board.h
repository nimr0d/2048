#ifndef _BOARD_H_
#define _BOARD_H_

#define P1 0
#define P2 1

typedef unsigned short bitboard;
typedef unsigned char tile;
typedef unsigned char uint8_t;

uint8_t lsb(bitboard b);
bitboard unset_lsb(bitboard b);

namespace bitboards {
	void init();
	extern bitboard sqr[16];
}

/*Immutable board representation*/
class board {
public:
	board(bool player);
	board(tile b[16], bool player);
	board(const board &b) = default;
	int eval() const;
	board *left() const;
	board *right() const;
	board *up() const;
	board *down() const;
	board *place(tile t, uint8_t pos) const;
	bool player() const;
	tile operator[](int i) const;
	bitboard space() const;
	int num_empty() const;

private:
	bool player_;
	tile b_[16];
	bitboard space_;
	uint8_t num_empty_;
};
#endif // _BOARD_H_