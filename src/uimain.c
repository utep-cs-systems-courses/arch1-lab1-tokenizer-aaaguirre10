#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_STR 100

int main()
{
  //attrbutes
  char userIn[MAX_STR], word[MAX_STR];
  char *pointer, *output, **tokenizer;
  int isSpace, isNonSpace, wordCount, terminate;

  //history phrase
  List *testList = init_history();
  terminate = wordCount = 0;
  pointer = &word[0];

  //main menu
  while(terminate == 0)
    {
      printf("-------------------------------------------------------\nWelcome to TOKENIZER 1301\n");
      printf("-------------------------------------------------------\n--> Type phrase to tokenize.\n--> Type @[index ID] to view a specific existing word.\n--> Type q to quit program.\n");
      printf("-------------------------------------------------------\n");
      printf(">: ");
      fgets(word, MAX_STR, stdin);
      
      //to terminate program
      if(word[0] == 'q' || word[0] == 'Q')
	{
	  printf("--> Program terminatad. Goodbye!\n");
	  terminate = 1;
	  break;
	}
      //hisotry functionality at given index
      else if(word[0] == '@')
	{
	  int idx = word[1] - '0';
	  printf("History at [%c]: %s\n", word[1], get_history(testList, idx));
	  printf("Returning to main menu...\n");
	  printf("|\n|\nv");
	}
      else
	{
	  printf("-------------------------------------------------------");
	  printf("\n--> Given phrase: %s", word);

	  //Start of the word in given phrase
	  output = word_start(pointer);
	  printf("--> Start of word: %c\n", *output);

	  //End of the word in given phrase
	  output = word_terminator(pointer);
	  printf("--> End of word: %c\n", *output);
	  
	  //Number of words in the phrase
	  wordCount = count_words(pointer);
	  printf("--> Number of words: %d\n", wordCount);

	  //Copy word based on the length
	  output = copy_str(pointer, 5);
	  printf("--> New copied word: %s,\n", output);

	  //Tokenizes the given phrase
	  tokenizer = tokenize(pointer);

	  //Prints the phrase in tokens based on how on mnay words.
	  printf("\n<-----Printing tokens----->\n");
	  print_tokens(tokenizer);

	  //Adds the word to the history list
	  add_history(testList, word);

	  //Prints the current token history
	  printf("\n<-----Current token history----->\n");
	  print_history(testList);

	  //Removes last phrase tokens
	  free_tokens(tokenizer);

	  printf("-------------------------------------------------------\n");
	  printf("Returning to main menu...\n");
	  printf("|\n|\nv");
	  printf("\n");
	  // return 0; <-- this will only run the program once.
	}
    }
}
