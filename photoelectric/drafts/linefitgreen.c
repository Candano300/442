{

      YELLOW = "\033[1;33m";
    RESET = "\033[0;0m";

  TCanvas *c1 = new TCanvas("green","green");
  TGraphErrors *mygraph = new
  
  TGraphErrors("/Users/Hazal/Desktop/School/442/Experiments/photoelectric/Analyses/Data/green.tsv");
  mygraph->SetTitle("Photoelectric Current vs Retarding Potential for Green Light");
  mygraph->GetXaxis()->SetTitle("Potential (V)");
  mygraph->GetYaxis()->SetTitle("Current (pA)");
  mygraph->Draw("AL*");
  TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0,0.3);
  ffitline->SetParameter(0,2);
  ffitline->SetParameter(1,3);
  ffitline->SetLineColor(kBlue);
  ffitline->Draw("same");
  mygraph->Fit(ffitline,"R+");
  TF1 *ffitline2 = new TF1("ffitline","[0]*x+[1]",0.6,3.0);
  ffitline2->SetParameter(0,2);
  ffitline2->SetParameter(1,3);
  ffitline2->SetLineColor(kRed);
  ffitline2->Draw("same");
  mygraph->Fit(ffitline2,"R+");
  gStyle->SetOptFit(1111);

 

}
