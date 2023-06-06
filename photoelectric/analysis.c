{
    string YELLOW = "\033[1;33m";
    string RESET = "\033[0;0m";



    string dataDirectory = "./data/";
    vector< vector<double> > parameters = {
        {0.0, 0.35, 0.7, 3.0}, //turq
        {0.0, 0.3, 1.5, 3.0}, // yellow
        {0.0, 0.5, 1.2, 3.0}, // blue
        {0.0, 0.2, 1.1, 3.0}, // green
        {0.05, 0.8, 0.9, 3.0} // violet
    };

    vector<double> y1;
    vector<double> y2;
    vector<double> x1;
    vector<double> x2;
    vector<double> sigma_y1;
    vector<double> sigma_y2;
    vector<double> sigma_x1;
    vector<double> sigma_x2;


    vector<string> frequency_names;
    int counter = 0;
    for (const auto& entry : filesystem::directory_iterator(dataDirectory)) {
        string filePath = entry.path().string();
        string filename = entry.path().filename().stem().string();
        frequency_names.push_back(filename);
        cout << YELLOW << "\n" << filename << RESET << endl;

        TCanvas *c1 = new TCanvas(filename.c_str(), filename.c_str());
        TGraphErrors *mygraph = new TGraphErrors(filePath.c_str());
        mygraph->SetTitle(("Photoelectric Current vs Retarding Potential for " + filename + " Light").c_str());
        mygraph->GetXaxis()->SetTitle("Potential (V)");
        mygraph->GetYaxis()->SetTitle("Current (pA)");
        mygraph->Draw("AL*");

        vector <double> rangeParams = parameters[counter];
        TF1 *ffitline1 = new TF1("ffitline1", "[0]*x+[1]", rangeParams[0], rangeParams[1]);
        ffitline1->SetLineColor(kBlue);
        mygraph->Fit(ffitline1, "R+");
        ffitline1->Draw("SAME");

        y1.push_back(ffitline1->GetParameter(0));
        x1.push_back(ffitline1->GetParameter(1));
        sigma_y1.push_back(ffitline1->GetParError(0));
        sigma_x1.push_back(ffitline1->GetParError(1));

        TF1 *ffitline2 = new TF1("ffitline2", "[0]*x+[1]", rangeParams[2], rangeParams[3]);
        ffitline2->SetLineColor(kRed);
        mygraph->Fit(ffitline2, "R+");
        ffitline2->Draw("SAME");

        y2.push_back(ffitline2->GetParameter(0));
        x2.push_back(ffitline2->GetParameter(1));
        sigma_y2.push_back(ffitline2->GetParError(0));
        sigma_x2.push_back(ffitline2->GetParError(1));

        gStyle->SetOptFit(1111);
        counter ++ ;

        c1->SaveAs(("./output/" + filename + ".png").c_str());

    }

    for (int i = 0; i < y1.size(); i++) {
        y1[i] *= 1e-12;
        y2[i] *= 1e-12;
        x1[i] *= 1e-12;
        x2[i] *= 1e-12;
        sigma_y1[i] *= 1e-12;
        sigma_y2[i] *= 1e-12;
        sigma_x1[i] *= 1e-12;
        sigma_x2[i] *= 1e-12;
    }

    double V;
    double sigma_V_square;
    double sigma_V;
    vector<double> sigma_V_s;

    cout << YELLOW << "\n" << '\t'<< '\t'<<  "V" << '\t' <<'\t' << "V Error" << RESET << endl;
    vector<double> V_s ;
    for (int i = 0; i < x1.size(); i++){

        V = (x2[i] - x1[i]) / (y1[i] - y2[i]);
        V_s.push_back(V*(1.60217e-19));

        sigma_V_square = pow( (x2[i] - x1[i] / pow(y1[i] - y2[i], 2) ), 2) *  pow(sigma_x1[i],2) 
        + pow( (x2[i] - x1[i] / pow(y1[i] - y2[i], 2) ), 2) *  pow(sigma_x2[i],2)
        + pow(  1 / (y1[i] - y2[i])  , 2) *  pow(sigma_y1[i],2)
        + pow(  1 / (y1[i] - y2[i])  , 2) *  pow(sigma_y2[i],2);
        sigma_V = sqrt(sigma_V_square)*(1.60217e-19);
        sigma_V_s.push_back(sigma_V);

        cout << YELLOW << std::setw(8) << left << frequency_names[i] << RESET;
        cout << '\t' << V * (1.60217e-19);
        cout << '\t' << sigma_V << endl;

    }
    // blue , violet, yellow, green, turq:  6.88e14, 7.41e14,5.19e14, 5.49e14, 6.08e14
    // turq, yellow, blue, green, violet

    vector<double> frequencies = {6.08e14, 5.19e14, 6.88e14, 5.49e14, 7.41e14};
    vector <double> frequency_error = {10-9};

    // Let's do the final fit
    TCanvas *c1 = new TCanvas("Final","Final");
    TGraphErrors *mygraph = new TGraphErrors(V_s.size(), &frequencies[0],&V_s[0], 0, &sigma_V_s[0]);
    mygraph->SetTitle("Photoelectric Current vs Retarding Potential for All Light");
    mygraph->GetYaxis()->SetTitle("Energy (keV)");
    mygraph->GetXaxis()->SetTitle("Frequency (Hz)");
    mygraph->Draw("A*");
    TF1 *ffitline = new TF1("ffitline","[0]*x+[1]",0,8e14);
    ffitline->SetLineColor(kBlue);
    ffitline->Draw("same");
    mygraph->Fit(ffitline,"R+");
    c1->SaveAs("./output/final.png");

    // Calculate the error, first write planck's constant in kev
    double h_accepted = 4.135667696e-15;
    double e = 1.602176634e-19;
    double h_observed = ffitline->GetParameter(0) / e  ;
    double sigma_h    = ffitline->GetParError(0) / e;
    double error      = abs(h_accepted - h_observed) / sigma_h;
    cout << YELLOW << "Accepted h:" << '\t' << RESET << h_accepted << endl;
    cout << YELLOW << "Calculated h: " << '\t' << RESET << h_observed << " +/- " << sigma_h << endl; 
    cout << YELLOW << "Error: " << '\t' << '\t' << RESET << error << " sigmas." << endl; 


    // Calculate the work function 

    double work_function = -1 * ffitline->GetParameter(1) / e;
    double sigma_work_function = ffitline->GetParError(1) / e;

    cout << YELLOW << "Work Function: " << '\t' << RESET << work_function << " +/- " << sigma_work_function << endl;




}
