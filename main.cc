#include <iostream>
#include "board.h"
#include "search.h"
#include <cstdlib>
#include <time.h>

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
	tile b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	board bd(b);
	srand (time(NULL));
	while (true) {
		board n;
		uint8_t N = bd.num_empty();
		bitboard space = bd.space();
		uint8_t spaces[N];
		for (uint8_t i = 0; i < N; ++i) {
			spaces[i] = lsb(space) - 1;
			space = unset_lsb(space);
		}

		tile t = (rand() % 100 > 90) ? 2 : 1;
		bd.place(&n, t, spaces[rand() % N]);

		bd = n;

		// std::cout << "After placement: \n";
		print_board(&bd);
		std::cout << "\n";

		switch (best_move(&bd, 12)) {
			case LEFT:
				bd.left(&n);
				break;
			case RIGHT:
				bd.right(&n);
				break;
			case UP:
				bd.up(&n);
				break;
			case DOWN:
				bd.down(&n);
				break;
			case NONE:
				return 0;
			default:
				std::cout << "Error\n";
				break;
		}
		bd = n;
		// std::cout << "After best move: \n";
		// print_board(&bd);
		// std::cout << "\n";
	}

	/*print_board(&bd);
	print_board(&bdl);
	print_bb(bdl.space());
	print_board(&bdr);
	print_bb(bdr.space());
	print_board(&bdu);
	print_bb(bdu.space());
	print_board(&bdd);
	print_bb(bdd.space());*/

	// std::cout << best_move(&bd, 12) << "\n";
}