#include "cache.h"

void parse_trace_line(CacheBlock ***pCacheArray, FILE* infile, char line[], char binaryMemAddress[ADDRESS_LENGTH], int* bytes)
{
    //replacing the newline character at the end with a null terminator!
    //If verbose mode is true, replacing the whitespace character with a nullterminator
    line[strlen(line) - 1] = '\0'; //h e l l o \n
    
    //if a line starts with 
    //if(line[0] == ' '){ //it is not a load instruction!
    //    fseek(infile, 1, SEEK_CUR); // Move the file cursor forward by 1 byte
    //} //we already loaded data to a line array so its pointless to fseek function

    char *hexa_memory_address = NULL;

    // ()L()0,1
    //hexa_memory_address = strtok(line, " ,"); //it's a dummy!!!
    hexa_memory_address = strtok(line, " ,"); //will extract type of operation
    hexa_memory_address = strtok(NULL, " ,"); //will get the memory address
    
    convert_to_binary(hexa_memory_address, binaryMemAddress);
    //now memory address stored in as binary!
    
    *bytes = atoi(strtok(NULL, " ,")); //will get bytes used!
    //we need to dereference to save the bytes Output parameter!!

    return;
}

/* we don't really need this function
void extract_byte(char* byte_content, char binaryMemAddress[ADDRESS_LENGTH], int s, int b)
{
    int j = 0;
    byte_content[b] = '\0'; // filling in a null terminator at the end of a string!!
    for (int i = b - 1; i < 0; i--, j--){
        byte_content[i] = binaryMemAddress[(ADDRESS_LENGTH - 1) - j]; //will store a char!
    }
    // b = 2   _ _
    return;
}
*/
void extract_setIndex(int* set_index, char binaryMemAddress[ADDRESS_LENGTH], int s , int b)
{
   
    int j = ADDRESS_LENGTH - 1 - b - s + 1; //indicates the beginning index of binaryMemAddress to copy from
    for (int i = 0; i < s; i++){
        //printf("\n%d\n", binaryMemAddress[j]);
        set_index[i] = binaryMemAddress[j] - '0'; // will store a int
        j++;
    }
    //here binaryMemAddress is an array of chars but not a string since it doesn't end with a null terminator
    return;
}

void extract_tag(char* tag, char binaryMemAddress[ADDRESS_LENGTH], int s, int b)
{
    int i = 0; //63 62   61 60   59 
    // extractig the rest of the 64 bit wide address
    for (i = 0; i < ADDRESS_LENGTH - b - s; i++){
        tag[i] = binaryMemAddress[i]; //will store a char!
    }
    //we wanna treat tag as a string
    tag[i] = '\0';// filling in a null terminator at the end of a string to use strcmp later!

    return;
}
 
//hexaMemAddress is a string while binaryMemAddress is just an array of char that doesn't end with a null terminator
// Precondition: binaryMemAddress: each array block init with 0 value
void convert_to_binary(char *hexaMemAddress, char binaryMemAddress[ADDRESS_LENGTH])
{
    //FIrst we need to know how many hexa digits there are in the memory Address
    int hexa_digit_count = strlen(hexaMemAddress);
    //we need to multiply by 4 for hexa digit count becuase to convert each hexa digit into binary
    //we need four digits of binary to represent each hexa digit!
    int binary_starting_index = ADDRESS_LENGTH - (4*hexa_digit_count);
    //ex: 0 1 2 3 4 5 6 7      
    int hexa_starting_index = 0;
    char hexaDIgitBinaryConverted[4];
    // the rest of the digit we can just fill in with a 0 using for loop which was already finished as before implementing the funcion
    while (binary_starting_index < ADDRESS_LENGTH){
        switch(hexaMemAddress[hexa_starting_index]){
            case '0':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case '1':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case '2':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case '3':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case '4':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case '5':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case '6':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case '7':
                hexaDIgitBinaryConverted[0] = '0';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case '8':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case '9':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case 'a':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case 'b':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '0';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case 'c':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case 'd':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '0';
                hexaDIgitBinaryConverted[3] = '1';
                break;
            case 'e':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '0';
                break;
            case 'f':
                hexaDIgitBinaryConverted[0] = '1';
                hexaDIgitBinaryConverted[1] = '1';
                hexaDIgitBinaryConverted[2] = '1';
                hexaDIgitBinaryConverted[3] = '1';
                //no need for break for 'f' since it is at the bottom. Fall -through logic
        }
        //After out of the switch statement
        //copy into the binaryMemAddress Array!
        for (int i = 0; i < 4;i++){
                                                            //binary_starting_index error!!!
            binaryMemAddress[binary_starting_index + i] = hexaDIgitBinaryConverted[i];
        }

        hexa_starting_index++; //Error: Make sure to increment hexa_starting_index as well!!
        binary_starting_index = binary_starting_index + 4;
    }
    
    //once out of the for loop, Hexadigit converted into binaryMemAddress
    return;
   
}

//to convert set_index (binary form) to decimal so that it can be directly mapped to the cache array
int convert_to_decimal(int *binary, int s)
{
    //example  00 01 10 11
    int decimal = 0;
    for (int i = 0; i < s; i++){
        decimal += binary[(s-1) - i] * (int)pow(2, i);
    }
    
    return decimal;
}

// Precondition: The input file is successfully opened
void run_cache_analysis(CacheBlock*** pCacheArray, int s, int E, int b, FILE *infile, FILE *outfile, int *hit_count, int *miss_count, int *eviction_count, Boolean verbose_mode)
{
    char line[100]; //100bytes
    char binaryMemAddress[ADDRESS_LENGTH]; //declare a char array
    for (int i = 0; i < ADDRESS_LENGTH; i++){
        binaryMemAddress[i] = '0';//init all elements with 0!
    }
    int bytes = 0;

    //char *byte_content =  (char *)malloc((b + 1) * sizeof(char));
    int *set_index = (int *)malloc(s * sizeof(int)); //we dont need to consider a null terminator since it's an int array
    if(set_index == NULL){
        printf("Malloc for int array failed! Cache Analysis not successful!\n");
        return;
    }
    char *tag = (char *)malloc((ADDRESS_LENGTH - b - s + 1) * sizeof(char)); //+1 is to include a nullterminator!
    if(tag == NULL){
        printf("Malloc for char array failed! Cache Analysis not successful!\n");
        return;
    }
    
    //initializing it!
    for (int i = 0; i < s; i++){
        set_index[i] = 0;
    }
    strcpy(tag, ""); // initializing it with an empty string possible since tag is not a null 
    // after malloc make sure to init!
    // Problem with this  you are now changing the pointer!! so allocated memory location lost@
    // byte_content = "";
    // set_index = "";
    // tag = "";

    int target_cache_row = 0;
    int target_cache_coulmn = 0;

    int perform_cache_analysis = 0;
    //Boolean is_M = FALSE;
    
    State cache_state;
    
    while (fgets(line, sizeof(line), infile) != NULL) //won't cause a seg error in this way when reaching to the end of file
    {
        perform_cache_analysis = 1;//first initially start with perform cache anaylysis one time
        // Given Input Data File, it always starts with white space
        // so checks for the second letter if it conains M or not
        // if it's M it involves both read operation and write operation
        if(line[1] == 'M'){ //if M set is_M to TRUE
            perform_cache_analysis = 2;//For M we will perform cache analysis twice
        }

        //if verbose is true it should be also written to the outputfile aswell
        if(verbose_mode == TRUE){
            //for outputfile we want to skip the whitespace at first!
            //since we don;t care about load instrcition for this assignment
            
            // hello\n\0     0 1 2 3 4 5 6 7
            line[strlen(line) - 1] = ' '; //changing from the \n to a whitespace. 
            fputs(&line[1], outfile);
        }
        
        //Make sure to reset the address!!!!!!!!!!!!!!! for each iternation!
        for (int i = 0; i < ADDRESS_LENGTH; i++){
            binaryMemAddress[i] = '0';
        }
        parse_trace_line(pCacheArray, infile, line, binaryMemAddress, &bytes);
        /*
        printf("Binary Mem: ");
        for (int i = 0; i < ADDRESS_LENGTH; i++)
        {
            printf("%c", binaryMemAddress[i]);
        }
        printf("\n");
        */
        // extract_byte(byte_content, binaryMemAddress, s, b);
        extract_setIndex(set_index, binaryMemAddress, s, b);
        extract_tag(tag, binaryMemAddress, s, b);
        //printf("Data Tag String: %s\n", tag);
        do
        {

            cache_state = is_cache_hit_miss(pCacheArray, set_index, tag, s, E, &target_cache_row, &target_cache_coulmn);
            //I don't need to call the function three times! in efficient I can just store it to an enum variable
            if (cache_state == MISS_INVALID_BIT || cache_state == MISS_TAG)
            {
                //Miss!
                printf("It's a Miss! ");
                (*miss_count)++;
                if(verbose_mode == TRUE){
                    fprintf(outfile, "miss ");
                }
                
                //After we know it's a miss we also need to know whether to perform eviction or not!
                //Warning is_cache_eviction should return enum values not Boolean values!!
                if (is_cache_eviction(pCacheArray, target_cache_row, E) == EVICTION){
                    //Eviction!
                    printf("It's an eviction! ");
                    (*eviction_count)++;
                    if(verbose_mode == TRUE){
                        fprintf(outfile, "eviction ");
                    }
                    
                    //implement eviction function!  //Error!! Argument order Be careful!!! not s b!
                    int LRU_cache_column = perform_cache_eviction(pCacheArray, E, b, target_cache_row);
                    //now performing cache replacement based on LRU replacement policy!
                    perform_cache_replacement(pCacheArray, target_cache_row, LRU_cache_column, tag, b);
                    
                }
                else{ // Eviction Not true which indicates that there is an empty cache block!
                    // implement cache write to an empty cache block! function!
                    //printf("\n");
                    //printf("Once we know it's a miss Data Tag String: %s\n", tag);
                    perform_cache_write(pCacheArray, target_cache_row, target_cache_coulmn, tag, E, b);
                }
            }
            else if(cache_state == HIT){
                //Hit!
                printf("It's a hit! ");
                perform_cache_hit(pCacheArray, target_cache_row, target_cache_coulmn, b);
                (*hit_count)++;
                if(verbose_mode == TRUE){
                    fprintf(outfile, "hit ");
                }
            }
            perform_cache_analysis--;
        } while (perform_cache_analysis > 0);
        printf("\n");
        if (verbose_mode == TRUE)
        {
            fprintf(outfile, "\n");
        }
    }
    
    //freeing the memory on the heap to prevent memory leaks!
    //free(byte_content);
    free(set_index);
    free(tag);
    
    return;
}


//Error: the return type is State that I have made! not Boolean!
State is_cache_hit_miss(CacheBlock ***pCacheArray, int *set_index, char *tag, int s, int E, int* target_cache_row, int* target_cache_column)
{
    int set_index_decimal = 0;
    set_index_decimal = convert_to_decimal(set_index, s);
    //printf("Once in the function Data Tag String: %s\n", tag);
    //going to the set row of the 2d array!
    //printf("String tag!!!:%s\n", tag);
    //printf("String Tag: %s\n", pCacheArray[1][0]->tag);
    //printf("String Tag: %s\n", pCacheArray[1][1]->tag);
    for (int i = 0; i < E; i++)
    {
        //Error Segmentation: Make sure to put [i] not [E] then you get a seg error!
        if(strcmp(pCacheArray[set_index_decimal][i]->tag, tag) == 0){
            
            if (pCacheArray[set_index_decimal][i]->valid_bit == 1){
                //printf("Found a matching tag! And it's a valid bit!\n");
                //printf("It's a hit!\n");
                *target_cache_row = set_index_decimal;
                *target_cache_column = i; //not E should be i not 1!
                return HIT;
                
                //once we found the matching tag and is a valid bit
                //it is guaranteed to be a hit!
                
            }
            else if (pCacheArray[set_index_decimal][i]->valid_bit == 0){
                //because the same tag cann't exist on the same row but can exist on differnt sets!
                //printf("Found a matching tag But valid bit is 0! It's a miss!\n");
                *target_cache_row = set_index_decimal;
                *target_cache_column = i; //not E should be i not 1
                return MISS_INVALID_BIT;
            }
        }
        //if tag doesn't match it will look for the cache block in the next column if it exists
    }
    //Error! even if it's a miss tag we should still update target  cache row at least!!!!
    *target_cache_row = set_index_decimal;
    // printf("Matching Tag with a valid not found! It's a miss\n");
    return MISS_TAG;
}

//we dont need to check the entire 2d cache array to see if its full or not
//we only need to check other columns on the same row indicated by set index! if its not direct mapped!
//Precondtion! Only invoked when miss occurs to determine if eviction should occur or not.
Boolean is_cache_full(CacheBlock ***pCacheArray, int cache_target_row, int E)
{
    //we can know if the target cache row is full by iteratively checking for it invalid exists
    for (int i = 0; i < E; i++){
        if(pCacheArray[cache_target_row][i]->valid_bit == 0){
            //printf("Cache Block with an invalid bit exists!The cache data structure is not full!\n");
            return FALSE;
        }
    }   
    //printf("Every Cache block has a valid bit! The cache is full!\n");
    return TRUE;
}

//Error: the return type is State that I have made! not Boolean!
//Precondition: Only implement this functon when Miss happens!
State is_cache_eviction(CacheBlock ***pCacheArray, int target_cache_row, int E)
{
    if(is_cache_full(pCacheArray, target_cache_row, E) == TRUE){
        return EVICTION;
    }
    // else if not cache full Eviction won't occur
    return NO_EVICTION;
}

//Precondition! Only implement this function, when it's a cache hit!
void perform_cache_hit(CacheBlock ***pCacheArray, int target_cache_row, int target_cache_column, int b)
{
    //Cache data already exists in the cache block!!
    for (int i = 0; i < (int)pow(2, b); i++){
        pCacheArray[target_cache_row][target_cache_column]->pBytesArray[i] = FILLED;
    }
    //since it's a cache hit, we dont need to modify the tag and valid bit@
    
    return;
}

// Precondtion! Only invoke this function When Miss occurs! But not eviction!
// This function won't apply to mapped -direct cache!
void perform_cache_write(CacheBlock ***pCacheArray, int target_cache_row, int target_cache_column, char *tag, int E, int b)
{
    //printf("Once we got in perform cache write func: Data Tag String: %s\n", tag);
    //First we need to find an empty cache block from the target cache row!!!
    for (int i = 0; i < E; i++){ //looping until find the empty cache block indicated by valid bit == 0
        if(pCacheArray[target_cache_row][i]->valid_bit == 0){
            //where we need to perform cache write! //Error:Not target_cache_column variable!! inseteadshould be I
            pCacheArray[target_cache_row][i]->valid_bit = 1;
            pCacheArray[target_cache_row][i]->least_recently_used_score = 1;
            //printf("0 Valid changed: %d\n", pCacheArray[target_cache_row][0]->valid_bit);
            //printf("0 Score: %d\n", pCacheArray[target_cache_row][0]->least_recently_used_score);
            //printf("1 Valid changed: %d\n", pCacheArray[target_cache_row][1]->valid_bit);
            //printf("1 Score: %d\n", pCacheArray[target_cache_row][1]->least_recently_used_score);
            //printf("Before 0 Tag copied: %s\n", pCacheArray[target_cache_row][0]->tag);
            //printf("Before 1 Tag copied: %s\n", pCacheArray[target_cache_row][1]->tag);
            strcpy(pCacheArray[target_cache_row][i]->tag, tag);
            //printf("0 Tag copied: %s\n", pCacheArray[target_cache_row][0]->tag);
            //printf("1 Tag copied: %s\n", pCacheArray[target_cache_row][1]->tag);
            // int byte_offset_index = convert_to_decimal(byte_content); I don't need to include this
            // because of cache all the byte offset will be filled with cache data. That is the beauty of cache!
            for (int  j= 0; j < (int)pow(2, b); j++){ //Error: Make sure to use j variable!!!
                pCacheArray[target_cache_row][i]->pBytesArray[j] = FILLED;
            }
            //Error! After we write the cache data to the block, we need to make sure to break out of the loop!!
            break;
        }
        //else if valid bit == 1 we are only gonna increment least_recently_used_score
        //to keep track of the cache block with LRU based on score (the higher the score, the less recently used!)
        else{
            pCacheArray[target_cache_row][i]->least_recently_used_score++;
        }
    }
        
    return;
    
    //If I defined function to have a enum Boolean data type.
    //If I don't write return TRUE it will cause a warning!
    //Warning: control reaches end of non-void function!
}


// Precondtion: Only when eviction needs to occur!! LRU function had been performed to 
//know which cache block to replace based on LRU Replacement policy
void perform_cache_replacement(CacheBlock ***pCacheArray, int target_cache_row, int LRU_cache_column, char*tag, int b)
{
    pCacheArray[target_cache_row][LRU_cache_column]->least_recently_used_score = 1; //we need to reset the score to 1
    strcpy(pCacheArray[target_cache_row][LRU_cache_column]->tag, tag);
    //printf("String Tag: %s\n", pCacheArray[target_cache_row][LRU_cache_column]->tag);
    //printf("String Tag: %s\n", pCacheArray[target_cache_row][1]->tag);
    pCacheArray[target_cache_row][LRU_cache_column]->valid_bit = 1; // change the valid from 0 to 1
    for (int i = 0; i < (int)pow(2, b); i++){
        pCacheArray[target_cache_row][LRU_cache_column]->pBytesArray[i] = FILLED;
    }

    return;
    /*
    int decimal;
    char *binary_converted = (char *)malloc(b * sizeof(char));
    if(binary_converted == NULL){
        printf("Malloc Function Failed!\n");
        return FALSE;
    }
    for (int i = 0; i < (int)pow(2, b); i++)
    {
        strcpy(pCacheArray[target_cache_row][LRU_cache_column]->pBytesArray[i], byte_content);
        decimal = convert_to_decimal(byte_content);
        decimal++;
        convert_decimal_to_binary(decimal, b, binary_converted);
        strcpy(byte_content, binary_converted);
    }
    free(binary_converted); //make sure to free the memory to prevent memory leak!
    return TRUE;
    */
}

// Precondition! Only implement this function when Eviction needs to occur when the cache data row is filled!!
//we only need to check columns! not the entire 2d array of cache data structure!
//beucase we already know the set index
void choose_LRU_cache(CacheBlock ***pCacheArray, int target_cache_row, int *LRU_cache_column, int E)
{
    //first we will increment the least_recently_used_score since we are about to evict the LRU cache block and
    //replace with a new Cache Data!!!
    for (int i = 0; i < E; i++){
        pCacheArray[target_cache_row][i]->least_recently_used_score++;
    }

    // We will first start with the assumption that min_times_used is equal to that of the first block in the cache
    int max_LRU_score = pCacheArray[target_cache_row][0]->least_recently_used_score;
    // int min_times_used = (int)pow(2, s) * E + 1;

    *LRU_cache_column = 0;
    
    for (int i = 0; i < E; i++){
        if(pCacheArray[target_cache_row][i]->least_recently_used_score > max_LRU_score){
            //update the max_LRU score!_used
            max_LRU_score = pCacheArray[target_cache_row][i]->least_recently_used_score;
            //Update the cache block row and column!
            *LRU_cache_column = i;
        }
    }

    return;
}



//Precondition! only implement this function after malloc was successfully performed to create
//memory space for the cache data structure on the heap
void deallocate_cache_structure(CacheBlock ***pCacheArray, int s, int E)
{
    for (int i = 0; i < (int)pow(2, s); i++){
        for (int j = 0; j < E; j++){
            free(pCacheArray[i][j]->pBytesArray);
        }
        free(pCacheArray[i]);
    }

    free(pCacheArray);
    printf("Freed the cache data structure successfully!\n");
    return;
}

//Precondition! Cache Miss occured! And Cache data structure is currently full!
int perform_cache_eviction(CacheBlock ***pCacheArray, int E, int b, int target_cache_row)
{
    //init a local variable to find the LRU cache column!
    int LRU_cache_column = 0;
    
    // first we need to know LRU CAche!
    choose_LRU_cache(pCacheArray, target_cache_row, &LRU_cache_column, E);
    
    //now LRU_cache_column updated!
    //now we need to perform eviction!
    pCacheArray[target_cache_row][LRU_cache_column]->least_recently_used_score = 0; //reset it to zero
    pCacheArray[target_cache_row][LRU_cache_column]->valid_bit = 0; //we will set the valid bit back to zero
    strcpy(pCacheArray[target_cache_row][LRU_cache_column]->tag, ""); //empty the tag
    for (int i = 0; i < (int)pow(2, b); i++){
        pCacheArray[target_cache_row][LRU_cache_column]->pBytesArray[i] = NOT_FILLED;
    }

    return LRU_cache_column;
}
