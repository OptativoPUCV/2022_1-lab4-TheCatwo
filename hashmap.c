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
    long i=hash(key, map->capacity);
    if( (map->buckets[i]==NULL) || (map->buckets[i]->value == NULL) ){
        Pair* newP = createPair(key, value);
        map->buckets[i] = newP;
        map->size++;
    }

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
  
    Pair** aux = map->buckets;
    long T = map->capacity;

    map->buckets = malloc( (T*2) * sizeof(map->buckets) );
    for(long i=0; i < (T*2); i++){
        map->buckets[i] = NULL;
    }
  
    map->size = 0;
    map->capacity =T*2;

    for( long i=0; i <T; i++ ){
        if( aux[i] != NULL){
            if( aux[i]->value != NULL){
                insertMap( map, aux[i]->key, aux[i]->value );
            }
            free(aux[i]);
        }
    }
    free(aux);

}


HashMap * createMap(long capacity) {
    HashMap *m=(HashMap*)malloc(sizeof(HashMap));
    if (!m)
      return NULL;
    
    m->buckets=(Pair**)malloc(capacity* sizeof(Pair*));

    m->size=0;
    m->capacity=capacity;
    m->current = -1;
    if (!m->buckets){
      free(m);
      m= NULL;
      return NULL;
    }
      
    int i;
    for (i= 0; i<capacity; i++)
      m->buckets[i]= 0;
    return m;
}

void eraseMap(HashMap * map,  char * key) {    
  
}

Pair * searchMap(HashMap * map,  char * key) {   
    long i = linearProbing(map, key);

    if( (map->Buckets[i]== NULL) || (map->Buckets[i]->value== NULL) ){
        return NULL;
    }
    map->current = i;
    return map->Buckets[map->current]->value;
}

Pair * firstMap(HashMap * map) {
  
    for(long i=0; i<(map->capacity); i++){
    if(map->buckets[i]!= NULL){
      if(map->buckets[i]->value!= NULL){
          map->current = i;
          return map->buckets[map->current]->value;
      }
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
 
    for( long i= (map->current + 1); i<(map->capacity); i++){
      if( map->buckets[i] != NULL){
        if(map->buckets[i]->value != NULL){
          map->current = i;
          return map->buckets[map->current]->value;
            }
        }
    }
    return NULL;
  
}

long linearProbing(HashMap* map, char * key){
    unsigned long num = stringHash(key);
    long i = num % (map->capacity);
    while(1){
        if( (map->Buckets[i] == NULL) || (map->Buckets[i]->value == NULL) ){
            break;
        }
        if( is_equal( map->Buckets[i]->key, key) ){
            break;
        }
        i++;
        if( i == (map->capacity)){
            i = 0;
        }
    }
    return i;
}

unsigned long stringHash(void* key){
    const char* A_key= key;
    unsigned long num= 5381;
    for(int i=0; A_key[i] != '\0'; i++){
        num *= 33;
        num += A_key[i];
    }
    return num;
}