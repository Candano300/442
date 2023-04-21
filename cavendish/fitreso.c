{
TCanvas *c1 = new TCanvas();
c1->SetGrid();


TGraphErrors *raw_data_graph = new TGraphErrors("/Users/Hazal/Desktop/cavendish/analysis/hazal-yagiz-merve.txt");
raw_data_graph->SetTitle("Fit for resonance");
raw_data_graph->SetLineColor(kRed);
raw_data_graph->SetLineWidth(4);
raw_data_graph->GetXaxis()->SetTitle("Time (sec)");
raw_data_graph->GetYaxis()->SetTitle("Voltage (V)");
raw_data_graph->Draw("AL");


//Now, we fit the data with a sine function: 
TF1 *sinfit = new TF1("sinfit","[3]+[0]*TMath::Sin([1]*x+[2])",1850,2050);
sinfit->SetParameters(1, 0.01, 8, 9);
sinfit->SetLineColor(kBlue);
sinfit->SetLineWidth(7);
raw_data_graph->Fit(sinfit,"R+");
gStyle->SetOptFit(1111);

}