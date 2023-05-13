
void makegraph(string filepath, string title ,vector<vector<double>>& fitparams){
cout <<"\n"<<yellow<< title <<reset<< "\n\n";


ifstream file;
file.open(filepath);

vector<double> U_2;
vector<double> I;


// skip the first few rows of the data:
string line;
for (int i = 0; i < 15; i++) {
    getline(file, line);
}

//start reading the data
while (getline(file, line)) {
    istringstream iss(line);
    string element;
    int count = 0;
    while (iss >> element) {
        count++;
        if (count == 4) { // 4th column is I
            I.push_back(stod(element) ); // be careful, it is in nA! 
        }
        if (count == 5){ // 5th column is U_2
            U_2.push_back(stod(element));
        }

    }
}

//Before starting to plot the graph, we also need the uncertainties, which is given as; 
vector<double> s_U_2(U_2.size(),0.05);
vector<double> s_I(I.size(),0.015); //it is in nA!


//Now we can plot the graph;
TCanvas *c1 = new TCanvas(title.c_str(),title.c_str()) ;
c1-> SetGrid();
TGraph *errors = new TGraphErrors(U_2.size(), U_2.data(),I.data(),s_U_2.data(),s_I.data());
string graph_title = "I vs U_{2} for " + title ;
errors->SetTitle(graph_title.c_str());
errors->GetXaxis()->SetTitle("U_{2} (V)");
errors->GetYaxis()->SetTitle("I (A)");

double max_U = *max_element(U_2.begin(), U_2.end());
double max_I = *max_element(I.begin(), I.end());
double min_U = *min_element(U_2.begin(), U_2.end());
double min_I = *min_element(I.begin(), I.end());

errors->GetYaxis()->SetRangeUser(min_I , max_I*1.1);
errors->GetXaxis()->SetRangeUser(min_U , max_U);
errors->SetMarkerColor(kBlue);
errors->SetLineColor(kBlue);
errors->SetLineWidth(4);
errors->Draw("APL");


TGraph *data = new TGraph(U_2.size(), U_2.data(),I.data());
data->SetMarkerSize(0.8);
data->SetMarkerStyle(2);
data->SetMarkerColor(kBlack);
data->Draw("SAME P");

//gStyle->SetOptFit(1111);



//generate an output file to store the fit parameters:
string output_file = "./output/gaussfits/" + title  + ".txt";
FILE *fp = fopen(output_file.c_str(),"w");
fprintf(fp,"mean\t\ts_mean\t\tsigma\t\ts_sigma\n");

// apply gaussian fit:
for(int i=0; i<fitparams.size(); i++){
    vector<double> gfitval = fitparams[i];
    TString name = Form("g%d", i+1);
    TF1 *g = new TF1(name, "gaus", gfitval[0], gfitval[1]);
    g->SetLineColor(kRed);
    g->SetLineWidth(5);
    errors->Fit(name, "R+");

    //this part is to generate a .txt file 
    for (int j = 1; j <= 2; j++) {
        Float_t value = g->GetParameter(j);
        Float_t error = g->GetParError(j);
        if (j == 1) {
            fprintf(fp, "%f\t%f\t", value, error);
        }if (j == 2) {
            fprintf(fp, "%f\t%f\n", value, error);
        }
}

}


fclose(fp);


};
