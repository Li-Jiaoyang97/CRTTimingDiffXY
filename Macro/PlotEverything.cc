#include "DefinePlotStyle.cc"
#include "PlotTimingDiff.cc"
#include "PlotMeanRMSPerTagger.cc"

void PlotEverything(){

    DefinePlotStyle();

    int run=18250;
    std::string fileDir = "/pnfs/sbnd/persistent/users/jiaoyang/AnalysisWorksopCRTData/";
    bool debug = false; 
    //PlotTimingDiff(run, fileDir, debug);

    std::string csvFileName_t1="/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250/PlotsModules_t1/timing_diff_fit_per_module_pair.csv";
    std::string savedir_t1 = "/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250/PlotsModules_t1/";
    int threshold = 100; // threshold for entries
    PlotMeanRMSPerTagger(csvFileName_t1, savedir_t1, threshold);

    std::string csvFileName_t0 ="/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250/PlotsModules_t0/timing_diff_fit_per_module_pair.csv";
    std::string savedir_t0 = "/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run18250/PlotsModules_t0/";
    PlotMeanRMSPerTagger(csvFileName_t0, savedir_t0, threshold);
}