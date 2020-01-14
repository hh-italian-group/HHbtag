#include <fstream>
#include <boost/algorithm/string.hpp>
#include <Math/VectorUtil.h>
#include "AnalysisTools/Run/include/program_main.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

namespace hh_btag{

namespace InputVars{
    enum vars { jet_valid = 0, jet_pt = 1, jet_eta = 2, rel_jet_M_pt = 3, rel_jet_E_pt = 4, jet_htt_deta = 5,
                  jet_deepFlavour = 6, jet_htt_dphi = 7, sample_year= 8, channelId = 9, htt_pt = 10, htt_eta = 10,
                  htt_met_dphi = 11, rel_met_pt_htt_pt = 12, htt_scalar_pt = 13
    };
 }

class HH_BTag {
public:
    HH_BTag(const std::string& model);
    // ~HH_BTag();


    float hello();
    std::vector<float> GetScore(const std::vector<float>& jet_pt, const std::vector<float>& jet_eta,
                                const std::vector<float>& rel_jet_M_pt, const std::vector<float>& rel_jet_E_pt,
                                const std::vector<float>& jet_htt_deta, const std::vector<float>& jet_deepFlavour,
                                const std::vector<float>& jet_htt_dphi, const std::vector<float>& sample_year,
                                const std::vector<float>& channelId, const std::vector<float>& htt_pt,
                                const std::vector<float>& htt_eta, const std::vector<float>& htt_met_dphi,
                                const std::vector<float>& rel_met_pt_htt_pt,
                                const std::vector<float>& htt_scalar_pt);

private:
    float number_of_var;
    std::string input_layer;
    std::string output_layer;
    std::shared_ptr<tensorflow::GraphDef> graph;
    tensorflow::Session* session;
    std::shared_ptr<tensorflow::Tensor> x;

};
}// namespace hh_btag
