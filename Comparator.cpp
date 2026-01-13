#include <fstream>//don't change this line
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "header/Comparator.hpp"//include any other necessary headers like iostream,cmath ect above this line
using namespace std;
struct MaterialData {
    string name;
    double purchaseCost;
    double annualEnergyCost;
    double lifeCycleCost;
};
void Comparator()//don't change this line
{
// Material list
    string materials[] = {
        "glass","concrete","wood_stave","rubber","copper",
        "cast_iron","galvanized_iron","wrought_iron",
        "stainless_steel","commercial_steel"
    };

    vector<MaterialData> results;
    for (string mat : materials) {
        string filename = mat + "_financial_report.txt";
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Comparator: Could not open " << filename << endl;
            continue;
        }

        MaterialData data;
        data.name = mat;

        file >> data.purchaseCost;
        file >> data.annualEnergyCost;
        file >> data.lifeCycleCost;

        double pumpPower;
        file >> pumpPower;

        file.close();
        results.push_back(data);
    }

    // Sort materials by lifecycle cost (ascending)
    sort(results.begin(), results.end(),
        [](const MaterialData& a, const MaterialData& b) {
            return a.lifeCycleCost < b.lifeCycleCost;
        });

    if (results.size() < 3) {
        cout << "Comparator Error: Not enough data to rank materials." << endl;
        return;
    }

    // Write final recommendation file
    ofstream out("final_recommendation.txt");
    if (!out.is_open()) {
        cout << "Comparator Error: Cannot create final_recommendation.txt" << endl;
        return;
    }

    // Top 3 Buying Prices
    out << results[0].purchaseCost << endl;
    out << results[1].purchaseCost << endl;
    out << results[2].purchaseCost << endl;

    // Top 3 Material Names
    out << results[0].name << endl;
    out << results[1].name << endl;
    out << results[2].name << endl;

    // Top 3 Life-Cycle Costs
    out << results[0].lifeCycleCost << endl;
    out << results[1].lifeCycleCost << endl;
    out << results[2].lifeCycleCost << endl;

    // Top 3 Annual Energy Costs
    out << results[0].annualEnergyCost << endl;
    out << results[1].annualEnergyCost << endl;
    out << results[2].annualEnergyCost << endl;

    out.close();

    cout << "Comparator: final_recommendation.txt generated successfully." << endl;
}
