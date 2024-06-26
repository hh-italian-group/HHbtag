#include "../interface/HH_BTag.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

namespace tensorflow {
    struct Options;
}

namespace {
    inline constexpr int GetCMSSWVersion()
    {
        int d1 =  *(PROJECT_VERSION + 6) - '0';
        int d2 =  *(PROJECT_VERSION + 7) - '0';
        if(d2 >= 0 && d2 <= 9) return d1 * 10 + d2;
        return d1;
    }

    template<typename Graph, bool>
    struct CreateSessionImpl;

    template<typename Graph>
    struct CreateSessionImpl<Graph, false> {
        static tensorflow::Session* Create(Graph* graph, const std::string& model_path)
        {
            return tensorflow::createSession(graph, model_path);
        }
    };

    template<typename Graph>
    struct CreateSessionImpl<Graph, true> {
        static tensorflow::Session* Create(Graph* graph, const std::string& model_path)
        {
            tensorflow::Options options;
            return tensorflow::createSession(graph, model_path, options);
        }
    };

    tensorflow::Session* CreateSession(tensorflow::MetaGraphDef* graph, const std::string& model_path)
    {
        return CreateSessionImpl<tensorflow::MetaGraphDef, GetCMSSWVersion() >= 14>::Create(graph, model_path);
    }
}

namespace hh_btag{

struct HH_BTag::NNDescriptor {
    std::unique_ptr<tensorflow::MetaGraphDef> graph;
    tensorflow::Session* session;
    std::string input_layer;
    std::string output_layer;
};

HH_BTag::HH_BTag(const std::array<std::string, HH_BTag::n_models>& models)
{
    for(size_t n = 0; n < HH_BTag::n_models; ++n) {
        nn_descs.at(n) = std::make_unique<NNDescriptor>();
        auto& nn_desc = *nn_descs.at(n);
        nn_desc.graph.reset(tensorflow::loadMetaGraphDef(models.at(n)));
        nn_desc.session = CreateSession(nn_desc.graph.get(), models.at(n));
        if (models.at(n).find("v1") != std::string::npos) {
                nn_desc.input_layer = "serving_default_input:0";
            } else if (models.at(n).find("v2") != std::string::npos) {
                nn_desc.input_layer = "serving_default_input_1:0";
            }
        nn_desc.output_layer = "StatefulPartitionedCall:0";
    }
}

std::vector<float> HH_BTag::GetScore(const std::vector<float>& jet_pt, const std::vector<float>& jet_eta,
                                     const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                     const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                     const std::vector<float>& jet_htt_dphi, int sample_year, int channelId,
                                     float htt_pt, float htt_eta, float htt_met_dphi, float rel_met_pt_htt_pt,
                                     float htt_scalar_pt, unsigned long long parity)
{
    tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape{1, HH_BTag::max_n_jets, HH_BTag::n_variables});
    x.flat<float>().setZero();

    if(channelId < 0 || channelId > 2)
        throw std::runtime_error("HH_BTag::GetScore: invalid channelId");
    if(sample_year < 2016 || sample_year > 2018)
        throw std::runtime_error("HH_BTag::GetScore: unknown sample_year");

    const size_t n_jets_evt = std::min(jet_pt.size(), HH_BTag::max_n_jets);
    for (size_t jet_index = 0; jet_index < n_jets_evt; ++jet_index) {
        const int n_jet = static_cast<int>(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_valid) = 1;
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_pt) = jet_pt.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_eta) = jet_eta.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_M_pt) = rel_jet_M_pt.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::rel_jet_E_pt) = rel_jet_E_pt.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_deta) = jet_htt_deta.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_deepFlavour) = jet_deepFlavour.at(jet_index);
        x.tensor<float, 3>()(0, n_jet, InputVars::vars::jet_htt_dphi) = jet_htt_dphi.at(jet_index);
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
    auto& nn_desc = *nn_descs.at(parity);
    tensorflow::run(nn_desc.session, { { nn_desc.input_layer, x } }, { nn_desc.output_layer }, &pred_vec);

    std::vector<float> scores(jet_pt.size(), 0);
    for (size_t jet_index = 0; jet_index < n_jets_evt; ++jet_index) {
        const int n_jet = static_cast<int>(jet_index);
        scores.at(jet_index) = pred_vec.at(0).matrix<float>()(0, n_jet);
    }

    return scores;
}

HH_BTag::~HH_BTag()
{
    for(size_t n = 0; n < HH_BTag::n_models; ++n)
        tensorflow::closeSession(nn_descs.at(n)->session);
}

}// namespace hh_btag
