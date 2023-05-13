{
  TCanvas *c1 = new TCanvas();
  c1->SetCanvasSize(1400,900);
  TGraphErrors *mygraph = new
      TGraphErrors("/Users/Hazal/Desktop/School/442/Experiments/photoelectric/Analyses/Data/blue.tsv");
  mygraph->SetTitle("Photoelectric Current vs Retarding Potential for Blue Light");
  gStyle->SetImageScaling(3.);
  mygraph->Draw("AL*");
  TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0.000,0.500);
  ffitline->SetParameter(0,2);
  ffitline->SetParameter(1,3);
  ffitline->SetLineColor(kBlue);
  ffitline->Draw("same");
  mygraph->Fit(ffitline,"R+");
  TF1 *ffitline2 = new TF1("ffitline","[0]*x+[1]",1.5,300);
  ffitline2->SetParameter(0,2);
  ffitline2->SetParameter(1,3);
  ffitline2->SetLineColor(kGreen);
  ffitline2->Draw("same");
  mygraph->Fit(ffitline2,"R+");
  gStyle->SetOptFit(1111);
  mygraph->GetXaxis()->SetTitle("Potential (V)");
  mygraph->GetYaxis()->SetTitle("Current (pA)");


}

