#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <getopt.h> //to parse the command line arguments
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define ADDRESS_LENGTH 64  // 64-bit memory addressing

typedef enum state{
    HIT = 1, MISS_TAG, MISS_INVALID_BIT, MISS_BYTE, NO_EVICTION, EVICTION
}State;

typedef enum cacheData{
    NOT_FILLED, FILLED
}CacheData;

typedef enum boolean{
    FALSE,TRUE
} Boolean;

typedef struct cacheBlock{
    int least_recently_used_score;
    int valid_bit;
    char tag[100];
    CacheData *pBytesArray;
} CacheBlock;

void parse_trace_line(CacheBlock ***pCacheArray, FILE* infile, char line[], char binaryMemAddress[ADDRESS_LENGTH], int* bytes);
void extract_byte(char* byte_content, char binaryMemAddress[ADDRESS_LENGTH], int s, int b);
void extract_setIndex(int* set_index, char binaryMemAddress[ADDRESS_LENGTH], int s, int b);
void extract_tag(char* tag, char binaryMemAddress[ADDRESS_LENGTH], int s, int b);
void convert_to_binary(char *hexaMemAddress, char binaryMemAddress[ADDRESS_LENGTH]);
int convert_to_decimal(int* binary, int s);
void run_cache_analysis(CacheBlock ***pCacheArray, int s, int E, int b, FILE *infile, FILE *outfile, int *hit_count, int *miss_count, int *eviction_count, Boolean verbose_mode);

State is_cache_hit_miss(CacheBlock ***pCacheArray, int* set_index, char* tag, int s, int E, int* target_cache_row, int* target_cache_column);
Boolean is_cache_full(CacheBlock ***pCacheArray, int target_index_row, int E);
State is_cache_eviction(CacheBlock ***pCacheArray, int target_cache_row, int E);

void perform_cache_hit(CacheBlock ***pCacheArray, int target_cache_row, int target_cache_column, int b);
void perform_cache_write(CacheBlock ***pCacheArray, int target_cache_row, int target_cache_column, char *tag, int E, int b);
void perform_cache_replacement(CacheBlock ***pCacheArray, int target_cache_row, int LRU_cache_column, char*tag, int b);
void choose_LRU_cache(CacheBlock ***pCacheArray, int target_cache_row, int *LRU_cache_column, int E);
int perform_cache_eviction(CacheBlock ***pCacheArray, int E, int b, int target_cache_row);
void deallocate_cache_structure(CacheBlock ***pCacheArray, int s, int E);