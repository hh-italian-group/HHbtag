#include "HH-btag/include/HH_BTag.h"

namespace hh_btag{

HH_BTag::HH_BTag(const std::string& model): graph(tensorflow::loadGraphDef(model)), session(tensorflow::createSession(graph.get()))
{
    number_of_var = 14;

    input_layer = graph->node(0).name();

    output_layer = graph->node(graph->node_size() - 1).name();

}
    std::vector<float> HH_BTag::GetScore(const std::vector<float>& jet_pt, const std::vector<float>& jet_eta,
                                         const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                         const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                         const std::vector<float>& jet_htt_dphi, const float& sample_year, const float& channelId,
                                         const float& htt_pt, const float& htt_eta, const float& htt_met_dphi,
                                         const float& rel_met_pt_htt_pt, float& htt_scalar_pt, int jet_size)
    {

        // x = std::make_shared<tensorflow::Tensor>(tensorflow::DT_FLOAT, tensorflow::TensorShape{1, 10, 14});
        // x->flat<float>().setZero();

        std::vector<float> scores = {};
        // std::cout << "input_layer=" << input_layer << '\n';
        //
        // for (unsigned long n_jet = 0; n_jet < std::min(jet_size, 10); n_jet++) {
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_pt) = jet_pt.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_eta) = jet_eta.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_M_pt) = rel_jet_M_pt.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_E_pt) = rel_jet_E_pt.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_deta) = jet_htt_deta.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_deepFlavour) = jet_deepFlavour.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_dphi) = jet_htt_dphi.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::sample_year) = sample_year.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::channelId) = channelId.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_pt) = htt_pt.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_eta) = htt_eta.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_met_dphi) = htt_met_dphi.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_met_pt_htt_pt) = rel_met_pt_htt_pt.at(n_jet);
        //     x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_scalar_pt) = htt_scalar_pt.at(n_jet);
        // }
        //
        // std::vector<tensorflow::Tensor> pred_vec;
        // tensorflow::run(session, { { input_layer, *x } }, { output_layer }, &pred_vec);
        //
        // for (size_t n_jet = 0; n_jet < 10; n_jet++) {
        //     const float pred = pred_vec[n_jet].flat<float>()(1);
        //     scores.push_back(pred);
        // }
        return scores;
    }
    HH_BTag::~HH_BTag()
    {
        tensorflow::closeSession(session);
    }

}// namespace hh_btag