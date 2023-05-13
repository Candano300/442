{
    gROOT->ProcessLine(".L makegraph.C"); // compile the function,
    // this line is the  same as executing .L makegraph.C in the ROOT framework 

    //for variable T ,  U1: 52V , U2: 91V
    makegraph("../data/T/U1052-U3091-T175.txt"," for T = 175K");
    makegraph("../data/T/U1052-U3091-T180.txt"," for T = 180K");
    makegraph("../data/T/U1052-U3091-T184.txt"," for T = 184K");
    makegraph("../data/T/U1052-U3091-T187.txt"," for T = 187K");
    
    //for variable U_1 , U2: 91V , T: 179K
    makegraph("../data/U1/U1035-U3099-T179.txt"," for U_{1} = 35V");
    makegraph("../data/U1/U1035-U3099-T179.txt"," for U_{1} = 47V");
    makegraph("../data/U1/U1035-U3099-T179.txt"," for U_{1} = 53V");
    makegraph("../data/U1/U1035-U3099-T179.txt"," for U_{1} = 55V");

    //for variable U_3 , U1: 52V , T: 179K
    makegraph("../data/U3/U1052-U3072-T180.txt"," for U_{2} = 72V");
    makegraph("../data/U3/U1052-U3085-T180.txt"," for U_{2} = 85V");
    makegraph("../data/U3/U1052-U3109-T180.txt"," for U_{2} = 109V");


}