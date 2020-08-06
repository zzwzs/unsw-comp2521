#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "textbuffer.h"

#define TRUE 1
#define FALSE 0 

struct textbuffer{
   struct line_Node* first;
   struct line_Node* last;
   struct line_Node* curr;
   int nitems;
};

typedef struct line_Node {
      char *value;
      //int ;
      struct line_Node* next;
      struct line_Node* previous;
} line_Node;
/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.
 */
TB newTB (char text[]) {
   //initialise a new textbuffer
   TB List_1;

	List_1 = malloc(sizeof (struct textbuffer));
	assert (List_1 != NULL);
	
	if(strlen(text) == 0){
	   List_1->curr = malloc(sizeof(struct line_Node));
	   List_1->first = List_1->curr;
	   List_1->first = List_1->curr;
	   List_1->curr->next =  NULL;
		List_1->curr->previous = NULL;
		List_1->curr->value = malloc(1 * sizeof(char));
		strcpy(List_1->curr->value, "");
	   return List_1;
	}
	
	int i = 0;
	int totalLineCount = 1;
	LP oldCurr = NULL;

	while (text[i] != '\0') {
		newTB->curr = malloc(sizeof(struct line_Node));
		assert(newTB->curr != NULL);
		if (totalLineCount == 1) {
			newTB->first = newTB->curr;
			newTB->curr->prev = NULL;
		} else if (totalLineCount == 2) {
			newTB->first->next = newTB->curr;
			newTB->curr->prev = oldCurr;
			oldCurr->next = newTB->curr;
		} else {
			newTB->curr->prev = oldCurr;
			oldCurr->next = newTB->curr;
		}

		//ASSIGNING THE TEXT VALUE
		int lineSize = 0; 
		for (int i = i; text[i] != '\n'; i++) {
			lineSize++;
		}

		newTB->curr->text = malloc((lineSize + 2) * sizeof(char));

		int textCharCount = 0;
		while (textCharCount <= lineSize) {
			newTB->curr->text[textCharCount] = text[i];
			textCharCount++;
			i++;
		}
		//ENDASSIGN
		oldCurr = newTB->curr;
		if (text[i] == '\0') {
			newTB->last = newTB->curr;
		} else {
			newTB->curr = newTB->curr->next;
		}

		totalLineCount++;
	}	
	//Putting the '\0' character on the last line
	// newTB->last->text = realloc(newTB->last->text, sizeof(newTB->last->text) + (1*sizeof(char)));
	// int final = strlen(newTB->last->text);
	// newTB->last->text[final] = '\0';

	newTB->last->next = NULL;
	newTB->curr = newTB->first;
 	// printTB(newTB);

	return newTB;
   //give text
   int i = 0;
   int j = 0;
   //int one_node = 1;
   while(text[i] != '\0'){
      line_Node *spz = malloc(sizeof(struct line_Node));
      while(text[i] != '\n' && text[i] != '\0'){
         spz->value[j] = text[i];
         if(List_1->nitems == 0){    //if spz is the first node
            List_1->first = spz;
	         List_1->last = spz;
	         List_1->curr = spz;
	         List_1->nitems++;
         }else {                     //if spz is not the first node
            List_1->curr->next = spz;
            spz->previous = List_1->curr;
            List_1->last = spz;
            List_1->curr = List_1->curr->next;
            List_1->nitems++;
         }
         j++;
         i++;
      }
      j = 0;
   }
	
	return List_1;
	//return NULL;
   
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
   assert(tb != NULL);
	line_Node *wwr, *prev; // wwr is same as curr in the list
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
char *dumpTB (TB tb, int showLineNumbers){
	assert(tb != NULL);
	
	int i = 0;
	int j = 0;
	int chars_num = 0;
	int k = 0;
	
	k = tb->nitems;        // k is how many items in the list
	tb->curr = tb->first;  //current is the first one
	
	if(tb->nitems == 0){    // if the list is empty
	   return "";
	}else {
	   while(k > 0){
	      while(tb->curr->value[i] != '\0'){
	         i++;
	      }
	      chars_num = chars_num + i;   //calculate how many chars in the list
	      i = 0;
	      k--;
	      tb->curr = tb->curr->next;   //current was moved to next one
	   }
	}
	
	char *array = calloc(1,sizeof(char)*chars_num);
	//k = tb->nitems;
	tb->curr = tb->first;   //current is the first node
	while(k < tb->nitems){
	   array[i] = k + 1;    //add a prefix corresponding to line number
	   i++;
	   while(tb->curr->value[j] != '\0'){
	      array[i] = tb->curr->value[j];  //copy tb->curr->value to array
	      j++;
	      i++;
	   }
	   k++;
	   j = 0;
	}
	return array;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
   if(tb == NULL){  //if tb is NULL
      return 0;
   }
	return tb->nitems; //return how many lines
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
   if(pos1 < 0 || pos1 > tb->nitems){        //if pos1 is out of range
      abort();
   }else if(pos2 < 0 || pos2 > tb->nitems){  //if pos2 is out of range
      abort();
   }else if(pos1 > pos2){  //if pos1 is greater than pos2
      abort();
   }else{
      int i = 0;
      tb->curr = tb->first; //current is the first node
      while(i < pos1){
         tb->curr = tb->curr->next; //let the current move to pos1
         i++;
      }
      while(i < pos2){      //Add a given prefix to all lines between pos1 and pos2
         strcat(tb->curr->value,prefix);
         tb->curr = tb->curr->next;
         i++;
      }
   }
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
   int i = 0;
   if(tb1 == NULL || tb2 == NULL) //if tb1 and tb2 are NULL
      return;

   if(tb2->nitems == 0) { //if tb2 is empty 
      free(tb2); //add it onto tb1 then free It
      return;
   }
   
   if(tb1->nitems == 0 || pos < 0 || pos >= tb1->nitems){ // if tb1 is empty or pos is invalid, the new node should be NULL
      //line_Node *position = NULL;
      if(tb1 == NULL || pos != tb1->nitems) {             // if pos != 0 and tb1 is not NULL
         abort();
      }
   }
   line_Node *position = tb1->first;   // otherwise the new node should be the first one in tb1

   for(; i < pos; i++) {        // move position to pos in tb1
      position = position->next;
   }
   if(pos == 0) {               //if we need to put tb2 to the head of tb1
      if(position == NULL) {    //if pos = 0 and tb1 is empty, just let tb2 to be tb1
         tb1->first = tb2->first;
         tb1->last = tb2->last;
      } else {                  //if tb1 is not empty, we should to reserve tb1 after pos.
         tb1->first = tb2->first;
         position->previous = tb2->last;
         tb2->last->next = position;
      }
   } else if(pos == tb1->nitems) {   // if we need to put tb2 to the end of tb1
      tb1->last->next = tb2->first;
      tb2->first->previous = tb1->last;
      tb1->last = tb2->last;
   } else {                          //if pos is not 0 and not the size of tb1
      position->previous->next = tb2->first;
      tb2->first->previous = position->previous;
      tb2->last->next = position;
      position->previous = tb2->last;
   }

   tb1->nitems = tb1->nitems + tb2->nitems; //change size of tb1 to the size of tb1 plus tb2
   free(tb2);
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
   TB List_2;
   
   List_2 = malloc(sizeof (struct textbuffer));
	assert (List_2 != NULL);
	List_2->nitems = 0;
	List_2->first = NULL;
	List_2->last = NULL;
	List_2->curr = NULL;
	
	tb2->curr = tb2->first;
	List_2->curr = List_2->first;
	if(tb2 != NULL){
	   while(tb2->curr != NULL){
	      List_2->curr->value = tb2->curr->value;
	      tb2->curr = tb2->curr->next;
	      List_2->curr = List_2->curr->next;
	   }
	   List_2->last = List_2->curr;
	   tb2->curr = tb2->first;
	}
	
   int i = 0;
   if(tb1 == NULL || List_2 == NULL) //if tb1 and List_2 are NULL
      return;

   if(List_2->nitems == 0) { //if List_2 is empty 
      free(List_2); //add it onto tb1 then free It
      return;
   }
   
   if(tb1->nitems == 0 || pos < 0 || pos >= tb1->nitems){ // if tb1 is empty or pos is invalid, the new node should be NULL
      //line_Node *position = NULL;
      if(tb1 == NULL || pos != tb1->nitems) {             // if pos != 0 and tb1 is not NULL
         abort();
      }
   }
   line_Node *position = tb1->first;   // otherwise the new node should be the first one in tb1

   for(; i < pos; i++) {        // move position to pos in tb1
      position = position->next;
   }
   if(pos == 0) {               //if we need to put List_2 to the head of tb1
      if(position == NULL) {    //if pos = 0 and tb1 is empty, just let List_2 to be tb1
         tb1->first = List_2->first;
         tb1->last = List_2->last;
      } else {                  //if tb1 is not empty, we should to reserve tb1 after pos.
         tb1->first = List_2->first;
         position->previous = List_2->last;
         List_2->last->next = position;
      }
   } else if(pos == tb1->nitems) {   // if we need to put List_2 to the end of tb1
      tb1->last->next = List_2->first;
      List_2->first->previous = tb1->last;
      tb1->last = List_2->last;
   } else {                          //if pos is not 0 and not the size of tb1
      position->previous->next = List_2->first;
      List_2->first->previous = position->previous;
      List_2->last->next = position;
      position->previous = List_2->last;
   }

   tb1->nitems = tb1->nitems + List_2->nitems; //change size of tb1 to the size of tb1 plus List_2
   free(List_2);
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
	int i = 0;
   if(from > to) {  //If to is less than from, abort
      abort();
   }
   if(from < 0 || from >= tb->nitems || to < 0 || to >= tb->nitems){  //If from and to are out of range, abort
      abort();
   }
   if(tb == NULL || tb->nitems == 0){  //If tb is empty or tb is NULL, abort
      abort();
   }
     
   line_Node *cut_B = tb->first;  //cut_B(begin) is the first node in tb
   line_Node *cut_E = tb->first;  //cut_E(end) is the first node in tb
   
   for(; i < from; i++) {            //move cut_B to position "from"
      cut_B = cut_B->next;
   }
   for(i = 0; i < to; i++) {         //move cut_E to position "to"
      cut_E = cut_E->next;
   }
   
   if(cut_B == NULL || cut_E == NULL) {
      abort();
   }
   
   if(from == 0){              //if we need to cut from the head of tb
      tb->first = cut_E->next;
   }
   if(to == tb->nitems){   //if we need to cut to the end of tb
      tb->last = cut_B->previous;
   }
   
   if(cut_B->previous != NULL){   //if we need to cut not from the head
      cut_B->previous->next = cut_E->next;
   }
   if(cut_E->next != NULL){       //if we need to cut not to the end
      cut_E->next->previous = cut_B->previous;
   }
   
   TB cut_Node = newTB("");       //make a new list to get what we cut

   cut_Node->first = cut_B;       //copy
   cut_Node->last = cut_E;
   cut_Node->curr = cut_Node->first;
   cut_B->previous = NULL;            //Cut_B->prev is the first node in cut_Node
   cut_E->next = NULL;                //Cut_E->prev is the last node in cut_Node

   cut_Node->nitems = to - from + 1;   //the size of what we cut
   tb->nitems = tb->nitems - to + from - 1; //the size of tb after cut

   return cut_Node;
	//return NULL;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search){
   /*Match result;
   
   result = malloc(sizeof (struct _matchNode));
   assert (result != NULL);
   
   result->lineNumber = 0;
   result->charIndex = 0;
   result->next = NULL;
   int is_first = 0;
    //int count = 0; // count for number of matched nodes
    //L list = emptyList(); // create a new match list
    for (line_Node curr = tb->first; curr != NULL; curr = curr->next){
        if (strstr(curr->value, search) != NULL){ // if it is inside
                //Match new = malloc (sizeof(matchNode));
            if (is_first == 0){
                result->lineNumber = curr->nitems;
                result->charIndex = findCharIndex (curr->message, search[0]);
                result = result->next;
                count++;
            } else if (count >= 1){
                result->lineNumber = curr->nitems;
                result->charIndex = findCharIndex (curr->message, search[0]);
                list->last->next = new;
                list->last = new;
                new->next = NULL;
                count++;
            }
        }
    }*/
    //Special cases
	if (search == NULL) {                  //if search is NULL
		fprintf(stderr, "Error, search term cannot be null\n");
		abort();
	} else if (strcmp(search, "") == 0) {  //if search has nothing
		return NULL;
	}
	int search_size = 0;
	search_size = strlen(search);          //search_size is the length of search

	int lineNum = 1;
	Match oldMatch = NULL;
	Match firstMatch = NULL;
	for (tb->curr = tb->first; tb->curr != NULL; tb->curr = tb->curr->next) {
		//Finding if the first letter of "search" appears in the line
		int firstLetterIndex = -1;
		for (int i = 0; tb->curr->value[i] != '\0'; i++) {
			if (tb->curr->value[i] == search[0]) {
				firstLetterIndex = i;
				//Checking if the rest of the word lines up
				int found = TRUE;
				for (int i = 0; i < search_size; i++) {
					if (tb->curr->value[i + firstLetterIndex] != search[i]) {
						found = FALSE;
						break;
					}
				}

				if (found == TRUE) {
					Match newMatch = malloc(sizeof(Match));		

					if (firstMatch == NULL) {
						firstMatch = newMatch;
						oldMatch = firstMatch;
					} else {
						oldMatch->next = newMatch;
					}
					newMatch->lineNumber = lineNum;
					newMatch->charIndex = firstLetterIndex;
					newMatch->next = NULL;
					oldMatch = newMatch;
				}
			}
		}


		lineNum++;
	}
	return firstMatch;
	//return result;
	//return NULL;
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
   if(from < 0 || from >= tb->nitems || to < 0 || to >= tb->nitems){  //If from and to are out of range, abort
      abort();
   }
   if(tb == NULL || tb->nitems == 0){  //If tb is empty or tb is NULL, abort
      abort();
   }
     
   line_Node *delete_B = tb->first;  //delete_B(begin) is the first node in tb
   line_Node *delete_E = tb->first;  //delete_E(end) is the first node in tb
   
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
      tb->last = delete_B->previous;
   }
   
   if(delete_B->previous != NULL){   //if we need to delete not from the head
      delete_B->previous->next = delete_E->next;
   }
   if(delete_E->next != NULL){       //if we need to delete not to the end
      delete_E->next->previous = delete_B->previous;
   }

   assert(tb != NULL);
	line_Node *curr, *prev;
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

}
TB newTB = malloc(sizeof(struct textbuffer));
	int i = 0;
	List_Node connect = NULL;
	while(i < to - from + 1){
		tb->curr = tb->first;
		newTB->curr = malloc(sizeof(struct line));            //give space for every nodes in list.
		assert(newTB->curr != NULL);
		newTB->curr->value = calloc(strlen(tb->curr->value) + 1, sizeof(char)); //give space for every chars in node.
		assert(newTB->curr->value != NULL);
		
		int move_from = 0;
		int length_curr = 0;
		while(move_from < from){
		   tb->curr = tb->curr->next;
		   move_from++;
		}
		strcpy(newTB->curr->value, tb->curr->value);
		length_curr = strlen(tb->curr->value);
		newTB->curr->value[length_curr] = '\0';
		if(to == from){
		   newTB->first = newTB->curr;
			newTB->last = newTB->curr;
			newTB->first->prev = NULL;
			newTB->last->next = NULL;
	   }else if(i == 0){          //Adding the first node to newTB
		   newTB->first = newTB->curr;
		   newTB->last = newTB->curr;
		   newTB->curr->next = NULL;
		   newTB->curr->prev = NULL;
		}else if(i == 1){    //Adding the first node to newTB
		   newTB->first->next = newTB->curr;
		   //newTB->last->prev = newTB->curr;
		}else if (i == to - from - 1){   //Adding the last node to newTB
		   connect->next = newTB->curr;
			newTB->last = newTB->curr;
			newTB->curr->next = NULL;
		}else {
		   connect->next = newTB->curr;
		   //newTB->curr->prev = connect;
		}
		newTB->curr->prev = connect;
		connect = newTB->curr;
		newTB->curr = newTB->curr->next;
		
		if(linesTB(tb) == 1){               //delete the last one node
		   tb->curr->value = realloc(tb->curr->value, 1 * sizeof(char));
			tb->curr->value[0] = '\0';
			tb->first = tb->curr;
			tb->last = tb->curr;
			return newTB;
		}else if(tb->curr == tb->first){     //delete the first node
		   tb->curr->next->prev = NULL;
			tb->first = tb->curr->next;
			free(tb->curr->value);
			free(tb->curr);
		}else if (tb->curr == tb->last){    //delete the last node
		   tb->curr->prev->next = NULL;
			tb->last = tb->curr->prev;
			free(tb->curr->value);
			free(tb->curr);
		}else {                             //delete node
		   tb->curr->prev->next = tb->curr->next;
			tb->curr->next->prev = tb->curr->prev;
			free(tb->curr->value);
			free(tb->curr);
	   }
	   //tb->curr = tb->first;
		i++;
	}
	// Creating the new textbuffer
	TB newTB = malloc(sizeof(struct textbuffer));

	int numLinesToDelete = to - from + 1; // +2 accounts for inclusive deleting
	int numLinesDeleted = 0;
	List_Node oldCurr = NULL;
	while (numLinesDeleted < numLinesToDelete) {
		//Advancing to the item to be deleted
		tb->curr = tb->first;
		for (int i = 0; i < from; i++) {
			tb->curr = tb->curr->next;
		}

		//Creating the new node in newTB
		newTB->curr = malloc(sizeof(struct line));
		assert(newTB->curr != NULL);
		newTB->curr->value = calloc(strlen(tb->curr->value) + 1, sizeof(char));
		assert(newTB->curr->value != NULL);
		strcpy(newTB->curr->value, tb->curr->value);
		newTB->curr->value[strlen(newTB->curr->value)] = '\0';


		if (numLinesToDelete == 1) { //Handling the special case where only one line is getting deleted
			newTB->first = newTB->curr;
			newTB->last = newTB->curr;
			newTB->first->prev = NULL;
			newTB->last->next = NULL;
		} else if (numLinesDeleted == 0) { //Adding the first item to newTB
			newTB->first = newTB->curr;
		} else if (numLinesDeleted == 1) { //Adding the second item to newTB
			newTB->first->next = newTB->curr;
		} else if (numLinesDeleted == numLinesToDelete - 1) { //Adding the last item to newTB
			oldCurr->next = newTB->curr;
			newTB->last = newTB->curr;
			newTB->curr->next = NULL;
		} else { //Adding every other item
			oldCurr->next = newTB->curr;
		}
		newTB->curr->prev = oldCurr;
		oldCurr = newTB->curr;
		newTB->curr = newTB->curr->next;

		//If we're deleting the last item in the list
		if (linesTB(tb) == 1) {
			tb->curr->value = realloc(tb->curr->value, 1 * sizeof(char));
			tb->curr->value[0] = '\0';
			tb->first = tb->curr;
			tb->last = tb->curr;
			return newTB;
		}
		//Delete node from tb
		if (tb->curr == tb->first) {
			tb->curr->next->prev = NULL;
			tb->first = tb->curr->next;
		} else if (tb->curr == tb->last) {
			tb->curr->prev->next = NULL;
			tb->last = tb->curr->prev;
		} else {
			tb->curr->prev->next = tb->curr->next;
			tb->curr->next->prev = tb->curr->prev;
		}

		numLinesDeleted++;
		free(tb->curr->value);
		free(tb->curr);
		tb->curr = tb->first;
	}
	
	
	
	//Find how many characters are in the entire text
	int totalLength = 0;
	tb->curr = tb->first;
	while (tb->curr != NULL) {
		totalLength += strlen(tb->curr->value);
		tb->curr = tb->curr->next;
	}
	char *newChar = calloc((totalLength + 1), sizeof(char));
	int lineNum = 1;
	tb->curr = tb->first;
	int newCharSize = 0;
	while (tb->curr != NULL) {
		if (showLineNumbers == TRUE) {
			//Finding how many digits the number has
			int digCount = numOfDigits(lineNum);
			totalLength = totalLength + (digCount + 2); //Resizing the totalLength to hold the number and ". "
			int staticDigCount = digCount;
			char *lineChar = calloc(digCount + 3,  sizeof(char)); //String to hold the line number
			//Resizing the newChar to hold the line number. +1 is for the "\0 "
			newChar = realloc(newChar, (totalLength + 1) * sizeof(char));

			//Writing each digit as a string to lineChar
			int lineCharLength = 0;
			while (digCount > 0) {
				// printf("digCount is %d\n", digCount);
				int offset = 0;
				int div = 1;
				int mod = 1;

				//Getting the necessary power of 10
				for (int i = 1; i <= digCount; i++) {
					mod *= 10;
				}
				offset = lineNum / mod;
				// if (lineNum == 10) {printf("offset after mod is %d\n", offset);}

				//Getting the necessary modulo
				for (int i = 1; i <= digCount + 1; i++) {
					div *= 10;
				}
				offset = lineNum % mod;

				//Final division
				div = 1;
				for (int i = 1; i < digCount; i++) {
					div *= 10;
				}
				offset = offset / div;
				// if (lineNum == 10) {printf("offset after div is %d\n", offset);}
				
				char digit = '0' + offset;

				if (lineCharLength == 0) {
				   lineChar[0] = digit;
				} else {
				   lineChar[lineCharLength] = digit;
				}
				digCount--;
				lineCharLength++;

			}
			lineChar[staticDigCount + 0] = '.';
			lineChar[staticDigCount + 1] = ' ';
			lineChar[staticDigCount + 2] = '\0';

			if (newCharSize == 0) {
			   strcpy(newChar, lineChar);
			} else {
			   strcat(newChar, lineChar);
			}
			free(lineChar);
		} 

	   strcat(newChar, tb->curr->value);
		tb->curr = tb->curr->next;
		lineNum++;
		newCharSize++;
	}
	return newChar;
	
	
	
int numOfDigits(int num) {
	int numOfDigits = 1;
	int check = 10;
	while (num >= check) {
		numOfDigits++;
		check *= 10;
	}
	return numOfDigits;
}

