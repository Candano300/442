{

    YELLOW = "\033[1;33m";
    RESET = "\033[0;0m";
  TCanvas *c1 = new TCanvas("violet","violet");
  TGraphErrors *mygraph = new
  TGraphErrors("~/Desktop/School/442/Experiments/photoelectric/Analyses/Data/violet.tsv");
  mygraph->SetTitle("Photoelectric Current vs Retarding Potential for Violet Light");
  mygraph->GetYaxis()->SetTitle("Current (pA)");
  mygraph->GetXaxis()->SetTitle("Potential (V)");
  mygraph->Draw("AL*");
  TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0,0.5);
  ffitline->SetParameter(0,2);
  ffitline->SetParameter(1,3);
  ffitline->SetLineColor(kBlue);
  ffitline->Draw("same");
  mygraph->Fit(ffitline,"R+");
  TF1 *ffitline2 = new TF1("ffitline","[0]*x+[1]",1.1,2.5);
  ffitline2->SetParameter(0,2);
  ffitline2->SetParameter(1,3);
  ffitline2->SetLineColor(kRed);
  ffitline2->Draw("same");
  mygraph->Fit(ffitline2,"R+");
  gStyle->SetOptFit(1111);


}

