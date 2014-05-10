/* Name: Dilan Samarasinghe
   ID: DS697678
*/

void setup(); // fills the two arrays with 0's
int  getLargestData(); // returns the largest data packet ID
int  getLargestControl(); // returns the largest control packet ID
void biggestPayload(); // returns the largest data payload size
void findMissingData(); // prints which data packets are missing
void findMissingControl(); // prints which control packets are missing
void foundControl(unsigned char); // updates control packet statistics
int  foundData(unsigned char,unsigned char); // updates data packets statistics
