#include "../interface/HH_BTag.h"

int main()
{
    hh_btag::HH_BTag test({ "HHTools/HHbtag/models/model_par_0.pb", "HHTools/HHbtag/models/model_par_1.pb" });

    // //Event par 1
    // std::vector<float> jet_pt = {57.564114,  43.643867, 139.50575 ,  60.247746, 233.31581 ,
    //     70.393974,  38.037094};
    // std::vector<float> jet_eta = {0.4898809 ,  1.7326078 ,  0.935248  ,  0.41925943, -0.03784877,
    //    -0.46906093,  0.9828494};
    // std::vector<float> rel_jet_M_pt = {0.17432605, 0.20295425, 0.13147171, 0.18970183, 0.10805585,
    //    0.14510198, 0.18137462};
    // std::vector<float> rel_jet_E_pt = {1.1358674, 2.923157 , 1.4760337, 1.1055808, 1.0065333, 1.1214676,
    //    1.5339122};
    // std::vector<float> jet_htt_deta = {0.13648209, -1.1062448 , -0.30888504,  0.20710355,  0.66421175,
    //     1.0954239 , -0.35648644};
    // std::vector<float> jet_deepFlavour = {0.99971014, 0.9892675 , 0.04916491, 0.04575676, 0.00776238,
    //    0.00580782, 0.00425575};
    // std::vector<float> jet_htt_dphi = {-1.1352652 , -0.58578235, -0.90678865,  1.883052  ,  2.6213546 ,
    //     1.769499  ,  2.4972382};
    //
    // float sample_year = 2016;
    // float channelId = 0;
    //
    // float htt_pt = 202.34824;
    // float htt_eta = 0.626363;
    // float htt_met_dphi = 2.5145135;
    // float rel_met_pt_htt_pt = 0.16836564;
    // float htt_scalar_pt = 229.08098;


    // Event par 0
    std::vector<float> jet_pt = {114.95624 , 157.82753 ,  20.41763 ,  22.221668};
    std::vector<float> jet_eta = {-1.6304693, -2.1735725,  0.591494 ,  1.3925074};
    std::vector<float> rel_jet_M_pt = {0.15912989, 0.16605657, 0.18568328, 0.19184326};
    std::vector<float> rel_jet_E_pt = {2.6558259, 4.454796 , 1.1946115, 2.1452858};
    std::vector<float> jet_htt_deta = {0.96147  ,  1.5045732, -1.2604933, -2.0615067};
    std::vector<float> jet_deepFlavour = {0.9529675 , 0.82010823, 0.00897067, 0.00666698};
    std::vector<float> jet_htt_dphi = {3.0571172, -2.6735168,  2.7761812, -2.7077053};

    float sample_year = 2016;
    float channelId = 0;

    float htt_pt = 306.61905;
    float htt_eta = -0.6689993;
    float htt_met_dphi = 0.18338251;
    float rel_met_pt_htt_pt = 0.32046267;
    float htt_scalar_pt = 315.96207;

    auto scores = test.HH_BTag::GetScore(jet_pt, jet_eta, rel_jet_M_pt, rel_jet_E_pt, jet_htt_deta,
                                         jet_deepFlavour, jet_htt_dphi, sample_year, channelId, htt_pt, htt_eta, htt_met_dphi,
                                         rel_met_pt_htt_pt, htt_scalar_pt, 1);

    for (size_t i = 0; i < scores.size(); ++i)
        std::cout << "jet #" << i << " score = " << scores.at(i) << "\n";

}
