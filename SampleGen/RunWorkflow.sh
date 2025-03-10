# bin/bash

lar -c run_crt_ptb_tdc_decoder_sbnd.fcl -S /exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/ListOfDataSample/List_run_17028_OffBeamZero_file_small -o ./run17028_artroot.root
lar -c run_crtreco_data.fcl -s run17028_artroot.root -o run17028_artroot_reco.root
lar -c run_crtana_data.fcl -s run17028_artroot_reco.root 
