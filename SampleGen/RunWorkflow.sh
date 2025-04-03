#!/bin/bash

RUN=$1

lar -c run_crt_ptb_tdc_decoder_sbnd.fcl -n 1000 -S /exp/sbnd/app/users/jiaoyang/AnalysisWorkshop_v10_04_03/work_dir/ListOfDataSample/List_run_${RUN}_OffBeamZero_file -o /pnfs/sbnd/scratch/users/jiaoyang/AnalysisWorkshopCRTData/run${RUN}_artroot_decoded.root
lar -c run_crtreco_data.fcl -n -1 -s /pnfs/sbnd/scratch/users/jiaoyang/AnalysisWorkshopCRTData/run${RUN}_artroot_decoded.root -o /pnfs/sbnd/scratch/users/jiaoyang/AnalysisWorkshopCRTData/run${RUN}_artroot_decoded_reco.root
lar -c run_crtana_data.fcl -n -1 -s /pnfs/sbnd/scratch/users/jiaoyang/AnalysisWorkshopCRTData/run${RUN}_artroot_decoded_reco.root -T /pnfs/sbnd/persistent/users/jiaoyang/AnalysisWorksopCRTData/run${RUN}_small.root
