{
  const int ndata = 5;

  float x[ndata] = { 1.5748031496062992e-06, 1.2987012987012988e-06, 1.904761904761905e-06, 1.5151515151515152e-06, 1.3071895424836602e-06};
  float y[ndata] = {267002.8658528325, 213830.31046498343, 334642.51822360774, 263242.3090637354, 215198.82095974757};
  float sy[ndata]= {1900.3762694151778, 1361.9764997769644, 2666.4742487936874, 1860.3696753620877, 1375.072338400943};

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
  mygraph->SetTitle("r = 2.00 cm");
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
  fnew->SetParameters(0,0); // arbitrary starting parameters
  mygraph->Fit(fnew);
  
}
