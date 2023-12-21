#include  <iostream>
#include  <cstdio>
#include  <cstdlib>
#include  <cmath>
#include  <iomanip>
#include  <ctime>
#include  <cstring>
#include  "Main.h"
#include  <fstream>
#include  "termcolor.hpp"

using namespace std;

// Below is the main function
int main(int argc , char *argv[])
{

    // Below initialize a random seed with the current time.
    int Seed =time(0);

    // Below checks for command line arguments, and if "-s" is provided, use the seed provided as an argument.
    if (argc== 3 && strcmp(argv[1] , "-s")==0)
    {
        // Below converts the argument to an integer and set it as the seed.
        Seed=atoi(argv[2]);
        // Below initializes the random number generator with the given seed.
        srand(Seed);
    }
    else
    {
        //Otherwise, it uses the default seed based on the current time
        srand(Seed);
    }

    int GridWidth;
    int GridHeight;
    int DWaterLine;
    int DirtballRadius;
    int DirtballPower;
    int DirtBalls;
    int XCenter;
    int YCenter;

    // Below creates output files for the landmass maps.
    ofstream FileF("final_landmass.txt");
    ofstream NFile("normalized_landmass.txt");
    ofstream RFile("raw_landmass.txt");


    // Below gives a welcome message and ask user inputs
    printf("Welcome to the LandCrafter!!\n");

    printf("Enter grid width: ");
    scanf("%d" , &GridWidth);

    printf("Enter grid height: ");
    scanf("%d" , &GridHeight);

    printf("Enter Amt for DWaterline (40-200): ");
    scanf("%d" , &DWaterLine);

    printf("Enter dirtball radius (minimum 2): ");
    scanf("%d" , &DirtballRadius);

    printf("Enter dirtball power rating (minimum = radius): ");
    scanf("%d" , &DirtballPower);

    printf("Enter number of dirtballs to drop: ");
    scanf("%d" , &DirtBalls);

    //Below creates a 2D array to represent the grid.
    int **Base=MakeArray(GridHeight , GridWidth);

    //Below stimulates the impact of dirtballs on the grid.
    for (int x=0; x<DirtBalls; x++)
    {
        // Below generates a random XCenter within the grid.
        XCenter =(int)(floor(fRand()* GridWidth));
        // Below generates a random YCenter within the grid.
        YCenter =(int)(floor(fRand()* GridHeight));

        //Below simulates the impact of a dirtball.
        DropDirtBall(Base, GridWidth, GridHeight, XCenter, YCenter, DirtballRadius, DirtballPower);
    }

    //Below finds the maximum value in the grid and the prints it.
    int max = FindMax(Base , GridWidth , GridHeight);
    cout << max << endl;

    //below prints the raw landmass data to a file.
    PrintRLand(Base , GridWidth , GridHeight , RFile);
    //below normalizes the map based on the maximum value.
    NormalizeMap(Base , GridWidth , GridHeight , FindMax(Base , GridWidth , GridHeight));

    //below creates the final landmass map and categorize terrain.
    char **FinalMap = FinalizeMap(Base , GridWidth , GridHeight , DWaterLine);
   
    //below prints the normalized landmass data to a file.
    PrintNLand(Base , GridWidth , GridHeight , NFile);

    //Below prints the polished landmass to a file.
    PrintPolishedLand(FinalMap , GridWidth , GridHeight , FileF);

    //Below deallocates the memory 
    RemoveArray(Base , GridHeight);
    RemoveFinalMap(FinalMap , GridHeight);

    // below closes the output files.
    RFile.close();
    NFile.close();
    FileF.close();

    //below returns 0 to indicate successful program execution.
    return 0;
}

// the below function generates a random floating-point number between 0 and 1.
double fRand()
{
    //below generates a random integer using rand() and divide it by (RAND_MAX + 1) to convert to a floating-point number in the range [0, 1].
    return (double)rand()/((double)RAND_MAX + 1);
}

// This below function dynamically allocates a 2D array of integers and initializes all elements to 0.
int **MakeArray(int GHeight , int GWidth)
{
    //below allocates an array of pointers for the rows of the 2D array.
    int **a = new int *[GHeight];

    //below iterates through rows.
    for (int x= 0; x< GHeight; x++)
    {
        //For each row, below allocate an array of integers for the columns.
        a[x] = new int[GWidth];
    }

    //below initializes all elements to 0 by iterating through rows and columns.
    for (int x=0; x <GHeight; x++)
    {
        for (int y= 0; y< GWidth; y++)
        {
            a[x][y]= 0;
        }
    }
    //below returns a pointer to the dynamically allocated 2D array.
    return a;
}

// This below function deallocates memory associated with a dynamically allocated 2D integer array.
void RemoveArray(int **a , int GHeight)
{
    int x=0;

    //Below iterates through rows of the 2D array.
    while (x<GHeight)
    {
        //Below deallocates the memory for each row array.
        delete[] a[x];
        x++;
    }

    //below deallocates the memory for the array of row pointers.
    delete[] a;
}

// below function deallocates memory associated with a dynamically allocated 2D character array.
void RemoveFinalMap(char **a , int GHeight)
{
    int x= 0;

    //below iterates through rows of the 2D character array.
    while (x< GHeight)
    {
        //deallocates the memory for each row array.
        delete[] a[x];
        x++;
    }

    //deallocates the memory for the array of row pointers.
    delete[] a;
}

//below function simulates the impact of a dirtball on a 2D integer grid.
void DropDirtBall(int **Area , int DWidth , int DHeight , int XCenter , int YCenter , int DRadius , int DPower)
{

    //below iterates through the rows of the grid.
    for (int p= 0; p< DHeight; p++)
    {
        //below iterates through the columns of the grid.
        for (int q= 0; q< DWidth; q++)
        {
             //below checks if the coordinates (q, p) are within the boundaries of the grid.
            if (q >= 0 && q< DWidth&& p>=0 && p< DHeight)
            {
                //below calculates the distance of the current cell from the dirtball's center.
                double DirtDistance = sqrt(pow(q - XCenter , 2) + pow(p - YCenter , 2));

                // If the cell is within the dirtball's radius, then it calculates and apply the impact value.
                if (DirtDistance<=DRadius)
                {
                    int ImpactVal=DPower - (int)(floor(DirtDistance));
                    //below applies the impact.
                    Area[p][q] +=ImpactVal;
                }
            }
        }
    }
}


//below function finds and returns the maximum value within a 2D integer grid.
int FindMax(int **Area , int DWidth , int DHeight)
{
    //below initializes Max with the value of the first cell.
    int Max= Area[0][0];

    //below iterates through the rows of the grid.
    for (int x= 0; x< DHeight; x++)
    {
        //below iterates through the columns of the grid.
        for (int y= 0; y< DWidth; y++)
        {
            //If the current cell value is greater than Max,then it updates the Max.
            if (Area[x][y]>Max)
            {
                Max = Area[x][y];
            }
        }
    }

    //below returns the maximum value found in the grid.
    return Max;
}

//below function normalizes the values in a 2D integer grid based on a specified maximum value.
void NormalizeMap(int **Area , int DWidth , int DHeight , int Max)
{
    //below iterates through the rows of the grid.
    for (int x= 0; x< DHeight; x++)
    {
        //below iterates through the columns of the grid.
        for (int y= 0; y< DWidth; y++)
        {
            //below normalizes each cell's value to a scale of 0-255 based on the maximum value in the grid.
            Area[x][y] = (int)(floor((((double)(Area[x][y]))/Max)*255));
        }
    }
}


// below function categorizes the landmass based on water levels and generates a 2D character map.
char **FinalizeMap(int **Area , int DWidth , int DHeight , int DWaterline)
{
    //below calculates the range of land (LandZone) based on the waterline level.
    int LandZone= 255 - DWaterline;

    //below creates a 2D character array to represent the final landmass map.
    char **FinalMap= new char *[DHeight];


    //below initializes each row of the character map with an array of characters.
    for (int x= 0; x< DHeight; x++)
    {
        FinalMap[x]= new char[DWidth];
    }

     //below iterates through the rows and columns of the character map.
    for (int x= 0; x< DHeight; x++)
    {
        for (int y= 0; y< DWidth; y++)
        {
            if (Area[x][y]<floor(0.5 * DWaterline))
            {
                // If the area is below half of the waterline, it's categorized as deep water.
                FinalMap[x][y] = '#'; // Represent deep water.

            }

            // If the area is within the waterline range, it's categorized as shallow water.
            else if ((Area[x][y]>=floor(0.5 * DWaterline))&&(Area[x][y] <= DWaterline))
            {
                FinalMap[x][y] = '~'; // rep shallow water
            }

            // Above water line conditions
            else
            {
                if (Area[x][y]<DWaterline + floor(0.15 * LandZone))
                {
                    // If the area is within 15% of the LandZone from the waterline, it's categorized as coast/beach.
                    FinalMap[x][y] = '.'; // rep coast / beach
                }

                else if (Area[x][y]>=(DWaterline + floor(0.15 * LandZone))&&(Area[x][y]<(DWaterline + floor(0.4 * LandZone))))
                {
                    // If the area is within the first 40% of LandZone from the waterline, it's categorized as plains/grass.
                    FinalMap[x][y] = '-'; // rep plains / grass
                }

               else if (Area[x][y]>=(DWaterline + floor(0.4 * LandZone))&&(Area[x][y] < (DWaterline + floor(0.8 * LandZone))))
                {
                    // If the area is within the first 80% of LandZone from the waterline, it's categorized as forest.
                    FinalMap[x][y] = '*'; // rep forest
                }
                else
                {
                    // If the area is beyond the first 80% of LandZone from the waterline, it's categorized as mountains.
                    FinalMap[x][y] = '^'; // rep mountains
                }
            }
        }
    }
     //Below returns the categorized landmass map.
    return FinalMap;
}

//below function prints the raw landmass data to a file and the console, formatting values in a grid.
void PrintRLand(int **Base , int DWidth , int DHeight , ofstream &File)
{
    // below iterates through the rows of the raw landmass data.
    for (int x= 0; x < DHeight;x++)
    {
         //below iterates through the columns of the raw landmass data.
        for (int y= 0; y < DWidth;y++)
        {
            //below writes the value from the raw landmass data to the file and console, formatted with 4 characters.
            File << setw(4) << Base[x][y];
            cout << setw(4) << Base[x][y];
        }
        
        //Below checks if the end of the file is not reached, then add a newline to the file and console.
        if(!File.eof()){
            File << endl;       
            cout << endl;
        }
    }
}


// The below function is responsible for printing a 2D map represented by a character array
// to the console with colorful text based on character types and saving the map to an
// output file.
void PrintPolishedLand(char **FinalMap , int DWidth , int DHeight , ofstream &File)
{
    //Below sets the text color to be used for printing using the termcolor library
    cout<<termcolor::colorize;
  
    //Below iterates through the 2D array representing the map, row by row.
    for (int x= 0; x < DHeight;x++)
    {
  
        //Below iterates through the elements in the current row
        for (int y= 0; y < DWidth;y++)
        {
           
           //Below checks the value at the current position in the map
           if((FinalMap[x][y]=='#')||(FinalMap[x][y]=='~')){
            //Below sets the text color to yellow for '#' and '~'
            cout<<termcolor::bright_yellow;
           }
           else if(FinalMap[x][y]=='.'){
            //Below sets the text color to blue for '.' 
            cout<<termcolor::bright_blue;
           
           }
           else if((FinalMap[x][y]=='-')||(FinalMap[x][y]=='*')){
            //Below sets the text color to green for '-' and '*' 
            cout<<termcolor::bright_green;
           
           }
           else{
            //Below sets the text color to red for any other character
            cout<<termcolor::bright_red;
           
           }
            //Below writes the current character to the output fil
            File << FinalMap[x][y];
             //Below prints the current character to the console
            cout << FinalMap[x][y];
        }

        //Below checks if the end of the input file has been reached
        if(!File.eof()){
           
           //Below writes a newline character to the output file and the console to move to the next row
            File << endl;       
            cout << endl;
        
        }
    }
}


// below function prints the normalized landmass data to a file and the console, formatting values in a grid.
void PrintNLand(int **Base , int DWidth , int DHeight , ofstream &File)
{
    //below iterates through the rows of the normalized landmass data.
    for (int x= 0; x < DHeight;x++)
    {
         //below iterates through the columns of the normalized landmass data.
        for (int y= 0; y < DWidth;y++)
        {
            // below writes the value from the normalized landmass data to the file and console, formatted with 4 characters.
            File << setw(4) << Base[x][y];
            cout << setw(4) << Base[x][y];
        }
         //below checks if the end of the file is not reached, then add a newline to the file and console.
        if(!File.eof()){
            File << endl;       
            cout << endl;
        }
    }
}