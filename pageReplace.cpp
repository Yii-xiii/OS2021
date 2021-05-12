#include "pageReplace.h" 
#include <stdio.h>
#define MAX_PHY_PAGE 64
#define MAX_PAGE 12
#define get_Page(x) (x>>MAX_PAGE)

#define MAX_VALUE 2147483647
#define N 4096 //2^12
#define M MAX_PHY_PAGE-20

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct Page {
        struct Page *next = NULL;
        struct Page *prev = NULL;
        int pgNum = -1;
        int last = 0; 
        int hitOther = MAX_PHY_PAGE;
        unsigned long count = 0;
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
static unsigned long cnt = 1;


int containPage(int pgNum) {
        struct Page *p;
        p = pagemap[(pgNum & (N - 1))];
        
        //if (p == NULL) {
        //      return 0;
        //}
       while (p != NULL) {
                if (p->pgNum == pgNum) {
                        //p->hit-=2;
                		p->last = p->hitOther;
                		p->hitOther = 0;
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
        int index = 0;
        //static int count = 0;
        int flag = 1;
        int replace = 0;
        int pgNum = get_Page(nwAdd);

            //printf("start at : %d\n",index);
            //if (!pgNum) {
            //  return;
            //}

        
            if (containPage(pgNum)) {
                return;
            }
            

            //printf("miss\n");
            //int end = index;
                while (pgNum) {
                        	/*if (pages[index].pgNum == pgNum) {
                                    flag = 0;
                                    replace = -1;
                                    pages[index].hit-=2;
                                    pages[index].count = cnt++;
                                    //break;
                            } else*/ 

                            if (flag && pages[index].pgNum == -1) {
                                        replace = index;
                                        flag = 0;
                            } else if (flag && //((max < (M) && pages[index].count < pages[replace].count) || 
                                (pages[index].hitOther > MAX(M,pages[index].last) && pages[index].count < pages[replace].count)) {
                                    replace = index;
                        	} 

                            pages[index].hitOther++;
                            index++;
                            if (index == MAX_PHY_PAGE) {
                                    index++;
                                break;
                            }
                    }

            //printf("replace : %d\n",replace);

        //if (replace != -1) {
                rmFromMap(pages + replace);
                //printf("return from rm\n");
                pages[replace].pgNum = pgNum;
                pages[replace].hitOther = 0;
                pages[replace].count = cnt++;
                pages[replace].last = 0;
                addToMap(pages + replace);
                physic_memery[replace] = pgNum;
        //}
}
