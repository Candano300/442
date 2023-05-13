// Line fitting macro written for ROOT
{
  const int ndata = 5;

  float x[ndata] = {1.2893982808022922e-06, 2.0454545454545453e-06, 2.616279069767442e-06, 1.6728624535315985e-06, 1.991150442477876e-06};
  float y[ndata] = {211796.52163618387, 345680.8567792635, 457349.58734323655, 280459.1996671617, 334663.85103748797};
  float sy[ndata]= {1353.3324066209832, 2821.884545136845, 4294.362322471705, 2062.19999755266, 2688.063060542072};


  float weight = 0;
  float totw = 0; // Total weight
  float xybar = 0, xbar = 0, ybar = 0, x2bar = 0; // weighted averages

  for (int i=0; i<ndata; ++i) {
    weight = 1./(sy[i]*sy[i]);
    totw += weight;
    xybar += (x[i]*y[i]*weight);
    xbar += (x[i]*weight);
    ybar += (y[i]*weight);
    x2bar += (x[i]*x[i]*weight);
  }

  xybar /= totw;
  xbar /= totw;
  ybar /= totw;
  x2bar /= totw;

  float sy2bar = ndata / totw; // weighted average error squared
  float slope = (xybar - xbar*ybar) / (x2bar - xbar*xbar);
  float itcpt = ybar - slope * xbar;
  float slopeerr = sqrt ( sy2bar / (ndata * (x2bar - xbar*xbar) ) );
  float itcpterr = sqrt ( x2bar ) * slopeerr;
  cout << "slope of fit line = " << slope << " +- " << slopeerr << endl;
  cout << "intercept of fit line = " << itcpt << " +- " << itcpterr << endl;

  TGraphErrors *mygraph = new TGraphErrors(ndata,x,y,0,sy);
  mygraph->SetTitle("r = 3.00 cm");
  mygraph->GetXaxis()->SetTitle("R^2/2V (m^2/V)");
  mygraph->GetYaxis()->SetTitle("1/B^2 (T^-2)");
  mygraph->Draw("A*");


  gStyle->SetOptFit(1111);
  
  TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0,6);
  ffitline->SetParameter(0,slope);
  ffitline->SetParameter(1,itcpt);
  ffitline->SetLineColor(kBlue); // draw in blue color
  ffitline->SetLineStyle(2); // draw dotted line
  ffitline->Draw("same");

  // let's also try the same with ROOT's own fitter
  TF1 *fnew = new TF1("fnew","[0]*x+[1]",0,6);
  fnew->SetParameters(3.1416,2.7182); // arbitrary starting parameters
  mygraph->Fit(fnew);
  
}
