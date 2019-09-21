#ifndef __PROGTEST__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/* Function to format text according to the given width */


int formatStrFinal(char * string,int len_string, int width, int nn){

  int mez = 0,i = 0;
  int act_len = 0;

  for( i = 0; i < len_string ; i++){

    act_len++;

    if( string[i] == '\n'){
      act_len = 0;
      mez = 0;
    }else if( string[i] != ' ' &&  act_len > width){
      if( mez == 0){
        return 0;
      }
      string[mez] = '\n';
      act_len = i- mez;
      mez = 0;
    }else if( string[i] == ' ' && act_len >= width ){
      string[i] = '\n';
      act_len = 0;
      mez = 0;
    }else if( string[i] == ' '){
      mez = i;
    }

  }
  string[len_string] = '\n';
  string[len_string+1] = '\0';
  return 1;
}

void formatString(char * string,const char * src, int * len_string, int * nn){

  int i = 0;
  int j = 0;
  int s = 0;
  int n = 0;


  for( i = 0; src[i]; i++){

      if( !isspace(src[i])){
//------------------------
        if( s > 0){
          string[j] = ' ';
          j++;
          s = 0;
        }
//-----------------------------
        if( n > 1){
          string[j] = '\n';
          j++;
          string[j] = '\n';
          j++;
          n = 0;
          s = 0;
          (*nn) +=2;
        }
//-------------------------------
        if( n == 1){
          string[j] = ' ';
          j++;
          n = 0;
        }
//----------------------------------
        string[j] = src[i];
        j++;
      }

      if( j > 0 && (src[i] == ' ' || src[i] == '\t')){
        s++;
      }

      if( j > 0 && src[i] == '\n' ){
        n++;
      }
  }
  *len_string = j;
}

void calcLength( const char * src, int * len_string){

  int i = 0;
  int j = 0;

  for( i = 0; src[i]; i++ ){

    if( !isspace(src[i])){
      (*len_string)++;
      if( j > 0 ){
        (*len_string)++;
        j = 0;
      }
    }
    if( *len_string > 0 && isspace(src[i])){
        j++;
    }
  }

}

char             * wordWrap                                ( int               width,
                                                             const char      * src )
{

  int len_string = 0;
  int nn = 0;
  if( src == NULL ){
    return NULL;
  }
   

  calcLength(src,&len_string);

  char * string = ( char * )malloc((len_string+500) * sizeof(char));

  formatString(string, src, &len_string, &nn);

  if( !formatStrFinal(string, len_string, width, nn)){
    free(string);
    return NULL;
  }

  return string;

}

#ifndef __PROGTEST__
int                main                                     ( void )
{
  char * res;
  const char * s0 =
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
    "libero non diam.";
  const char * s1 =
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat\n"
    "orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. Pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nam\n"
    "in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor\n"
    "ultrices neque. Mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
    "libero non diam.\n"
    "\n"
    "Proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
    "amet, magna. Nam congue cursus magna. In malesuada, velit a gravida sodales,\n"
    "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. Nulla\n"
    "eget risus. Quisque nec sapien blandit odio convallis ullamcorper. Lorem\n"
    "ipsum dolor sit amet, consectetuer adipiscing elit. Pellentesque cursus.\n"
    "Aliquam tempus neque vitae libero molestie ut auctor.\n"
    "\n"
    "\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit.\tNam tristique magna nec pede. Sed\n"
    "a nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec\n"
    "sed mauris. Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
    "turpis. Mauris malesuada nisi sed enim. In hac habitasse platea dictumst.\n"
    "Fusce    faucibus, turpis nec auctor posuere, nulla tellus scelerisque metus,\n"
    "quis molestie mi dui id quam. Mauris vestibulum. Nam ullamcorper.\n"
    "\n";
  res = wordWrap ( 40, s0 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n" ) );

  free ( res );

  res = wordWrap ( 120, s0 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
    "feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
    "turpis egestas. Nam in pede. Etiam eu sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris semper,\n"
    "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. Pellentesque dui. Vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
  free ( res );

  res = wordWrap ( 10, s1 );
  assert ( res == NULL );

  res = wordWrap ( 40, s1 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. Pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. Nam in pede.\n"
    "Etiam eu sem id urna ultricies congue.\n"
    "Vestibulum porttitor ultrices neque.\n"
    "Mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "Pellentesque dui. Vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate\n"
    "id, fringilla sit amet, magna. Nam\n"
    "congue cursus magna. In malesuada, velit\n"
    "a gravida sodales, dolor nisl vestibulum\n"
    "orci, sit amet sagittis mauris tellus\n"
    "nec purus. Nulla eget risus. Quisque nec\n"
    "sapien blandit odio convallis\n"
    "ullamcorper. Lorem ipsum dolor sit amet,\n"
    "consectetuer adipiscing elit.\n"
    "Pellentesque cursus. Aliquam tempus\n"
    "neque vitae libero molestie ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate\n"
    "suscipit. Nam tristique magna nec pede.\n"
    "Sed a nisi. Nulla sed augue ut risus\n"
    "placerat porttitor. Ut aliquam. Nulla\n"
    "facilisi. Nulla vehicula nibh ac sapien.\n"
    "Nunc facilisis dapibus ipsum. Donec sed\n"
    "mauris. Nulla quam nisi, laoreet non,\n"
    "dignissim posuere, lacinia nec, turpis.\n"
    "Mauris malesuada nisi sed enim. In hac\n"
    "habitasse platea dictumst. Fusce\n"
    "faucibus, turpis nec auctor posuere,\n"
    "nulla tellus scelerisque metus, quis\n"
    "molestie mi dui id quam. Mauris\n"
    "vestibulum. Nam ullamcorper.\n" ) );
  free ( res );

  res = wordWrap ( 80, s1 );
  assert ( ! strcmp ( res,
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit amet, ligula. Integer volutpat orci et\n"
    "elit. Nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies turpis. Pellentesque habitant morbi tristique\n"
    "senectus et netus et malesuada fames ac turpis egestas. Nam in pede. Etiam eu\n"
    "sem id urna ultricies congue. Vestibulum porttitor ultrices neque. Mauris\n"
    "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
    "ante nisl ac ante. Pellentesque dui. Vestibulum pretium, augue non cursus\n"
    "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
    "\n"
    "Proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. Nam congue\n"
    "cursus magna. In malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
    "sit amet sagittis mauris tellus nec purus. Nulla eget risus. Quisque nec sapien\n"
    "blandit odio convallis ullamcorper. Lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. Pellentesque cursus. Aliquam tempus neque vitae libero molestie\n"
    "ut auctor.\n"
    "\n"
    "In nec massa eu tortor vulputate suscipit. Nam tristique magna nec pede. Sed a\n"
    "nisi. Nulla sed augue ut risus placerat porttitor. Ut aliquam. Nulla facilisi.\n"
    "Nulla vehicula nibh ac sapien. Nunc facilisis dapibus ipsum. Donec sed mauris.\n"
    "Nulla quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. Mauris\n"
    "malesuada nisi sed enim. In hac habitasse platea dictumst. Fusce faucibus,\n"
    "turpis nec auctor posuere, nulla tellus scelerisque metus, quis molestie mi dui\n"
    "id quam. Mauris vestibulum. Nam ullamcorper.\n" ) );
  free ( res );

  return 0;
}
#endif /* __PROGTEST__ */
