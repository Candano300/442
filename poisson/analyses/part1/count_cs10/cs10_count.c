{
TH1F *histo = new
TH1F("histo","Histogram",10, 50, 140);
histo->SetTitle("Histogram of Cs for 10 Seconds");
std::ifstream
file("/Users/Hazal/cs10.tsv");
float datum;
while (file>>datum) histo->Fill(datum);
gStyle->SetOptFit(1111);
histo->GetXaxis()->SetTitle("Counts");
histo->GetYaxis()->SetTitle("Number of Counts");
histo->Draw("HIST SAME E1");
}




