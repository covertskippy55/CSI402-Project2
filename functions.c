/* Name: Dilan Samarasinghe
   ID: DS697678
*/

#include <stdio.h>
#include "constants.h"
#include "globals.h"

/* This function takes in nothing and returns nothing. It will set up the two arrays that store the packet IDs so that they are set to 0 at the start 
*/
void setup(){
  int i; // temp variable
  // loop through the arrays setting each to 0
  for(i = 0; i < 256; i++){
    control[i] = 0;
    data[i] = 0;
  }  
}

/* This function takes in a byte ( unsigned char) and returns nothing. It takes said byte,and changes the array at that index to 1.
 */
void foundControl(unsigned char second){
  // change control array to 1 at that index
  control[second] = 1;

}
/* This function takes in two bytes and returns an unsigned long int. It will find the number of bytes to skip in the binary file, and change the data array to 1 at calculated index.
 */

unsigned long int foundData(unsigned char first, unsigned char second){
  unsigned long int skip = (first & mask2); // get the number of bytes to skip by masking the first byte
  // change array at this index to 1
  data[second] = 1;
  // see if the current payload size is bigger than whats stored
  if(skip > lpayload){
    lpayload = skip;
  }
  return skip;
  
}
/* This function takes nothing and returns nothing. It will print what the biggest payload size is */
void biggestPayload(){
  printf("The largest data packet payload = %d \n",lpayload);
  fflush(stdout);
}

/* This function takes in nothing and returns the largest data size as an int. */
int getLargestData(){
  int j; // temp variable
  // traverse through the array starting from the end untill you find the first 1 then return that index
  for( j = ARRAY_SIZE-1;j > 0; j--){
    if(data[j] == 1){
      return j;
    }
  }
  return 0; // otherwise return 0
}

/* Same function as above but for control packets */
int getLargestControl(){
    int i;// temp variable
    for(i = ARRAY_SIZE-1; i > 0; i--){
      if(control[i] == 1){
        return i;
      }
    }
    return 0;
  }
/* This function takes in nothing and returns nothing. It will print the numbers of the missing packets starting at 0 to the highest packet recieved. If three or more values were missing in a row it will print the range, otherwise it will print single values.*/
void findMissingData(){
  int i = 0; // index value
  int low = 0; // value to keep track of the low end for range printing
  int highest = getLargestData(); // get and store the highest packet ID
  // while the current i value is less than the highest seen loop through
  while(i < highest){
    // check if the current value and the next two values are all zeroes
    if((data[i] == 0)&& (data[i+1] == 0) && (data[i+2] == 0)){
      // if so set low to be the current i value and add 3 to i. This gives us the new i value 
      low = i;
      i = i+3;
      // loop through the rest of the array incrementing i until you find a 1
      while(data[i] == 0){
	i++;
      }
      // print the low value( our starting 0 ) and the current i value minus 1(since the abouve loop will stop when i is at a 1) as a range
      printf(" %d - %d,",low,i-1);
    }
    // otherwise if the current i value is 0 then print it as a single value and increment i
    else if(data[i] == 0){
      printf("%d,",i);
      i++;
     }
    // if the current i value is a one this else will trigger, in that case increment i by 1
    else{
      i++;
    }
  }
}

/* This function is the same as above function but to find and pring missing control packets */
void findMissingControl(){
  int i = 0;
  int low = 0;
  int highest = getLargestControl();
  while(i < highest){
    if((control[i] == 0)&& (control[i+1] == 0) && (control[i+2] == 0)){
      low = i;
      i = i+3;
      while(control[i] == 0){
	i++;
      }
      printf(" %d - %d,",low,i-1);
    }
    else if(control[i] == 0){
      printf(" %d,",i);
      i++;
    }
    else{
      i++;
    }
  }
}
