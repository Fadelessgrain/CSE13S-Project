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

#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
#define OPTIONS "h:f:m"
int main(int argc, char **argv) {
    int opt = 0;
    uint32_t hash_size = 10000;
    uint32_t bloom_size = 1 << 20;
    bool mtf = false;
    FILE *badspeak = fopen("badspeak.txt", "r");
    FILE *newspeak = fopen("newspeak.txt", "r");
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': hash_size = atoi(optarg); break;
        case 'f': bloom_size = atoi(optarg); break;
        case 'm': mtf = true; break;
        }
    }
    BloomFilter *b = bf_create(bloom_size);
    if (!b) {
        fprintf(stderr, "Invalid Bloom Filter");
        exit(1);
    }
    HashTable *ht = ht_create(hash_size, mtf);
    if (!ht) {
        fprintf(stderr, "Invalid Hash Table");
        exit(1);
    }
    char badspeak_array[1000] = "";
    char bad[1000];
    char good[1000];
    while (fscanf(badspeak, "%s\n", badspeak_array) != EOF) {
        bf_insert(b, badspeak_array);
        ht_insert(ht, badspeak_array, NULL);
    }

    LinkedList *badwords = ll_create(mtf);
    LinkedList *goodwords = ll_create(mtf);

    while (fscanf(newspeak, "%s %s\n", bad, good) != EOF) {
        ht_insert(ht, bad, good);
        bf_insert(b, bad);
    }

    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, " Failed to compile regex.\n");
        return 1;
    }
    char *word = NULL;
    uint32_t rightspeak = 0;
    uint32_t thoughtcrime = 0;
    while ((word = next_word(stdin, &re)) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i += 1) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(b, word) == 1) {
            Node *trans_words = ht_lookup(ht, word);
            if (ll_lookup(badwords, trans_words->oldspeak) == NULL
                && strlen(trans_words->newspeak) == 0) {
                ll_insert(badwords, (trans_words)->oldspeak, NULL);
                thoughtcrime += 1;
            } else {
                rightspeak += 1;
                ll_insert(goodwords, (trans_words)->oldspeak, (trans_words)->newspeak);
            }
            node_delete(&trans_words);
        }
    }
    //		node_delete(&trans_words);
    if (rightspeak > 1 && thoughtcrime > 1) {
        printf("\nDear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt\nfeelings or cause "
               "your comrades to think unpleasant thoughts.\nThis is doubleplus bad.To correct "
               "your wrongthink and\npreserve community consensus we will be sending you "
               "tojoycamp\nadministered by Medellins Miniluv. Beware of the hippos.\n");
        printf("\nYour errors:\n\n");
        ll_print(badwords);
        printf("\nThink of these words on your vacation!\n\n");
        ll_print(goodwords);
    }
    if (thoughtcrime > 1) {

        printf("\nDear Comrade,\n\n");
        printf("You have chosen to use degenerate words that may cause hurt\nfeelings or cause "
               "your comrades to think unpleasant thoughts.\nThis is doubleplus bad.To correct "
               "your wrongthink and\npreserve community consensus we will be sending you "
               "tojoycamp\nadministered by Medellins Miniluv. Beware of the hippos.\n");
        printf("\nYour errors:\n\n");
        ll_print(badwords);
    }
    if (rightspeak > 1) {

        printf("\nDear Comrade,\n\n");
        printf("Submitting your text helps to preserve feelings and prevent\nbadthink. Some of the "
               "words that you used are not goodspeak.\nThe list shows how to turn the oldspeak "
               "words into newspeak.\n");
        ll_print(goodwords);
    }
	fclose(badspeak);
    fclose(newspeak);
    clear_words();
    regfree(&re);
//    fclose(badspeak);
  //  fclose(newspeak);
    bf_delete(&b);
    ht_delete(&ht);
    ll_delete(&badwords);
    ll_delete(&goodwords);
	printf("hello");
    return 0;
}
