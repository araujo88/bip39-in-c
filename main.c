
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rand.h>

#define WORD_COUNT 2048
#define SEQUENCE_LENGTH 12

int RAND_bytes_secure(unsigned char *buf, int num)
{
#ifdef __STDC_LIB_EXT1__
    memset_s(buf, num, 0, num);
#else
    void *volatile ptr = buf;
    memset(ptr, 0, num); // Zero out the buffer
#endif
    int final_ret = 1;
    while (num > 0)
    {
        int this_round = num > 10 ? 10 : num;
        int ret = RAND_bytes(buf, this_round);
        if (ret != 1)
        {
            final_ret = ret; // Capture the first error encountered
            break;           // Stop on error
        }
        buf += this_round;
        num -= this_round;
    }
    return final_ret;
}

// Function to generate a cryptographically secure random number
// Returns a random number in the range [0, max)
unsigned int secure_rand(unsigned int max)
{
    unsigned int rand_val;
    do
    {
        if (RAND_bytes_secure((unsigned char *)&rand_val, sizeof(rand_val)) != 1)
        {
            fprintf(stderr, "Error generating secure random number\n");
            exit(1); // In a real application, you might want to handle this more gracefully
        }
    } while (rand_val >= (UINT_MAX - (UINT_MAX % WORD_COUNT)));
    return rand_val % max;
}

int main()
{
    char *words[WORD_COUNT];
    char buffer[100]; // Assumes each word won't exceed 99 characters
    FILE *file;
    int i;

    // Open the file
    file = fopen("english.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    // Read words from file into array
    for (i = 0; i < WORD_COUNT && fgets(buffer, sizeof(buffer), file); i++)
    {
        // Allocate memory for the word, plus null terminator
        words[i] = (char *)malloc(strlen(buffer) + 1);
        // Copy the word from buffer, removing newline if present
        strcpy(words[i], buffer);
        words[i][strcspn(words[i], "\n")] = 0; // Remove newline character
    }

    fclose(file);

    for (i = 0; i < SEQUENCE_LENGTH; i++)
    {
        // Generate a cryptographically secure random index and print the word
        int index = secure_rand(WORD_COUNT);
        printf("%s\n", words[index]);
    }

    // Free the allocated memory for words, securely wiping their contents first
    for (i = 0; i < WORD_COUNT; i++)
    {
        if (words[i] != NULL)
        {
#ifdef __STDC_LIB_EXT1__
            memset_s(words[i], strlen(words[i]), 0, strlen(words[i]));
#else
            void *volatile ptr = words[i];
            memset(ptr, 0, strlen(words[i]));
#endif
            free(words[i]);
            words[i] = NULL; // Avoid dangling pointer by setting it to NULL
        }
    }

    return 0;
}
