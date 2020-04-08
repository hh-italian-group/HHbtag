#include "../interface/HH_BTag.h"
#include <iostream>


int main()
{
    hh_btag::HH_BTag test("/afs/cern.ch/work/m/mdidomen/hh-italian/Analysis_2018/CMSSW_10_2_16/src/hh-bbtautau/Studies/python/prova_pipo_v2_par1.pb");

    std::vector<float> jet_pt = {60, 50, 60};
    std::vector<float> jet_eta = {2.5, 2.4, 2.5};
    std::vector<float> rel_jet_M_pt = {3, 3, 3};
    std::vector<float> rel_jet_E_pt = {3, 3,3};
    std::vector<float> jet_htt_deta = {0.3, 0,3, 0.3};
    std::vector<float> jet_deepFlavour = {0.9, 0.98, 0.9};
    std::vector<float> jet_htt_dphi = {0.3, 0,3, 0.3};

    float sample_year = 2017;
    float channelId = 2017;

    float htt_scalar_pt = 50;

    float htt_pt = 50;
    float htt_eta = 3;
    float htt_met_dphi = 3;
    float rel_met_pt_htt_pt = 2;
    auto scores = test.HH_BTag::GetScore(jet_pt, jet_pt, jet_eta, rel_jet_M_pt, rel_jet_E_pt, jet_htt_deta,
                                           jet_deepFlavour, jet_htt_dphi, sample_year, channelId, htt_pt, htt_eta, htt_met_dphi,
                                           rel_met_pt_htt_pt, htt_scalar_pt, 3);

   // std::cout << "size of scores = " << scores.size()  << "\n";
   // for (size_t i = 0; i < scores.size(); ++i)
   // {
   //     std::cout << "i = " << i << ", score = " <<  scores.at(i) << "\n";
   // }

}
