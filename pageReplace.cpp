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
        int replace = -1; 
        int pgNum = get_Page(nwAdd);


        if (count) {
	        int end = (index + count - 1) % count;
	        int mod = count == MAX_PHY_PAGE ? count : count + 1;
		        while (true) {
		                if ((replace == -1) && (!nodes[index].status)) {
		                        replace = index;
		                        //if ((nodes + index) == NULL) {
		                        //      break;
		                        //} 
		                        index = (index + 1) % mod;
		                } else if (nodes[index].pgNum == pgNum) {
		                        replace = -1;
		                        nodes[index].status = 2;
		                        index = (index + 1) % MAX_PHY_PAGE;
		                        break;
		                } else {
		                        nodes[index].status--;
		                        index = (index + 1) % mod;
		                }

		                if ((replace != -1) && index == end) {
		                        index = (index + 1) % mod;
		                        break;
		                }
		        }
	    } else {
	    	replace = 0;
	    	index++;
	    }

        if (replace != -1) {
                nodes[replace].pgNum = pgNum;
                nodes[replace].status = 2;
                physic_memery[replace] = pgNum;
                if (count != MAX_PHY_PAGE) {
                        count++;
                }
        }
}
