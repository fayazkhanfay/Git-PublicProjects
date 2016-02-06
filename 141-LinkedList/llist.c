#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  return l;
}

void lst_free(LIST *l) {
NODE *p = l->front;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}

void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}

/**
* TODO:  print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void lst_print_rev(LIST *l)
{
    int n = lst_len(l);
    int i = 1;
    NODE* p= l->front;
    NODE* tempP = p;
    //printf("\nlist length:::%i\n",n);
    printf("[");
    while (n!=0)
    {
        //printf("lst1 contents in printed reverse:[");
        while (i!=n)
        {
            p=p->next;
            i++;
        }
        printf("%i  ",p->val);
        p=tempP;
        i=1;
        n--;
    }
    printf("]\n");

}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {//In the lab it says their is a bug here but it exactly the same
NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
	lst_push_front(l, val);
  else {  // at least one element before push
	p = malloc(sizeof(NODE));
	p->val = val;
	p->next = NULL;
	l->back->next = p;

	l->back = p;  
  }
}

int lst_len(LIST *l) {
NODE *p = l->front;
int n=0;

  while(p != NULL) {
    n++;
    p = p->next;
  }
  return n;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x)
{
    NODE *p = l->front;
    int n=0;
    
    while(p != NULL) {
        if(p->val == x)
            n++;
        p = p->next;
    }
    return n;
    
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/

int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
	return 0;
  }
  return 1;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l)
{
    NODE *p=l->front;
    NODE *q=l->back;
    //NODE *q=l->front;
    int n= lst_len(l);
    int i=1;
    while (i<=n)
    {
        if (i==n&&p==q)
        {
            //printf("\nwalked succesfully..i::%i,,,n::%i\n",i,n);
            return 1;//Success
        }
        p=p->next;
        i++;
    }
    //printf("\nwalk UNsuccesfully\n");
    fprintf(stderr,"lst_sanity3 error: back pointer is not the last reachable node\n");
    return 0;//UNsuccess
}



ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
 

  if(lst_is_empty(l))
	return DEFAULT;   // no-op// also means 0 from the lab

  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }
  return ret;
}

     
  


/* TODO 
*    
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l)
{
    ElemType ret;
    NODE *q=NULL;
    NODE *p=l->front;
    
    
    if(lst_is_empty(l))
        return DEFAULT;
    
    ret= l->back->val;
    
    if(l->front == l->back)
    {  // one element
        free(l->front);
        l->front = NULL;
        l->back = NULL;
    }
    else
    {
        q = l->back;  // don't lose node being deleted
        
        while (p->next!=q)
        {
            p=p->next;
        }
        l->back=p;
        l->back->next=NULL;
        free(q);
    }
    
    return ret;
} 

/* TODO
*  For full credit, you cannot allocate any new memory!
*
* description:  self-evident
*/
void lst_reverse(LIST *l)
{

    NODE* q=l->back;
    NODE* temp;

    
    NODE* p;
    
    int n= lst_len(l)-1;

    //printf("listNNN::%i",n);
    int i;
    
    while (n>0)
    {
        i=1;
        p=l->front;
        while (i<n)
        {
            p=p->next;
            i++;
        }
        //printf("\nkjvskj:::%i\n",p->val);
        q->next=p;
        q=p;
        //return;
        n--;
    }
    temp=l->back;
    l->back=l->front;
    l->front=temp;
    l->back->next=NULL;
    
     
 
    
}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL)
  {
     if(x == p->next->val)
     {
         tmp = p->next;
         p->next = tmp->next;
         
         if(tmp == l->back)
             l->back = p;
         
         free(tmp);
         return 1;
     }
      
     p = p->next;
  }
  return 0;
}




int lst_remove_all_slow(LIST *l, ElemType x) {
int n=0;
  while(lst_remove_first(l, x))
	n++;
  return n;
}

/** TODO
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
 * all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(ElemType n)
{
    
    LIST* lst_func;
    lst_func= lst_create();
    if(n>=1)
        lst_push_back(lst_func,1);
    
    int i=2;
    while (i<=n)
    {
        lst_push_back(lst_func,0);
        i++;
    }

    
	return lst_func;

}

// TODO
// desc:  see header file
int lst_remove_all_fast(LIST *l, ElemType x)
{
    NODE *p;
    NODE *q;
    NODE *tmp;
    int count=0;
    if(l->front == NULL) return 0;
    while(l->front->val == x)//took this from remove slow but changed it to a while loop
    {
        lst_pop_front(l);
        count++;
       // return 1;
    }
    // lst non-empty; no match on 1st elem
    p = l->front->next;
    q = l->front;
    while(p!=l->back)
    {
        
        if(p->val==x)
        {
            q->next=p->next;
            free(p);
            p=q->next;
            count++;
          
        }
        else
        {
            q=p;
            p=p->next;
        }
   
    }
    
    if (p->val==x)
    {
        lst_pop_back(l);
        count++;
    }
    
    return count;
  
}




// TODO
int lst_is_sorted(LIST *l)
{
    if (lst_len(l)==1)
    {
        return 1;//It is sorted increasing
    }
    
    NODE* p=l->front;
    NODE* q=p->next;
    
    while (p->next!=NULL)
    {
        q=p->next;
        
        if (q->val<p->val)
            return 0;
        
        p=p->next;
    }
    
    
  return 1;//It is sorted increasing

}



/** TODO
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x)
{
    NODE* new=malloc(sizeof(NODE));
    new->val=x;

    NODE* p=l->front;
    int i=1;
    int n =lst_len(l);
    //printf("listlength::%i\n",n);
    
    if(l->front->val>x)
    {
        new->next=l->front;
        l->front=new;
        return;
    }

    while (p!=l->back)
    {
        if(p->next->val>x)
        {
            //printf("i:::%i:::val::%i\n",i,p->val);
            new->next=p->next;
            p->next=new;
            return;
        }
        //printf("%i ",p->val);
        p=p->next;
    }
    //printf("\nafter while%i\n",p->val);
    new->next=NULL;
    l->back->next=new;
    l->back=new;
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
extern void lst_merge_sorted(LIST *a, LIST *b);
void lst_merge_sorted(LIST *a, LIST *b)
{
    NODE* A_p=a->front;
    NODE* B_p=b->front;
    
    NODE* A_q;
    
    
    if (lst_len(b)==0)
    {
        printf("\nSecond list empty,Nothing to Merge\n");
    }
    
    if(B_p->val<=A_p->val&&b->front!=NULL)
    {
        b->front=B_p->next;
        B_p->next=a->front;
        a->front=B_p;
        A_p=B_p->next;
        B_p=b->front;
        A_p=a->front;
    }
    
    A_q=a->front->next;
    
    while (A_q!=NULL&&b->front!=NULL)
    {
        if (b->front->val>=A_p->val&&b->front->val<=A_q->val)
        {
            b->front=b->front->next;
            B_p->next=A_q;
            A_p->next=B_p;
            A_p=B_p;
            B_p=b->front;
        }
        else
        {
            A_q=A_q->next;
            A_p=A_p->next;
        }
    }
    
    if (b->front==NULL)
        return;//Second list is empty

    a->back->next=b->front;
    a->back=b->back;
    b->front=NULL;
    b->back=NULL;
    B_p=NULL;
}


void Read_Add(LIST *l, LIST* Add[])
{
     NODE* p;
    //NODE*d;
    //d= Add;
    
    p=l->front;
    int count=0;
    while (p->next!=NULL)
    {
        printf("VAlue::%i",p->val);
        //Add[count]=p->next;
        p=p->next;
        count++;
    }
}
/*
 void Read_Add(LIST *l, LIST* Add[])
 {
 LIST* p;
 //NODE*d;
 //d= Add;
 
 //p=l->front;
 int count=0;
 while (l->front->next!=NULL)
 {
 printf("VAlue::%i",l->front->val);
 Add[count]=p;
 l->front=l->front->next;
 count++;
 }
 
 }
 */



