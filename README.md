# LandCrafter
LandCrafter is a terrain generation tool that simulates the impact of dirtballs on a 2D grid to create diverse landmasses. It categorizes the terrain based on water levels and generates visual maps representing deep water, shallow water, coast, plains, forest, and mountains.

## Features

- **Dirtball Impact:** Simulate the impact of dirtballs on the grid.
- **Terrain Categorization:** Categorize the landmass based on water levels.
- **Visual Maps:** Generate visual maps representing different types of terrain.

## How to Use

1. Clone the Repository:
   ```bash
   git clone https://github.com/your-username/LandCrafter.git
   cd LandCrafter
   ```
2. Compile and Run
   ```bash
   g++ Main.cpp -o LandCrafter
   ./LandCrafter
   ```
3. Provide Input
   Follow the prompts to enter grid dimensions, dirtball parameters, and other inputs.

4. View Results
 -  Raw Landmass Data: `raw_landmass.txt`
 -  Normalized Landmass Data: `normalized_landmass.txt`
 -  Final Landmass Map: `final_landmass.txt`

5. Command Line Options
   - Use `-s` to provide a seed for random number generation.
   - For Example
     ```bash
     ./LandCrafter -s 123
     ```


   
