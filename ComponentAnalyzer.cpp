#include <fstream> // don't change this line
#include <iostream>
#include <cmath>
#include <string>
#include "header/ComponentAnalyzer.hpp" // don't change this line

using namespace std;

bool ComponentAnalyzer() // don't change this line
{
    // Constants
    const double g = 9.81;

    // Variables from physics_results.txt
    double velocity, reynolds, frictionFactor, majorHeadLoss;

    // Variables from user_fittings.txt
    int elbow90, elbow45, gateValve, teeBranch, teeThrough, swingCheck;

    // Variables from clean_data.txt
    double viscosity, density, roughness, cost, maxPressure;

    // -------------------- Read physics_results.txt --------------------
    ifstream physicsFile("physics_results.txt");
    if (!physicsFile.is_open()) {
        cout << "Error: physics_results.txt not found!" << endl;
        return false;
    }

    physicsFile >> velocity;
    physicsFile >> reynolds;
    physicsFile >> frictionFactor;
    physicsFile >> majorHeadLoss;
    physicsFile.close();

    // -------------------- Read user_fittings.txt --------------------
    ifstream fittingsFile("user_fittings.txt");
    if (!fittingsFile.is_open()) {
        cout << "Error: user_fittings.txt not found!" << endl;
        return false;
    }

    fittingsFile >> elbow90;
    fittingsFile >> elbow45;
    fittingsFile >> gateValve;
    fittingsFile >> teeBranch;
    fittingsFile >> teeThrough;
    fittingsFile >> swingCheck;
    fittingsFile.close();

    // -------------------- Read clean_data.txt --------------------
    ifstream cleanDataFile("clean_data.txt");
    if (!cleanDataFile.is_open()) {
        cout << "Error: clean_data.txt not found!" << endl;
        return false;
    }

    cleanDataFile >> viscosity;
    cleanDataFile >> density;
    cleanDataFile >> roughness;
    cleanDataFile >> cost;
    cleanDataFile >> maxPressure;
    cleanDataFile.close();

    // -------------------- K-values (Textbook Standard) --------------------
    double K_elbow90 = 0.9;
    double K_elbow45 = 0.4;
    double K_gateValve = 0.15;
    double K_teeBranch = 1.8;
    double K_teeThrough = 0.6;
    double K_swingCheck = 2.0;

    // -------------------- Minor Head Loss --------------------
    double velocityHead = (velocity * velocity) / (2 * g);

    double minorHeadLoss = 
        (elbow90 * K_elbow90 +
         elbow45 * K_elbow45 +
         gateValve * K_gateValve +
         teeBranch * K_teeBranch +
         teeThrough * K_teeThrough +
         swingCheck * K_swingCheck) * velocityHead;

    // -------------------- Total Head Loss --------------------
    double totalHeadLoss = majorHeadLoss + minorHeadLoss;

    // -------------------- Pressure Drop --------------------
    double pressureDrop = density * g * totalHeadLoss;

    // -------------------- Safety Check --------------------
    bool isSafe;
    string safetyText;

    if (pressureDrop <= maxPressure) {
        isSafe = true;
        safetyText = "SAFE";
    } else {
        isSafe = false;
        safetyText = "UNSAFE";
    }

    // -------------------- Write total_loss.txt --------------------
    ofstream outFile("total_loss.txt");
    if (!outFile.is_open()) {
        cout << "Error: Cannot create total_loss.txt" << endl;
        return false;
    }

    outFile << minorHeadLoss << endl;
    outFile << totalHeadLoss << endl;
    outFile << pressureDrop << endl;
    outFile << safetyText << endl;

    outFile.close();

    return isSafe;
}
