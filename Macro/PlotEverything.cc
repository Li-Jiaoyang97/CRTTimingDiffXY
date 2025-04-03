#include "DefinePlotStyle.cc"
#include "PlotTimingDiff.cc"
#include "PlotMeanRMSPerTagger.cc"

void PlotEverything(int run=18348){

    DefinePlotStyle();

    std::string fileDir = "/pnfs/sbnd/persistent/users/jiaoyang/AnalysisWorksopCRTData/";
    bool debug = false; 
    PlotTimingDiff(run, fileDir, debug);

    std::string csvFileName_t1=Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t1/timing_diff_fit_per_module_pair.csv", run);
    std::string savedir_t1 = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t1/", run);
    int threshold = 100; // threshold for entries
    PlotMeanRMSPerTagger(csvFileName_t1, savedir_t1, threshold);

    std::string csvFileName_t0 = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t0/timing_diff_fit_per_module_pair.csv", run);
    std::string savedir_t0 = Form("/exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/Plots/run%i/PlotsModules_t0/", run);
    PlotMeanRMSPerTagger(csvFileName_t0, savedir_t0, threshold);
}