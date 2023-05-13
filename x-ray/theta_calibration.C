{
  ifstream file("./data/35kV-kalibrasyon.txt");

  vector<double> x_values;
  vector<double> y_values;
  string line;
  while (getline(file, line)) {
    double x, y;
    if (sscanf(line.c_str(), "%lf\t%lf", &x, &y) == 2) {
      x_values.push_back(x);
      y_values.push_back(y);
    }
  }
  //calculate sigma of theta 
  vector<double> sigma_x;
    for (int i = 0; i < x_values.size(); i++) {
        sigma_x.push_back(0.1);
    }

  vector<double> sigma_y;
  for (int i = 0; i < y_values.size(); i++) {
    sigma_y.push_back(sqrt( y_values[i]/5) );
  }

  TGraphErrors* data_with_unc = new TGraphErrors(x_values.size(), x_values.data(), y_values.data(), sigma_x.data(),sigma_y.data());
  TCanvas* c1 = new TCanvas();
  data_with_unc->GetXaxis()->SetRangeUser(0, 45);
  data_with_unc->SetTitle("Calibration Data at 35kV");
  data_with_unc->GetXaxis()->SetTitle("Crystal Degree (deg)");
  data_with_unc->GetYaxis()->SetTitle("Rate (imp/s)");
  data_with_unc->SetLineColor(kBlue);
  data_with_unc->Draw("AP");

  TGraph *datapoints = new TGraph(x_values.size(), x_values.data(), y_values.data());
  datapoints->SetMarkerStyle(8);
  datapoints->SetMarkerSize(0.5); 
  datapoints->SetMarkerColor(kBlack);
  datapoints->SetLineColor(kBlue);
  datapoints->SetLineWidth(5);
  datapoints->Draw("SAME PL");

  c1->SaveAs("./outputs/theta_calibration.svg");
  c1->SaveAs("./outputs/theta_calibration.png");

    data_with_unc->GetXaxis()->SetRangeUser(0, 27);



  TF1* gauss0 = new TF1("gaussian0", "gaus", 6.42, 6.74);
  gauss0 -> SetLineWidth(5);
  data_with_unc->Fit(gauss0,"R");
  gauss0->Draw("SAME");

  TF1* gauss1 = new TF1("gaussian", "gaus", 7.60, 7.90);
  gauss1 -> SetLineWidth(5);
  data_with_unc->Fit(gauss1,"R");
  gauss1->Draw("SAME");

  TF1* gauss2 = new TF1("gaussian2", "gaus", 13.25, 13.60);
  gauss2 -> SetLineWidth(5);
  data_with_unc->Fit(gauss2,"R");
  gauss2->Draw("SAME");

  TF1* gauss3 = new TF1("gaussian3", "gaus", 14.90, 15.20);
  gauss3 -> SetLineWidth(5);
  data_with_unc->Fit(gauss3,"R");
  gauss3->Draw("SAME");

  TF1* gauss4 = new TF1("gaussian4", "gaus", 19.90, 20.25);
  gauss4 -> SetLineWidth(5);
  data_with_unc->Fit(gauss4,"R");
  gauss4->Draw("SAME");

  TF1* gauss5 = new TF1("gaussian5", "gaus", 22.37, 23.00);
  gauss5 -> SetLineWidth(5);
  data_with_unc->Fit(gauss5,"R");
  gauss5->Draw("SAME");

  TLegend* legend = new TLegend(0.75,0.7,0.9,0.9);
  legend->SetTextSize(0.03);
  legend->AddEntry(datapoints, "Data points","p");
  legend->AddEntry(data_with_unc, "Uncertainty", "p");
  legend->AddEntry(gauss1, "Gaussian Fits", "l");
  //legend->Draw();

  gStyle->SetOptFit(1111);


  c1->SaveAs("./outputs/theta_calibration2.svg");
  c1->SaveAs("./outputs/theta_calibration2.png");


}