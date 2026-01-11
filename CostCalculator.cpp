#include <fstream>//don't change this line
#include "header/CostCalculator.hpp"//include any other necessary headers like iostream,cmath ect above this line
void CostCalculator()//don't change this line
{
    // Variables from input files
    double minorHeadLoss;
    double totalHeadLoss;
    double totalPressureDrop;
    double roughness;
    double density;
    double viscosity;
    double cost;
    double maxPressure;

    //Defines the function interfaces for cost calculations
    double purchaseCost;
    double pumpPower_kW;
    double annualEnergyCost;
    double pumpPower;
    double annualEnergyCost;
    double tenYearCost;
    
    double pipelength;
    cout << "Please enter the length of the pipe: "<<endl;
    cin >> pipelength;
  
    // Fixed constant
    double fluidDensity = 1000.0; 
    double gravity = 9.81;   
  
    //Assumption valuue
    double flowRate = 0.01;  //Assume                
    double pumpEfficiency = 1; //Assume 100% pump efficiency
    double electricityPrice = 0.50; // RM/kWh  

    // Read total_loss.txt
    ifstream totalLossFile("total_loss.txt");
    if (!totalLossFile)
    {
        cout << "Error: Cannot open total_loss.txt" << endl;
        return;
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
        return;
    }

    cleanDataFile >> roughness;
    cleanDataFile >> density;
    cleanDataFile >> viscosity;
    cleanDataFile >> cost;
    cleanDataFile >> maxPressure;
    cleanDataFile.close();

    // Calculations

    // Purchase Cost
    purchaseCost = cost * pipeLength;

    // Convert to kW
    pumpPower_kW = pumpPower / 1000.0;
    // Annual Energy Cost
    annualEnergyCost = pumpPower_kW * 24 * 365 * electricityPrice;
  
    // Pump Power (W)
    pumpPower = (fluidDensity * gravity * flowRate * totalHeadLoss) / pumpEfficiency;

    // Annual Energy Cost
    annualEnergyCost = pumpPower_kW * 24 * 365 * electricityPrice;

    // 10-Year total lifecycle cost
    tenYearCost = purchaseCost + (annualEnergyCost * 10);

    
    ofstream reportFile("financial_report.txt");
    if (!reportFile)
    {
        cout << "Error: Cannot create financial_report.txt" << endl;
        return;
    }

    reportFile << purchaseCost << endl;
    reportFile << annualEnergyCost << endl;
    reportFile << tenYearCost << endl;
    reportFile << pumpPower << endl;

    reportFile.close();

    cout << "CostCalculator: financial_report.txt is generated." << endl;
}

