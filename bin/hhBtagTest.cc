#include <map>
#include "../interface/HH_BTag.h"

int main()
{
    std::array <std::string, 2> models;
    for(size_t n = 0; n < 2; ++n) {
        std::ostringstream ss_model;
        ss_model << "HHTools/HHbtag/models/HHbtag_v1_par_" << n << ".pb";
        std::string model = ss_model.str();
        models.at(n) = model;
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
        inputVariables({57.564114, 43.643867, 139.50575,  60.247746, 233.31581, 70.393974,  38.037094}, // example values from event number with parity odd
                       {0.4898809 ,  1.7326078 ,  0.935248  ,  0.41925943, -0.03784877, -0.46906093,  0.9828494},
                       {0.17432605, 0.20295425, 0.13147171, 0.18970183, 0.10805585, 0.14510198, 0.18137462},
                       {1.1358674, 2.923157 , 1.4760337, 1.1055808, 1.0065333, 1.1214676, 1.5339122},
                       {0.13648209, -1.1062448 , -0.30888504,  0.20710355,  0.66421175, 1.0954239 , -0.35648644},
                       {0.99971014, 0.9892675 , 0.04916491, 0.04575676, 0.00776238, 0.00580782, 0.00425575},
                       {-1.1352652 , -0.58578235, -0.90678865,  1.883052  ,  2.6213546 ,1.769499  ,  2.4972382},
                       2016, 0, 202.34824, 0.626363, 2.5145135, 0.16836564, 229.08098 ),
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
                                         input_variables.at(i).rel_met_pt_htt_pt, input_variables.at(i).htt_scalar_pt, 1);

         std::cout << "*************** parity " << i << " ***************" << "\n";
         for (size_t n_jet = 0; n_jet < scores.size(); ++n_jet)
            std::cout << "jet #" << n_jet << " score = " << scores.at(n_jet) << "\n";
    }

}
