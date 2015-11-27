#include <stack>
#include "search.h"

struct entry {
	board *b;
	unsigned short depth;
	entry(board *b, unsigned short depth) : b(b), depth(depth) {}
};

board *think(const board *b, unsigned short depth) {
	stack<entry> stk;
	stk.emplace(b, depth);

	while (!stk.empty()) {
		entry e = stk.top();
		stk.pop();
		board *node = e.b;
		unsigned short depth = e.depth;
	}

}