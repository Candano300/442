{

    // Values from the output of calibration.c 
    vector<double> experimental_theta = {6.60858, 7.73428, 13.417  , 15.0649 , 20.0906 , 22.6886 };
    vector<double> experimental_sigma_theta = {7.33008e-02,0.0550475, 0.0600465, 0.0537266, 0.0555138, 0.0389494};
    vector<double> theoretical_theta = { 6.43695807,  7.24700782, 12.95700727, 14.61332023, 19.65342192,22.23717828};


    TCanvas *c1 = new TCanvas();



    TGraphErrors* expvstheo = new TGraphErrors(experimental_theta.size(), experimental_theta.data(), theoretical_theta.data(), experimental_sigma_theta.data());
    expvstheo-> SetTitle("Experimental vs Theoretical Angles");
    expvstheo->GetXaxis()->SetTitle("Experimental Angle (deg)");
    expvstheo->GetYaxis()->SetTitle("Theoretical Angle (deg)");
    expvstheo->SetMarkerStyle(8);
    expvstheo->SetMarkerSize(0.3);
    expvstheo->SetMarkerColor(kBlack);
    expvstheo->Draw("AP");    

    TGraph *datapoints = new TGraph(experimental_theta.size(), experimental_theta.data(), theoretical_theta.data());
    datapoints->SetMarkerStyle(8);
    datapoints->SetMarkerSize(0.3);
    datapoints->SetMarkerColor(kBlack);
    datapoints->SetLineColor(kBlack);
    datapoints->Draw("SAME P");
    

    TF1* line = new TF1("linefit", "[0]*x+[1]", 0, 30);
    line->SetParameters(1,1);
    line->SetLineWidth(5);
    line->SetLineColor(kRed);
    line->SetMarkerStyle(8);
    datapoints->Fit(line);
    line->Draw("SAME");

    gStyle->SetOptFit(1111);

    c1->SaveAs("./outputs/plot-angles.png");
    c1->SaveAs("./outputs/plot-angles.svg");
    c1->SaveAs("./outputs/plot-angles.pdf");

}