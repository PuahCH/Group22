#include <iostream>
#include "DataPrep.hpp"
#include "PhysicsEngine.hpp"
#include "header/ComponentAnalyzer.hpp"
#include "header/CostCalculator.hpp"
#include "header/Comparator.hpp"

int main() {
    runDataPrep();        
    runPhysicsEngine();   
    runComponentCalc();   
    runEconomicsCalc();   
    runComparator();      
}
