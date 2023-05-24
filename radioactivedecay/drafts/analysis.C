{
   
    vector<string> files;
    string directoryPath = "./data"; // Specify the directory path

    // Iterate over each file in the directory
    for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }


    vector<double> half_lifes;
    int canvas_counter = 1 ; 
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

            for (int i = 0; i < time.size(); i++) {
                time[i] = time[i] - time[0];
            }

            inputFile.close(); // Close the file after reading

            /*
            cout << counts.size() << endl;
            cout << time.size() << endl;
            */

            /*
            // Check if it works
            cout << "Time" << '\t' <<  "Counts" << endl;
            for (int i = 0; i < time.size(); i++) {
                cout << time[i] << '\t' << counts[i] << endl;
            }
            */

            // Now that we can see that it works, we need to prepare the data for the fit,
            // therefore we have to first get the time difference between  successive counts
            // s_i = t_i+1 - t_i

            vector <double> time_diff; //s_i
            for (int i = 0; i < time.size()-1; i++) {
                time_diff.push_back(time[i+1] - time[i]);
            }

            // get the inverse time_diff too for the plotting, 1/s_i 
            vector <double> inverse_time_diff; //1/s_i
            for (int i = 0; i < time_diff.size(); i++) {
                // Let's calibrate this for the fit,
                inverse_time_diff.push_back(1/time_diff[i] * time_diff[0]); 
            
                
            }


            /*
            //Check if it is correct: 
            cout << "\nTime difference" << endl;
            for (int i = 0; i < time_diff.size(); i++) {
                cout << time_diff[i] << endl;
            }
            */

    
            //Calculate the average time between successive counts,
            // T_i = (t_i+1 + t_i)/2

            vector <double> time_avg;
            for (int i = 0; i < time.size()-1; i++) {
                time_avg.push_back((time[i+1] + time[i])/2);
            }


            /*
            //Check if it is correct:
            cout << "\nTime average" << endl;
            for (int i = 0; i < time_avg.size(); i++) {
                cout << time_avg[i] << endl;
            }
            */


            // Since ROOT will not fit the data linearly if we change the graph to the log-scale,
            // which is explained in this site; 
            // https://root.cern/doc/master/classTGraphPainter.html#GrP7
            // we have to change the data to the log-scale manually.

            // where y axis will be 
            // y = ln(1/s_i) = -ln(s_i)
            // and x axis will be
            // x = ln(1/s_0) - lambda*T_i
            // where lambda is the decay constant
            // in order to find lambda, we will have to put (1/s_0) to the y-axis for each graph. 


            /*
            vector <double> y;
            vector <double> x;

            for (int i = 0; i < time_diff.size(); i++) {
                y.push_back(-1*TMath::Log(time_diff[i]));
                x.push_back(-1*TMath::Log(time_diff[0]) - time_avg[i]);
            }

            string canvas_name = "c" + to_string(canvas_counter);
            string g1_title = "Logarithmic plot of the data (" + fileName + ")";
            TCanvas *c1 = new TCanvas(canvas_name.c_str() , canvas_name.c_str());
            TGraph *g1 = new TGraph(x.size(), &x[0], &y[0]);
            g1->SetMarkerStyle(20);
            g1->SetMarkerColor(kRed);
            g1->SetLineColor(kRed);
            //g1->GetXaxis()->SetLimits(x_range_beginning, x_range_ending);
            g1->SetTitle(g1_title.c_str());
            g1->GetXaxis()->SetTitle("ln(1/s_0) - #lambdaT_i");
            g1->GetYaxis()->SetTitle("-ln(s_i)");
            g1->Draw("AP");
            */

            string canvas_name_2 = "linear_plot_" + to_string(canvas_counter);
            TCanvas *c2 = new TCanvas(canvas_name_2.c_str() , canvas_name_2.c_str());

            string g2_title = "Linear plot of the data 1/s_{i} vs T_{i} for  " + fileName;
            TGraph  *g2 = new TGraph(time_avg.size(), &time_avg[0], &inverse_time_diff[0]);
            g2->SetMarkerStyle(20);
            g2->SetMarkerSize(0.5);
            g2->SetMarkerColor(kRed);
            g2->SetLineColor(kRed);
            g2->SetTitle(g2_title.c_str());
            g2->GetXaxis()->SetTitle("Avg. Time T_{i}");
            g2->GetYaxis()->SetTitle("Inverse Time Diff. 1/s_{i}");
            g2->Draw("AP");


            double exp_fit_beginning = time_avg[0] ; 
            TF1* exp_fit = new TF1("expFunc", "exp(-[0] * x)", exp_fit_beginning, 250);
            exp_fit -> SetLineColor(kBlue);
            exp_fit -> SetLineWidth(8);
            exp_fit -> SetParName(0, "#lambda");

            g2->Fit(exp_fit, "R");
            gStyle->SetOptFit(1111);





            canvas_counter++;

            // Let's check if the lambda's are...accurate? Calculate the halflife of the Radon 

            double half_life = TMath::Log(2)/exp_fit->GetParameter(0);
            half_lifes.push_back(half_life);



        }
    }

    cout << "\033[1;33mCALCULATED HALF LIFES\033[0m" << endl;   
    for(int i = 0 ; i < half_lifes.size() ; i++){
        cout << half_lifes[i] << endl ; 
    }

    // All of them are shit 
}