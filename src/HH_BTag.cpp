#include "../include/HH_BTag.h"

float HH_BTag::hello()
{
    std::cout << "nutella" << '\n';
    return 10;
}

    HH_BTag::HH_BTag(const std::string& model): graph(tensorflow::loadGraphDef(model)), session(tensorflow::createSession(graph.get())),
                                                x(tensorflow::DT_FLOAT, tensorflow::TensorShape{1, 10, 14})
    {
        number_of_var = 14;
    }

    std::vector<float> HH_BTag::GetScore(float var_1, float var_2, float var_3, float var_4, float var_5, float var_6,
                                         float var_7, float var_8, float var_9, float var_10, float var_11, float var_12,
                                         float var_13, float var_14)
    {
        std::vector<float> scores;

        for (size_t n_jet = 0; n_jet < 10; n_jet++) {
            x.tensor<float, 3>()(0, n_jet, t_vars::jet_pt) = var_1;
            x.tensor<float, 3>()(0, n_jet, t_vars::jet_eta) = var_2;
            x.tensor<float, 3>()(0, n_jet, t_vars::rel_jet_M_pt) = var_3;
            x.tensor<float, 3>()(0, n_jet, t_vars::rel_jet_E_pt) = var_4;
            x.tensor<float, 3>()(0, n_jet, t_vars::jet_htt_deta) = var_5;
            x.tensor<float, 3>()(0, n_jet, t_vars::jet_deepFlavour) = var_6;
            x.tensor<float, 3>()(0, n_jet, t_vars::jet_htt_dphi) = var_7;
            x.tensor<float, 3>()(0, n_jet, t_vars::sample_year) = var_8;
            x.tensor<float, 3>()(0, n_jet, t_vars::channelId) = var_9;
            x.tensor<float, 3>()(0, n_jet, t_vars::htt_pt) = var_10;
            x.tensor<float, 3>()(0, n_jet, t_vars::htt_eta) = var_11;
            x.tensor<float, 3>()(0, n_jet, t_vars::htt_met_dphi) = var_12;
            x.tensor<float, 3>()(0, n_jet, t_vars::rel_met_pt_htt_pt) = var_13;
            x.tensor<float, 3>()(0, n_jet, t_vars::htt_scalar_pt) = var_14;
        }

        const std::string& input_layer = graph->node(0).name();
        const std::string& output_layer = graph->node(graph->node_size() - 1).name();

        std::vector<tensorflow::Tensor> pred_vec;
        tensorflow::run(session, { { input_layer, x } }, { output_layer }, &pred_vec);

        for (size_t n_jet = 0; n_jet < 10; n_jet++) {
            const float pred = pred_vec[n_jet].flat<float>()(1);
            scores.push_back(pred);
        }
        return scores;
    }
    // ~HH_BTag::HH_BTag()
    // {
    //     tensorflow::closeSession(session);
    // }

//}
