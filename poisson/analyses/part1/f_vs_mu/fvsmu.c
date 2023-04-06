{
   TCanvas *c1 = new TCanvas();
   c1->SetWindowSize(1400, 900);


   TGraphErrors *mygraph = new TGraphErrors("/Users/Hazal/Desktop/fvsmu.tsv");
   mygraph->SetTitle("sqrt(mu)/sigma vs mu");
   mygraph->Draw("A*");



  TF1 *ffitline = new TF1("ffitline","[1]",0,150);
  ffitline->SetParameter(1,10e+4);
  ffitline->SetLineColor(kBlue);
  ffitline->Draw("same");
  mygraph->Fit(ffitline,"R");


  gStyle->SetOptFit(1111);

   mygraph->GetXaxis()->SetTitle("mu");
   mygraph->GetYaxis()->SetTitle("sqrt(mu)/sigma");



}








