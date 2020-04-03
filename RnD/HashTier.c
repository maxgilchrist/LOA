#include <stdint.h>
#include <stdlib.h>
int factorial(int n ) {
	return ((n==1) || (n==0)) ? 1 : n * factorial(n-1);
}
int choose(int n, int k) {
	return (factorial(n)/(factorial(k)*factorial(n-k)));
}
int rearranger-ox-positions(int s, int o, int x) {
	return (choose(s,o+x)*choose(o+x,x));
}
int* butfirst(int* position, int s) {
	int newposition[s-1];
	for (int i = 1; i < s; i++} {
		*(newposition+i-1) = *(position+i);
	}
	return newposition;
}
struct node {
	int key;
	int val;
	struct node* next;
};

struct table {
	int size;
	struct node** list;
};
struct tiernode {
	uint8_t key;
	struct table* val;
	struct tiernode* next;
};
struct tiertable {
	int size;
	struct tiernode** list;
};
struct table* makeTable(int size) {
	struct table* t = (struct table*) malloc(sizeof(struct table));
	t->size = size;
	t->list = (struct node**) malloc(sizeof(struct node*) *size);
	for (int i = 0; i < size; i++) {
		t->list[i] = NULL;
	}
	return t;
}
int lookupHelper(struct table* t, int key) {
	struct node* list = t->list[key];
	struct node* temp = list;
	while(temp) {
		if(temp->key == key) {
			return temp->val;
		}
		temp  = temp->next;
	}
	return -1;
}
void insertHelper(struct table* t, int key, int val) {
	struct node* list = t->list[key];
	struct node* newNode = (struct node*) malloc(sizeof(struct node));
	struct node* temp = list;
	while(temp) {
		if(temp->key == key) {
			temp->val = val;
			return;
		}
		temp = temp->next;
	}
	newNode->key = key;
	newNode->val = val;
	newNode->next = list;
	t->list[key] = newNode;
}
void insertTable(struct tiertable* t, uint8_t key, struct table* val) {
	struct tiernode* list = t->list[key];
	struct tiernode* newTierNode = (struct tiernode*) malloc(sizeof(struct tiernode));
	struct tiernode* temp = list;
	while(temp) {
		if(temp->key == key) {
			temp->val = val;
			return;
		}
		temp = temp->next;
	}
	newTierNode->key = key;
	newTierNode->val = val;
	newTierNode->next = list;
	t->list[pos] = newTierNode;
}
struct table* lookupTier(struct tiertable* t, int* position) {
	int s = 64; int o = 0; int x = 0;
	for (int i = 0; i < s; i++) {
		if (*(position+i)==2) {
			o++;
		} else if (*(position+i)==3) {
			x++;
		}

	}
	int key = indexTierFinder(o-2,x-2);
	struct tiernode* list = t->list[key];
	struct tiernode* temp = list;
	while(temp) {
		if(temp->key==key) {
			return temp->val;
		}
	}
	return NULL;
}
uint8_t indexTierFinder(int white, int black) {
	return white*11 + black;
}
//Sizeof tiertable for this game is 121 so indexes will be 
//i = # of 2 and j = # of 3 
//so the index = i * 11 + j 
//TODO: reminder to make sure to amke everything line up
struct tiertable* makeTierTable(int size) {
	struct tiertable* t = (struct tiertable*) malloc(sizeof(struct tiertable));
	t->size = size;
	t->list = (struct tiernode**) malloc(sizeof(struct tiernode*)*size);
	struct table* temp;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			temp = makeTable(rearranger-ox-positions(s,i+2,j+2));
			t->list[indexTierFinder(i,j)] = temp;		
		}
	}	
	return t;
}
int hash-rearranger-ox-h(int* position, int s, int o, int x) {
	if ((s==o)||(s==x)||((o==0)&&(x==0))) {
		return 0;
	} else if (*(position)==0) {
		return hash-rearranger-ox-h(butfirst(position,s),s-1,o,x);
	} else if (*(position)==2) {
		return ((x+o)==s ? 0 : rearranger-ox-positions(s-1,o,x) + hash-rearranger-ox-h(butfirst(position,s),s-1,o-1,x);
	} else {
		return (x+o)==s ? 0 : rearranger-ox-positions(s-1,o,x) + (o==0? : rearranger-ox-positions(s-1,o,x-1) + hash-arranger-ox-h(butfirst(position,s),s-1,o,x-1));
	}
}
void insert(struct tiertable* t, int* key, int val) {}
	struct table* currentTier = lookupTier(t,key);
	insertHelper(currentTier, hash-arranger-ox-h(position,s,o,x),val);
}
//Check stored should have all of the symmtery stuff
//It will be using vector operations
//ill put it in a different file
//API is void CheckStored(struct table* t, int* position) {}
int lookup(struct tiertable* t, int* position) {
	struct table* currentTier = lookupTier(t,position);
	CheckStored(currentTier,position);
	return lookupHelper(currentTier,hash-arranger-ox-h(position,s,o,x));
}

