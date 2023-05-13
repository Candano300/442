{
   TCanvas *c1 = new TCanvas();
   c1->SetWindowSize(1400, 900);


   TGraphErrors *mygraph = new TGraphErrors("/home/acer/Desktop/0_PHYS442/4th_Week_4th_exp/raw_data/Vs.txt");
   mygraph->SetTitle("Stopping Energy vs Frequency");
   mygraph->Draw("A*");



  TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",510e+12,750e+12);
  ffitline->SetParameter(0,1e-34);
  ffitline->SetParameter(1,2e-19);
  ffitline->SetLineColor(kBlue); // draw in blue color
//   ffitline->SetLineStyle(2); // draw dotted line
  ffitline->Draw("same");
  mygraph->Fit(ffitline,"R");


//   // let's also try the same with ROOT's own fitter
//   TF1 *fnew = new TF1("fnew","[0]*x+[1]",8.5,9.5);
//   fnew->SetParameters(3.1416,2.7182); // arbitrary starting parameters
//   mygraph->Fit(fnew);
  

   mygraph->GetXaxis()->SetTitle("Frequencey(10^14 Hz)");
   mygraph->GetYaxis()->SetTitle("Energy qV (keV)");


   // mygraph->GetXaxis()->SetLimits(7.5, 11);

   // mygraph->SetMinimum(-30);
   // mygraph->SetMaximum(160);
}



   // TF1 *gauss_draw = new TF1("gauss_draw","95*TMath::Gaus(x,153,15)",145,175);
   // gauss_draw->SetLineColor(kBlue);
   // gauss_draw->SetLineWidth(5);
   // gauss_draw->Draw("same");


   // TF1 *gauss_fit = new TF1("gauss_fit","[0]*TMath::Gaus(x,[1],[2])",80,130);
   // gauss_fit->SetParameters(150,100,20);
   // gauss_fit->SetLineColor(kGreen);
   // gauss_fit->SetLineWidth(5);
   // mygraph->Fit(gauss_fit,"R");
 


   // TF1 *expo_fit = new TF1("expo_fit","[3]*exp([4]*x)",0,60);
   // expo_fit->SetParameters(100,0.5);
   // expo_fit->SetLineColor(kRed);
   // expo_fit->SetLineWidth(5);
   // mygraph->Fit(expo_fit,"R+");






