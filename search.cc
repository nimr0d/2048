#include "search.h"
#include <algorithm>
#include <vector>

struct comp_p1 {
	bool operator()(board *a, board *b) {
		return a->eval() < b->eval();
	}
};

struct comp_p2 {
	bool operator()(const board &a, const board &b) {
		return a.eval() > b.eval();
	}
};

int minimax_p1(const board *b, unsigned short depth, int alpha, int beta) {
	if (depth == 0) {
		return b->eval();
	}
	int v = -INFTY // FIXME;
	std::vector<board *> children;
	board l, r, u, d;

	if (b->left(&l)) children.push_back(&l);
	if (b->right(&r)) children.push_back(&r);
	if (b->up(&u)) children.push_back(&u);
	if (b->down(&d)) children.push_back(&d);

	std::sort(children.begin(), children.end(), comp_p1);

	for (board *child : children) {
		int s = minimax_p2(child, depth - 1, alpha, beta);
		if (s > v) v = s;
		if (v > alpha) alpha = v;
		if (beta <= alpha) break;
	}
	return v;
}

int minimax_p2(const board *b, unsigned short depth, int alpha, int beta) {
	if (depth == 0) {
		return b->eval();
	}
	int v = INFTY // FIXME;
	uint8_t N = 2 * b->num_empty();
	bitboard space = b->space();
	board children[N];
	for (uint8_t i = 0; i < N; i += 2) {
		uint8_t pos = lsb(space);
		unset_lsb(space);
		b->place(children + i, 1, pos);
		b->place(children + (i + 1), 2, pos);
	}
	std::sort(children, children + N, comp_p2);

	for (uint8_t i = 0; i < N; ++i) {
		int s = minimax_p1(children + i, depth - 1, alpha, beta);
		if (s < v) v = s;
		if (v < beta) beta = v;
		if (beta <= alpha) break;
	}
	return v;
}