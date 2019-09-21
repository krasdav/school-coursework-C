#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* System of redistribution of billboards along the highway.
 * initial input: length of the highway , { possible positions of billboards }
 * queries : max possible length between billboards
 * output : how many billboards can be placed
 * Example:
 Possible placements:
  1000: { 250, 500, 750 }
  Query:
  800
  Billboards: 1

  500
  Billboards: 1

  300
  Billboards: 3

  250
  Billboards: 3

  200
  N/A
 */
#define MAX_LEN 1000000

int sortThem( const void *a, const void *b);
void printArr( int cnt, int array[]);
int Na( int * array, int road, int cnt, int dist);
int remove(int array,int * cnt);

int main( void )
{

  int static array[MAX_LEN];
  int road = 0, bill = 0, dist = 0 , mozn = 0, i = 0;
  char c ;
  int ret,ret1,cnt=0;
  int b = 0;

  printf("Possible placements:\n");

  ret1 =  scanf("%d : %c", &road, &c);

  if( ret1 != 2 || c != '{' || road <= 0 || ret1 == EOF){
    printf("Invalid Input.\n");
    return 1;
   }

    while( c != '}'){
      if( scanf(" %d %c", &mozn, &c) != 2 || (c != ',' && c != '}')|| mozn < 1 || mozn > road-1 || mozn > MAX_LEN) {
        printf("Invalid Input.\n");
        return 1;
      }
    array[i++] = mozn;
    cnt++;
    }

  qsort( array, cnt, sizeof(int), sortThem);

  int j = 0;
  for ( i = 1 ; i < cnt ; i ++){
    if( array[i] != array[j]){
      j++;
      array[j] = array[i];
    }
  }
  cnt = (j+1);

  printf("Query\n");
while(!feof(stdin)){

  bill = 0;
  j = 0;

  ret = scanf("%d", &dist);

  if( ret == EOF){
    return 0;
  }
  if( ret != 1 || dist <= 0){
    printf("Invalid Input.\n");
    return 1;
  }

  for( b = 0 ; b < cnt; b++){


    if( array[b] <= dist && road - array[b] <= dist ){
      bill++;
      break;
    }


    if( j == 0 ){
      
       if(array[b] > dist ){
        bill++;
        j = array[b-1];
       
     }else if ( array[b] == dist){
         bill++;
         j = array[b];
       }

    }else if( j != 0){
       if(array[b] - j > dist){

        j = array[b-1];
        bill++;
       }
     
       if( road - array[b] <= dist && array[b]- j <= dist){
         bill++;
         break;
       }
     }
  }


  if( dist > (road - 1)) {
    bill = 0;
  }
if( Na( array, road, cnt, dist) == 1)
  printf("N/A\n");
else
  printf("Billboards: %d\n", bill);
}
  return 0;
}


int sortThem( const void *a, const void *b)
{
  int aa, bb;

  aa = *( int *)a;
  bb = *( int *)b;

  return ( aa - bb);

}
void printArr( int cnt, int array[]){

  int i;

  for( i = 0; i < cnt; i++){
    printf("%d\n", array[i]);
  }
}

int Na( int array[], int road, int cnt,int dist)
{
   int i;
   for( i = 1; i < cnt+1 ; i++ ){
    if( array[i] - array[i-1] > dist){
      return 1;
    }
   }
   if( road - array[cnt-1] > dist){
     return 1;
   }
   if( array[0] > dist){
     return 1;
   }

   return 0;

}
