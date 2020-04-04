#include "DataLoad.h"
void DataLoad::init(const Eigen::VectorXd & loads_p,
                    const Eigen::VectorXd & loads_q,
                    const Eigen::VectorXi & loads_bus_id)
{
    p_mw_ = loads_p;
    q_mvar_ = loads_q;
    bus_id_ = loads_bus_id;
    status_ = std::vector<bool>(loads_p.size(), true);
}

void DataLoad::fillSbus(Eigen::VectorXcd & Sbus, bool ac, const std::vector<int> & id_grid_to_solver){
    int nb_load = nb();
    int bus_id_me, bus_id_solver;
    cdouble tmp;
    for(int load_id = 0; load_id < nb_load; ++load_id){
        //  i don't do anything if the load is disconnected
        if(!status_[load_id]) continue;

        bus_id_me = bus_id_(load_id);
        bus_id_solver = id_grid_to_solver[bus_id_me];
        if(bus_id_solver == _deactivated_bus_id){
            //TODO improve error message with the gen_id
            throw std::runtime_error("One load is connected to a disconnected bus.");
        }
        tmp = static_cast<cdouble>(p_mw_(load_id));
        if(ac) tmp += my_i * q_mvar_(load_id);
        Sbus.coeffRef(bus_id_solver) -= tmp;
    }
}

void DataLoad::compute_results(const Eigen::Ref<Eigen::VectorXd> & Va,
                               const Eigen::Ref<Eigen::VectorXd> & Vm,
                               const Eigen::Ref<Eigen::VectorXcd> & V,
                               const std::vector<int> & id_grid_to_solver,
                               const Eigen::VectorXd & bus_vn_kv)
{
    int nb_load = nb();
    v_kv_from_vpu(Va, Vm, status_, nb_load, bus_id_, id_grid_to_solver, bus_vn_kv, res_v_);
    res_p_ = p_mw_;
    res_q_ = q_mvar_;
}

void DataLoad::reset_results(){
    res_p_ = Eigen::VectorXd();  // in MW
    res_q_ =  Eigen::VectorXd();  // in MVar
    res_v_ = Eigen::VectorXd();  // in kV
}

void DataLoad::change_p(int load_id, double new_p, bool & need_reset)
{
    bool my_status = status_.at(load_id); // and this check that load_id is not out of bound
    if(!my_status) throw std::runtime_error("Impossible to change the active value of a disconnected load");
    p_mw_(load_id) = new_p;
}

void DataLoad::change_q(int load_id, double new_q, bool & need_reset)
{
    bool my_status = status_.at(load_id); // and this check that load_id is not out of bound
    if(!my_status) throw std::runtime_error("Impossible to change the reactive value of a disconnected load");
    q_mvar_(load_id) = new_q;
}

double DataLoad::get_p_slack(int slack_bus_id)
{
    int nb_element = nb();
    double res = 0.;
    for(int line_id = 0; line_id < nb_element; ++line_id)
    {
        if(!status_[line_id]) continue;
        if(bus_id_(line_id) == slack_bus_id) res -= res_p_(line_id);
    }
    return res;
}
