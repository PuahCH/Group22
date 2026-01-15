#include <fstream>//don't change this line
#include "header/CostCalculator.hpp"//include any other necessary headers like iostream,cmath ect above this line
using namespace std;
void CostCalculator()//don't change this line
{
    // Variables from input files
    double minorHeadLoss;
    double totalHeadLoss;
    double totalPressureDrop;
    double roughness;
    double fluidDensity;
    double viscosity;
    double cost;
    double maxPressure;

    //Defines the function interfaces for cost calculations
    double purchaseCost;
    double pumpPower_kW;
    double annualEnergyCost;
    double pumpPower;
    double tenYearCost;

    //Variables from user input file
    double flowRate;
    double pipeLength;

    // Fixed constant
    double gravity = 9.81;   
  
    //Assumption valuue                 
    double pumpEfficiency = 1; //Assume 100% pump efficiency
    double electricityPrice = 0.50; // RM/kWh  
    
    //Read user_input.txt
    ifstream userinputFile("user_input.txt");
    if (!userinputFile)
    {
        cout << "Error: Cannot open user_input.txt" << endl;
     
    }

    userinputFile >> flowRate;
    userinputFile >> pipeLength;
    userinputFile.close();

    // Read total_loss.txt
    ifstream totalLossFile("total_loss.txt");
    if (!totalLossFile)
    {
        cout << "Error: Cannot open total_loss.txt" << endl;
       
    }

    totalLossFile >> minorHeadLoss;
    totalLossFile >> totalHeadLoss;
    totalLossFile >> totalPressureDrop;
    totalLossFile.close();

    // Read clean_data.txt
    ifstream cleanDataFile("clean_data.txt");
    if (!cleanDataFile)
    {
        cout << "Error: Cannot open clean_data.txt" << endl;
       
    }

    cleanDataFile >> viscosity;
    cleanDataFile >> fluidDensity;
    cleanDataFile >> roughness;
    cleanDataFile >> cost;
    cleanDataFile >> maxPressure;
    cleanDataFile.close();

    // Calculations

    // Purchase Cost
    purchaseCost = cost * pipeLength;

   // Pump Power (W)
    pumpPower = (fluidDensity * gravity * flowRate * totalHeadLoss) / pumpEfficiency;
    
    // Convert to kW
    pumpPower_kW = pumpPower / 1000.0;
    // Annual Energy Cost
    annualEnergyCost = pumpPower_kW * 24 * 365 * electricityPrice;

    // 10-Year total lifecycle cost
    tenYearCost = purchaseCost + (annualEnergyCost * 10);

    
    ofstream reportFile("financial_report.txt");
    if (!reportFile)
    {
        cout << "Error: Cannot create financial_report.txt" << endl;
        
    }

    reportFile << purchaseCost << endl;
    reportFile << annualEnergyCost << endl;
    reportFile << tenYearCost << endl;
    reportFile << pumpPower << endl;

    reportFile.close();
   
}

