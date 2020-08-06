#include <stdlib.h> 
#include <stdio.h> // FOR DEBUGGING PURPOSES ONLY, REMEMBER TO REMOVE 
#include <assert.h> //FOR DEBUGGING PURPOSES ONLY, REMEMBER TO REMOVE
#include "textbuffer.h"
#include <string.h>
#define TRUE 1
#define FALSE 0

struct line {
	char *value;
	struct line *next;
	struct line *prev;
};

typedef struct line *List_Node;


struct textbuffer{	
	int nitems;
	List_Node first;
	List_Node last;
	List_Node curr;
};


/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.4
 */
TB newTB (char text[]) {
   TB List_1 = malloc(sizeof(struct textbuffer));			//Allocating space for the newlist
   assert(List_1 != NULL);											//List_1 is not NULL
   List_1->nitems = 0;												//initialise the size of List_1
		
   if (strcmp(text,"") == 0) {										//If the text[] is ""
	   List_1->curr = malloc(sizeof(struct line));			//Allocating space for node curr
	   List_1->first = List_1->curr;								//node first is curr
	   List_1->last = List_1->curr;									//node last is curr
	   List_1->curr->next =  NULL;									//next is NULL
	   List_1->curr->prev = NULL;									//previous is NULL
	   List_1->curr->value = malloc(sizeof(char));			//Allocating space for the value of curr
	   strcpy(List_1->curr->value, "");
		//List_1->nitems++;
	   return List_1;
   }


   int chars = 0;														//how many chars
   int lines = 1;														//how many lines
	
   List_Node previous = NULL;

   while (text[chars] != '\0') {								//If the text is not traversed 
	   List_1->curr = malloc(sizeof(struct line));
		
	   if (lines == 1) {												//if this is the first line 
		   List_1->first = List_1->curr;
		   List_1->curr->prev = NULL;
		   previous = List_1->curr;
	   } else if (lines == 2) {									//if this is the second line
		   List_1->first->next = List_1->curr;
		   List_1->curr->prev = previous;
		   previous->next = List_1->curr;
		   previous = List_1->curr;
	   } else {															//otherwise previous is curr->prev.
		   List_1->curr->prev = previous;
		   previous->next = List_1->curr;
		   previous = List_1->curr;
	   }
      //List_1->nitems++;

	   int len_line = 0; 											//length of line
	   int i = chars;											
	   while (text[i] != '\n') {
		   len_line++;
		   i++;
	   }

	   List_1->curr->value = malloc((len_line + 3) * sizeof(char));   //Allocating space for the value of curr

	   i = 0;
	   while (i <= len_line) {										//copy text to List_1
		   List_1->curr->value[i] = text[chars];
		   i++;
		   chars++;
	   } 
       List_1->curr->value[i] = '\0';                     //Putting the '\0' character on the last line

	   if (text[chars] == '\0') {                         //if this is the last one char
	   	   List_1->last = List_1->curr;
	   } else {                                           //otherwise curr = curr->next
		   List_1->curr = List_1->curr->next;
	   }

	   lines++;
   }	

   List_1->last->next = NULL;                            //List_1->last is the last one node in the list
   return List_1;
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
//THIS IS VERY BROKEN
void releaseTB (TB tb) {
	assert(tb != NULL);
	List_Node wwr, prev; // wwr is same as curr in the list
	wwr = tb->first;
	while (wwr != NULL) {
		prev = wwr;
		wwr = wwr->next;
		free(prev->value);
		free(prev);
	}
	free(tb);
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number iff showLineNumbers == TRUE
 */
//CHECK FOR EMPTY STRING CASE
//Sometimes, the printing will glitch a bit when there are >~100 lines
char *dumpTB (TB tb, int showLineNumbers){
   assert(tb != NULL);
   int chars_num = 0;
   int i = 0;
   i = linesTB(tb);
   tb->curr = tb->first;                //curr is the first node in list
   while (i > 0) {                      //calculate how many chars in the tb
	  chars_num = chars_num + strlen(tb->curr->value);
	   tb->curr = tb->curr->next;
	   i--;
   }
   tb->curr = tb->first;                //curr is the first node in list
   char *array = calloc((chars_num + 1), sizeof(char)); //give space for array
   if(showLineNumbers != TRUE){         //if showLineNumbers != TRUE we need to copy tb to the array
	   while (tb->curr != NULL) {
	   strcat(array, tb->curr->value);
	   tb->curr = tb->curr->next;
	   }
   }else {                              //otherwise we need insert characters such as '1. ', '2. ' ......
	   tb->curr = tb->first;
	   int offset = 1;
	   array = realloc(array, (chars_num + 1 + linesTB(tb) * 3)*sizeof(char));      //give space for the number and dot and space.
	   char *character = calloc(2,sizeof(char));                                    //to hold the characters we need to insert
       character[0] = '.';
	   character[1] = ' ';
	   //if(linesTB(tb) < 10){
	   char *number = calloc(1,sizeof(char));                                       //to hold the numbers we need to insert
	       while(tb->curr != NULL && offset < 10){                                  //first ten lines
		       number[0] = '0' + offset;                                            //number will change in each line
		       strcat(array,number);                                                //copy number to the array
		       strcat(array,character);                                             //copy characters to the array
		       strcat(array, tb->curr->value);                                      //copy tb to the array
		       tb->curr = tb->curr->next;                                           //tb move forward
	           offset++;                                                            //change the number
		   }
		//}else if(linesTB(tb) < 100){
		   offset = 0;
		   if(linesTB(tb) > 10){                                                    //if there are lines more than ten
		   int carry = 0;                                                           //carry or not
		   number = realloc(number,2 * sizeof(char));                               //change the size of number for another number
		   number[0] = '1';                                                         //10+
		   while(tb->curr != NULL){                                                 //loop(up to tb is null)
		      if(carry == 1){                                                       //if carry
		        number[0] = number[0] + 1;                                          //first number plus 1
		        number[1] = '0';                                                    //second number change to 0
		        offset = 1;
		        carry = 0;
		      }else {
		      	number[1] = '0' + offset;                                           //second number change
		      }
		      	strcat(array,number);                                               //copy numbers to array
		      	strcat(array,character);                                            //copy characters to array
		      	strcat(array, tb->curr->value);                                     //copy tb to array
		      	tb->curr = tb->curr->next;                                          //tb move forward
		      	offset++;
		      	if(offset == 10){                                                   //numbers will carry
		      	    carry = 1;
		      	}
		    }
		   
		}   
    }
	return array;
}	
/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
   int nitems = 0;                  //there are nitems nodes
   List_Node curr = tb->first;      //curr is the first node
   while (curr != NULL) {           //curr move towards up to it is NULL, each times nitems = nitems + 1
	   nitems++;
	   curr = curr->next;
   }
   return nitems;
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
//NOTE: This function doesn't work when the prefix as exactly 8 characters
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
	if(pos1 < 0 || pos1 > linesTB(tb)){        //if pos1 is out of range
      abort();
   }else if(pos2 < 0 || pos2 > linesTB(tb)){  //if pos2 is out of range
      abort();
   }else if(pos1 > pos2){  //if pos1 is greater than pos2
      abort();
   }
	int length_prefix = 0;
	length_prefix = strlen(prefix);            //Find the size of the prefix

	tb->curr = tb->first;
	
	int i = 0;
	while (i < pos1) {                         //move to where we should to start to add
		tb->curr = tb->curr->next;
		i++;
	}

	while (i < pos2 + 1) {                     //add to each line up to i = pos2
	  int length_after_add = 0;
      int j = 0;
      int k = 0;
	  length_after_add = strlen(tb->curr->value) + length_prefix;
	  tb->curr->value = realloc(tb->curr->value, length_after_add * sizeof(char));  //extend more space of store what we add
      j = length_after_add;
	     while (j >= length_prefix) {
			tb->curr->value[j] = tb->curr->value[j - length_prefix];                   //just shift the tb from first to length_after_add and empty space for add.
			j--;
		}

		while (k < length_prefix) {
			tb->curr->value[k] = prefix[k];                                            //just copy prefix to the head of tb
			k++;
		}

		j = strlen(tb->curr->value);                                                  //Putting the '\0' character on the last line
		tb->curr->value[j] = '\0';
		tb->curr = tb->curr->next;                                                    //move to next node.
		i++;
	}

	return;
}

/* Merge 'tb2' into 'newTB' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'newTB'.
 * - The old line 'pos' of 'newTB' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2) {
   int i = 0;
   if(tb1 == NULL || tb2 == NULL) //if tb1 and tb2 are NULL
      return;

   if(linesTB(tb2) == 0) { //if tb2 is empty 
      free(tb2); //add it onto tb1 then free It
      return;
   }
   
   if(linesTB(tb1) == 0 || pos < 0 || pos >= linesTB(tb1)){ // if tb1 is empty or pos is invalid, the new node should be NULL
      //line_Node *position = NULL;
      if(tb1 == NULL || pos != linesTB(tb1)) {             // if pos != 0 and tb1 is not NULL
         abort();
      }
   }
   List_Node position = tb1->first;   // otherwise the new node should be the first one in tb1

   for(; i < pos; i++) {        // move position to pos in tb1
      position = position->next;
   }
   if(pos == 0) {               //if we need to put tb2 to the head of tb1
      if(position == NULL) {    //if pos = 0 and tb1 is empty, just let tb2 to be tb1
         tb1->first = tb2->first;
         tb1->last = tb2->last;
      } else {                  //if tb1 is not empty, we should to reserve tb1 after pos.
         tb1->first = tb2->first;
         position->prev = tb2->last;
         tb2->last->next = position;
      }
   } else if(pos == linesTB(tb1)) {   // if we need to put tb2 to the end of tb1
      tb1->last->next = tb2->first;
      tb2->first->prev = tb1->last;
      tb1->last = tb2->last;
   } else {                          //if pos is not 0 and not the size of tb1
      position->prev->next = tb2->first;
      tb2->first->prev = position->prev;
      tb2->last->next = position;
      position->prev = tb2->last;
   }

   tb1->nitems = tb1->nitems + tb2->nitems; //change size of tb1 to the size of tb1 plus tb2
   free(tb2);
}

/* Copy 'tb2' into 'newTB' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'newTB'.
 * - The old line 'pos' of 'newTB' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'newTB'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
   if(tb1 == NULL)                     //if tb1 and List_2 are NULL
      return;
   
   if(linesTB(tb1) == 0 || pos < 0 || pos >= linesTB(tb1)){ // if tb1 is empty or pos is invalid, the new node should be NULL
      //List_Node *position = NULL;
      if(tb1 == NULL || pos != linesTB(tb1)) {             // if pos != 0 and tb1 is not NULL
         abort();
      }
   }

   int length_tb1 = linesTB(tb1);                           //the length of tb1
   int length_tb2 = linesTB(tb2);                           //the length of tb2
   int i = 0;

   while (i < length_tb2) {                                 //Creating some new nodes for paste at the end of tb1
		tb1->last->next = malloc(sizeof(struct line));        //allocating space for new nodes in tb1
		tb1->last->next->prev = tb1->last;
		tb1->last = tb1->last->next;
		tb1->last->next = NULL;
		i++;
	}

	List_Node curr = tb1->last;
	i = 0;
	while (i < length_tb2) {
		tb1->curr = curr;
		if (i <  length_tb1 - pos) {                 //if there is a line we should copy
		   int j = 0;
		   int num = 0;
		   List_Node start_copy = tb1->curr;
		   while (j < length_tb2) {                  //move start_copy to previous
				start_copy = start_copy->prev;
				j++;
		   }
		   num = strlen(start_copy->value) + 1;      //calculate how many spaces we should creat
		   tb1->curr->value = calloc(num, sizeof(char));
		}
		curr = curr->prev;
		i++;
   }

   tb1->curr = tb1->last;                          //tb1->curr is the last node
   i = 0;
   while (i < length_tb1 - pos) {
	   int j = 0;
	   int length_copy = 0;
	   List_Node start_copy = tb1->curr;
	   while (j < length_tb2) {                     //move start_copy to where copy starts
		   start_copy = start_copy->prev;
		   j++;
	   }
	   length_copy = strlen(start_copy->value);     //calculate the length of what we need to copy
	   tb1->curr->value = realloc(tb1->curr->value, (length_copy + 1) * sizeof(char));  //extend the space of where we need to copy.
		
	   strcpy(tb1->curr->value, start_copy->value); //store original tb1
	   tb1->curr->value[strlen(tb1->curr->value)] = '\0'; //Putting the '\0' character on the last line
	   tb1->curr = tb1->curr->prev;                       //move forward
       i++;
   }	

   tb1->curr = tb1->first;                         //move tb1->curr to the first node in tb1 
   tb2->curr = tb2->first;                         //move tb2->curr to the first node in tb2
   int count = 0;
   while (count < pos) {                           //move to where we should to paste
	   tb1->curr = tb1->curr->next;
	   count++;
   }
   count = 0;
   while (count < length_tb2) {                    //just paste
	   strcpy(tb1->curr->value, tb2->curr->value);  //copy
	   tb1->curr->value[strlen(tb2->curr->value)] = '\0'; //Putting the '\0' character on the last line
	   tb1->curr = tb1->curr->next;                 //tb1 move forward
	   tb2->curr = tb2->curr->next;                 //tb2 move forward
	   count++;
	}
}

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
TB cutTB (TB tb, int from, int to){
   if(from > to) {  //If to is less than from, abort
      abort();
   }
   if(from < 0 || from >= linesTB(tb) || to < 0 || to >= linesTB(tb)){  //If from and to are out of range, abort
      abort();
   }
   if(tb == NULL || linesTB(tb) == 0){  //If tb is empty or tb is NULL, abort
      abort();
   }
	
   TB newTB = malloc(sizeof(struct textbuffer));
 
   int i = 0;
   List_Node connect = NULL;
   while (i < to - from + 1) {         //go through all we need cut
	   int move_from = 0;
	   tb->curr = tb->first;            //let tb->curr to be the first node in list
	   newTB->curr = malloc(sizeof(struct line));   //give space for all nodes
	   newTB->curr->value = calloc(strlen(tb->curr->value), sizeof(char));    //give space for all chars
		
	   while (move_from < from) {       //move to where we have to cut.
		   tb->curr = tb->curr->next;
		   move_from++;
	   }

	   strcpy(newTB->curr->value, tb->curr->value);
	   if (i == 0 || to == from) {//Putting the first node to newTB or only add one node
		   newTB->first = newTB->curr;
		   newTB->last = newTB->curr;
		   newTB->first->prev = NULL;
	       newTB->last->next = NULL;
	   } else if (i == 1) { //Putting the second node to newTB
		   newTB->first->next = newTB->curr;
	   } else if (i == to - from) { //Putting the last node to newTB
		   connect->next = newTB->curr;
		   newTB->last = newTB->curr;
		   newTB->curr->next = NULL;
	   } else {             //Putting all other nodes
		   connect->next = newTB->curr;
		   newTB->curr->prev = connect;
	   }
	   connect = newTB->curr;           //store newTB.
	   newTB->curr = newTB->curr->next; //move to next node

	   if (linesTB(tb) == 1) {               //delete the last one node
		   /*tb->first = tb->curr;
			tb->last = tb->curr;
			free(tb->curr->value);
		   free(tb->curr); */
		   tb->curr->value = realloc(tb->curr->value,sizeof(char));
		   free(tb->curr->value);
		   free(tb->curr);
	   }else if (tb->curr == tb->first) {     //delete the first node
		   tb->curr->next->prev = NULL;
		   tb->first = tb->curr->next;
		   free(tb->curr->value);
		   free(tb->curr);
	   } else if (tb->curr == tb->last) {    //delete the last node
		   tb->curr->prev->next = NULL;
		   tb->last = tb->curr->prev;
		   free(tb->curr->value);
		   free(tb->curr);   
	   } else {                             //delete node
		   tb->curr->prev->next = tb->curr->next;
		   tb->curr->next->prev = tb->curr->prev;
		   free(tb->curr->value);
		   free(tb->curr);
	   }

	   i++;
   }
   return newTB;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search){
   int search_length = 0;
   int line_N = 1;
   search_length = strlen(search);                 //search_length is the length of search.
   Match connect = NULL;									//to make sure result is always the first node in the list
   Match result = NULL;										//what we should to return.
   tb->curr = tb->first;                           //tb->curr is the first node in tb
   while (tb->curr != NULL ) {							//go through the all tb
	   int same_letter = -1;
	   int i = 0;
	   while (i < strlen(tb->curr->value)) {			//go through all nodes and to find same first letter.
	   	  if (tb->curr->value[i] == search[0]) {		//if find the same first letter
			   same_letter = i;								//change the value of same_letter to the position
			   char all_same = 'Y';
			   int j = 0;
			   while (j < search_length) {				//compare all chars in tb->curr and search.
			   	  if (tb->curr->value[j + i] != search[j]) {	//if there are difference between tb_curr and search
					   all_same = 'N';
					   break;
				   }
				   j++;
			   }
			   if (all_same == 'Y') {							//if tb->curr is same as search.
				   Match newNode = malloc(sizeof(Match));		//allocating space for newpoint.

				   if (result == NULL) {						//if this node is the first node to put in.
					   result = newNode;							//let result be the first node
					   connect = newNode;
					   newNode->next = NULL;
			       } else {
					   connect->next = newNode;			//connect->newNode  =>  newNode become new connect.
					   connect = newNode;
					   newNode->next = NULL;				//put new node to follow the last one.
				   }
				   newNode->lineNumber = line_N;				//lineNumber
				   newNode->charIndex = same_letter;		//charIndex						
												
			   }
		   }
		   i++;
	   }

	   tb->curr = tb->curr->next;							//tb->curr move forward.
	   line_N++;
   }
   return result;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
   int i = 0;
   if(from > to) {  //If to is less than from, abort
      abort();
   }
   if(from < 0 || from >= linesTB(tb) || to < 0 || to >= linesTB(tb)){  //If from and to are out of range, abort
      abort();
   }
   if(tb == NULL || linesTB(tb) == 0){  //If tb is empty or tb is NULL, abort
      abort();
   }
     
   List_Node delete_B = tb->first;  //delete_B(begin) is the first node in tb
   List_Node delete_E = tb->first;  //delete_E(end) is the first node in tb
   
   for(; i < from; i++) {            //move delete_B to position "from"
      delete_B = delete_B->next;
   }
   for(i = 0; i < to; i++) {         //move delete_E to position "to"
      delete_E = delete_E->next;
   }
   
   if(from == 0){              //if we need to delete from the head of tb
      tb->first = delete_E->next;
   }
   if(to == tb->nitems - 1){   //if we need to delete to the end of tb
      tb->last = delete_B->prev;
   }
   
   if(delete_B->prev != NULL){   //if we need to delete not from the head
      delete_B->prev->next = delete_E->next;
   }
   if(delete_E->next != NULL){       //if we need to delete not to the end
      delete_E->next->prev = delete_B->prev;
   }

   assert(tb != NULL);
	List_Node curr, prev;
	curr = delete_B;
	while (curr != delete_E) {   //while delete_B != delete_E we should to free the value and the node.
		prev = curr;
		curr = curr->next;
		free(prev->value);
		free(prev);
	}

   tb->nitems = tb->nitems - to + from -1;   //change the size of tb to it is after delete

}


/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
void formRichText (TB tb){
	
}

/* Your whitebox tests
 */
void whiteBoxTests() {
//give some inputs
    char twoLines[] = "first line\nsecond line\n";

    char fourLines[] = "line 1\nline 2\nline 3\nline 4\n";
 
    char emptyspace[] = "";


//make new list
    TB tb1;
    TB tb2;
    
//Testing newTB(normal)
    tb1 = newTB(twoLines);
    assert(tb1 != NULL);
    assert(tb1->first != NULL);
    assert(tb1->first->next != NULL);
    assert(tb1->first->next->next == NULL);
    
//Testing releaseTB
    releaseTB(tb1);
    assert(tb1 == NULL);
    
//Testing newTB an empty line
    tb1 = newTB(emptyspace);
    assert(tb1 != NULL);
    assert(tb1->first == NULL);
    assert(tb1->last == NULL);
    releaseTB(tb1);

//Testing dumpTB
	 tb1 = newTB(fourLines);
	 releaseTB(tb1);
//Testing linesTB
	 tb1 = newTB(fourLines);
	 assert(linesTB(tb1) == 4);
	 releaseTB(tb1);
//Testing addPrefixTB
    tb1 = newTB(fourLines);
    addPrefixTB(tb1, 0, 2, "a ");
	assert(tb1->first->value[0] == 'a');
	assert(tb1->first->value[1] == ' ');
	assert(tb1->first->next->value[0] == 'a');
    releaseTB(tb1);

//Testing mergeTB
    tb1 = newTB(fourLines);
    tb2 = newTB(twoLines);
    mergeTB(tb1, 2, tb2);
    assert(tb1 != NULL);
    releaseTB(tb1);


//Testing pasteTB
    tb1 = newTB(fourLines);
    tb2 = newTB(twoLines);
    pasteTB(tb1, 2, tb2);
    assert(tb2 != NULL);
    releaseTB(tb1);
    releaseTB(tb2);


//Testing cutTB(normal)
    tb1 = newTB(fourLines);
    tb2 = cutTB(tb1, 1, 1);
    assert(tb1 != NULL);
    assert(linesTB(tb2) == 1);
    releaseTB(tb1);
    releaseTB(tb2);
//Testing cutTB(cut all)
    tb1 = newTB(twoLines);
    tb2 = cutTB(tb1, 0, 1);
    assert(tb1 == NULL);
    releaseTB(tb1);
    releaseTB(tb2);

//Testing deleteTB(normal)
    tb1 = newTB(fourLines);
    deleteTB(tb1, 1, 1);
    assert(linesTB(tb1) == 3);
    releaseTB(tb1);
//Testing deleteTB(delete all)
    tb1 = newTB(twoLines);
    deleteTB(tb1, 0, 1);
    assert(tb1 == NULL);
    releaseTB(tb1);
}


