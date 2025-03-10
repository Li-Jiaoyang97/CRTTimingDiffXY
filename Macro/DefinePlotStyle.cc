void DefinePlotStyle(){
	// declare the global plotting style.
	gStyle->SetTitleFont(62, "TXYZ");
	gStyle->SetTitleSize(0.05,"TXYZ");

	// LABELS SIZE AND FONT
	gStyle->SetLabelFont(62, "TXYZ");
	gStyle->SetLabelSize(0.05,"TXYZ");

	// AXIS OFFSETS AND SIZES
	gStyle->SetTitleXOffset(1.2);
	gStyle->SetTitleXSize(0.06);

	gStyle->SetTitleYOffset(1.5);
	gStyle->SetTitleYSize(0.05);
	gStyle->SetMarkerStyle(33);
	gStyle->SetMarkerSize(1.5);
	gStyle->SetLineColor(46);
	gStyle->SetLineWidth(2);
	
    // set margin on the left and bottom 
    gStyle->SetPadLeftMargin(0.15);
    gStyle->SetPadBottomMargin(0.15);
}