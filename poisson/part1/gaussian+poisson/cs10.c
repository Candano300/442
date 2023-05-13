{
TH1F *histo = new
TH1F("histo","Histogram",10, 75, 140);
histo->SetTitle("Plot of Cs for 10 seconds");
TF1 *gauss_fit = new
TF1("gauss_fit","[0]*TMath::Gaus(x,[1],[2])",75,140);
gauss_fit->SetParameters(10,100,2);
gauss_fit->SetLineColor(kRed);
gauss_fit->SetLineWidth(5);
TF1 *poisson = new
TF1("poisson","[0]*TMath::Poisson(x,[1])",75,140);
poisson->SetParameters(25,100);
poisson->SetLineColor(kBlue);
poisson->SetLineWidth(5);
std::ifstream
file("/Users/Hazal/cs10.tsv");
float datum;
while (file>>datum) histo->Fill(datum);
gStyle->SetOptFit(1111);
histo->Fit(gauss_fit,"R+");
histo->Fit(poisson,"R+");
histo->GetXaxis()->SetTitle("Counts");
histo->GetYaxis()->SetTitle("Number of Counts");
histo->Draw("HIST SAME E1");
}



