{
    string YELLOW = "\033[1;33m" ;
    string RESET = "\033[0m"     ;

    vector<vector<double>> fit_parameters = { 
    { 20,250,0.059}, // c1
    { 20,250,0.05}, // c2
    { 22,200,0.125},  // c3
    { 20,250,0.05},  // c4
    { 40 , 180, 0.02} , // c5
    { 20,250,0.028},   // c6
    { 15,155,0.090},  //c7
    { 7.15 , 180 ,0.25},  //c8
    { 340,450,0.002}, //c9
    { 50,250,0.021}, //c10
    { 15,150,0.13}, //c11
    { 10 ,140,0.125}, // c12
    { 0,300,0.5}, // c13
    { 20,250,0.083}, // c14
    { 20,250,0.05}, // c15 
    { 20,250,0.045} //c16
    };


    vector<string> files;
    string directoryPath = "./data"; 

    // Iterate over each file in the directory
    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }

    vector<double> half_lifes, lambdas, lambda_errors;
    vector<double> voltage2500, voltage3000, voltage3500, voltage4000;
    vector<double> voltage2500_errors, voltage3000_errors, voltage3500_errors, voltage4000_errors;
    vector<double> squeeze2, squeeze3, squeeze4, squeeze5;
    vector<double> squeeze2_errors, squeeze3_errors, squeeze4_errors, squeeze5_errors;



    // counters 
    int canvas_counter = 1 ; 
    int parameter_counter = 0 ;

    for (const string& file : files) {

        vector<double> time;
        vector<double> counts;
        
        filesystem::path filePath(file);
        string fileName = filePath.filename().string();

        ifstream inputFile(file);
        if (inputFile.is_open()) {
            string line;
            getline(inputFile, line); // Read and discard the first line (header)

            while (getline(inputFile, line)) {
                istringstream iss(line);
                double c, t;
                if (iss >> c >> t) { // Read counts and time from the line
                    counts.push_back(c);
                    time.push_back(t);
                }
            }
            // Calibrate the time to start from 0 , so the time averages will be calculated correctly
            for (int i = 0; i < time.size(); i++) {
                time[i] = time[i] - time[0];
            }

            inputFile.close(); 

            // CALCULATE THE TIME DIFFERENCES AND TIME AVERAGES

            // 1/s_i , s_i = t_i+1 - t_i
            vector <double> inverse_time_diff; 
            for (int i = 0; i < time.size(); i++) {
                double s_i = time[i+1] - time[i];
                inverse_time_diff.push_back(1/s_i); 

            }

            // T_i = (t_i+1 + t_i)/2
            vector <double> time_avg;
            for (int i = 0; i < time.size()-1; i++) {
                time_avg.push_back((time[i+1] + time[i])/2);
            }

            // sigma T_i
            vector<double> time_avg_error; 
            for (int i = 0; i < time.size()-1; i++) {
                time_avg_error.push_back( 0.3 /TMath::Sqrt(2)); 
            }


            // PLOT THE GRAPH
            
            //  y axis will be   : y = 1/s_i
            //  x axis will be   : x =  1/s_0 * exp(-lambda*T_i ), lambda: decay constant 

            vector <double> y;
            vector <double> x;
            vector <double> y_error;
            vector <double> x_error;

            string canvas_name = "c_expo" + to_string(canvas_counter);
            cout << YELLOW << '\n' << canvas_name << '\t' <<  fileName << RESET << endl;

            cout << YELLOW << "N_0" << RESET << '\t' << inverse_time_diff[0] << endl;

            for (int i = 0; i < inverse_time_diff.size(); i++) {
                y.push_back(inverse_time_diff[i]);
                x.push_back(time_avg[i]);
                y_error.push_back(0.3*TMath::Sqrt(2)*inverse_time_diff[i]);
                x_error.push_back(time_avg_error[i]);
            }

            TCanvas *c1 = new TCanvas(canvas_name.c_str() , canvas_name.c_str());
            c1-> SetLogy();
            c1-> SetGrid();
            c1 -> SetFrameLineWidth(2);


            string g1_title = fileName ;
            TGraphErrors *g1 = new TGraphErrors(x.size(), &x[0], &y[0], &x_error[0], &y_error[0]);


            double fit_begin = fit_parameters[parameter_counter][0];
            double fit_end = fit_parameters[parameter_counter][1];
            double parameter = fit_parameters[parameter_counter][2];
            cout << YELLOW << "Parameter:" << RESET << '\t' << parameter << endl;

            //auto yMax = std::max_element(y.begin(), y.end());
            //auto yMin = *std::min_element(y.begin(), y.end());
            //int  yMax_index = std::distance(y.begin(), yMax);

            g1->GetXaxis()->SetLimits(fit_begin, fit_end);
            g1->GetYaxis()->SetRangeUser(2e-2, 1);
            g1->SetMarkerSize(0.7);
            g1->SetMarkerColor(kRed);
            g1->SetTitle(g1_title.c_str());
            g1->GetXaxis()->SetTitle("- T_i");
            g1->GetYaxis()->SetTitle("-ln(s_{i})+ln(s_{0})");
            g1->Draw("AP");

            TF1* ffitline = new TF1("expFunc", "[1]*exp(-[0] * x)", fit_begin, fit_end);
            ffitline -> SetLineColor(kBlue);
            ffitline -> SetLineWidth(8);
            ffitline -> SetParName(0, "#lambda");
            ffitline -> SetParameter(0, 1.12e-2);
            ffitline -> SetParameter(1, parameter);

            //ffitline->SetParLimits(0, 1.12e-2 - 0.3e-2, 1.12e-2 + 0.3e-2);
            //ffitline->SetParLimits(1, parameter - 0.3, parameter + 0.3);


            g1->Fit(ffitline, "R");
            gStyle->SetOptFit(1111);
            
            string saveas = "./output/" + fileName + ".png";
            c1->SaveAs(saveas.c_str());
            

            canvas_counter++;
            parameter_counter++;


            // Let's check if the lambda's are...accurate? Calculate the halflife of the Radon (this is just to check,
            // it is not a part of the analysis)
            double half_life = TMath::Log(2)/ffitline->GetParameter(0);
            half_lifes.push_back(half_life);

            // Also, let's save the lambdas and their errors to a vector
            lambdas.push_back(ffitline->GetParameter(0));
            lambda_errors.push_back(ffitline->GetParError(0));


            // We also need to save the individual voltages lambdas
            // We can use the parameter fileName to get the voltage name

            if (fileName.substr(0,4) == "3000") {
                voltage3000.push_back(ffitline->GetParameter(0));
                voltage3000_errors.push_back(ffitline->GetParError(0));
            }
            else if (fileName.substr(0,4) == "2500") {
                voltage2500.push_back(ffitline->GetParameter(0));
                voltage2500_errors.push_back(ffitline->GetParError(0));
            }
            else if (fileName.substr(0,4) == "3500") {
                voltage3500.push_back(ffitline->GetParameter(0));
                voltage3500_errors.push_back(ffitline->GetParError(0));
            }else if (fileName.substr(0,4) == "4000") {
                voltage4000.push_back(ffitline->GetParameter(0));
                voltage4000_errors.push_back(ffitline->GetParError(0));
            }

            // Also we need to save the squeezes too 
            if (fileName.substr(6,1) == "2"){
                squeeze2.push_back(ffitline->GetParameter(0));
                squeeze2_errors.push_back(ffitline->GetParError(0));
            }
            else if (fileName.substr(6,1) == "3"){
                squeeze3.push_back(ffitline->GetParameter(0));
                squeeze3_errors.push_back(ffitline->GetParError(0));
            }
            else if (fileName.substr(6,1) == "4"){
                squeeze4.push_back(ffitline->GetParameter(0));
                squeeze4_errors.push_back(ffitline->GetParError(0));
            }else if (fileName.substr(6,1) == "5"){
                squeeze5.push_back(ffitline->GetParameter(0));
                squeeze5_errors.push_back(ffitline->GetParError(0));
            }

        }
    }

    // check half life (this part is not a part of the analysis, just checking)
    cout << YELLOW << "CALCULATED HALF LIFES" << RESET << endl;  
    for(int i = 0 ; i < half_lifes.size() ; i++){
        cout << "c" << i+1 << '\t' << ':' << '\t' << half_lifes[i] << endl ; 
    }

    // CALCULATE THE WEIGHTED MEAN OF LAMBDA
    double sum1 = 0;
    double sum2 = 0;
    for(int i = 0 ; i < lambdas.size() ; i++){
        sum1 += lambdas[i]/(lambda_errors[i]*lambda_errors[i]);
        sum2 += 1/(lambda_errors[i]*lambda_errors[i]);
    }

    double weighted_lambda = sum1/sum2;
    double weighted_lambda_error = 1/TMath::Sqrt(sum2);

    cout << "\n" << YELLOW <<  "Weighted lambda" << " : " << RESET  << weighted_lambda << '\n' 
         << YELLOW << "Weighted lambda error" << " : " << RESET  << weighted_lambda_error << endl ;

    // CALCULATE THE WEIGHTED MEAN OF HALF LIFE
    double weighted_half_life = TMath::Log(2)/weighted_lambda;
    double error_weighted_half_life = std::abs(-TMath::Log(2)  / (weighted_lambda * weighted_lambda)) * weighted_lambda_error;

    cout << "\n" << YELLOW << "Weighted half life: " << RESET << weighted_half_life << endl ;
    cout << YELLOW << "Weighted half life error: " << RESET << error_weighted_half_life << endl ;



    // OTHER CALCULATIONS:


    // THE WEIGHTED MEAN OF LAMBDA FOR EACH VOLTAGE
    
    double sum2500_1 = 0;
    double sum2500_2 = 0;
    for(int i = 0 ; i < voltage2500.size() ; i++){
        sum2500_1 += voltage2500[i]/(voltage2500_errors[i]*voltage2500_errors[i]);
        sum2500_2 += 1/(voltage2500_errors[i]*voltage2500_errors[i]);
    }

    double weighted_lambda2500 = sum2500_1/sum2500_2;
    double weighted_lambda2500_error = 1/TMath::Sqrt(sum2500_2);

    double sum3000_1 = 0;
    double sum3000_2 = 0;
    for(int i = 0 ; i < voltage3000.size() ; i++){
        sum3000_1 += voltage3000[i]/(voltage3000_errors[i]*voltage3000_errors[i]);
        sum3000_2 += 1/(voltage3000_errors[i]*voltage3000_errors[i]);
    }

    double weighted_lambda3000 = sum3000_1/sum3000_2;
    double weighted_lambda3000_error = 1/TMath::Sqrt(sum3000_2);

    double sum3500_1 = 0;
    double sum3500_2 = 0;
    for(int i = 0 ; i < voltage3500.size() ; i++){
        sum3500_1 += voltage3500[i]/(voltage3500_errors[i]*voltage3500_errors[i]);
        sum3500_2 += 1/(voltage3500_errors[i]*voltage3500_errors[i]);
    }

    double weighted_lambda3500 = sum3500_1/sum3500_2;
    double weighted_lambda3500_error = 1/TMath::Sqrt(sum3500_2);

    double sum4000_1 = 0;
    double sum4000_2 = 0;
    for(int i = 0 ; i < voltage4000.size() ; i++){
        sum4000_1 += voltage4000[i]/(voltage4000_errors[i]*voltage4000_errors[i]);
        sum4000_2 += 1/(voltage4000_errors[i]*voltage4000_errors[i]);
    }

    double weighted_lambda4000 = sum4000_1/sum4000_2;
    double weighted_lambda4000_error = 1/TMath::Sqrt(sum4000_2);


    vector <double> voltages = {2500, 3000, 3500, 4000};
    vector <double> voltages_errors = {0, 0, 0, 0};
    vector <double> weighted_lambdas_voltages = {weighted_lambda2500, weighted_lambda3000, weighted_lambda3500, weighted_lambda4000};
    vector <double> weighted_lambdas_voltages_errors = {weighted_lambda2500_error, weighted_lambda3000_error, weighted_lambda3500_error, weighted_lambda4000_error};



    // PLOT VOLTAGE VS LAMBDA
    cout << "\n" <<  YELLOW  << "Weighted Lambdas for Each Voltage"<<   RESET  << endl;

    TCanvas *c2 = new TCanvas("Voltage vs Lambda" , "Voltage vs Lambda");
    c2-> SetGrid();
    c2 -> SetFrameLineWidth(2);

    TGraphErrors *g3 = new TGraphErrors(voltages.size(), &voltages[0], &weighted_lambdas_voltages[0], 0 , &weighted_lambdas_voltages_errors[0]);
    g3->SetTitle("Voltage vs Decay Constant #lambda");
    g3->GetXaxis()->SetTitle("Voltage (V)");
    g3->GetYaxis()->SetTitle("#lambda (s^{-1})");
    g3->Draw("AP");

    TGraph *g2 = new TGraph(voltages.size(), &voltages[0], &weighted_lambdas_voltages[0]);
    g2->SetMarkerStyle(20);
    g2->SetMarkerSize(0.7);
    g2->Draw("SAME P");

    TF1 *ffitline2 = new TF1("ffitline2", "[0]*x + [1]", 2400, 4100);
    ffitline2->SetParameter(0,0.012);
    ffitline2->SetLineColor(kBlue);
    ffitline2->SetLineWidth(4);

    c2->SaveAs("./output/Voltage_vs_Lambda.png");
    g3->Fit(ffitline2, "R");
    gStyle->SetOptFit(1111);




    //WEIGHTED MEAN OF LAMBDA FOR EACH SQUEEZE

    double sum_squeeze2_1 = 0;
    double sum_squeeze2_2 = 0;
    for(int i = 0 ; i < squeeze2.size() ; i++){
        sum_squeeze2_1 += squeeze2[i]/(squeeze2_errors[i]*squeeze2_errors[i]);
        sum_squeeze2_2 += 1/(squeeze2_errors[i]*squeeze2_errors[i]);
    }
    double weighted_lambda_squeeze2 = sum_squeeze2_1/sum_squeeze2_2;
    double weighted_lambda_squeeze2_error = 1/TMath::Sqrt(sum_squeeze2_2);

    double sum_squeeze3_1 = 0;
    double sum_squeeze3_2 = 0;
    for(int i = 0 ; i < squeeze3.size() ; i++){
        sum_squeeze3_1 += squeeze3[i]/(squeeze3_errors[i]*squeeze3_errors[i]);
        sum_squeeze3_2 += 1/(squeeze3_errors[i]*squeeze3_errors[i]);
    }
    double weighted_lambda_squeeze3 = sum_squeeze3_1/sum_squeeze3_2;
    double weighted_lambda_squeeze3_error = 1/TMath::Sqrt(sum_squeeze3_2);

    double sum_squeeze4_1 = 0;
    double sum_squeeze4_2 = 0;
    for(int i = 0 ; i < squeeze4.size() ; i++){
        sum_squeeze4_1 += squeeze4[i]/(squeeze4_errors[i]*squeeze4_errors[i]);
        sum_squeeze4_2 += 1/(squeeze4_errors[i]*squeeze4_errors[i]);
    }
    double weighted_lambda_squeeze4 = sum_squeeze4_1/sum_squeeze4_2;
    double weighted_lambda_squeeze4_error = 1/TMath::Sqrt(sum_squeeze4_2);

    double sum_squeeze5_1 = 0;
    double sum_squeeze5_2 = 0;
    for(int i = 0 ; i < squeeze5.size() ; i++){
        sum_squeeze5_1 += squeeze5[i]/(squeeze5_errors[i]*squeeze5_errors[i]);
        sum_squeeze5_2 += 1/(squeeze5_errors[i]*squeeze5_errors[i]);
    }
    double weighted_lambda_squeeze5 = sum_squeeze5_1/sum_squeeze5_2;
    double weighted_lambda_squeeze5_error = 1/TMath::Sqrt(sum_squeeze5_2);


    vector <double> squeezes = {2, 3, 4, 5};
    vector <double> squeezes_errors = {0, 0, 0, 0};
    vector <double> weighted_lambdas_squeezes = {weighted_lambda_squeeze2, weighted_lambda_squeeze3, weighted_lambda_squeeze4, weighted_lambda_squeeze5};
    vector <double> weighted_lambdas_squeezes_errors = {weighted_lambda_squeeze2_error, weighted_lambda_squeeze3_error, weighted_lambda_squeeze4_error, weighted_lambda_squeeze5_error};
    

    cout << "\n" << YELLOW  << "Weighted Lambdas for Each Squeeze"<<   RESET  << endl;   

    TCanvas *c3 = new TCanvas("Squeeze vs Lambda" , "Squeeze vs Lambda");
    c3-> SetGrid();
    c3 -> SetFrameLineWidth(2);

    TGraphErrors *g4 = new TGraphErrors(squeezes.size(), &squeezes[0], &weighted_lambdas_squeezes[0], 0 , &weighted_lambdas_squeezes_errors[0]);
    g4->SetTitle("Number of Squeezes vs Decay Constant #lambda");
    g4->GetXaxis()->SetTitle("Number of Squeeze");
    g4->GetYaxis()->SetTitle("#lambda (s^{-1})");
    g4->Draw("AP");

    TGraph *g5 = new TGraph(squeezes.size(), &squeezes[0], &weighted_lambdas_squeezes[0]);
    g5->SetMarkerStyle(20);
    g5->SetMarkerSize(0.7);
    g5->Draw("SAME P");


    TF1 *ffitline3 = new TF1("ffitline3", "[0]*x + [1]", 1.5, 5.5);
    ffitline3->SetLineColor(kBlue);
    ffitline3->SetLineWidth(4);


    g4->Fit(ffitline3, "R");
    gStyle->SetOptFit(1111);

    c3->SaveAs("./output/Squeeze_vs_Lambda.png");


}