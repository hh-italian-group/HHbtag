# HH-btag   
Interface providing feature computation for CMS RunII HH-btag  NN to the identification of the reconstructed b-jets for the final state of hh->bbtautau

# Installation

1. cmsrel CMSSW_10_2_20
1. cd CMSSW_10_2_20/src
1. cmsenv
1. git clone git@github.com:hh-italian-group/HHbtag.git
1. scram b

# Testing
1. hhBtagTest
Will produce the resulting scores for the input values for two events

# Features

The features used for the training are:

1. jet_pt: pT of each of the jets
1. jet_eta: eta of each of the jets
1. rel_jet_M_pt: Relative mass of the b-jet candidate: jet M / jet pT
1. rel_jet_E_pt Relative energy of the b-jet candidate: jet E / jet pT
1. jet_htt_deta: Eta between the b-jet and the HTT candidate. The HTT 4-momentum is calculated as the sum of the 4-momentum of the 2 taus with highest DeepTauVsJet Discriminator)
1. jet_deepFlavour: The score of the b-jet candidate given by the DeepFlavour b-tagger
1. jet_htt_dphi: Phi between the b-jet and the HTT candidate (HTT 4-momentum calculated as the sum of the 4-momentum of the 2 taus with highest DeepTauVsJet Discriminator)
1. sample_year: Year of the sample (2016, 2017 or 2018)
1. channelId: 0 - eTau, 1 - muTau, 2 tauTau
1. htt_pt: pT of HTT candidate
1. htt_eta: pT of HTT candidate
1. htt_met_dphi: Phi between the HTT candidate and the MET
1. rel_met_pt_htt_pt: Relative MET:  MET / pT of HTT candidate
1. htt_scalar_pt: Sum of the pT of  the 2 taus with highest DeepTauVsJet Discriminator
