#include "board.h"

#define R1 .4
#define R2 R1 * R1

uint8_t lsb(bitboard b) {
	return __builtin_ffs(b);
}

bitboard unset_lsb(bitboard b) {
	return b & (b - 1);
}

namespace bitboards {
	void init() {
		for (uint8_t p = 0; p < 16; ++p) {
			sqr[p] = 1 << p;
		}
	}
	bitboard sqr[16];
}

board::board(tile b[16]) {
	space_ = 0;
	num_empty_ = 0;
	for (int i = 0; i < 16; ++i) {
		b_[i] = b[i];
		if (!b[i]) {
			space_ |= bitboards::sqr[i];
			++num_empty_;
		}
	}
}

int board::eval() const {
	int e = num_empty_;
	return e;
}

bool board::left(board *n) const {
	n->clear();
	bool r = false;
	for (uint8_t p = 0; p < 16;) {
		uint8_t count = 0;
		bool coll = false;
		for (const uint8_t bnd = p + 4; p < bnd; ++p) {
			if (b_[p] == 0) {
				++count;
			}
			else if (coll && n->b_[p - count - 1] == b_[p]) {
				++count;
				++n->b_[p - count];
				coll = false;
				r = true;
			}
			else {
				n->b_[p - count] = b_[p];
				coll = true;
				r = r || count;
			}
		}
		n->space_ |= ((1 << count) - 1) << (p - count);
		n->num_empty_ += count;
	}
	return r;
}

bool board::right(board *n) const {
	n->clear();
	bool r = false;
	for (int8_t p = 15; p >= 0;) {
		uint8_t count = 0;
		bool coll = false;
		for (const uint8_t bnd = p - 3; p >= bnd; --p) {
			if (b_[p] == 0) {
				++count;
			}
			else if (coll && n->b_[p + count + 1] == b_[p]) {
				++count;
				++n->b_[p + count];
				coll = false;
				r = true;
			}
			else {
				n->b_[p + count] = b_[p];
				coll = true;
				r = r || count;
			}
		}
		n->space_ |= ((1 << count) - 1) << (p + 1);
		n->num_empty_ += count;
	}
	return r;
}

bool board::up(board *n) const {
	n->clear();
	bool r = false;
	for (uint8_t j = 0; j < 4; ++j) {
		uint8_t count = 0;
		bool coll = false;
		uint8_t p = j;
		for (; p < 16; p += 4) {
			if (b_[p] == 0) {
				++count;
			}
			else if (coll && n->b_[p - 4 * (count + 1)] == b_[p]) {
				++count;
				++n->b_[p - 4 * count];
				coll = false;
				r = true;
			}
			else {
				n->b_[p - 4 * count] = b_[p];
				coll = true;
				r = r || count;
			}
		}
		n->space_ |= (((1 << (4 * count)) - 1) / 15) << (j + 4 * (4 - count));
		n->num_empty_ += count;
	}
	return r;
}

bool board::down(board *n) const {
	n->clear();
	bool r = false;
	for (int8_t j = 0; j < 4; ++j) {
		uint8_t count = 0;
		bool coll = false;
		int8_t p = 12 + j;
		for (; p >= j; p -= 4) {
			if (b_[p] == 0) {
				++count;
			}
			else if (coll && n->b_[p + 4 * (count + 1)] == b_[p]) {
				++count;
				++n->b_[p + 4 * count];
				coll = false;
				r = true;
			}
			else {
				n->b_[p + 4 * count] = b_[p];
				coll = true;
				r = r || count;
			}
		}
		n->space_ |= (((1 << (4 * count)) - 1) / 15) << j;
		n->num_empty_ += count;
	}
	return r;
}

void board::place(board *n, tile t, uint8_t pos) const {
	*n = board(*this);
	n->b_[pos] = t;
	n->space_ ^= bitboards::sqr[pos];
	--n->num_empty_;
}


tile board::operator[](int i) const {
	return b_[i];
}

bitboard board::space() const {
	return space_;
}

int board::num_empty() const {
	return num_empty_;
}

void board::clear() {
	for (uint8_t i = 0; i < 16; ++i) {
		b_[i] = 0;
	}
	space_ = 0;
	num_empty_ = 0;
}