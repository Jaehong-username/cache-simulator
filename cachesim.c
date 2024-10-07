/****************************************************************************************************************************
* Programmer: Jaehong Lee
* Class: CPTs 360, Fall 2024
* Programming Assignment: PA1
* Date: September 26th, 2024
* Description: This assignment is a cache simulator project. The cache simulator will tell you counts of hits, misses, and
               evictions in total, taking lines of valgrind memory trace as an input. Depending on command line arguments,
               cache simulator data strcuture will be different depending values passed in for s (number of set index bits),
               E (number of lines per set), b (number of block offset bits).For more information on how to run this program, 
               please include -h in your command line argument to run the program.
****************************************************************************************************************************/


//These following five will be the test cases for the project

//   ./cachesim -s 1 -E 1 -b 1 -t traces/trace01.dat
//   ./cachesim -s 4 -E 2 -b 4 -t traces/trace02.dat
//   ./cachesim -s 2 -E 1 -b 4 -t traces/trace03.dat
//   ./cachesim -s 5 -E 1 -b 5 -t traces/trace04.dat
//   ./cachesim -v -s 4 -E 1 -b 4 -t traces/trace02.dat

//Additional
//   ./cachesim -v -s 1 -E 1 -b 1 -t traces/trace01.dat
//   ./cachesim -v -s 2 -E 1 -b 4 -t traces/trace03.dat
//   ./cachesim -v -s 5 -E 1 -b 5 -t traces/trace04.dat
#include "cache.h"



//-Werror    will treat warnings as errors!
//For this cache simulator, we are using LRU (least-recently used) replacement policy

/* 
 * this function provides a standard way for your cache
 * simulator to display its final statistics (i.e., hit and miss)
 */ 
void print_summary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
}

/*
 * print usage info
 */
void print_usage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/trace01.dat\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/trace01.dat\n", argv[0]);
    exit(0);
}

/*
 * starting point
 */
int main(int argc, char* argv[])
{
   
    int hit_count = 0;
    int miss_count = 0;
    int eviction_count = 0;
    
    //Cache Organziation!
    int s = 0;
    int E = 0;
    int b = 0;
    
    //File path:
    FILE *infile = NULL;
    FILE *outfile = NULL;
    char file_path[100] = "";
    char outfile_path[100] = "";
    char *cmd_infile[] = {"traces/trace01.dat", "traces/trace02.dat", "traces/trace03.dat", "traces/trace04.dat", 0};
    char *cmd_outfile[] = {"traces/output/trace01out.txt", "traces/output/trace02out.txt", "traces/output/trace03out.txt", "traces/output/trace04out.txt", 0};
    int file_num = 0;
    // Verbose Mode on or off? based on the command line argument
    Boolean verbose_mode = FALSE;
    
    char c = '\0';
    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (c)
        {
            // other condition checking
        case 's':
            s = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'b':
            b = atoi(optarg);
            break;
        case 't':
            strcpy(file_path, optarg);
            break;
        case 'v':
            verbose_mode = TRUE; //if v passed in command line argument, set verbose_mode true!
            break;
        case 'h':
            print_usage(argv);
            exit(0); // exit(0) indicates successful termination of the program!
        default:
            print_usage(argv);
            exit(1);
        }
    }
    
    
    //Allocating memory space for cache data structure! 2d array
    CacheBlock ***pCacheArray = (CacheBlock***)malloc(pow(2, s) * sizeof(CacheBlock**)); 
    //we need a 2d array!
    //And each array block will store a pointer as well!
    //Therefore we need a triple pointer!
    //each array block will store a ptr to CaceBlock created on the heap
    for (int i = 0; i < (int)pow(2, s); i++){
        //defining for each row!
        pCacheArray[i] = (CacheBlock **)malloc(E * sizeof(CacheBlock *));
        // Error!!!! Infinite Loop! instead of j < pow(2, j) I should have just written j < E   E is an argument we passed in command line
        for (int j = 0; j < E; j++){
            //Warning!  not casting (CacheBlock**)! instead should be (CacheBlock*)
            pCacheArray[i][j] = (CacheBlock *)malloc(sizeof(CacheBlock));
            //init data members
            pCacheArray[i][j]->least_recently_used_score = 0;
            pCacheArray[i][j]->valid_bit = 0;
            strcpy(pCacheArray[i][j]->tag, "");
            // Segmentation error!!! when init string, you should just use
            // pCacheArray[i][j]->tag = "";
            // strcpy(pCacheArray[i][j]->tag, "");
            pCacheArray[i][j]->pBytesArray = NULL;
            //allocating memory space for how many bytes in each cache block!
            
            pCacheArray[i][j]->pBytesArray = (CacheData*)malloc((int)pow(2, b) * sizeof(CacheData));
            //for example if b = 1 we will make room for  0 and 1 in the cache
            //since this program only requires us to know whether hit, miss, eviction rather than the actual data content is
            //i have decided to feel enum values: Filled vs Not-Filled
            for (int k = 0; k < (int)pow(2, b); k++){ //filling each byte will Filled or Not filled
                pCacheArray[i][j]->pBytesArray[k] = NOT_FILLED; //init with NNOT_FILLED
            }
        }
    }

    //choosing which file to open so that I can use switch statement!
    while (cmd_infile[file_num]){
        if (strcmp(file_path, cmd_infile[file_num]) == 0){
            strcpy(outfile_path, cmd_outfile[file_num]);
            file_num++; // because trace file starts at 01 not 00
            break;
        }
        file_num++;
    }

    switch(file_num){
        case 1:
            infile = fopen(file_path, "r");
            outfile = fopen(outfile_path, "w");
            if (infile != NULL && outfile != NULL)
            {
                run_cache_analysis(pCacheArray, s, E, b, infile, outfile, &hit_count, &miss_count, &eviction_count, verbose_mode);
                if (verbose_mode == TRUE)
                {
                    fprintf(outfile, "hits:%d misses:%d evictions:%d\n", hit_count, miss_count, eviction_count);
                }
                else
                {
                    fprintf(outfile, "Verbose Mode is not on!\n");
                }
                fclose(infile);
                fclose(outfile);
            }
            break;
        case 2: //Error!: make sure to put infile =  and outfile =
            infile = fopen(file_path, "r");
            outfile = fopen(outfile_path, "w");
            if(infile != NULL && outfile != NULL){
                run_cache_analysis(pCacheArray, s, E, b, infile, outfile, &hit_count, &miss_count, &eviction_count, verbose_mode);
                if(verbose_mode == TRUE){
                    fprintf(outfile, "hits:%d misses:%d evictions:%d\n", hit_count, miss_count, eviction_count);
                }else{
                    fprintf(outfile, "Verbose Mode is not on!\n");
                }
                fclose(infile);
                fclose(outfile);
            }
            break;
        case 3:
            infile = fopen(file_path, "r");
            outfile = fopen(outfile_path, "w");
            if(infile != NULL && outfile != NULL){
                run_cache_analysis(pCacheArray, s, E, b, infile, outfile, &hit_count, &miss_count, &eviction_count, verbose_mode);
                if(verbose_mode == TRUE){
                    fprintf(outfile, "hits:%d misses:%d evictions:%d\n", hit_count, miss_count, eviction_count);
                }else{
                    fprintf(outfile, "Verbose Mode is not on!\n");
                }
                fclose(infile);
                fclose(outfile);
            }
            break;
        case 4:
            infile = fopen(file_path, "r");
            outfile = fopen(outfile_path, "w");
            if(infile != NULL && outfile != NULL){
                run_cache_analysis(pCacheArray, s, E, b, infile, outfile, &hit_count, &miss_count, &eviction_count, verbose_mode);
                if(verbose_mode == TRUE){
                    fprintf(outfile, "hits:%d misses:%d evictions:%d\n", hit_count, miss_count, eviction_count);
                }else{
                    fprintf(outfile, "Verbose Mode is not on!\n");
                }
                fclose(infile);
                fclose(outfile);
            }
            break;
        default:
            printf("input file does not exist in the folder!\n");
            exit(1);
    }

    
    // print cache hit and miss statistics at the end!
    print_summary(hit_count, miss_count, eviction_count);
    
    //free the memory to prevent memory leaks!
    deallocate_cache_structure(pCacheArray, s, E);
    // assignment done. life is good!
    
    return 0;
}
