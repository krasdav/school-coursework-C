#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Program for calculating highway fees. Different sections of highway have different rates.
 * input: List of highway fees depending on the section, length of the highway , list of querries
 * output: list of fees to be paid
 Example:
 Toll:
 { [ 50: A=10.5, E=80 ], [ 30: Z=20, A=7.5, X=130 ], [ 200: A=0, E=300 ] }
 Search:
 10 70
 10 - 70: A=570.000000, E=4800.000000, X=2600.000000, Z=400.000000

 100 200
 100 - 200: E=30000.000000, X=13000.000000, Z=2000.000000

 55 166
 55 - 166: A=187.500000, E=27800.000000, X=14430.000000, Z=2220.000000
 */

int getIndex( char letter);
int checkRangeAZ( char letter);
void calculateFees( int start, int end, struct SECTION *section, int i);
void printFees( int start, int end,double sums[]);

struct SECTION
{
  long long int dist_tot;
  long long int distance ;
  double fee[26];
};

int main ( void )
{
  char letter,sign;
  int i = 0;
  int size = 10;
  int start,end;

  struct SECTION * sec = (SECTION * ) malloc( size * sizeof( SECTION ));


  printf("Toll:\n");
  if( scanf( " %c", &sign) != 1 || sign != '{')
  {
    printf("Invalid Input.\n");
    free(sec);
    return 0;
  }
  for( int r = 0; r < 26; r++){
    sec[0].fee[r] = 0;
  }
  sec[0].dist_tot = 0;
  while(sign != '}')
  {
    if( scanf(" [ %lld %c", &sec[i].distance, &sign) != 2 || sign != ':' || sec[i].distance <= 0)
    {
      printf("Invalid Input.\n");
      free(sec);
      return 0;
    }
    while( sign != ']')
    {
      if( scanf(" %c", &letter) != 1 || checkRangeAZ(letter) == 0) 
      {
        printf("Invalid Input.\n");
        free(sec);
        return 0;
      }
      if( scanf(" = %lf %c", &sec[i].fee[getIndex(letter)], &sign) != 2 || (sign != ',' && sign != ']') || sec[i].fee[getIndex(letter)] < 0 ) 
      {
        printf("Invalid Input.\n");
        free(sec);
        return 0;
      }
    }
    if( scanf(" %c", &sign) != 1 || (sign != ',' && sign != '}'))
    {
      printf("Invalid Input.\n");
      free(sec);
      return 0;
    }
    sec[i].dist_tot += sec[i].distance;
    i++;
    if( i >= size )
    {
      struct SECTION * new_sec = ( SECTION *) realloc( sec , size * 2 * sizeof( SECTION ));
      if( !new_sec )
      {
        free(sec);
        size = i = 0;
        break;
      }
      size = size * 2;
      sec = new_sec;
    }

    sec[i] = sec[i-1];
  }

  printf("Search:\n");
  while(!feof(stdin))
  {
    int ret1 = scanf(" %d %d", &start,&end);

    if( ret1 == EOF){
      free(sec);
      return 0;
    }

    if( ret1 != 2 || start == end || end > sec[i].dist_tot || start < 0 || end < 0)
    {
      printf("Invalid Input.\n");
      free(sec);
      return 0;
    }

    calculateFees( start,end,sec,i);

  }
  free(sec);
  return 0;
}

int checkRangeAZ( char letter){
  if( letter < 65 || letter > 90)
    return 0;

  return 1;
}

int getIndex( char letter)
{
  return letter-65;
}

void calculateFees( int start, int end, struct SECTION * section, int i){

 struct fees{
    long long int dist_tot;
    long long int dist;
    double fees[26];
  };

  struct fees * secin = (fees *) malloc(i * sizeof(fees));
  memcpy(secin,section, i * sizeof(* section));

  double actuals[26];
  double sums[26];
  int z = 0,t = 0;
  for ( t = 0; t < 26; t++) {
    actuals[t] = 0;
    sums[t] = 0;
  }

  int current_sec = 0;
  int remaining = 0;
  int str = start;
  int ed = end;


    while (end != 0){
      int tmp = 0;
      if(start > end ){
        tmp = start;
        start = end;
        end = tmp;
      }

      if( secin[current_sec].dist < start ){
        secin[current_sec+1].dist = secin[current_sec].dist + secin[current_sec+1].dist;
      }else if(secin[current_sec].dist >= start){
        remaining = secin[current_sec].dist - start;
        end -= start;
        start = 0;
        if (remaining > end) {
          remaining = end;
        }
        end -= remaining;
      for( z = 0; z < 26; ++z){
        if( secin[current_sec].fees[z] > 0.0){
          }
          actuals[z] = secin[current_sec].fees[z];
          sums[z] += actuals[z] * remaining;
        }
      }
      ++current_sec;
    }
  printFees(str,ed,sums);
  free(secin);
}

void printFees( int str, int ed, double sums[]){
  int j ;

  int flag = 1;
  printf("%d - %d:", str, ed);
  for( j = 0; j < 26; j++){
    if(sums[j] > 0 && flag == 1){
      printf( " %c=%f",(char)(j+65),sums[j]);
      flag = 0;
    }else if(sums[j] > 0 && flag == 0){
      printf(", %c=%f",(char)(j+65),sums[j]);
    }
  }
  printf("\n");
}
