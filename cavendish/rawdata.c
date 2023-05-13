{
TCanvas *t1 = new TCanvas();
t1->SetGrid();

TGraphErrors *raw_data_graph = new TGraphErrors("/Users/Hazal/Desktop/cavendish/analysis/hazal-yagiz-merve.txt");
raw_data_graph->SetTitle("Raw Data");
raw_data_graph->SetLineColor(kRed);
raw_data_graph->SetLineWidth(4);
raw_data_graph->Draw();
raw_data_graph->GetXaxis()->SetTitle("Time (sec)");
raw_data_graph->GetYaxis()->SetTitle("Voltage (V)");
}