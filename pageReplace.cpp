#include "pageReplace.h" 
#include <stdio.h>
#define MAX_PHY_PAGE 64
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

#define MAX_VALUE 2147483647
#define N 16384 //2^14

struct Page {
        struct Page *next = NULL;
        struct Page *prev = NULL;
        int pgNum = -1;
        int hit = -1;
        long count = 0;
};
/*
struct Node {
    struct Node *next;
    struct Node **prev;
    long pgNum = -1;
};
*/

struct Page *pagemap[N];
struct Page pages[MAX_PHY_PAGE];
static unsigned long cnt = 0;

int containPage(int pgNum) {
	struct Page *p;
	p = pagemap[(pgNum & (N - 1))];
	/*
	if (p == NULL) {
		return 0;
	}
	*/

	while (p != NULL) {
		if (p->pgNum == pgNum) {
			p->hit++;
			p->count = cnt++;
			return 1;
		}
		p = p->next;
	}

	return 0;
}

void rmFromMap(struct Page* p) {
	if (p->pgNum == -1) {
		return;
	}

	if (p->next != NULL) {
		(p->next)->prev = p->prev;
	}
	if (p->prev != NULL) {
		(p->prev)->next = p->next;
	}
}

void addToMap(struct Page* p) {
	struct Page *head = pagemap[(p->pgNum) & (N - 1)];
	if (head == NULL) {
		pagemap[p->pgNum & (N - 1)] = p;
		return;
	}

	p->prev = head;
	if ((head)->next != NULL) {
		((head)->next)->prev = p;
	}
	p->next = (head)->next;
	pagemap[p->pgNum & (N - 1)] = p;

}

//struct Node *head = NULL;

void pageReplace(long *physic_memery, long nwAdd) {
    	static int index = 0;
    	//static int count = 0;
        int replace = -1; 
        int min = MAX_VALUE;
        int pgNum = get_Page(nwAdd);

	    //printf("start at : %d\n",index);
	    //if (!pgNum) {
	    //	return;
	    //}

	    if (containPage(pgNum)) {
	    	return;
	    }

	    //printf("miss\n");
	    int end = index;
	        while (true) {
	                /*
	                if (pages[index].pgNum == pgNum) {
		                    replace = -1;
		                    pages[index].hit++;
		                    index = (index + 1) % MAX_PHY_PAGE;
		                    break;
		            } else 
		            */


		            if (pages[index].hit < min || (pages[index].hit == min && pages[index].count < pages[replace].count)) {
		                    replace = index;
		                    min = pages[index].hit;
		                    index = (index + 1) % MAX_PHY_PAGE;
		                    if (min == -1) {
		                    	break;
		                    }
	                } else {
		                    index = (index + 1) % MAX_PHY_PAGE;
		            }

		            if (index == end) {
		                    index = (index + 1) % MAX_PHY_PAGE;
	                        break;
		            }
		    }
		    
	    //printf("replace : %d\n",replace);

        if (replace != -1) {
        		rmFromMap(pages + replace);
        		//printf("return from rm\n");
                pages[replace].pgNum = pgNum;
                pages[replace].hit = 0;
                pages[replace].count = cnt++;
        		addToMap(pages + replace);
                physic_memery[replace] = pgNum;
        }
}
