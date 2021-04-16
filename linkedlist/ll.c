#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef struct ll_node {
	void* payload;
	struct ll_node* next;
} ll_node_t;

typedef struct ll_head {
	ll_node_t* head;
	int size;
} ll;

ll* ll_construct() {
	ll* head = (ll*) malloc(sizeof(ll));
	head->head = NULL;
	head->size = 0;
	return head;
}

int ll_destroy(ll* head) {
	ll_node_t* curr = head->head;
	ll_node_t* next = curr->next;

	while (curr != NULL) {
		ll_node_t* temp = curr;
		curr = curr->next;
		free(temp);
	}

	free(head);
	return 1;
}

int ll_deep_destroy(ll* head) {
	ll_node_t* curr = head->head;
	ll_node_t* next = curr->next;

	while (curr != NULL) {
		free(curr->payload);
		ll_node_t* temp = curr;
		curr = curr->next;
		free(temp);
	}

	free(head);
	return 1;
}

int ll_insert(ll* head, void* payload) {
	ll_node_t* curr = head->head;
	head->size++;

	// empty LL
	if (curr == NULL) {
		head->head = (ll_node_t*) malloc(sizeof(ll_node_t));
		head->head->payload = payload;
		head->head->next = NULL;
		return 1;
	}

	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = (ll_node_t*) malloc(sizeof(ll_node_t));
	curr->next->next = NULL;
	curr->next->payload = payload;

	return 1;
}

int ll_insert_posn(ll* head, void* payload, int posn) {
	if (posn > head->size - 1)
		return -1;

	ll_node_t* curr = head->head;
	int counter;
	for (counter = 0; counter < posn-1; counter++) {
		curr = curr->next;
	}

	// time to insert here
	ll_node_t* old_next = curr->next;
	curr->next = (ll_node_t*) malloc(sizeof(ll_node_t)); 
	curr->next->payload = payload;
	curr->next->next = old_next;
	head->size++;
	return 1;
}

int ll_find(ll* head, void* payload) {
	ll_node_t* curr = head->head;

	int counter = 0;
	while (curr != NULL) {
		if (curr->payload == payload)
			return counter;
		curr = curr->next;
		counter++;
	}
	return -1;
}

void* ll_get(ll* head, int posn) {
	ll_node_t* curr = head->head;
	if (posn > head->size - 1)
		return NULL;

	int i;
	for (i = 0; i < posn; i++) {
		curr = curr->next;
	}

	return curr->payload;
}

int ll_delete(ll* head, int posn) {
	ll_node_t* curr = head->head;
	ll_node_t* prev = NULL;
	if (posn > head->size - 1)
		return -1;

	if (posn == 0) {
		ll_node_t* shunned = head->head;
		head->head = head->head->next;
		free(shunned);
		head->size--;
		return 1;
	}

	int i;
	for (i = 0; i < posn; i++) {
		prev = curr;
		curr = curr->next;
	}

	ll_node_t* link = curr->next;
	free(curr);
	prev->next = link;
	head->size--;
	return 1;
}

void* ll_peek(ll* head) {
	return head->head->payload;
}

void* ll_pop(ll* head) {
	void* payload = head->head->payload;
	ll_delete(head, 0);
	return payload;
}

int ll_reverse(ll* head) {
	ll_node_t* curr = head->head;
	ll_node_t* prev = NULL;
	ll_node_t* next = NULL;

	while(curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	head->head = prev;
	return 1;
}

int ll_print(ll* head) {
	ll_node_t* curr = head->head;

	while (curr != NULL) {
		printf("%d\n", *(int*) curr->payload);
		curr = curr->next;
	}
	return 1;
}

char* gimme_string(int len) {
	char* str = (char*) malloc(sizeof(char) * (len+1));
	str[len] = '\0';
	while (len-- > 0) {
		int index = rand() % strlen(charset);
		str[len] = charset[index];
	}
	printf("%c\n", str);
	return str;
}


int main(int argc, int* argv) {
	// FULL TEST
	ll* ll1 = ll_construct();

	// STANDARD INSERT
	int i;
	for (i = 0; i < 100; i++) {
		int* hey = (int*) malloc(sizeof(int));
		hey[0] = i;
		ll_insert(ll1, hey);
	}

	// POSITIONAL INSERT
	int* hey = (int*) malloc(sizeof(int));
	hey[0] = 420;
	ll_insert_posn(ll1, hey, 50);

	// FIND POSITION
	printf("Found: %d\n", ll_find(ll1, hey));

	// GET
	printf("Get: %d\n", *(int*) ll_get(ll1, 50));

	// DELETE
	ll_delete(ll1, 50);

	// GET AGAIN
	printf("Get again: %d\n", *(int*) ll_get(ll1, 50));

	printf("\n\nReverse and print:\n\n", ll_reverse(ll1));

	// PEEK / POP
	printf("Peek: %d\n", *(int*) ll_peek(ll1));
	printf("Popped: %d\n", *(int*) ll_pop(ll1));
	printf("Peek: %d\n", *(int*) ll_peek(ll1));

	ll_print(ll1);
	ll_deep_destroy(ll1);

	printf("STRING TIME");
	printf("%c\n", gimme_string(50));

	ll* ll2 = ll_construct();


	return 0;
}