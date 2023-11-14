#include <stdio.h>	

	char heap[8192];

typedef struct metadata {
    struct metadata *prev;
    struct metadata *next;
    unsigned int size;
    int free;
}
 metadata;

metadata *head = (metadata*) heap;
void *jalloc(unsigned int size) {
    		metadata *current = head;
	//	printf("%p, %i, %i\n", current, current->free, current->size);
    	while (current && !(current->free && current->size >= size)) {
        		current = current->next;   //checking if can fit if not then move to the next one
	//	printf("%s%p\n", "hello", current);
    		}
    		if (!current) {
	//	printf("%s\n", "new current");
        	return NULL;
    		}
	//	printf("%i\n", current->size);
    		if (current->size > size + sizeof(metadata)) {
     		metadata *new_block = (metadata *)((char *)current + sizeof(metadata) + size);
       		new_block->prev = current; 
	        new_block->next = current->next;
        	new_block->size = current->size - size - sizeof(metadata);
        	new_block->free = 1;
       		current->next = new_block;
        	current->size = size;
    		}
    	current->free = 0;			
    	return (void *)(current + sizeof(metadata));		
	}

void jfree(void *p) {  
	    if (!p) { //if p is empty
        	return;
    	}
   	 metadata *current = (metadata *)p - sizeof(metadata); //set current
    	current->free = 1; //free 1
    	if (current->prev && current->prev->free) { //if current has a prev and is free
        	current->prev->next = current->next;
        	current->prev->size += current->size + sizeof(metadata);
        	if(current->next){
			current->next->prev = current->prev;
    	}
}
    	if (current->next && current->next->free) {
       		current->next = current->next->next;
        	current->size += current->next->size + sizeof(metadata);
		if(current->next->next){
			current->next->next->prev = current;
	}
    }
}
int main(){
	head->size = sizeof(heap)-sizeof(metadata);
	head->free = 1;

        void *pt = jalloc(256);
        void *p = jalloc(512);
        char *pp = jalloc(1024);

        printf("%p\n", pt);
        printf("%p\n", p);
        printf("%p\n", pp);
	jfree(p);
	void *rp = jalloc(289);
	void *r = jalloc(100);
	 printf("%p\n", rp);
        printf("%p\n", r);
}
