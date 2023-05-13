{
TH1F *histo = new
TH1F("histo","Histogram",10, 0, 80);
histo->SetTitle("Histogram for n=1");
TF1 *poisson = new TF1("poisson","[1]*[0]*x*TMath::Exp(-[0]*x)",0,80);
poisson->SetParameters(1, 30);
poisson->SetLineColor(kBlue);
poisson->SetLineWidth(5);
std::ifstream
file("/Users/Hazal/Desktop/poisson/analyses/part2/data/n1.tsv");
float datum;
while (file>>datum) histo->Fill(datum);
gStyle->SetOptFit(1111);
histo->Fit(poisson,"R+");
histo->GetXaxis()->SetTitle("Time difference between pulses (seconds)");
histo->GetYaxis()->SetTitle("Frequency of the time difference (seconds)^(-1)");
histo->Draw("HIST SAME E1");
}
