#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *m=(HashMap*)malloc(sizeof(HashMap));
    if (!m)
      return NULL;
    
    m->size=0;
    m->capacity=capacity;
    m->buckets=(Pair**)malloc(capacity* sizeof(Pair*));
  
    if (!m->buckets){
      free m;
      m= NULL;
      return NULL;
    }
      
    int i;
    for (i= 0; i<capacity; i++)
      m->buckets[i]= 0;
    return m;
}

void eraseMap(HashMap * map,  char * key) {    
  if (map){
        if (map->buckets){
            int i = 0;
            for (i = 0; i<key; i++){
                HashMap *p = map->buckets[i];
                HashMap *q = NULL;
                while (p)	{
                    q = p->next;
                    p->current = 0;	
                    p = q;
                }
            }
            free(map->buckets);	
            map->buckets = NULL;
        }
        free(map);		
		map= NULL;
    }
	return;
}

Pair * searchMap(HashMap * map,  char * key) {   

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
