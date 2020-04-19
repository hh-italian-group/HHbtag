#include "../interface/HH_BTag.h"

namespace hh_btag{

HH_BTag::HH_BTag(const std::array<std::string, HH_BTag::n_models>& models)
{
    for(size_t n = 0; n < HH_BTag::n_models; ++n) {
        nn_descs.at(n).graph.reset(tensorflow::loadGraphDef(models.at(n)));
        nn_descs.at(n).session = tensorflow::createSession(nn_descs.at(n).graph.get());
        nn_descs.at(n).input_layer = nn_descs.at(n).graph->node(0).name();
        nn_descs.at(n).output_layer = nn_descs.at(n).graph->node(nn_descs.at(n).graph->node_size() - 1).name();
    }

}

std::vector<float> HH_BTag::GetScore(const std::vector<float>& jet_pt, const std::vector<float>& jet_eta,
                                     const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                     const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                     const std::vector<float>& jet_htt_dphi, int sample_year, int channelId, float htt_pt,
                                     float htt_eta, float htt_met_dphi, float rel_met_pt_htt_pt,
                                     float htt_scalar_pt, int parity)
{
    tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape{1, HH_BTag::max_n_jets, HH_BTag::n_variables});
    x.flat<float>().setZero();

    int n_jets_evt = std::min(static_cast<int>(jet_pt.size()), static_cast<int>(HH_BTag::max_n_jets));
    for (int n_jet = 0; n_jet < n_jets_evt; n_jet++) {
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_valid) = 1;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_pt) = jet_pt.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_eta) = jet_eta.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_M_pt) = rel_jet_M_pt.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_E_pt) = rel_jet_E_pt.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_deta) = jet_htt_deta.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_deepFlavour) = jet_deepFlavour.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_dphi) = jet_htt_dphi.at(n_jet);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::sample_year) = sample_year;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::channelId) = channelId;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::htt_pt) = htt_pt;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::htt_eta) = htt_eta;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::htt_met_dphi) = htt_met_dphi;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::rel_met_pt_htt_pt) = rel_met_pt_htt_pt;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::htt_scalar_pt) = htt_scalar_pt;
    }
    std::vector<tensorflow::Tensor> pred_vec;
    parity = parity % n_models;
    tensorflow::run(nn_descs.at(parity).session, { { nn_descs.at(parity).input_layer, x } },
                    { nn_descs.at(parity).output_layer }, &pred_vec);

    std::vector<float> scores(jet_pt.size(), 0);
    for (int n_jet = 0; n_jet < n_jets_evt; n_jet++)
        scores.at(n_jet) = pred_vec.at(0).matrix<float>()(0, n_jet);

    return scores;
}
HH_BTag::~HH_BTag()
{
    for(size_t n = 0; n < HH_BTag::n_models; ++n)
        tensorflow::closeSession(nn_descs.at(n).session);
}

}// namespace hh_btag
