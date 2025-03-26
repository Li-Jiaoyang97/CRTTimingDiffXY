void PlotMeanRMSPerTagger(std::string csvFileName = "/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250_save/PlotsModules_t1/timing_diff_fit_per_module_pair.csv", std::string savedir = "/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250_save/PlotsModules_t1/", int threshold = 1000)
{
    // read in csv file.
    std::ifstream csvfile(csvFileName.c_str());

    std::string line;
    std::vector<int> tagger_vec;
    std::vector<int> module1_vec;
    std::vector<int> module2_vec;
    std::vector<double> mean_vec;
    std::vector<double> rms_vec;
    std::vector<double> chi2_ndf_vec;
    std::vector<int> entries_vec;
    std::map<int, std::vector<int>> tagger_mean_map, tagger_RMS_map;
    while (std::getline(csvfile, line))
    {
        if (line.find("Tagger") != std::string::npos)
            continue;
        std::istringstream iss(line);
        int tagger, module1, module2, entries;
        double mean, rms, chi2_ndf;
        if (!(iss >> tagger >> module1 >> module2 >> mean >> rms >> chi2_ndf >> entries))
        {
            std::cout << "Error in Tagger " << tagger << ", with Module1: " << module1 << ", Module2: " << module2 << ", Mean " << mean << ", RMS " << rms << std::endl;
            continue;
        } // error
        if (entries < threshold){
            std::cout<< "Skipping Tagger " << tagger << ", with Module1: " << module1 << ", Module2: " << module2 << ", Entries " << entries << std::endl;
            continue; // skip if entries are less than threshold
        }
        tagger_vec.push_back(tagger);
        module1_vec.push_back(module1);
        module2_vec.push_back(module2);
        mean_vec.push_back(mean);
        rms_vec.push_back(rms);
        chi2_ndf_vec.push_back(chi2_ndf);
        entries_vec.push_back(entries);

        tagger_mean_map[tagger].push_back(mean);
        tagger_RMS_map[tagger].push_back(rms);
    }
    csvfile.close();


    std::vector<std::string> tagger_labels = {"Bottom", "South", "North", "West", "East", "TopLow", "TopHigh"};
    for (auto const &pair : tagger_mean_map)
    {
        TRandom3 *randGen = new TRandom3(0);
        int rand = randGen->Integer(1000);
        TH1D *histo_mean = new TH1D(Form("histo_mean_%i_%i", pair.first, rand), "", 40, -40, 40); //10, -5, 5
        TH1D *histo_rms = new TH1D(Form("histo_rms_%i_%i", pair.first, rand), "", 20, 0, 20); //10, 0, 10
        int tagger = pair.first;
        std::vector<int> mean_vec = pair.second;
        for (int i = 0; i < mean_vec.size(); i++)
        {
            histo_mean->Fill(mean_vec[i]);
            histo_rms->Fill(tagger_RMS_map[tagger][i]);
        }
        histo_mean->SetTitle(Form("%s CRT Wall; Mean [ns]; Entries", tagger_labels[tagger].c_str()));
        histo_mean->Draw();

        TCanvas *canvas = new TCanvas("canvas", "canvas", 800, 600);
        canvas->cd();
        histo_mean->SetStats(0);
        histo_mean->SetLineColor(kBlack);
        histo_mean->SetLineWidth(2);
        histo_mean->Draw();
        canvas->SaveAs(Form("%sTagger_%i_Mean.pdf", savedir.c_str(), tagger));
        delete canvas;

        TCanvas *canvas2 = new TCanvas("canvas2", "canvas2", 800, 600);
        canvas2->cd();
        histo_rms->SetTitle(Form("%s CRT Wall; RMS [ns]; Entries", tagger_labels[tagger].c_str()));
        histo_rms->SetStats(0);
        histo_rms->SetLineColor(kBlack);
        histo_rms->SetLineWidth(2);
        histo_rms->Draw();
        canvas2->SaveAs(Form("%sTagger_%i_RMS.pdf", savedir.c_str(), tagger));
        delete canvas2;
    }
}
