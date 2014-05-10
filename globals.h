/* Name: Dilan Samarasinghe
   ID: DS697678

*/

int control[ARRAY_SIZE]; // stores the control packet ids
int data[ARRAY_SIZE]; // stores the data packet ids
int mask2 = 0x7F; // mask to get last seven bits in the first byte
int mask3 = 0xFF; // mask to get the last byte
int lpayload = 0; // holds the largest payload value in data packets.
