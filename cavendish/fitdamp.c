{
TCanvas *t1 = new TCanvas();
t1->SetGrid();

TGraphErrors *raw_data_graph = new TGraphErrors("/Users/Hazal/Desktop/cavendish/analysis/hazal-yagiz-merve.txt");
raw_data_graph->SetTitle("Fit for damping");
raw_data_graph->SetLineColor(kRed);
raw_data_graph->SetLineWidth(4);
raw_data_graph->Draw("AL");
raw_data_graph->GetXaxis()->SetTitle("Time (sec)");
raw_data_graph->GetYaxis()->SetTitle("Voltage (V)");



gStyle->SetOptFit(1111);
TF1 *sinfit = new TF1("exp_sine","[0]*TMath::Exp(-[1]*x)*TMath::Sin([2]*x+[3]) + [4]",2500,3000);
sinfit->SetParameters(5, 0.01, 0.01, 8, 9);
sinfit->SetLineColor(kBlue);
sinfit->SetLineWidth(5);
raw_data_graph->Fit(sinfit,"R+");
gStyle->SetOptFit(1111);


}