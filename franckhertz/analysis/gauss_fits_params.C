{
string yellow = "\033[1;33m";
string reset = "\033[0m";
gROOT->ProcessLine(".L initial_gauss_fits.C");    

// FOR VARIABLE T , U1: 52V , U2: 91V
cout << "\n\n"<<yellow<<"FOR VARIABLE T , U1: 52V , U2: 91V" <<reset << "\n\n";

vector<vector<double> > fit_params = {
    {4.70 ,6.00 },     //1st peak
    {9.60,11.00 },     //2nd peak
    {14.50,15.50},     //3rd peak
    {19.30,21.00}      //4th peak
    };
makegraph("../data/T/U1052-U3091-T175.txt","T = 175K",fit_params);

fit_params = {
    {4.80 ,6.00 },     //1st peak
    {9.90,11.00 },     //2nd peak
    {14.50,15.70},     //3rd peak
    {19.30,20.70},     //4th peak
    {24.00,26.00},     //5th peak
    {29.40,30.80}      //6th peak
    };
makegraph("../data/T/U1052-U3091-T180.txt","T = 180K",fit_params);


fit_params = {
    {4.70 ,6.10 },     //1st peak
    {9.70,10.70 },     //2nd peak
    {14.25,16.00},     //3rd peak
    {19.30,20.70},     //4th peak
    {24.00,26.00},     //5th peak
    {29.50,30.70}      //6th peak
};
makegraph("../data/T/U1052-U3091-T184.txt","T = 184K",fit_params);


fit_params = {
    {4.70 ,6.10 },     //1st peak
    {9.55,11.00 },     //2nd peak
    {14.20,16.00},     //3rd peak
    {19.70,20.60},     //4th peak
    {24.00,26.00},     //5th peak
    {29.50,30.70}      //6th peak   
};
makegraph("../data/T/U1052-U3091-T187.txt","T = 187K",fit_params);

// FOR VARIABLE U_1 , U2: 91V , T: 179K
cout  << "\n\n" << yellow << "FOR VARIABLE U_1 , U2: 91V , T: 179K"  << reset << "\n\n";

fit_params = {
    {4.70 ,6.00 },     //1st peak
    {9.70,11.10 },     //2nd peak
    {14.33,16.00},     //3rd peak
    {19.60,21.00},     //4th peak
    {24.50,26.00},     //5th peak
    {29.60,30.90}      //6th peak

};
makegraph("../data/U1/U1035-U3099-T179.txt","U_{1} = 35V",fit_params);

fit_params = {
    {4.80 ,6.00 },     //1st peak
    {9.70,11.00 },     //2nd peak
    {14.33,16.00},     //3rd peak
    {19.30,21.00},     //4th peak
    {24.00,26.00},     //5th peak
    {29.50,30.80}      //6th peak
};
makegraph("../data/U1/U1047-U3099-T179.txt","U_{1} = 47V",fit_params);

fit_params = {
    {4.90 ,6.00 },     //1st peak
    {9.70,11.00 },     //2nd peak
    {14.33,16.00},     //3rd peak
    {19.40,21.00},     //4th peak
    {24.40,26.00}      //5th peak

};
makegraph("../data/U1/U1053-U3099-T179.txt","U_{1} = 53V",fit_params);

fit_params = {
    {4.70 ,6.20 },     //1st peak
    {9.55,11.00 },     //2nd peak
    {14.33,16.00},     //3rd peak
    {19.40,20.90},     //4th peak
    {24.00,26.00}      //5th peak

};
makegraph("../data/U1/U1055-U3099-T179.txt","U_{1} = 55V",fit_params);

// FOR VARIABLE U_3 , U1: 52V , T: 180K
cout  << "\n\n" << yellow << "FOR VARIABLE U_3 , U1: 52V , T: 180K" << reset << "\n\n";

fit_params={
    {4.70 ,6.30 },     //1st peak
    {9.30,11.00 },     //2nd peak
    {14.33,15.70},     //3rd peak
    {19.30,21.00}      //4th peak
};
makegraph("../data/U3/U1052-U3072-T180.txt","U_{3} = 72V",fit_params);

fit_params={
    {4.70 ,6.10 },     //1st peak
    {9.55,11.00 },     //2nd peak
    {14.33,16.00},     //3rd peak
    {19.30,21.00},     //4th peak
    {24.30,26.00}      //5th peak


};
makegraph("../data/U3/U1052-U3085-T180.txt","U_{3} = 85V",fit_params);

fit_params = {
    {4.70 ,6.00 },     //1st peak
    {9.70,11.00 },     //2nd peak 
    {14.33,16.00},     //3rd peak
    {19.50,21.00},     //4th peak 
    {24.25,26.00},     //5th peak
    {29.70,31.00}      //6th peak
};
makegraph("../data/U3/U1052-U3109-T180.txt","U_{3} = 109V",fit_params);



} 