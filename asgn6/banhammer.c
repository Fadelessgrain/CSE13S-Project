#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// code below from Shahiti's section
#define WORD "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
// code above from shahiti's section

#define OPTIONS "h:f:m"
int main(int argc, char **argv) {
    int opt = 0;
    // standard ht and bf size
    uint32_t hash_size = 10000;
    uint32_t bloom_size = 1 << 20;
    bool mtf = false;
    // opens the files badspeak and newspeak
    FILE *badspeak = fopen("badspeak.txt", "r");
    FILE *newspeak = fopen("newspeak.txt", "r");
    // checks the command line options parsed by the user
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hash_size = atoi(optarg); break;
        case 'f': bloom_size = atoi(optarg); break;
        case 'm': mtf = true; break;
        }
    }

    // code below inspired by Shahiti's section
    // creates a BF
    BloomFilter *b = bf_create(bloom_size);
    // makes sure the BF was created
    if (!b) {
        fprintf(stderr, "Invalid Bloom Filter");
        exit(1);
    }
    // creates a HT
    HashTable *ht = ht_create(hash_size, mtf);
    // makes sure a HT was created
    if (!ht) {
        fprintf(stderr, "Invalid Hash Table");
        exit(1);
    }

    // code above from Shahiti's section
    // array that 'stores' what we read in from badspeak
    char badspeak_array[1000] = { 0 };
    // array that 'stores' words from newspeak
    char bad[1000] = { 0 };
    // array that 'stores' words from newspeak
    char good[1000] = { 0 };

    // reads from badspeak file
    while (fscanf(badspeak, "%s\n", badspeak_array) != EOF) {
        // inserts words read into the bf
        bf_insert(b, badspeak_array);
        // inserts words read to the ht
        ht_insert(ht, badspeak_array, NULL);
    }
    // creates two LL, one for badspeak words and newspeak words
    LinkedList *badwords = ll_create(mtf);
    LinkedList *goodwords = ll_create(mtf);

    // reads from newspeak file
    while (fscanf(newspeak, "%s %s\n", bad, good) != EOF) {
        // insersts both the badspeak and goodspeak to ht
        ht_insert(ht, bad, good);
        // inserts the badspeak into the bf
        bf_insert(b, bad);
    }
    // makes sure that regEX can compile
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, " Failed to compile regex.\n");
        return 1;
    }
    // array that will be used to read from stdin
    char *word = NULL;
    // keeps tract of when the user has committed a rightspeak crime
    uint32_t rightspeak = 0;
    // keeps tract of when the useer has committed a thought crime
    uint32_t thoughtcrime = 0;
    // reads from stdin
    while ((word = next_word(stdin, &re)) != NULL) {
        // sets the characters to lowercase so that regEX can read it
        for (uint32_t i = 0; i < 1; i += 1) {
            word[i] = tolower(word[i]);
        }
        // checks that the word was added to the BF
        if (bf_probe(b, word) == true) {
            // temp node that stores the node returned from ht_lookup

            Node *trans_words = ht_lookup(ht, word);
            //checks to see if the ht contains the word and if it doesn't have a new
            // speak translation
            if (ht_lookup(ht, word) != NULL && trans_words->newspeak == NULL) {
                // insert the word into the badspeak LL
                ll_insert(badwords, (trans_words)->oldspeak, NULL);
                // increment the counter that will be used to print out the correct format
                thoughtcrime += 1;
            }
            // checks to see if the ht contains the word and if it has a new speak translation
            if (ht_lookup(ht, word) != NULL && trans_words->newspeak != NULL) {
                // increment the counter that will be used to print out the correct format
                rightspeak += 1;
                // inserts the badspeak and newspeak into the goodspeak LL
                ll_insert(goodwords, (trans_words)->oldspeak, (trans_words)->newspeak);
            }
        }
    }
    // if the user commited both rightspeak and thoughtspeak crimes, they needs to go to Joycamp
    if (rightspeak > 0 && thoughtcrime > 0) {
        printf("\nDear Comrade,\n");
        printf("You have chosen to use degenerate words that may cause hurt\nfeelings or cause "
               "your comrades to think unpleasant thoughts.\nThis is doubleplus bad.To correct "
               "your wrongthink and\npreserve community consensus we will be sending you "
               "to joycamp\nadministered by Medellin's Miniluv. Beware of the hippos.\n");
        printf("\nYour errors:\n\n");
        //prints the badspeak words
        ll_print(badwords);
        printf("\nThink of these words on your vacation!\n\n");
        //prints the newspeak words
        ll_print(goodwords);

        // since the user commited thoughtcrime, they needs to go to Joycamp
    } else if (thoughtcrime > 0) {

        printf("\nDear Comrade,\n");
        printf("You have chosen to use degenerate words that may cause hurt\nfeelings or cause "
               "your comrades to think unpleasant thoughts.\nThis is doubleplus bad.To correct "
               "your wrongthink and\npreserve community consensus we will be sending you "
               "to joycamp\nadministered by Medellin's Miniluv. Beware of the hippos.\n");
        printf("\nYour errors:\n\n");
        // printds the badspeak words
        ll_print(badwords);

        // since the user only commited rightspeak crime, they should go to counseling
    } else if (rightspeak > 0) {
        // print out fromat given to us
        printf("\nDear Comrade,\n\n");
        printf("Submitting your text helps to preserve feelings and prevent\nbadthink. Some of the"
               "words that you used are not goodspeak.\nThe list shows how to turn the oldspeak "
               "words into newspeak.\n\n");
        // print out the goodspeak LL
        ll_print(goodwords);
    }
    // closes the files and deletes all the ADTS we created
    fclose(badspeak);
    fclose(newspeak);
    clear_words();
    regfree(&re);
    bf_delete(&b);
    ht_delete(&ht);
    ll_delete(&badwords);
    ll_delete(&goodwords);
    return 0;
}
