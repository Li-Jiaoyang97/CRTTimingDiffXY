std::map<int, TH1D *> DeclareHistoMap(std::string h_histo_name, std::vector<int> tag_vec, int bins, double min, double max);
std::vector<TH1D *> DeclareHistoVec(std::string h_histo_name, int vector_size, std::vector<std::string> histolabels, int bins, double min, double max);
void PlotFitAndSaveForTagger(std::vector<TH1D*> h_t1_diff_vec, std::vector<std::string> tagger_vec, std::string axisLabel, std::string saveDir, std::string saveName);
void PlotFitAndSaveForPair(std::map<int, TH1D *> h_t0_diff_map, std::map<int, int> module_tagger_pair_map, std::string axisLabel, std::string saveDir, std::string saveName, std::string csvfilename);


// Main function. 
void PlotTimingDiff(int run=18250, std::string fileDir = "/exp/sbnd/data/users/jiaoyang/AnalysisWorksopCRTData/", bool _debug = false){

    std::string filename = Form("run%i", run); //_small_sample

    TFile *f = new TFile(Form("%s%s.root", fileDir.c_str(), filename.c_str()));
    TTree *tree = (TTree*)f->Get("crtana/tree");

    // read in TBranch 
    std::vector<int16_t> *cl_tagger = 0;
    std::vector<uint8_t> *cl_composition = 0;
    std::vector<bool>    *cl_has_sp = 0;
    std::vector<std::vector<uint32_t>> *cl_sh_ts0_set = 0; 
    std::vector<std::vector<uint32_t>> *cl_sh_ts1_set = 0;
    std::vector<std::vector<uint16_t>> *cl_sh_feb_mac5_set = 0; 
    std::vector<std::vector<double>>   *cl_sh_time_walk_set = 0;
    std::vector<std::vector<double>>   *cl_sh_prop_delay_set = 0;
    std::vector<std::vector<uint32_t>> *cl_channel_set = 0;

    tree->SetBranchAddress("cl_tagger", &cl_tagger);
    tree->SetBranchAddress("cl_composition", &cl_composition);
    tree->SetBranchAddress("cl_has_sp", &cl_has_sp);
    tree->SetBranchAddress("cl_sh_ts0_set", &cl_sh_ts0_set);
    tree->SetBranchAddress("cl_sh_ts1_set", &cl_sh_ts1_set);
    tree->SetBranchAddress("cl_sh_feb_mac5_set", &cl_sh_feb_mac5_set);
    tree->SetBranchAddress("cl_sh_time_walk_set", &cl_sh_time_walk_set);
    tree->SetBranchAddress("cl_sh_prop_delay_set", &cl_sh_prop_delay_set);
    tree->SetBranchAddress("cl_channel_set", &cl_channel_set);

    // TH1D vectors defined by tagger.
    std::vector<std::string> tagger_vec = {"tagger_0", "tagger_1", "tagger_2", "tagger_3", "tagger_4", "tagger_5", "tagger_6"};
    const int ntaggers = tagger_vec.size();
    std::vector<TH1D *> h_t0_diff_vec = DeclareHistoVec("h_t0_diff", ntaggers, tagger_vec, 100, -50, 50);
    std::vector<TH1D *> h_t1_diff_vec = DeclareHistoVec("h_t1_diff", ntaggers, tagger_vec, 100, -50, 50);

    // This the module pair mapping vector, which is calculated by imodule*1000 + jmodule; imodule < jmodule.
    std::vector<int> module_pair_mapping_vec = {16, 17, 18, 1016, 1017, 1018, 2016, 2017, 2018, 2021, 2022, 2023, 3021, 3022, 3023, 4021, 4022, 4023, 5018, 5019, 6018, 6019, 7018, 7019, 7023, 7024, 8023, 8024, 9023, 9024, 10015, 10016, 10017, 11015, 11016, 11017, 12015, 12016, 12017, 12020, 12021, 12022, 13020, 13021, 13022, 14020, 14021, 14022, 25042, 25043, 25044, 26042, 26043, 26044, 26047, 26048, 26049, 27037, 27038, 27039, 27042, 27043, 27044, 27047, 27048, 27049, 28037, 28038, 28039, 28047, 28048, 28049, 29037, 29038, 29039, 30040, 30041, 30042, 31040, 31041, 31042, 31045, 31046, 31047, 32035, 32036, 32037, 32040, 32041, 32042, 32045, 32046, 32047, 33035, 33036, 33037, 33045, 33046, 33047, 34035, 34036, 34037, 50063, 50064, 50065, 51059, 51060, 51061, 51063, 51064, 51065, 52059, 52060, 52061, 52063, 52064, 52065, 53059, 53060, 53061, 54062, 54063, 54064, 55058, 55059, 55060, 55062, 55063, 55064, 56058, 56059, 56060, 56062, 56063, 56064, 57058, 57059, 57060, 66079, 66080, 66081, 67075, 67076, 67077, 67079, 67080, 67081, 68075, 68076, 68077, 68079, 68080, 68081, 69075, 69076, 69077, 70078, 70079, 71074, 71075, 71076, 71078, 71079, 71080, 72074, 72075, 72076, 72078, 72079, 72080, 73074, 73075, 73076, 78082, 78083, 80082, 84099, 84100, 84101, 85094, 85095, 85096, 85099, 85100, 85101, 86094, 86095, 86096, 86099, 86100, 86101, 87094, 87095, 87096, 88097, 88098, 88099, 89092, 89093, 89094, 89097, 89098, 89099, 90092, 90093, 90094, 90097, 90098, 90099, 91092, 91093, 91094, 102117, 102118, 102119, 103112, 103113, 103114, 103117, 103118, 103119, 104112, 104113, 104114, 104117, 104118, 104119, 105112, 105113, 105114, 106115, 106116, 106117, 107110, 107111, 107112, 107115, 107116, 107117, 108110, 108111, 108112, 108115, 108116, 108117, 109110, 109111, 109112, 120122, 120123, 121122, 121123, 126128, 126139, 127128, 127139, 129131, 129132, 130131, 130132, 135137, 135138, 136137, 136138};
    
    std::cout<<"Check! There are "<<module_pair_mapping_vec.size()<<" module pairs."<<std::endl;

    /*
    for (int i=0; i<tree->GetEntries(); i++){
        
        tree->GetEntry(i);
        for (int icluster=0; icluster<cl_sh_ts0_set->size(); icluster++){

            if (!cl_has_sp->at(icluster)) continue; 
            if (cl_sh_ts0_set->at(icluster).size()!=2) continue; 

            for (int ihit=0; ihit<cl_sh_ts0_set->at(icluster).size()-1; ihit++){
                for (int jhit=ihit+1; jhit<cl_sh_ts0_set->at(icluster).size(); jhit++){

                    int imodule = cl_channel_set->at(icluster).at(ihit)/32;
                    int jmodule = cl_channel_set->at(icluster).at(jhit)/32;
                    
                    int mapping = -1;
                    if (imodule < jmodule){ 
                        mapping = imodule*1000 + jmodule;
                    }else{
                        mapping = jmodule*1000 + imodule;
                    }
                    module_pair_mapping_vec.push_back(mapping);
                }
            }
        }
    }
    // make module_pair_mapping_vec unique. 
    std::sort(module_pair_mapping_vec.begin(), module_pair_mapping_vec.end());
    module_pair_mapping_vec.erase(std::unique(module_pair_mapping_vec.begin(), module_pair_mapping_vec.end()), module_pair_mapping_vec.end());

    // print module_pair_mapping_vec
    //if (_debug){
        for (int i=0; i<module_pair_mapping_vec.size(); i++){
            std::cout<<module_pair_mapping_vec[i]<<", ";
        }
        std::cout<<std::endl;
    //}

    // print out for each tagger, how many unique module pairs are there.
    if (_debug){
        for (auto const& pair : module_tagger_pair_map) {
            int mapping = pair.first;
            int tagger = pair.second;
            std::cout<<mapping/1000<<", "<<mapping%1000<<"tagger: "<<tagger<<std::endl;
        }
    }
    */
    std::map<int, TH1D *>  h_t0_diff_map = DeclareHistoMap("h_t0_diff_pair", module_pair_mapping_vec, 100, -50, 50);
    std::map<int, TH1D *>  h_t1_diff_map = DeclareHistoMap("h_t1_diff_pair", module_pair_mapping_vec, 100, -50, 50);
            
    // loop over events
    std::map<int, int> module_tagger_pair_map; module_tagger_pair_map.clear();
    for (int i=0; i<tree->GetEntries(); i++){
        
        tree->GetEntry(i);
        for (int icluster=0; icluster<cl_sh_ts0_set->size(); icluster++){
            
            if (!cl_has_sp->at(icluster)) continue; // skip if there is no space point. 
            if (cl_sh_ts0_set->at(icluster).size()!=2) continue; // only keep if there are 2 hits in the cluster 
            if (cl_tagger->at(icluster) != 1) continue; // only keep tagger 1
            for (int ihit=0; ihit<cl_sh_ts0_set->at(icluster).size()-1; ihit++){
                for (int jhit=ihit+1; jhit<cl_sh_ts0_set->at(icluster).size(); jhit++){

                    double t0_ihit_afterCorrection = (double)cl_sh_ts0_set->at(icluster).at(ihit) - cl_sh_time_walk_set->at(icluster).at(ihit) - cl_sh_prop_delay_set->at(icluster).at(ihit);
                    double t0_jhit_afterCorrection = (double)cl_sh_ts0_set->at(icluster).at(jhit) - cl_sh_time_walk_set->at(icluster).at(jhit) - cl_sh_prop_delay_set->at(icluster).at(jhit);

                    double t1_ihit_afterCorrection = (double)cl_sh_ts1_set->at(icluster).at(ihit) - cl_sh_time_walk_set->at(icluster).at(ihit) - cl_sh_prop_delay_set->at(icluster).at(ihit);
                    double t1_jhit_afterCorrection = (double)cl_sh_ts1_set->at(icluster).at(jhit) - cl_sh_time_walk_set->at(icluster).at(jhit) - cl_sh_prop_delay_set->at(icluster).at(jhit);

                    int imodule = cl_channel_set->at(icluster).at(ihit)/32;
                    int jmodule = cl_channel_set->at(icluster).at(jhit)/32;

                    double time_diff_t0(-1000.), time_diff_t1(-1000.);
                    int mapping = -1; 
                    if (imodule < jmodule){ 
                        mapping = imodule*1000 + jmodule;  
                        time_diff_t0 = t0_ihit_afterCorrection - t0_jhit_afterCorrection;
                        time_diff_t1 = t1_ihit_afterCorrection - t1_jhit_afterCorrection;
                    }else{
                        mapping = jmodule*1000 + imodule;
                        time_diff_t0 = t0_jhit_afterCorrection - t0_ihit_afterCorrection;
                        time_diff_t1 = t1_jhit_afterCorrection - t1_ihit_afterCorrection;
                    }

                    module_tagger_pair_map[mapping] = cl_tagger->at(icluster);
                    
                    if (_debug) std::cout<<"Taggar: "<<cl_tagger->at(icluster)<<", t1 diff: "<<time_diff_t1<<", t0 diff: "<<time_diff_t0<<std::endl;

                    //if (mapping == 130*1000+132 ){
                    //    std::cout<<"Taggar: "<<cl_tagger->at(icluster)<<", t1 diff: "<<time_diff_t1<<", t0 diff: "<<time_diff_t0<<std::endl;
                    //}

                    // fill in module pair histograms
                    h_t0_diff_map[mapping]->Fill(time_diff_t0);
                    h_t1_diff_map[mapping]->Fill(time_diff_t1);

                    // fill in tagger histograms
                    h_t0_diff_vec[cl_tagger->at(icluster)]->Fill(time_diff_t0);
                    h_t1_diff_vec[cl_tagger->at(icluster)]->Fill(time_diff_t1);
                }
            }
        }
    }   

    // save the histograms
    std::string saveModulesT0Dir = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t0/", run) ;
    gSystem->Exec(Form("mkdir -p %s", saveModulesT0Dir.c_str()));
    gSystem->Exec(Form("rm %s/*", saveModulesT0Dir.c_str()));
    std::string csvfilename = "timing_diff_fit_per_module_pair";
    PlotFitAndSaveForPair(h_t0_diff_map, module_tagger_pair_map, "#Delta t_{0} (ns)", saveModulesT0Dir, "t0_diff", csvfilename);

    std::string saveModulesT1Dir = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t1/", run);
    gSystem->Exec(Form("mkdir -p %s", saveModulesT1Dir.c_str()));
    gSystem->Exec(Form("rm %s/*", saveModulesT1Dir.c_str()));
    PlotFitAndSaveForPair(h_t1_diff_map, module_tagger_pair_map, "#Delta t_{1} (ns)", saveModulesT1Dir, "t1_diff", csvfilename);

    std::string saveTaggerDir = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsTagger/", run);
    gSystem->Exec(Form("mkdir -p %s", saveTaggerDir.c_str()));
    gSystem->Exec(Form("rm %s/*", saveTaggerDir.c_str()));
    PlotFitAndSaveForTagger(h_t0_diff_vec, tagger_vec, "#Delta t_{0} (ns)", saveTaggerDir, "t0_diff");
    PlotFitAndSaveForTagger(h_t1_diff_vec, tagger_vec, "#Delta t_{1} (ns)", saveTaggerDir, "t1_diff");

}

void PlotFitAndSaveForTagger(std::vector<TH1D*> h_t1_diff_vec, std::vector<std::string> tagger_vec, std::string axisLabel, std::string saveDir, std::string saveName){
    // Canvas for t1 diff
    TCanvas *canvas = new TCanvas("canvas", "canvas", 800*4, 600*2);
    canvas->Divide(4,2);
    for (int i=0; i<h_t1_diff_vec.size(); i++){
        canvas->cd(i+1);
        h_t1_diff_vec[i]->SetStats(0);
        h_t1_diff_vec[i]->SetLineColor(kBlack);
        h_t1_diff_vec[i]->SetLineWidth(2);
        h_t1_diff_vec[i]->SetTitle(Form("%s; %s; Entries", tagger_vec[i].c_str(), axisLabel.c_str()));
        h_t1_diff_vec[i]->Draw();

        // fit with a Gaussian function
        TF1 *f1 = new TF1("f1","gaus", -50, 50);
        h_t1_diff_vec[i]->Fit("f1", "R");

        // EXTRA PARAMETERS
        double t1_diff_mean = f1->GetParameter(1);
        double t1_diff_RMS = f1->GetParameter(2);
        // Get parameters error
        double t1_diff_mean_err = f1->GetParError(1);
        double t1_diff_RMS_err = f1->GetParError(2);

        // draw parameters in canvas
        TLatex *latex1 = new TLatex();
        latex1->SetTextSize(0.04);
        latex1->SetTextAlign(10);  //align at top
        latex1->DrawLatexNDC(0.6, 0.7, Form("Mean = %.2f #pm %.2f", t1_diff_mean, t1_diff_mean_err));
        latex1->DrawLatexNDC(0.6, 0.6, Form("RMS = %.2f #pm %.2f", t1_diff_RMS, t1_diff_RMS_err));
        latex1->DrawLatexNDC(0.6, 0.5, Form("#chi^{2}/ndf = %.2f/%.2d", f1->GetChisquare(), f1->GetNDF()));
        latex1->Draw("same");
    }
    canvas->SaveAs(Form("%s%s.pdf", saveDir.c_str(), saveName.c_str()));
}

void PlotFitAndSaveForPair(std::map<int, TH1D *> h_t0_diff_map, std::map<int, int> module_tagger_pair_map, std::string axisLabel, std::string saveDir, std::string saveName, std::string csvfilename){
    // open a csv file 
    std::ofstream csvfile;
    csvfile.open(Form("%s%s.csv", saveDir.c_str(), csvfilename.c_str()));
    csvfile << "Tagger\tModule1\tModule2\tMean\tRMS\tchi2/ndf\tEntires\tOutliers" << std::endl;

    for (auto const& pair : h_t0_diff_map) {

        int module_pair_sum = pair.first;
        TH1D* histo = pair.second;

        TCanvas *canvas = new TCanvas(Form("canvas_%i", module_tagger_pair_map[module_pair_sum]), "", 800, 600);
        if (histo->GetEntries() == 0) continue; // if histo is empty, skip

        histo->SetStats(0);
        histo->SetLineColor(kBlack);
        histo->SetLineWidth(2);
        histo->SetTitle(Form("Tagger %i, Module %i and %i; %s; Entries", module_tagger_pair_map[module_pair_sum], (module_pair_sum/1000), (module_pair_sum%1000), axisLabel.c_str()));
        histo->Draw();

        // fit with a Gaussian function
        TF1 *f1 = new TF1("f1","gaus", -50, 50);
        histo->Fit("f1", "R");

        double t1_diff_mean = f1->GetParameter(1);
        double t1_diff_RMS = f1->GetParameter(2);
        double t1_diff_mean_err = f1->GetParError(1);
        double t1_diff_RMS_err = f1->GetParError(2);

        int entries = histo->Integral(1, histo->GetNbinsX());
        int outliers = histo->GetBinContent(0) + histo->GetBinContent(histo->GetNbinsX()+1);
        csvfile<< Form("%i\t%i\t%i\t%.2f\t%.2f\t%.2f\t%i\t%i", module_tagger_pair_map[module_pair_sum], (module_pair_sum/1000), (module_pair_sum%1000), t1_diff_mean, t1_diff_RMS, f1->GetChisquare()/f1->GetNDF(), entries, outliers) << std::endl;

        TLatex *latex1 = new TLatex();
        latex1->SetTextSize(0.04);
        latex1->SetTextAlign(10);  //align at top
        latex1->DrawLatexNDC(0.6, 0.7, Form("Mean = %.2f #pm %.2f", t1_diff_mean, t1_diff_mean_err));
        latex1->DrawLatexNDC(0.6, 0.6, Form("RMS = %.2f #pm %.2f", t1_diff_RMS, t1_diff_RMS_err));
        latex1->DrawLatexNDC(0.6, 0.5, Form("#chi^{2}/ndf = %.2f/%.2d", f1->GetChisquare(), f1->GetNDF()));
        latex1->Draw("same");

        canvas->SaveAs(Form("%s%s_Tagger_%i_Module_%i_and_%i.pdf", saveDir.c_str(), saveName.c_str(), module_tagger_pair_map[module_pair_sum], (module_pair_sum/1000), (module_pair_sum%1000)));
        //delete canvas;
    }
    csvfile.close();
}


std::map<int, TH1D *> DeclareHistoMap(std::string h_histo_name, 
                                        std::vector<int> tag_vec,
                                        int bins, 
                                        double min, 
                                        double max)
{
    std::map<int, TH1D *> h_histo_map;
    for (int ihisto=0; ihisto<tag_vec.size(); ihisto++){
        std::string h_histo_name_new = Form("%s_%i", h_histo_name.c_str(), tag_vec[ihisto]);
        TH1D *h_histo_temp = new TH1D(h_histo_name_new.c_str(),"", bins, min, max); 
        std::string h_histo_title= Form("%i", tag_vec[ihisto]);
        h_histo_temp->SetTitle(h_histo_title.c_str());  
        h_histo_map[tag_vec[ihisto]] = h_histo_temp;
    }
    return h_histo_map;
}

std::vector<TH1D *> DeclareHistoVec(std::string h_histo_name, 
    int vector_size, std::vector<std::string> histolabels, 
    int bins, 
    double min, 
    double max)
{
std::vector<TH1D *> h_histo_vec;
for (int ihisto=0; ihisto<vector_size; ihisto++){
std::string h_histo_name_new = Form("%s_%s", h_histo_name.c_str(), histolabels[ihisto].c_str());
TH1D *h_histo_temp = new TH1D(h_histo_name_new.c_str(),"", bins, min, max); 
std::string h_histo_title= Form("%s", histolabels[ihisto].c_str());
h_histo_temp->SetTitle(h_histo_title.c_str());  
h_histo_vec.push_back(h_histo_temp);
}
return h_histo_vec;
}