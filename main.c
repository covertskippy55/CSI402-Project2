/* Name: Dilan Samarasinghe
   ID: DS697678
*/

#include <stdio.h>
#include "constants.h"
#include "prototypes.h"


int main(int argc,char *argv[]){
  unsigned char first; // holds the first byte of the heading
  unsigned char second; // holds the second byte of the heading
  int mask1 = 0x01; // hex mask to & with first byte to get the first bit
  unsigned int test; // holds the first bit of the first byte
  unsigned long int skip; // holds the value to seek the binary file
  FILE *infileptr; // infile pointer
  int numControl = 0;//stores the number of control packets
  int numData = 0;// stores the number of data packets
  int value;// holds the stats values to be printed
  // check if the number of arguments are correct
  if(argc != NUM_ARG){
    fprintf(stderr,"Invalid number of commands. Usage p2 flag infile \n");
    exit(1);
  }
  // check if the flag is correct
  if(((strcmp(argv[1],"-c"))!= 0) && ((strcmp(argv[1],"-d"))!= 0) && ((strcmp(argv[1],"-cd"))!= 0)){
    fprintf(stderr,"The flag you entered is incorrect. Please choose one of: -c -d -cd next time \n");
    exit(1);
  }
  // open file for reading
  if((infileptr = fopen(argv[2],"r"))==NULL){
    fprintf(stderr,"Error occured during opening of %s \n",argv[2]);
    exit(1);
  }
  setup();
  // while the return of fread is equal to 1,the number of entries,read the next byte
  while(fread((void*)&first,sizeof(unsigned char),1,infileptr)== 1){
    //read the next byte into second
    fread((void*)&second,sizeof(unsigned char),1,infileptr);
    // right shift first by 7 bits then and with mask 1 to store the first bit of first as last bit of test
    test =((first >> 7) & mask1);
    //see if the shifted last bit is 0 and call foundData
    if(test == 0){
	// store the value returned from foundData in skip
      skip = foundData(first,second);
      numData++; // increment the number of data packets
      fseek(infileptr,skip,SEEK_CUR);// fseek the number of bytes specified by skip
    }
    // otherwise check if the shifted last bit is 1 and call foundControl
    else if(test == 1){
      foundControl(second);
      numControl++;//increment the number of control packets
    }
 }
  // print the appropriate stats based on the flag provided

  if(strcmp(argv[1],"-c") == 0){
    printf("\n");
    printf("Information about Control Packets: \n\n");
    fflush(stdout);
    printf("The number of control packets = %d \n",numControl);
    fflush(stdout);
    value = getLargestControl();
    printf("The largest control packet ID = %d \n",value);
    fflush(stdout);
    printf("Missing IDs are: ");
    findMissingControl();
    printf("\n");
    fflush(stdout);
    

  }  
  else if(strcmp(argv[1],"-d") == 0){
    printf("\nInformation about Data packets:\n\n");
    fflush(stdout);
    printf("The number of data packets = %d \n",numData);
    fflush(stdout);
    value = getLargestData();
    printf("The largest data packet ID = %d \n",value);
    fflush(stdout);
    biggestPayload();
    printf("Missing IDs are: ");
    findMissingData();
    printf("\n");
    fflush(stdout);
  }
  else if(strcmp(argv[1],"-cd") == 0){
    printf("\nInformation about Control Packets: \n\n");
    fflush(stdout);
    printf("The number of control packets = %d \n",numControl);
    fflush(stdout);
    value = getLargestControl();
    printf("The largest control packet ID = %d \n",value);
    fflush(stdout);
    printf("Missing IDs are: ");
    findMissingControl();
    printf("\n");
    fflush(stdout);
    printf("--------------------------------------------\n\n");
    fflush(stdout);
    printf("\nInformation about Data packets: \n\n");
    fflush(stdout);
    printf("The number of data packets = %d \n",numData);
    fflush(stdout);
    value = getLargestData();
    printf("The largest data packet ID = %d \n",value);
    fflush(stdout);
    biggestPayload();
    printf("Missing IDs are: ");
    findMissingData();
    printf("\n");
    fflush(stdout);
  }


  // close the file
   if(fclose(infileptr)== EOF){
    fprintf(stderr,"Error occured during closing of %s \n",argv[2]);
    exit(1);
  }
  
  return 1;
} // end of main
