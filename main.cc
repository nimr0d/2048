#include <iostream>
#include "board.h"
#include "search.h"
#include <cstdlib>

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
	tile b[16] = {1, 1, 0, 1, 2, 0, 2, 3, 2, 1, 0, 0, 0, 1, 1, 0};
	board bd(b);
	
	/*print_board(&bd);
	print_board(&bdl);
	print_bb(bdl.space());
	print_board(&bdr);
	print_bb(bdr.space());
	print_board(&bdu);
	print_bb(bdu.space());
	print_board(&bdd);
	print_bb(bdd.space());*/

	std::cout << best_move(&bd, 12) << "\n";
}