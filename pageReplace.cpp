#include "pageReplace.h" 
#include <stdio.h>
#define MAX_PHY_PAGE 64 
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

struct Node {
	//struct Node *next;
	//struct Node **prev;
	long pgNum;
	int status = 0;
};

//struct Node *head = NULL;
struct Node nodes[MAX_PHY_PAGE];

void pageReplace(long *physic_memery, long nwAdd) {
	static int index = 0;
	static int count = 0;
	int end = (!count)? 0 : (index + count - 1) % count;
	int replace = -1;
	int pgNum = get_Page(nwAdd);

	while (true) {
		if ((replace == -1) && (!nodes[index].status)) {
			replace = index;
			//if ((nodes + index) == NULL) {
			//	break;
			//}
			index = (index + 1) % count;
		} else if (nodes[index].pgNum == pgNum) {
			replace = 0;
			nodes[index].status = 1;
			//index = (index + 1) % MAX_PHY_PAGE;
			break;
		} else if ((replace != -1) && index == end) {
			//index = (index + 2) % MAX_PHY_PAGE;
			break;
		} else {
			nodes[index].status--;
			index = (index + 1) % count;
		}
	}

	if (replace != -1) {
		nodes[replace].pgNum = pgNum;
		nodes[replace].status = 1;
		physic_memery[replace] = pgNum;
		if (count != MAX_PHY_PAGE) {
			count++;
		}
	}
}
