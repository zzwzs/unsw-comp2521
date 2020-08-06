#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;

    // Cut first 3 lines of tb1
    tb2 = cutTB(tb1, 0, 2);
    s = dumpTB(tb1,FALSE);
    printf ("tb2 = cutTB(tb1, 0, 2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,FALSE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);


    return EXIT_SUCCESS;
}
