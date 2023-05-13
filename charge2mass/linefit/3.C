// Line fitting macro written for ROOT
{
  const int ndata = 5;

  float x[ndata] = {2.580645161290323e-06, 3.007518796992481e-06, 2.4615384615384615e-06, 2.259887005649718e-06, 2.5641025641025644e-06};
  float y[ndata] = {448880.3337625808, 529269.8048203065, 428708.5419044482, 388851.2851741027, 444733.65543928527};
  float sy[ndata]= {4175.631011744938, 5346.1596446495605, 3897.3503809495287, 3366.677793715175, 4117.904217030419};


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
  mygraph->SetTitle("r = 4.00 cm");
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
