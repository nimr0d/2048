#include <iostream>
#include "board.h"

void print_board(board *b) {
	for (int p = 0; p < 16;) {
		for (const int bnd = p + 4; p < bnd; ++p) {
			int c = (*b)[p];
			if (c) {
				std::cout << (1 << c) << " ";
			} else {
				std::cout <<  "_ ";
			}
			
		}
		std::cout << "\n";
	}
	std::cout << "Empty spaces: " << b->num_empty() << "\n";
}
void print_bb(bitboard b) {
	for (int p = 0; p < 16;) {
		for (const int bnd = p + 4; p < bnd; ++p) {
			std::cout << ((b >> p) & 1) << " ";
			
		}
		std::cout << "\n";
	}
}

int main() {
	bitboards::init();
	char b[16] = {1, 1, 0, 1, 2, 0, 2, 3, 2, 1, 0, 0, 0, 1, 1, 0};
	board bd(b);
	print_board(&bd);
	print_board(bd.left());
	print_bb(bd.left()->space());
	print_board(bd.right());
	print_bb(bd.right()->space());
	print_board(bd.up());
	print_bb(bd.up()->space());
	print_board(bd.down());
	print_bb(bd.down()->space());
	print_board(bd.place(4, 2));
}