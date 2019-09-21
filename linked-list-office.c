#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Program to handle employes and their cars in the offices */



typedef struct TCar
{
  struct TCar              * m_Next;
  char                     * m_Model;
} TCAR;

typedef struct TEmployee
{
  struct TEmployee         * m_Next;
  struct TCar              * m_Car;
  char                     * m_Name;
} TEMPLOYEE;

typedef struct TOffice
{
  TEMPLOYEE                * m_Emp;
  TCAR                     * m_Car;
} TOFFICE;

#endif /* __PROGTEST__ */

void printOffice( TOFFICE * office){

  TEMPLOYEE * tmp = office->m_Emp;
  TCar * tmp2 = office->m_Car;

  printf("Seznam :\n");
  while( tmp ){
    if( tmp->m_Car != NULL)
    printf("ZAMESTNANEC : %s || AUTO : %s \n", tmp->m_Name, tmp->m_Car->m_Model);
    else
    printf("ZAMESTNANEC : %s\n", tmp->m_Name);
    tmp = tmp->m_Next;
  }
  while( tmp2 ){
    if( tmp2 != NULL)
    printf("AUTA : %s\n", tmp2->m_Model);

    tmp2 = tmp2->m_Next;
  }

}


TOFFICE          * initOffice   ()
{
  TOFFICE  * o;

  o = ( TOFFICE *)malloc(sizeof( *o ));
  o->m_Emp = NULL;
  o->m_Car = NULL;

  return o;
}
void               addEmployee  ( TOFFICE         * office,
                                  const char      * name )
{

    if(name == NULL)
      return;


    TEMPLOYEE * new_emp = ( TEMPLOYEE *)malloc( sizeof(TEmployee));

    int length = strlen(name);
    new_emp->m_Name = ( char *)malloc(sizeof(char)* length + 1);
    strncpy(new_emp->m_Name, name, length);
    new_emp->m_Name[length] = '\0';
    new_emp->m_Car = NULL;

    if( office->m_Emp == NULL){
      office->m_Emp = new_emp;
      new_emp->m_Next = NULL;
    }else{
      new_emp->m_Next = office->m_Emp;
      office->m_Emp = new_emp;
    }

}
void               addCar       ( TOFFICE         * office,
                                  const char      * model )
{

  if( model == NULL)
    return;


  TCAR * new_car = ( TCAR* )malloc( sizeof( TCar ));
  int length = strlen( model );

  new_car->m_Model = ( char * )malloc( sizeof( char ) * length + 1 );
  strncpy(new_car->m_Model, model, length );
  new_car->m_Model[length] = '\0';

  if( office->m_Car == NULL){

    office->m_Car = new_car;
    new_car->m_Next = NULL;

  }else{
    new_car->m_Next = office->m_Car;
    office->m_Car = new_car;
  }

}

void matchCars( TOFFICE * new_of, TOFFICE * old_of){

  if( new_of == NULL)
    return;

  TEMPLOYEE * cur_emp = old_of->m_Emp;
  TEMPLOYEE * pt_emp = new_of->m_Emp;

  TCAR * pt_car = new_of->m_Car;

  while( cur_emp != NULL){
    if( cur_emp->m_Car != NULL ){

      while( pt_car != NULL){
        if( !strcmp( pt_car->m_Model,cur_emp->m_Car->m_Model)){
          pt_emp->m_Car = pt_car;
          pt_car = new_of->m_Car;
          break;
        }
        pt_car = pt_car->m_Next;
      }

    }

    pt_emp = pt_emp->m_Next;
    cur_emp = cur_emp->m_Next;

  }

}

TOFFICE          * cloneOffice  ( TOFFICE         * office )
{

  if( office == NULL)
    return NULL;

  TOFFICE * o;
  o = ( TOFFICE *)malloc( sizeof( *o ));
  o->m_Emp = NULL;
  o->m_Car = NULL;

  TEMPLOYEE * cur_emp = office->m_Emp;
  TEMPLOYEE * tail_emp = NULL;
  TEMPLOYEE * new_list_emp = NULL;

  TCAR * cur_car = office->m_Car;
  TCAR * new_list_car = NULL;
  TCAR * tail_car = NULL;


  while( cur_emp != NULL ){

    if( new_list_emp == NULL){
      
      new_list_emp = ( TEMPLOYEE* )malloc( sizeof( TEmployee ));
      int length = strlen(office->m_Emp->m_Name);

      new_list_emp->m_Name = ( char *)malloc( sizeof( char ) * length  + 1);
      strncpy(new_list_emp->m_Name,cur_emp->m_Name,length);
      new_list_emp->m_Name[length] = '\0';
      new_list_emp->m_Car = NULL;

      o->m_Emp = new_list_emp;

      new_list_emp->m_Next = NULL;
      tail_emp = new_list_emp;
    }else{
      
      tail_emp->m_Next = ( TEMPLOYEE* )malloc( sizeof( TEmployee ));
      tail_emp = tail_emp->m_Next;

      int length = strlen(cur_emp->m_Name);

      tail_emp->m_Name = ( char *)malloc( sizeof( char ) * length  +1);
      strncpy(tail_emp->m_Name, cur_emp->m_Name, length);
      tail_emp->m_Name[length] = '\0';
      tail_emp->m_Car = NULL;

      tail_emp->m_Next = NULL;
    }

    cur_emp = cur_emp->m_Next;

  }

while( cur_car != NULL ){

  if( new_list_car == NULL){

    new_list_car = ( TCAR* )malloc( sizeof( TCar ));
    int length = strlen(office->m_Car->m_Model);

    new_list_car->m_Model = ( char *)malloc( sizeof( char ) * length  +1);
    strncpy(new_list_car->m_Model, cur_car->m_Model, length);
    new_list_car->m_Model[length] = '\0';

    o->m_Car = new_list_car;
    new_list_car->m_Next = NULL;
    tail_car = new_list_car;
  }else{
    tail_car->m_Next = ( TCAR* )malloc( sizeof( TCar ));
    tail_car = tail_car->m_Next;

    int length = strlen(cur_car->m_Model);

    tail_car->m_Model = ( char *)malloc( sizeof( char ) * length  +1);
    strncpy(tail_car->m_Model, cur_car->m_Model,length);
    tail_car->m_Model[length] = '\0';

    tail_car->m_Next = NULL;
  }

  cur_car = cur_car->m_Next;
}

  matchCars( o , office);

  return o;

}
void               freeOffice   ( TOFFICE         * office )
{

  if( office == NULL)
    return;

  TCAR * current_car = office->m_Car;
  TCAR * next_car;


  TEMPLOYEE * current_emp = office->m_Emp;
  TEMPLOYEE * next_emp;

  while( current_car != NULL){
    next_car = current_car->m_Next;
    free(current_car->m_Model);
    free(current_car);
    current_car = next_car;
  }

  while( current_emp != NULL){
    next_emp = current_emp->m_Next;
    free(current_emp->m_Name);
    free(current_emp);
    current_emp = next_emp;

  }


  free(office);

}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TOFFICE * a, *b;
  char tmp[100];

  assert ( sizeof ( TOFFICE ) == 2 * sizeof ( void * ) );
  assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
  assert ( sizeof ( TCAR ) == 2 * sizeof ( void * ) );
  a = initOffice ();
  addEmployee ( a, "Peter" );
  addEmployee ( a, "John" );
  addEmployee ( a, "Joe" );
  addEmployee ( a, "Maria" );
  addCar ( a, "Skoda Octavia" );
  addCar ( a, "VW Golf" );
  a -> m_Emp -> m_Car = a -> m_Car;
  a -> m_Emp -> m_Next -> m_Next -> m_Car = a -> m_Car -> m_Next;
  a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = a -> m_Car;
  assert ( a -> m_Emp
           && ! strcmp ( a -> m_Emp -> m_Name, "Maria" )
           && a -> m_Emp -> m_Car == a -> m_Car );
  assert ( a -> m_Emp -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Joe" )
           && a -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( a -> m_Car
           && ! strcmp ( a -> m_Car -> m_Model, "VW Golf" ) );
  assert ( a -> m_Car -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( a -> m_Car -> m_Next -> m_Next == NULL );
  //printf("%s\n",a->m_Emp->m_Car->m_Model); ***************
  b = cloneOffice ( a );
  strncpy ( tmp, "Moe", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Victoria", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Peter", sizeof ( tmp ) );
  addEmployee ( a, tmp );
  strncpy ( tmp, "Citroen C4", sizeof ( tmp ) );
  addCar ( a, tmp );
  b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car = b -> m_Car -> m_Next -> m_Next;
  assert ( a -> m_Emp
           && ! strcmp ( a -> m_Emp -> m_Name, "Peter" )
           && a -> m_Emp -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Name, "Victoria" )
           && a -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Car == NULL );
        //   printf("%s ||| %s \n", a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car->m_Model,  a -> m_Car -> m_Next ->m_Model);//***********
        //   printf("%s ||| %s \n", a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, a -> m_Car -> m_Next ->m_Model);//******
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next
          && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
          && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Car == a -> m_Car -> m_Next );
  assert ( a -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( a -> m_Car
           && ! strcmp ( a -> m_Car -> m_Model, "Citroen C4" ) );
  assert ( a -> m_Car -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Model, "VW Golf" ) );
  assert ( a -> m_Car -> m_Next -> m_Next
           && ! strcmp ( a -> m_Car -> m_Next -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( a -> m_Car -> m_Next -> m_Next -> m_Next == NULL );
//  printf("b->m_Emp : %s\n\n\n",b->m_Emp->m_Name);
//  printf("284 :  %s\n\n\n",b -> m_Emp -> m_Car->m_Model);
//  printf("284 :  %s\n\n\n",b -> m_Car->m_Model);
  assert ( b -> m_Emp
           && ! strcmp ( b -> m_Emp -> m_Name, "Maria" )
           && b -> m_Emp -> m_Car == b -> m_Car );
  assert ( b -> m_Emp -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Name, "Joe" )
           && b -> m_Emp -> m_Next -> m_Car == NULL );
  assert ( b -> m_Emp -> m_Next -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Emp -> m_Next -> m_Next -> m_Car == b -> m_Car -> m_Next );
  assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Car == NULL );
  assert ( b -> m_Emp -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b -> m_Car
           && ! strcmp ( b -> m_Car -> m_Model, "VW Golf" ) );
  assert ( b -> m_Car -> m_Next
           && ! strcmp ( b -> m_Car -> m_Next -> m_Model, "Skoda Octavia" ) );
  assert ( b -> m_Car -> m_Next -> m_Next == NULL );
  //printOffice(b);///*************
  freeOffice ( a );
  //printOffice(a);///*************
  freeOffice ( b );
  return 0;
}
#endif /* __PROGTEST__ */
