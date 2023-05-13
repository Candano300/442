{
TCanvas *c1 = new TCanvas();
c1->SetGrid();


TGraphErrors *graph = new TGraphErrors("linefit_data.txt");
graph->SetTitle("# of shots vs sin(theta/2)");
graph->GetXaxis()->SetTitle("sin(theta/2)");
graph->GetYaxis()->SetTitle("# of shots");
graph->Draw("A*");

TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0,10);
ffitline->SetParameters(50,5);
ffitline->SetLineColor(kRed);
ffitline->SetLineWidth(4);
ffitline->Draw("Same");

graph->Fit(ffitline,"R+");
gStyle->SetOptFit(1111);
}