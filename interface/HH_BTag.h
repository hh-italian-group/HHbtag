#include <vector>
#include <string>
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

namespace hh_btag{

namespace InputVars{
    enum vars { jet_valid = 0, jet_pt = 1, jet_eta = 2, rel_jet_M_pt = 3, rel_jet_E_pt = 4, jet_htt_deta = 5,
                jet_deepFlavour = 6, jet_htt_dphi = 7, sample_year= 8, channelId = 9, htt_pt = 10, htt_eta = 11,
                htt_met_dphi = 12, rel_met_pt_htt_pt = 13, htt_scalar_pt = 14
    };
 }

class HH_BTag {
public:
    static constexpr size_t n_models = 2;
    static constexpr size_t max_n_jets = 10;
    static constexpr size_t n_variables = 15;

    HH_BTag(const std::array <std::string, n_models>& models);
    ~HH_BTag();



    struct NNDescriptor {
        std::unique_ptr<tensorflow::GraphDef> graph;
        tensorflow::Session* session;
        std::string input_layer;
        std::string output_layer;
    };

    std::vector<float> GetScore(const std::vector<float>& jet_pt, const std::vector<float>& jet_eta,
                                const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                const std::vector<float>& jet_htt_dphi, int sample_year, int channelId, float htt_pt,
                                float htt_eta, float htt_met_dphi, float rel_met_pt_htt_pt,
                                float htt_scalar_pt, unsigned long long parity);

private:
    std::array<NNDescriptor, n_models> nn_descs;
};
}// namespace hh_btag
