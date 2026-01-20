#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include "header/DataPrep.hpp"
#include "header/PhysicsEngine.hpp"
#include "header/ComponentAnalyzer.hpp"
#include "header/CostCalculator.hpp"
#include "header/Comparator.hpp"
using namespace std;
namespace fs = experimental::filesystem;

void clearFile(string filename) {
    ofstream ofs(filename, ios::trunc);
    ofs.close();}

int main() {
  string material[] = {"glass","concrete","wood_stave","rubber","copper","cast_iron","galvanized_iron","wrought_iron","stainless_steel","commercial_steel"};
  string archivename;
    for(int i = 0; i<(sizeof(material)/sizeof(material[0]));i++){
    DataPrep(material[i]);
    PhysicsEngine();
    bool safety = ComponentAnalyzer();

    if ( safety == false){
        clearFile("clean_data.txt");
        clearFile("physics_results.txt");
        clearFile("total_loss.txt");
        continue;
    }
        
    CostCalculator();
    archivename = material[i] + "_financial_report.txt";
    if (fs::exists("financial_report.txt")) {
            fs::copy_file("financial_report.txt", archivename, fs::copy_options::overwrite_existing);} 
    else {
            cout<< "Error: financial_report.txt was not found for " << material[i] << endl;}
        clearFile("clean_data.txt");
        clearFile("physics_results.txt");
        clearFile("total_loss.txt");
        clearFile("financial_report.txt");
    }
Comparator();
for(int i = 0; i<(sizeof(material)/sizeof(material[0])); i++){
        string fileToDelete = material[i] + "_financial_report.txt";
        if (fs::exists(fileToDelete)) {
            fs::remove(fileToDelete);}}
}
