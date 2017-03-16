#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<sys/timeb.h>

/*
*Michal Chorobik 0937145
*mchorobi@uofguelph.mail.ca
*March 13, 2017
*/

int main(int argc, char const *argv[]) {
  int count=0;
  int position=0;

  char alphabet [26];
  for (int i=0;i<26;i++){
    alphabet[i]=0;
  }

  struct timeb start, end;
  int diff;
  ftime(&start);

  char word [99];
  printf("enter the string: ");
  scanf("%s",word);
  int patShift=0;

  //this for loop assigns the index of a letter in the word string to the position that represtents that letter in the alphabet
  for (int i=0;i<strlen(word)-1;i++){
    position = word[i] - 'a';
    count=0;
    for (int a=i;a<strlen(word);a++){
      count++;
    }
    alphabet[position]=count-1;
  }
  //here i assign any letter that isnt in the word string with the length of the word string
  for (int i=0;i<26;i++){
    if(alphabet[i]==0){
      alphabet[i]=strlen(word);
    }
  }

  //*****************************************************

  int  totalcount=0;
  char str[225];
  FILE*fp = fopen("data_5.txt", "r");
  count=strlen(word)-1;

  //data_5.txt is parsed line at a time
  while (fgets (str, 225, fp)!=NULL) {

//***********************************************************************
    for (int x=0;x<strlen(str);x++){
      for(int y=strlen(word)-1+x;y>x;y--){
          if(word[count]!=str[y]){
            position=str[y]-'a';
            if((position>25)||(position<0)){
              break;
            }
            patShift++;
            x+=alphabet[position];
            x--;
            break;
          }
          if(count==1){
            if(word[count-1]==str[y-1]){
              totalcount++;
            }
          }
          count--;
      }
      count=strlen(word)-1;
    }
//***********************************************************************

  }
  fclose(fp);

  ftime(&end);
   diff = (int) (1000.0 * (end.time - start.time)
       + (end.millitm - start.millitm));

  printf("\nOperation took %u milliseconds\n", diff);
  printf("pattern shifts: %d\n",patShift);
  printf("total: %d\n",totalcount);
  return 0;
}
