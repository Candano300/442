{
TH1F *histo = new
TH1F("histo","Histogram",10, 0, 10);
histo->SetTitle("Plot of Ba for 1 second");
TF1 *gauss_fit = new
TF1("gauss_fit","[0]*TMath::Gaus(x,[1],[2])",0,25);
gauss_fit->SetParameters(30,2,2);
gauss_fit->SetLineColor(kRed);
gauss_fit->SetLineWidth(5);
TF1 *poisson = new
TF1("poisson","[0]*TMath::Poisson(x,[1])",0,25);
poisson->SetParameters(30,2);
poisson->SetLineColor(kBlue);
poisson->SetLineWidth(5);
std::ifstream
file("/Users/Hazal/ba1.tsv");
float datum;
while (file>>datum) histo->Fill(datum);
gStyle->SetOptFit(1111);
histo->Fit(poisson,"R+");
histo->GetXaxis()->SetTitle("Counts");
histo->GetYaxis()->SetTitle("Number of Counts");
histo->Draw("HIST SAME E1");
}
