{

// As calculated in the analysis .ipynb ; 

vector<double> energy    = {2.40326493e-15, 2.88391792e-15, 3.36457090e-15, 3.84522389e-15,4.32587687e-15, 4.80652986e-15}; // in eV
vector<double> frequency = {3.80579292e+18, 4.52782309e+18, 5.39316662e+18, 5.84710261e+18, 6.93321739e+18, 7.98233309e+18}; // in Hz
vector<double> sigma_frequency = {5.62556001e+17, 2.28775675e+17, 2.09294738e+17, 1.04899928e+17,1.93262716e+17, 4.57393450e+17};


TGraphErrors *errors = new TGraphErrors(frequency.size(), frequency.data(), energy.data(),sigma_frequency.data(),0);
errors->SetTitle("Energy vs Frequency");
errors->GetXaxis()->SetTitle("Frequency (Hz)");
errors->GetYaxis()->SetTitle("Energy (eV)");
errors->GetXaxis()->SetLimits(0, 0.12e20); //only way to show x axis in the scope of x10^{18} 
errors->SetMarkerColor(kBlack);
errors->SetMarkerStyle(20);
errors->SetMarkerSize(0.5);
errors->SetLineColor(kBlue);
errors->Draw("AP");

TF1 *fit = new TF1("fit", "[0]*x+[1]", 0, 0.12e20);
fit->SetLineColor(kRed);
fit->SetLineWidth(5);
//fit->SetParameter(0,6);
//fit->SetParameters(1,1);
fit->SetParameter(0,6.626e-34);
fit->SetParameter(1,4e-18);
fit->SetParLimits(0, 0, 7e-34);
fit->SetParLimits(1, 0.0, 5e-18);
errors->Fit(fit, "M"," ", 3e18,8e18);
fit->Draw("SAME");

gStyle->SetOptFit(1111);

c1->SaveAs("./outputs/evsf.png");
c1->SaveAs("./outputs/evsf.svg");
c1->SaveAs("./outputs/evsf.pdf");




}   