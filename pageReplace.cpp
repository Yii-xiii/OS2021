#include "pageReplace.h" 
#include <stdio.h>
#define MAX_PHY_PAGE 64 
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

struct Node {
	//struct Node *next;
	//struct Node **prev;
	long pgNum;
	int status;
};

//struct Node *head = NULL;
struct Node nodes[MAX_PHY_PAGE];

void pageReplace(long *physic_memery, long nwAdd) {
	static int index = 0;
	int end = (index + (MAX_PHY_PAGE - 1)) % MAX_PHY_PAGE;
	int replace = -1;
	int pgNum = get_Page(nwAdd);

	while (true) {
		if ((replace == -1) && ((nodes + index) == NULL || !nodes[index].status)) {
			replace = index;
			index = (index + 1) % MAX_PHY_PAGE;
			if ((nodes + index) == NULL) {
				break;
			}
		} else if (nodes[index].pgNum == pgNum) {
			replace = 0;
			nodes[index].status = 2;
			index = (index + 1) % MAX_PHY_PAGE;
			break;
		} else if ((replace != -1) && index == end) {
			index = (index + 2) % MAX_PHY_PAGE;
			break;
		} else {
			nodes[index].status--;
			index = (index + 1) % MAX_PHY_PAGE;
		}
	}

	if (replace != -1) {
		nodes[replace].pgNum = pgNum;
		nodes[replace].status = 1;
		physic_memery[replace] = pgNum;
	}
}
