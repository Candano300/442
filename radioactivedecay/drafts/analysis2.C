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
            getline(inputFile, line); 

            while (getline(inputFile, line)) {
                istringstream iss(line);
                double c, t;
                if (iss >> c >> t) { 
                    counts.push_back(c);
                    time.push_back(t);
                }
            }
            // Calibrate the time to start from 0 
            for (int i = 0; i < time.size(); i++) {
                time[i] = time[i] - time[0];
            }

            inputFile.close(); // Close the file after reading


            // Get the time difference between successive counts
            // s_i = t_i+1 - t_i

            vector <double> time_diff; //s_i
            for (int i = 0; i < time.size()-1; i++) {
                time_diff.push_back(time[i+1] - time[i]);
            }

            // Get the inverse time_diff too for the plotting, 1/s_i 
            vector <double> inverse_time_diff; //1/s_i
            for (int i = 0; i < time_diff.size(); i++) {
                inverse_time_diff.push_back(1/time_diff[i]); 
            
                
            }

            //Calculate the average time between successive counts,
            // T_i = (t_i+1 + t_i)/2
            vector <double> time_avg;
            for (int i = 0; i < time.size()-1; i++) {
//              time_avg.push_back(     (   (time[i+1] + time[i])/2     )  *   inverse_time_diff[0]  );
                time_avg.push_back(     (   (time[i+1] + time[i])/2     )   );
            }


            string canvas_name_2 = "linear_plot_" + to_string(canvas_counter);
            TCanvas *c2 = new TCanvas(canvas_name_2.c_str() , canvas_name_2.c_str());

            string g2_title = "Linear plot of the data 1/s_{i} vs T_{i} for  " + fileName;
            TGraph  *g2 = new TGraph(time_avg.size(), &time_avg[0], &inverse_time_diff[0]);
            //g2->GetXaxis()->SetLimits(50, 250);
            g2->SetMarkerStyle(20);
            g2->SetMarkerSize(0.5);
            g2->SetMarkerColor(kRed);
            g2->SetLineColor(kRed);
            g2->SetTitle(g2_title.c_str());
            g2->GetXaxis()->SetTitle("Avg. Time T_{i}");
            g2->GetYaxis()->SetTitle("Inverse Time Diff. 1/s_{i}");
            g2->Draw("AP");


            //double exp_fit_beginning = time_avg[0] + 30 ; 
            TF1* exp_fit = new TF1("expFunc", "[1]*exp(-[0] * x)", 30, 140);
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
    // All of them are shit lol 
}