#include <iostream>
#include "board.h"

void print_board(board *b) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int p = 4 * i + j;
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

int main() {
	bitboards::init();
	char b[16] = {1, 1, 0, 1, 2, 0, 2, 3, 2, 1, 0, 0, 0, 1, 1, 0};
	board bd(b);
	print_board(&bd);
	print_board(bd.left());
	print_board(bd.right());
	print_board(bd.up());
	print_board(bd.down());
}