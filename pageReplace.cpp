#include "pageReplace.h" 
#include <stdio.h>
#define MAX_PHY_PAGE 64
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

#define MAX_VALUE 2147483647

struct Node {
        //struct Node *next;
        //struct Node **prev;
        long pgNum = -1;
        int hit = -1;
};

//struct Node *head = NULL;
struct Node nodes[MAX_PHY_PAGE];

void pageReplace(long *physic_memery, long nwAdd) {
    	static int index = 0;
    	//static int cold = 0;
        int replace = -1; 
        int min = MAX_VALUE;
        int pgNum = get_Page(nwAdd);
	    int end = (index + MAX_PHY_PAGE - 1) % MAX_PHY_PAGE;

	    //printf("start at : %d\n",index);

	        while (true) {
	                if (nodes[index].pgNum == pgNum) {
		                    replace = -1;
		                    nodes[index].hit++;
		                    index = (index + 1) % MAX_PHY_PAGE;
		                    break;
		            } else if (index == end) {
		                    index = (index + 2) % MAX_PHY_PAGE;
	                        break;
		            }

		            if (nodes[index].hit < min) {
		                    replace = index;
		                    min = nodes[index].hit;
		                    index = (index + 1) % MAX_PHY_PAGE;
	                } else {
		                    index = (index + 1) % MAX_PHY_PAGE;
		            }
		    }
		    
	    

        if (replace != -1) {
                nodes[replace].pgNum = pgNum;
                nodes[replace].hit = 0;
                physic_memery[replace] = pgNum;
        }
}
