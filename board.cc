#include "board.h"

char lsb(bitboard b) {
	return __builtin_ffs(b);
}
char unset_lsb(bitboard b) {
	char c = __builtin_ffs(b);
	b &= (b - 1);
	return c;
}

namespace bitboards {
	void init() {
		for (char p = 0; p < 16; ++p) {
			sqr[p] = 1u << p;
		}
	}
	bitboard sqr[16];
}

board::board() {
	space_ = 0u;
	num_empty_ = 0;
}

board::board(char b[16]) : board() {
	for (int i = 0; i < 16; ++i) {
		b_[i] = b[i];
		if (!b[i]) {
			space_ |= bitboards::sqr[i];
			++num_empty_;
		}
	}
}

int board::eval() const {
	return num_empty_;
}

board *board::left() const {
	board *n = new board();
	n->num_empty_ = num_empty_;
	for (int i = 0; i < 4; ++i) {
		int count = 0;
		bool coll = false;
		for (int j = 0; j < 4; ++j) {
			int p = 4 * i + j;
			if (b_[p] == 0) {
				++count;
			}
			else if (coll && n->b_[p - count - 1] == b_[p]) {
				++count;
				++n->b_[p - count];
				coll = false;
			}
			else {
				n->b_[p - count] = b_[p];
				coll = true;
			}
		}
		n->space_ |= ((1u << (4 - count)) - 1) << (i << 2);
		n->num_empty_ -= count;
	}
	return n;
}

board *board::right() const {
	board *n = new board();
	return n;
}
board *board::up() const {
	board *n = new board();
	return n;
}
board *board::down() const {
	board *n = new board();
	return n;
}
board *board::place(char tile, char pos) const {
	board *n = new board(*this);
	n->b_[pos] = tile;
	n->space_ ^= bitboards::sqr[pos];
	--n->num_empty_;
	return n;
}
int board::operator[](int i) const {
	return b_[i];
}
bitboard board::space() const {
	return space_;
}
int board::num_empty() const {
	return num_empty_;
}