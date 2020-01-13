#include <fstream>
#include <boost/algorithm/string.hpp>
#include <Math/VectorUtil.h>
#include "AnalysisTools/Run/include/program_main.h"
#include "AnalysisTools/Core/include/RootExt.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

class HH_BTag {
public:
    HH_BTag(const std::string& model);
    // ~HH_BTag();

    float hello();
    std::vector<float> GetScore(float var_1, float var_2, float var_3, float var_4, float var_5, float var_6, float var_7,
                                float var_8, float var_9, float var_10, float var_11, float var_12, float var_13, float var_14);

    enum t_vars {jet_valid = 0, jet_pt = 1, jet_eta = 2, rel_jet_M_pt = 3, rel_jet_E_pt = 4, jet_htt_deta = 5,
             jet_deepFlavour = 6, jet_htt_dphi = 7, sample_year= 8, channelId = 9, htt_pt = 10, htt_eta = 10,
             htt_met_dphi = 11, rel_met_pt_htt_pt = 12, htt_scalar_pt = 13};
private:
    float number_of_var;
    std::shared_ptr<tensorflow::GraphDef> graph;
    tensorflow::Session* session;
    tensorflow::Tensor x;

};
