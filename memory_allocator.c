#include <stdio.h>
#include<stdlib.h>
#define NUM_OF_BLOCK 50
#define HEAP_BLOCK 64

void *mem_head ;


struct heap_block
{
    void * ptr;
    struct heap_block * next;
    int end;
    int free;
};


struct heap_block * link_list_head = NULL;


void init_heap(){
    mem_head = (void *) malloc( HEAP_BLOCK * NUM_OF_BLOCK);
    // printf("%p",mem_head);
    struct heap_block * current =  malloc(sizeof(struct heap_block));

    for(int i =0;i<NUM_OF_BLOCK;i++){
        if(link_list_head==NULL){
            link_list_head = (struct heap_block * )  malloc(sizeof(struct heap_block));
            link_list_head->free = -1;
            link_list_head->next = NULL;
            link_list_head->end = -1;
            link_list_head->ptr = (void *) mem_head;
            current = link_list_head;
            mem_head = (void *)  ((int *)mem_head + HEAP_BLOCK);

        }else{
            struct heap_block * temp =  malloc(sizeof(struct heap_block));
            temp->free = -1;
            temp->next = NULL;
            temp->end = -1;
            temp->ptr = (void *) mem_head ;
            mem_head = (void *) ((int *)mem_head + HEAP_BLOCK);
            current->next = temp;
            current = temp;

        }
    }
}

void * my_malloc(int size){
    int blocks;
    if(size % HEAP_BLOCK == 0){
        blocks = size / HEAP_BLOCK;
    }else{
        blocks = (size / HEAP_BLOCK) + 1;
    }

    struct heap_block * temp = link_list_head;
    int current_blocks = 0;
    struct heap_block * current_ptr = link_list_head;
    while(temp->next != NULL){
        if(current_blocks == blocks){
            temp->end = -1;
            temp = current_ptr;
            struct heap_block * last ;
            for(int i =0;i<blocks;i++){
                temp->free = 1;
                if(i  == blocks - 1){
                    temp->end = -1;
                }else{
                    temp->end = 1;
                }
                      
                temp = temp->next;
            }
            // temp->end = -1;
            current_ptr->end = 1;
            return current_ptr->ptr;
        }
        if(temp->free == -1){
            current_blocks++;
        }else if (temp->free == 1){
            printf("This address is teken %p", temp->ptr);
            current_blocks = 0;  
            current_ptr = temp->next;  
        }
        temp = temp->next;
    }

    return NULL;
}

void my_free(void * ptr){
    
    printf("%p", ptr);
    
    struct heap_block * temp = link_list_head;
    int iter = 0;

    while (temp->next != NULL)
    {
        if(temp->ptr == ptr){
            printf("iter %d", iter);
            break;
        }
        iter++;
        temp = temp->next;
    }

    // occupy address
    // printf("is Occupy %d",link_list_head->end);
    // printf("\n\n");
    while (temp->end == 1)
    {
        // printf("Occupy %p \n", temp->ptr);
        temp->free = -1;
        temp->end = -1;
        temp = temp->next;
    }
    ptr = NULL;

    



    
}

void print_heap(){
    struct heap_block * temp = link_list_head;
    while(temp->next != NULL){
        printf("%d \t", temp->free);
        printf("%p \t", temp->ptr);
        printf("%d \n", temp->end);


        temp = temp->next;
    }
}


int main() {

    init_heap();
    

    int *block1 = (int *) my_malloc(sizeof(int) * 100);
    printf(" %p\n ", block1);
    print_heap();
    int *block2 = (int *) my_malloc(sizeof(int) * 200);
    printf(" %p\n ", block2);
     print_heap();

    //  save number into array
    for(int i=0;i<30;i++){
        block1[i] = i * 9;
    }
    for(int i=0;i<30;i++){
        printf("%d ",block1[i]);
    }
    



    //  free some space


    my_free(block1);



    print_heap();

    
}
