#include <map>
#include "../interface/HH_BTag.h"

int main()
{
    std::array <std::string, 2> models;
    for(size_t n = 0; n < 2; ++n) {
        std::ostringstream ss_model;
        ss_model << "HHTools/HHbtag/models/HHbtag_v1_par_" << n;
        models.at(n) = ss_model.str();
    }
    hh_btag::HH_BTag test(models);

    struct inputVariables {
        std::vector<float> jet_pt;
        std::vector<float> jet_eta;
        std::vector<float> rel_jet_M_pt;
        std::vector<float> rel_jet_E_pt;
        std::vector<float> jet_htt_deta;
        std::vector<float> jet_deepFlavour;
        std::vector<float> jet_htt_dphi;
        int sample_year;
        int channelId;
        float htt_pt;
        float htt_eta;
        float htt_met_dphi;
        float rel_met_pt_htt_pt;
        float htt_scalar_pt;

        inputVariables() {}
         inputVariables(std::vector<float> _jet_pt, std::vector<float> _jet_eta, std::vector<float> _rel_jet_M_pt,
         std::vector<float> _rel_jet_E_pt, std::vector<float> _jet_htt_deta, std::vector<float> _jet_deepFlavour,
         std::vector<float> _jet_htt_dphi, int _sample_year, int _channelId, float _htt_pt, float _htt_eta,
         float _htt_met_dphi, float _rel_met_pt_htt_pt,  float _htt_scalar_pt)
            : jet_pt(_jet_pt), jet_eta(_jet_eta), rel_jet_M_pt(_rel_jet_M_pt), rel_jet_E_pt(_rel_jet_E_pt),
              jet_htt_deta(_jet_htt_deta), jet_deepFlavour(_jet_deepFlavour), jet_htt_dphi(_jet_htt_dphi),
              sample_year(_sample_year), channelId(_channelId), htt_pt(_htt_pt), htt_eta(_htt_eta),
              htt_met_dphi(_htt_met_dphi), rel_met_pt_htt_pt(_rel_met_pt_htt_pt), htt_scalar_pt(_htt_scalar_pt){}
    };

    std::vector<inputVariables> input_variables = {
        inputVariables({345.21616 , 137.2016  ,  67.34632 , 405.96768 ,  25.621525}, // example values from event number with parity odd
                       {0.29921052,  0.219595  ,  0.08965404, -0.02061346,  0.1756713},
                       {0.1059498 , 0.08227845, 0.1511094 , 0.08988122, 0.24139585},
                       {1.0504552, 1.0275075, 1.0153292, 1.0042428, 1.0437677},
                       {0.00293145, 0.08254696, 0.21248792, 0.32275543, 0.12647067},
                       {0.9823262 , 0.98088145, 0.01650896, 0.009126  , 0.00841168},
                       {-2.524436 , -2.967691 ,  1.731121 ,  0.3825634,  2.2681534},
                       2016, 2, 97.48188, 0.30214196, -2.1884985, 0.9407843, 112.31701 ),
        inputVariables({114.95624 , 157.82753 ,  20.41763 ,  22.221668}, // example values from event number with parity even
                       {-1.6304693, -2.1735725,  0.591494 ,  1.3925074},
                      {0.15912989, 0.16605657, 0.18568328, 0.19184326},
                      {2.6558259, 4.454796 , 1.1946115, 2.1452858},
                      {0.96147  ,  1.5045732, -1.2604933, -2.0615067},
                      {0.9529675 , 0.82010823, 0.00897067, 0.00666698},
                      {3.0571172, -2.6735168,  2.7761812, -2.7077053},
                      2016, 0, 306.61905, -0.6689993, 0.18338251,
                      0.32046267, 315.96207 )
    };

    for (int i = 0; i < static_cast<int>(input_variables.size()); ++i){
        auto scores = test.HH_BTag::GetScore(input_variables.at(i).jet_pt, input_variables.at(i).jet_eta,
                                             input_variables.at(i).rel_jet_M_pt, input_variables.at(i).rel_jet_E_pt,
                                             input_variables.at(i).jet_htt_deta, input_variables.at(i).jet_deepFlavour,
                                             input_variables.at(i).jet_htt_dphi, input_variables.at(i).sample_year,
                                             input_variables.at(i).channelId, input_variables.at(i).htt_pt,
                                             input_variables.at(i).htt_eta, input_variables.at(i).htt_met_dphi,
                                             input_variables.at(i).rel_met_pt_htt_pt,
                                             input_variables.at(i).htt_scalar_pt, i);

         std::cout << "*************** parity " << i << " ***************" << "\n";
         for (size_t n_jet = 0; n_jet < scores.size(); ++n_jet)
            std::cout << "jet #" << n_jet << " score = " << scores.at(n_jet) << "\n";
    }

}
