#include <stdio.h>
#include <stdlib.h>
#include <ConfigImpl.h>

#ifdef IMPL_REC

void torre_hanoi(int n, char or, char ds, char aux) {
   if (n > 0) {
      torre_hanoi(n-1, or, aux, ds);      
      printf("Mova de %c para %c\n", or, ds);
      torre_hanoi(n-1, aux, ds, or);            
   }  
}


void _testar() {
    torre_hanoi(10,'A','B','C');
    system("pause");
}

#endif