#include <iostream>
#include <fstream>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"

int main() {
    std::ifstream calibFile("./data/35kV-kalibrasyon.txt");
    std::string line;
    std::vector<std::string> calibData;

    if (calibFile.is_open()) {
        for (int i = 0; i < 3; i++) {
            getline(calibFile, line);
        }
        while (getline(calibFile, line)) {
            calibData.push_back(line);
        }
        calibFile.close();
    } 
    std::vector<double> theta;
    std::vector<double> intensity;
    for (std::vector<std::string>::iterator it = calibData.begin(); it != calibData.end(); it++) {
        std::string line = *it;
        int pos = line.find(" ");
        std::string thetaStr = line.substr(0, pos);
        std::string intensityStr = line.substr(pos + 1, line.length() - pos - 1);
        theta.push_back(stod(thetaStr));
        intensity.push_back(stod(intensityStr));
    }
    void plotGraph(std::vector<double>& theta, std::vector<double>& intensity)
{
    TGraph *graph = new TGraph(theta.size(), &theta[0], &intensity[0]);
    
    graph->SetTitle("Theta vs. Intensity");

    graph->GetXaxis()->SetTitle("Theta");
    graph->GetYaxis()->SetTitle("Intensity");

    TCanvas *canvas = new TCanvas("canvas", "Theta vs. Intensity", 800, 600);
    graph->Draw("APL");

    canvas->Print("theta_vs_intensity.pdf");
}
    

    return 0;
}
