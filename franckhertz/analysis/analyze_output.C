{
    string directory_path = "./output/gaussfits";

    string yellow = "\033[0;33m";
    string reset = "\033[0m";

    vector<double> weighted_averages;
    vector<double> weighted_uncertainties;


    // Iterate over every file in the directory
    for (const auto& file : filesystem::directory_iterator(directory_path)) {
        string file_path = file.path().string();
        cout << "\n" <<yellow << "Processing file: " << file_path << reset<< endl;

        vector<double> mean;
        vector<double> sigma;
        vector<double> s_mean;
        vector<double> s_sigma;


        ifstream infile(file_path);
        string line;

        getline(infile, line);
        cout << line  << endl;


        while (getline(infile, line)) {
            cout << line << endl;
            stringstream ss(line);
            double value;

            ss >> value;
            mean.push_back(value);

            ss >> value;
            s_mean.push_back(value);

            ss >> value;
            sigma.push_back(value);

            ss >> value;
            s_sigma.push_back(value);
        }

        // CALCULATE THE WEIGHTED AVERAGE OF THE MEAN VALUES

        // find the difference and uncertainty between each peak 
        vector<double> diff_mean;
        vector<double> diff_sigma;

        for(int i = 0; i < mean.size() - 1 ; i++){
            double difference = mean[i+1] - mean[i];
            double uncertainty = sqrt(pow(s_mean[i+1],2) + pow(s_mean[i],2));
            diff_mean.push_back(difference);
            diff_sigma.push_back(uncertainty);
        }

        // apply weighted average formula to the difference,
        // where weight is, as calculated by erhan gulmez's book, is 
        // W = 1/sigma^2

        vector<double> w(diff_sigma.size());
        for(int i = 0; i < diff_sigma.size() ; i++){
            w[i] = 1/pow(diff_sigma[i],2);
        }


        //calculate weighted average and uncertainty
        double sum1 = 0;
        double sum2 = 0;
        for (int i=0; i < diff_mean.size() ; i++){
            sum1 += diff_mean[int(i)]*w[int(i)];
            sum2 += w[i];
        }
        double weighted_average = sum1/sum2;
        double weighted_uncertainty = sqrt(1/sum2);

        cout << yellow << "weighted average"<< "\t" << ": " << reset << weighted_average <<  endl;  
        cout << yellow << "weighted uncertainty"<< "\t" <<": "<< reset << weighted_uncertainty << endl;

        weighted_averages.push_back(weighted_average);
        weighted_uncertainties.push_back(weighted_uncertainty);

        
        infile.close();

    }


    // plot a histogram with the weighted averages
    //TH1F *h1 = new TH1F("h1","Weighted averages", 12, 4.75, 5.10);
    //TH1F *h1 = new TH1F("h1","Weighted averages", 10, 4.80, 5.10);


    TH1F *h2 = new TH1F("h2","Weighted averages", 10, 4.80, 5.10);
    
    for(int i = 0; i < weighted_averages.size() ; i++){
        h2->Fill(weighted_averages[i]);
        }

    h2->SetMarkerStyle(20); // set marker style
    h2->SetMarkerSize(0.5); // set marker size
    h2->SetMarkerColor(kRed); // set marker color
    h2->Draw(); // 


    TH1F *h1 = new TH1F("h1","Weighted averages", 15, 4.80, 5.10);

    for(int i = 0; i < weighted_averages.size() ; i++){
        h1->Fill(weighted_averages[i], weighted_uncertainties[i]);
    }
    h1->GetXaxis()->SetTitle("Value of weighted averages Delta E_{i} (V)");
    h1->GetYaxis()->SetTitle("# of occurences");
    h1->GetYaxis()->SetRangeUser(0, 8);
    h1->SetMarkerStyle(20); // set marker style
    h1->SetMarkerSize(0.5); // set marker size
    h1->SetMarkerColor(kRed); // set marker color
    h1->Draw("E1 SAME"); // draw histogram with error bars




}
