#include <stdio.h>
#include <stdlib.h>
#include "list.h"


// very incomplete small test program...

int main() {
LIST *lst1;
    LIST *lst2;
    LIST *lst_func;
    
int i=1;

  lst1 = lst_create();
    lst2= lst_create();
    

  /*for(i=0; i<5; i++) {
     lst_push_front(lst1, i);
  }
  for(i=0; i<5; i++) {
     lst_push_back(lst1, i);
  }*/

    //lst_push_back(lst1, i);
    
    while (i<14)
    {
        //lst_push_front(lst1, i);
        lst_push_back(lst1, i);
        i=i+2;
    }
    i=0;
    lst_push_back(lst2, i);
    while (i<18)
    {
        //lst_push_front(lst1, i);
        lst_push_back(lst2, i);
        i=i+2;
    }
    
    lst_sanity1(lst1);
    lst_sanity2(lst1);
    lst_sanity3(lst1);
    printf("lst_len(lst1) : %i\n", lst_len(lst1));
    printf("lst1 contents: ");
    lst_print(lst1);
   
    //-------------------
        //REVERSE PRINT TEST
   /* printf("lst_len(lst1) : %i\n", lst_len(lst1));
    printf(" REVERSE lst1 contents: ");
    lst_print_rev(lst1);
    */
    //------------------
    lst_func=lst_sra_bad_case(10);
    lst_sanity1(lst_func);
    lst_sanity2(lst_func);
    lst_sanity3(lst_func);
    printf("lst_len(lst_func) : %i\n", lst_len(lst_func));
    printf("lst_func contents: ");
    lst_print(lst_func);

    //lst_push_back(lst1, 1);
 /* printf("lst_len(lst1) : %i\n", lst_len(lst1));
  printf("lst1 contents: ");
  lst_print(lst1);


    printf("lst_len(lst2) : %i\n", lst_len(lst2));
    printf("lst2 contents: ");
    lst_print(lst2);
    */
  //lst_pop_front(lst1);
  //lst_pop_front(lst1);
  //printf("lst1 contents after two pops: ");
  //lst_print(lst1);

    //printf("\nINSANE\n");
  /** TODO:  test code here! **/
    //lst_sanity3(lst1);
    //printf("\nINSANE\n");
  /** test code for lst_count **/

  //printf("number of 3's = %i\n", lst_count(lst1, 3));
  //printf("number of 0's = %i\n", lst_count(lst1, 0));
    
    //lst_reverse(lst1);
    //printf("\nSorted::%i\n",lst_is_sorted(lst1));
    //lst_insert_sorted(lst1,13);
    //lst_remove_all_fast(lst1, 0);
    //lst_merge_sorted(lst1,lst2);
    //lst_func=lst_sra_bad_case(15);
    //lst_merge_sorted(lst1, lst2);
    
    
    lst_sanity1(lst1);
    lst_sanity2(lst1);
    lst_sanity3(lst1);
    /*
    printf("lst_len(lst1) : %i\n", lst_len(lst1));
    printf("lst1 contents: ");
    lst_print(lst1);*/
    
    //lst_sanity1(lst2);
    //lst_sanity2(lst2);
    //lst_sanity3(lst2);
    
   /* printf("lst_len(lst2) : %i\n", lst_len(lst2));
    printf("lst2 contents: ");
    lst_print(lst2);
    */
    
    
    //printf("\nINSANE\n");
    //printf("lst_len(lst2) : %i\n", lst_len(lst_func));
    //printf("lst2 contents: ");
    //lst_print(lst_func);
    
    //lst_print(lst1);
    /*lst_sanity1(lst1);
    lst_sanity2(lst1);
    lst_sanity3(lst1);
    lst_print(lst1);*/

  /** test code for lst_print_rev **/
   // printf("lst1 contents in printed reverse: ");
    //lst_print_rev(lst1);


  /** test code for lst_push_back **/
   /* printf("\nPOP BACK\n");
    while (lst_is_empty(lst1)!=1)
    {
        
    
        lst_pop_back(lst1);
        lst_sanity1(lst1);
        lst_sanity2(lst1);
        lst_sanity3(lst1);
        lst_print(lst1);
    
    }*/
    
  lst_free(lst1);
}
  
