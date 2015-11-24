#include "board.h"

char lsb(bitboard b) {
	return __builtin_ffs(b)
}
char unset_lsb(bitboard b) {
	char c = __builtin_ffs(b);
	b &= (b - 1);
	return c;
}

board::board(char b[16]) {
	for (int i = 0; i < 16; ++i) {
		if (b[i]) {
			tiles_[b[i]] |= sqr[i];
		} else {
			space_ |= sqr[i];
		}
	}
}

int board::eval() const {
	return num_empty_;
}

board *board::left() const {
	board *b = new board();
	for (int i = 0; i < 4; ++i) {
		int count = 0;
		for (int j = 0; i < 3; ++j) {
			int p = 4 * i + j;
			for (int tile = 0; tile < 17; ++tile) {
				bitboard t = tiles_[tile];
				if (t & sqr[p]) {
					b->tiles_[tile] |= sq[p - count];
					if (t & sqr[p + 1]) {
						++j;
						++count;
					}
					break;
				}
			}
		}
	}
	for (int tile = 0; tile < 17; ++tile) {
		b->space_ &= ~(b->tiles_[tile]);
	}
	return b;
}
board *board::right() const;
board *board::up() const;
board *board::down() const;
board *board::place(char tile, char pos) const {
	board *b = new board(*this);
	b->tiles[tile] |= sqr[pos];
	b->space ^= sqr[pos];
	return b;
}
bitboard board::space() {
	return space_;
}