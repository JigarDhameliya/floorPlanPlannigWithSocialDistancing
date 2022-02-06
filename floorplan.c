#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define true 1
#define false 0

//method signatures
void setInitialFloorPlan(int a,int b,char[][b]);
int setFloorPlan(int a, int b, int c,char[][b]);
void printFloorPlan(int a,int b,char[][b]);
void generateRandomElement(int a ,int[]);


int main(){
  int length;
  int width;
  int numIterations;

//Error handling to only take positive numbers greater than 0
  do{
    printf("How wide (in feet) is the restaurant floor? ");
    scanf("%d", &width);
    printf("\n");
  }while(width<=0);
  width=(int)width/2;

  do{
    printf("How long (in feet) is the restaurant floor? ");
    scanf("%d", &length);
    printf("\n");
  }while (length<=0);
  length=(int)length/2;

  do{
    printf("How many seatings would you like to simulate? ");
    scanf("%d", &numIterations);
    printf("\n");
  }while(numIterations<0);

//char array of floor and int array to store random numbers from the given array
  char floorPlan[length][width];
  int randomElements[numIterations];
  //int testerArray[15] = {6,1,4,3,4,8,12,3,4,11,2,4,1,4,5};
  setInitialFloorPlan(length,width,floorPlan);
  generateRandomElement(numIterations,randomElements);
  printf("\n");

//for each element in the random array try to seat the parties and print either the table was found or not
  for(int i=0;i<numIterations;i++){
    int columnValue = setFloorPlan(length,width,randomElements[i],floorPlan);
    if(columnValue != 0){
      columnValue = (int)(columnValue/6);
      columnValue+=1;
      printf("Table for %d was found in column %d\n",randomElements[i],columnValue);
      printFloorPlan(length,width,floorPlan);
      printf("\n");
    }
    else
      printf(" ***Table for %d was not available ***\n",randomElements[i]);
      printf("\n");

  }
  return 0;
}

//Initialize the whole array as "."
void setInitialFloorPlan(int length, int width, char theArray[][width]){
  char charDot = '.';
  for(int i=0;i<length;i++){
    for(int j=0;j<width;j++){
      theArray[i][j] = charDot;
    }
  }
}

//prints the floorplan
void printFloorPlan(int length, int width, char theArray[][width]){
  for(int i=0;i<length;i++){
    for(int j=0;j<width;j++){
      printf("%c ", theArray[i][j]);
    }
    printf("\n");
  }
}

//generates n random elemens and stores them in randomElements array
void generateRandomElement(int n,int theArray[]){
  int givenArray[11] = {1, 2, 2, 3, 3, 4, 4, 5, 6, 8,12};
  srand(time(NULL));
  for(int i=0;i<n;i++){
    theArray[i] = givenArray[(int)(rand()/(double)RAND_MAX*11)];
  }
}

/*
Sets the floorplan
finds a "." and then
Checks 3 things
A - if there is a dot on top of it and after 3 indices then assigns the chairs and table
B - if there is a C on top of it and a dot after 3 indices then assigns the chairs and table after
3 places so we can follow the social distancing.
C - if there is a C on top of it and a C after 3 indices then it continues to search'
also there is a boolean that acts a break. It ensures that the tables are assignes only once.
*/

int setFloorPlan(int length,int width,int n,char theArray[][width]){
  int i=1;
  int j=1;
  char charDot = '.';
  char charC = 'C';
  char charT = 'T';
  char fakeBool = true;
  if(n%2 == 1)
    n = n+1;
  int numChairsInCol = (int)(n/2);
  for(j=1;j<width-1;j+=6){
    for(i=1;i<length-1;i++){
      char check = theArray[i][j];
      char check2 = theArray[i-1][j];
      char check3 = theArray[i+3][j];
      if(check == charDot && check2 == charDot && check3 == charDot && fakeBool){
        //bounds check
        if((i+numChairsInCol+3 < length) && (j+3< width)){
          for(int k=0;k<numChairsInCol;k++){
            theArray[i+k][j] = charC;
            theArray[i+k][j+1] = charT;
            theArray[i+k][j+2] = charC;
          }
          fakeBool = false;
          return j;
        }
        else{
          continue;
        }
      }
      else if(check == charDot && check2 == charC && check3 == charDot && fakeBool){
        if((i+numChairsInCol+3 < length) && (j+3< width)){
          for(int k=0;k<numChairsInCol;k++){
            theArray[i+k+3][j] = charC;
            theArray[i+k+3][j+1] = charT;
            theArray[i+k+3][j+2] = charC;
          }
          fakeBool = false;
          return j;
        }
        else{
          continue;
        }
      }
      else if(check == charDot && fakeBool && check2 == charC && check3 == charC){
        i = i+3;
        continue;
      }
    }
  }
  return 0;
}
