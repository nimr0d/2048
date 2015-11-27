#include <iostream>
#include "board.h"

void print_board(board b) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int p = 4 * i + j;
			std::cout << b[p] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Empty spaces: " << b.num_empty() << "\n";
}

int main() {
	bitboards::init();
}