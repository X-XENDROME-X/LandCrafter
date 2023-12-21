#ifndef Main_H
#define Main_H
#include  <fstream>

using namespace std;

//below is a function prototype for generating a random double value between 0 and 1.
double fRand();

//below is a function prototype for creating a 2D integer array (grid) with given dimensions.
int** MakeArray(int GWidth, int GHeight);

//below is a function prototype for removing a dynamically allocated 2D integer array.
void RemoveArray(int** a, int GHeight);

//below is a function prototype for dropping dirt balls on the grid to modify the terrain.
void DropDirtBall(int** Area, int DWidth, int DHeight, int DirtWaterline, int DRadius, int DPower, int DBalls);

//below is a function prototype for printing the final landmass map to a file and the console.
void PrintPolishedLand(char** FinalMap, int DWidth, int DHeight , ofstream &File);

//below is a function prototype for finding the maximum value within a 2D integer grid.
int FindMax(int** Area, int DWidth, int DHeight);

//below is a function prototype for normalizing the values in a 2D integer grid.
void NormalizeMap(int** Area, int DWidth, int DHeight, int Max);

//below is a function prototype for categorizing the landmass and generating a character map.
char** FinalizeMap(int** Area, int DWidth, int DHeight, int DWaterline);

//below is a function prototype for printing the raw landmass data to a file and the console.
void PrintRLand(int** Base, int width, int height, ofstream &File);

//below is a function prototype for removing a dynamically allocated character array (2D).
void RemoveFinalMap(char **a, int GHeight);

//below is a function prototype for printing the normalized landmass data to a file and the console.
void PrintNLand(int **Base, int DWidth, int DHeight ,ofstream &File);

#endif 
