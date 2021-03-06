#include <stdio.h> //input and output for functions
#include <stdlib.h> //standard lib

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  if (c == ' ' || c =='\t'){
    return 1; //Returns true is if the char is a space
  }
  return 0; //else returns false
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c)
{
  if (c == ' ' || c == '\t' || c == '\0')
    return 0; //Returns false if the char is a space
  
  return 1; //Else returns true
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str)
{
  while(space_char(*str) == 1 && *str != '\0')
    {
      str++; //iterate through the string until the start of the word is found.
    }
  return str; //returns index
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  word = word_start(word);
  while (non_space_char(*word) == 1 && *word != '\0')
    {
      word++; //iterate through a string until the end of a word.
    }
  return word; //returns index after word ends.
}


/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  int w_counter = 1;            //tracker
  str = word_start(str);        //string is now start of word

  while(*str != '\0')           //while the index 0 in not null
    {
      if(space_char(*str) == 1) //if there a space,tab,null in word = true
	{
	  w_counter++;         //word count increment
	}
      str++;                    //next word in str
    }
  return w_counter;            //return how many words in str.
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  //new string, allocating memory(malloc) for every char in string.
  char *n_str = (char *) malloc((len + 1) * sizeof(char)); //since "char" we allocate 1 to it.
  int i;                    //int i
  for (i = 0; i< len; i++)  //iterate based on len
    {
      n_str[i] = inStr[i];  //copy letter to new string for every letter in old string
    }
  n_str[i] = '\0';          //new string[i] = space
  return n_str;             //return new string 
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str)
{
  int w_counter = count_words(str); //keep count words to tokenize
  char *word_end; //pointer to the end of the word
  char **do_token = (char**) malloc((w_counter + 1) * sizeof(char*)); //allocates memory for tokens

  //for loop to iterate through every word and in the string.
  int i;
  for(i = 0; i < w_counter; i++) 
    {
      str = word_start(str); //hold start of word.
      word_end = word_terminator(str); //holds end of the word.
      do_token[i] = copy_str(str, (word_end - str)); //stores a current copy of the word
      str = word_terminator(str); //updates string.
    }
  do_token[i] = NULL; //ends the array with null terminator
  return do_token; //returns tokens
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  int i;
  for(i = 0; tokens[i] != NULL; i++)
    {
      printf("tokens[%d] = %s\n", i, tokens[i]); //prints all tokens
    }
}
/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens)
{
  int i;
  for(i = 0; tokens[i] != NULL; i++) //iterate through tokens if not equal to null
    {
      free(tokens[i]); //deallocates memory from each tokens
    }
  free(tokens[i]); 
  free(tokens); //deallocates memory from all tokens
}
