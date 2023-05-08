{
gSystem->RedirectOutput("../outputs/linefits/txt/linefits.txt", "w");

cout << "\n------------------------------------------------------------------------------" << endl;
cout << "\n15kV\n" << endl;

ifstream f; 
f.open("../data/15kV.txt");
vector<double> thetas;
vector<double> rate;
string line;


while (getline(f, line)) {
  double x, y;
  if (sscanf(line.c_str(), "%lf\t%lf", &x, &y) == 2) {
    thetas.push_back(x);
    rate.push_back(y);
  }
}
f.close();

//first, we need to calibrate thetas, and also convert them to radians for the sin() function
// to work properly, since we will use the wavelengths as the x axis in the graph
vector<double> calibrated_thetas;
for (auto it = thetas.begin(); it != thetas.end(); it++) {
auto calibrated = 0.989902 * (*it) - 0.26433 ;
auto calibrated_radians = calibrated * M_PI/ 180.0; // convert to radians
calibrated_thetas.push_back(calibrated_radians);
}

// then, we need to find the wavelength of each theta by Bragg's law:
d = 2.82e-10; // lattice spacing in meters
n = 1 ; // order of diffraction
vector<double> wavelengths;
for(auto it = calibrated_thetas.begin(); it != calibrated_thetas.end(); it++) {
  auto bragg = 2*n*(sin(*it))*d; 
  // Scaling the graph of ROOT is impossible with values this small, 
  // so we need to convert the wavelength to nm.
  // 1 nm = 1e-9 meters
  auto bragg_in_nm = bragg * 1e9;
  wavelengths.push_back(bragg_in_nm);
}

vector<double> sigma_y;
for (int i = 0; i < rate.size(); i++) {
  sigma_y.push_back(sqrt( rate[i]/5) );
}

vector<double> sigma_x;  //sigma x == sigma lambda 
double sigma_calibrated_thetas = 0.989902 * 0.1;
for (int i = 0;  i< rate.size(); i++){
    double sigma = 2 * d * cos(calibrated_thetas[i]) * sigma_calibrated_thetas;
    sigma_x.push_back(sigma);
}


TCanvas *c1 = new TCanvas();

TGraph *datapoints = new TGraph(wavelengths.size(), wavelengths.data(), rate.data());
datapoints->SetTitle("Linefit at 15kV");
datapoints->GetXaxis()->SetTitle("Wavelength (nm)");
datapoints->GetYaxis()->SetTitle("Rate (imp/s)");
datapoints->GetXaxis()->SetRangeUser(0.025, 0.089);
datapoints->GetYaxis()->SetRangeUser(0.00, 23);
datapoints->SetMarkerStyle(8);
datapoints->SetMarkerSize(0.8); 
datapoints->SetMarkerColor(kBlack);
datapoints->SetLineColor(kBlue);
datapoints->SetLineWidth(4);
datapoints->Draw("APL");

TGraphErrors *data= new TGraphErrors(wavelengths.size(), wavelengths.data(), rate.data(), sigma_x.data() , sigma_y.data());
data->SetLineColor(kBlue);
data->SetLineWidth(1);
data->Draw("SAME P");


TF1* linefit = new TF1("linefit", "[0]*x+[1]", 0.081, 0.1);
linefit->SetLineWidth(5);
linefit->SetLineColor(kRed);
linefit->SetMarkerStyle(8);
datapoints->Fit(linefit, "R", "", 0.078, 0.085);
linefit->Draw("SAME");

gStyle->SetOptFit(1111);


//Let's also calculate an approximate h value to check whether the fit is correct: 
double slope = linefit->GetParameter(0);
double intercept = linefit->GetParameter(1);
double lambda_min = -(intercept/slope) * 1e-9; // convert nm to m
double c = 3e8; // speed of light
double f_max = c / lambda_min;
double e = 1.602e-19; // electron charge
double V = 15e3; // voltage
double h_approx = e*V/f_max;
cout << "\nApproximate value of Planck's constant: " << h_approx << endl;
cout << "Actual value of Planck's constant: " << 6.626e-34 << endl;
//

gSystem->RedirectOutput(0);
c1->SaveAs("../outputs/linefits/images/svg/15kV.png");
c1->SaveAs("../outputs/linefits/images/pdf/15kV.pdf");
c1->Close();

}