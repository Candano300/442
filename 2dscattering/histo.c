{
TCanvas *c1 = new TCanvas();
c1->SetGrid();

TH1F *histo = new TH1F("histo", "Histogram", 18, 0, 360); // 17 bins for 17 data points
histo->SetTitle("Number of hits in each degree interval");
histo->GetXaxis()->SetTitle("Degree interval");
histo->GetYaxis()->SetTitle("Frequency of each hit");
histo->SetFillColor(kBlue); // set the fill color to blue
histo->SetLineColor(kBlack); 
histo->SetLineWidth(4);


std::ifstream file("/Users/Hazal/Desktop/rawdata.txt");
float datum;
int bin = 1;
while (file >> datum) {
    histo->SetBinContent(bin, datum); // set the bin content to the value of the data point
    bin++;
}


histo->Draw();
}


