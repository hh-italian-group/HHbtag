#include "../interface/HH_BTag.h"
#include <typeinfo>

namespace hh_btag{

HH_BTag::HH_BTag(const std::string& model): graph(tensorflow::loadGraphDef(model)), session(tensorflow::createSession(graph.get()))
{
    number_of_var = 14;

    input_layer = graph->node(0).name();
    output_layer = graph->node(graph->node_size() - 1).name();
}
    std::vector<float> HH_BTag::GetScore(const std::vector<float>& jet_valid, const std::vector<float>& jet_pt,
                                         const std::vector<float>& jet_eta,
                                         const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                         const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                         const std::vector<float>& jet_htt_dphi, const float& sample_year, const float& channelId,
                                         const float& htt_pt, const float& htt_eta, const float& htt_met_dphi,
                                         const float& rel_met_pt_htt_pt, float& htt_scalar_pt, int jet_size)
    {

        x = std::make_shared<tensorflow::Tensor>(tensorflow::DT_FLOAT, tensorflow::TensorShape{1, 10, 15});
        x->flat<float>().setZero();

        std::vector<float> scores = {};

        for (int n_jet = 0; n_jet < std::min(jet_size, 10); n_jet++) {
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_valid) = jet_pt.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_pt) = jet_pt.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_eta) = jet_eta.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_M_pt) = rel_jet_M_pt.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_E_pt) = rel_jet_E_pt.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_deta) = jet_htt_deta.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_deepFlavour) = jet_deepFlavour.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_dphi) = jet_htt_dphi.at(n_jet);
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::sample_year) = sample_year;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::channelId) = channelId;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_pt) = htt_pt;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_eta) = htt_eta;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_met_dphi) = htt_met_dphi;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::rel_met_pt_htt_pt) = rel_met_pt_htt_pt;
            x->tensor<float, 3>()(0, n_jet, InputVars::vars::htt_scalar_pt) = htt_scalar_pt;
        }
        std::vector<tensorflow::Tensor> pred_vec;

        auto shape_input =  graph->node().Get(0).attr().at("shape").shape() ;
        for (int i = 0; i < shape_input.dim_size(); i++) {
            std::cout << "input = "<<shape_input.dim(i).size()<<std::endl;
        }
        std::cout << "graph->node_size()=" << graph->node_size() << "\n";
        // auto shape =  graph->node().Get(graph->node_size()).attr().at("shape").shape() ;
        // for (int i = 0; i < shape.dim_size(); i++) {
        //     std::cout << "output =" << shape.dim(i).size()<<std::endl;
        // }

        tensorflow::run(session, { { input_layer, *x } }, { output_layer }, &pred_vec);


        for (int n_jet = 0; n_jet < std::min(jet_size, 10); n_jet++) {
            std::cout << "n_jet = " <<  n_jet<< "\n";
            const float pred = pred_vec[n_jet].flat<float>()(1);
            std::cout << "n = " << n_jet << ", score = " <<  pred << "\n";
            scores.push_back(pred);
        }
        std::cout << "size of scores = " << scores.size()  << "\n";
        return scores;
    }
    HH_BTag::~HH_BTag()
    {
        tensorflow::closeSession(session);
    }

}// namespace hh_btag
