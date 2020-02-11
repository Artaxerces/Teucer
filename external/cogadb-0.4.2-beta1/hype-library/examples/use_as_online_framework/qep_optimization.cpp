

#include <iostream>
#include <hype.hpp>
#include <core/time_measurement.hpp>

#include <core/scheduler.hpp>
#include <util/print.hpp>

#include <query_optimization/qep.hpp>



using namespace hype;

typedef hype::core::Scheduler Scheduler;
typedef hype::core::SchedulingDecisionVector SchedulingDecisionVector;
typedef hype::core::SchedulingDecisionVectorPtr SchedulingDecisionVectorPtr;
typedef hype::core::OperatorSequence OperatorSequence;

typedef uint64_t Timestamp;

using namespace std;

typedef void (*AlgorithmImplementation)(const Tuple&);

typedef std::map<std::string,AlgorithmImplementation> OperatorMap; 
typedef std::map<std::string,double> AlgorithmSpeedMap; 

OperatorMap operator_map;
AlgorithmSpeedMap algorithm_speed_map;
double MICRO_SECONDS_PER_TUPLE=0.001;

//functions generated with:
//for NAME in SORT SELECTION GROUPBY AGGREGATION; do \
//for PD in CPU GPU; do \
//echo -e "void ${PD}_$NAME(const Tuple& tuple){\n\
//\tassert(!tuple.empty()); \
//\tboost::this_thread::sleep(boost::posix_time::microseconds(tuple[0])); \n\
//}\n"; done; done

void CPU_SORT(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["CPU_SORT"])); 
}

void GPU_SORT(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["GPU_SORT"])); 
}

void CPU_SELECTION(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["CPU_SELECTION"])); 
}

void GPU_SELECTION(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["GPU_SELECTION"])); 
}

void CPU_GROUPBY(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["CPU_GROUPBY"])); 
}

void GPU_GROUPBY(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["GPU_GROUPBY"])); 
}

void CPU_AGGREGATION(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["CPU_AGGREGATION"])); 
}

void GPU_AGGREGATION(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["GPU_AGGREGATION"])); 
}

void CPU_UNION(const Tuple& tuple){
	assert(tuple.size()==2);
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*(tuple[0]+tuple[1])*algorithm_speed_map["CPU_UNION"])); 
}

void GPU_UNION(const Tuple& tuple){
	assert(tuple.size()==2);
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*(tuple[0]+tuple[1])*algorithm_speed_map["GPU_UNION"])); 
}

void CPU_INTERSECT(const Tuple& tuple){
	assert(tuple.size()==2);
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*(tuple[0]+tuple[1])*algorithm_speed_map["CPU_INTERSECT"])); 
}

void GPU_INTERSECT(const Tuple& tuple){
	assert(tuple.size()==2);
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*(tuple[0]+tuple[1])*algorithm_speed_map["GPU_INTERSECT"])); 
}

void COPY_OPERATOR(const Tuple& tuple){
	boost::this_thread::sleep(boost::posix_time::microseconds(MICRO_SECONDS_PER_TUPLE*tuple[0]*algorithm_speed_map["COPY"])); 
}


void initOperators(){
        
        core::Scheduler& scheduler=core::Scheduler::instance();

	DeviceSpecification cpu_dev_spec(hype::PD0, //by convention, the first CPU has Device ID: PD0  (any system has at least one)
                                         hype::CPU, //a CPU is from type CPU
                                         hype::PD_Memory_0); //by convention, the host main memory has ID PD_Memory_0

	DeviceSpecification gpu_dev_spec(hype::PD1, //different porcessing device (naturally)
                                         hype::GPU, //Device Type
                                         hype::PD_Memory_1); //seperate device memory

        {
            AlgorithmSpecification cpu_alg("CPU_SORT",
                                           "SORT",
                                           hype::Least_Squares_1D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_SORT",
                                            "SORT",
                                            hype::Least_Squares_1D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }
                                         
        
        {
            AlgorithmSpecification cpu_alg("CPU_SELECTION",
                                           "SELECTION",
                                           hype::Least_Squares_1D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_SELECTION",
                                            "SELECTION",
                                            hype::Least_Squares_1D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }     
        
        {
            AlgorithmSpecification cpu_alg("CPU_GROUPBY",
                                           "GROUPBY",
                                           hype::Least_Squares_1D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_GROUPBY",
                                            "GROUPBY",
                                            hype::Least_Squares_1D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }        
        
        {
            AlgorithmSpecification cpu_alg("CPU_AGGREGATION",
                                           "AGGREGATION",
                                           hype::Least_Squares_1D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_AGGREGATION",
                                            "AGGREGATION",
                                            hype::Least_Squares_1D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }    
        
        
        {
            AlgorithmSpecification cpu_alg("CPU_UNION",
                                           "UNION",
                                           hype::Multilinear_Fitting_2D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_UNION",
                                            "UNION",
                                            hype::Multilinear_Fitting_2D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }    
        
        {
            AlgorithmSpecification cpu_alg("CPU_INTERSECT",
                                           "INTERSECT",
                                           hype::Multilinear_Fitting_2D,
                                           hype::Periodic,
                                           hype::ResponseTime);

            AlgorithmSpecification gpu_alg("GPU_INTERSECT",
                                            "INTERSECT",
                                            hype::Multilinear_Fitting_2D,
                                            hype::Periodic,
                                            hype::ResponseTime);

            scheduler.addAlgorithm(cpu_alg, cpu_dev_spec);
            scheduler.addAlgorithm(gpu_alg, gpu_dev_spec);
        }    
        
        //register operators
        //generated with 
        //for NAME in SORT SELECTION GROUPBY AGGREGATION; do \
        //for PD in CPU GPU; do \
        //echo -e "operator_map.insert(make_pair(\"${PD}_$NAME\",&${PD}_$NAME));"; done; done
        operator_map.insert(make_pair("CPU_SORT",&CPU_SORT));
        operator_map.insert(make_pair("GPU_SORT",&GPU_SORT));
        operator_map.insert(make_pair("CPU_SELECTION",&CPU_SELECTION));
        operator_map.insert(make_pair("GPU_SELECTION",&GPU_SELECTION));
        operator_map.insert(make_pair("CPU_GROUPBY",&CPU_GROUPBY));
        operator_map.insert(make_pair("GPU_GROUPBY",&GPU_GROUPBY));
        operator_map.insert(make_pair("CPU_AGGREGATION",&CPU_AGGREGATION));
        operator_map.insert(make_pair("GPU_AGGREGATION",&GPU_AGGREGATION));

        operator_map.insert(make_pair("CPU_UNION",&CPU_UNION));
        operator_map.insert(make_pair("GPU_UNION",&GPU_UNION));
        operator_map.insert(make_pair("CPU_INTERSECT",&CPU_INTERSECT));
        operator_map.insert(make_pair("GPU_INTERSECT",&GPU_INTERSECT));
        
        
        operator_map.insert(make_pair("COPY_CPU_CP",&COPY_OPERATOR));
        operator_map.insert(make_pair("COPY_CP_CPU",&COPY_OPERATOR));
        operator_map.insert(make_pair("COPY_CP_CP",&COPY_OPERATOR));
        
        //generated with 
        //for NAME in SORT SELECTION GROUPBY AGGREGATION; do \
        //for PD in CPU GPU; do \
        //echo -e "algorithm_speed_map.insert(make_pair(\"${PD}_$NAME\",1.0));"; done; done
        algorithm_speed_map.insert(make_pair("CPU_SORT",1.0));
        algorithm_speed_map.insert(make_pair("GPU_SORT",0.33));
        algorithm_speed_map.insert(make_pair("CPU_SELECTION",0.25));
        algorithm_speed_map.insert(make_pair("GPU_SELECTION",1.0));
        algorithm_speed_map.insert(make_pair("CPU_GROUPBY",1.0));
        algorithm_speed_map.insert(make_pair("GPU_GROUPBY",0.5));
        algorithm_speed_map.insert(make_pair("CPU_AGGREGATION",1.0));
        algorithm_speed_map.insert(make_pair("GPU_AGGREGATION",0.1));
        
        
        algorithm_speed_map.insert(make_pair("CPU_UNION",1.0));
        algorithm_speed_map.insert(make_pair("GPU_UNION",0.4));
        algorithm_speed_map.insert(make_pair("CPU_INTERSECT",1.0));
        algorithm_speed_map.insert(make_pair("GPU_INTERSECT",0.4));
        
        algorithm_speed_map.insert(make_pair("COPY_CPU_CP",10.0));   
        algorithm_speed_map.insert(make_pair("COPY_CP_CPU",10.0));
        algorithm_speed_map.insert(make_pair("COPY_CP_CP",10.0));
        
        
        core::Scheduler::instance().print();
        
} 



void executeOperator(const SchedulingDecision& sched_dec){
        OperatorMap::iterator it=operator_map.find(sched_dec.getNameofChoosenAlgorithm());
        Timestamp begin=core::getTimestamp();
        (*(it->second))(sched_dec.getFeatureValues());   
        Timestamp end=core::getTimestamp();
        core::Scheduler::instance().addObservation(sched_dec,double(end-begin));
}


void executePlan(SchedulingDecisionVectorPtr phy_plan){

    for(unsigned int i=0;i<phy_plan->size();++i){
        executeOperator((*phy_plan)[i]);
    }

}

void trainOperators(){
    
    std::vector<std::string> operator_names;
    operator_names.push_back("SELECTION");
    operator_names.push_back("SORT");
    operator_names.push_back("GROUPBY");
    operator_names.push_back("AGGREGATION");
    
//    OperatorMap::iterator it;
//    for(it=operator_map.begin();it!=operator_map.end();++it){
      for(unsigned int i=0;i<operator_names.size();++i){
        cout << "Train Algorithm " << operator_names[i] << endl; 
        for(unsigned int j=10000;j<10*1000*1000;j+=10000){

            Tuple t; t.push_back(j);
            OperatorSpecification op_spec(operator_names[i],
                                          t,
                                          hype::PD_Memory_0, //input data is in CPU RAM
                                          hype::PD_Memory_0); //output data has to be stored in CPU RAM

            DeviceConstraint dev_constr;

            executeOperator(core::Scheduler::instance().getOptimalAlgorithm(op_spec,dev_constr));
            
        }
    }
    
    
        std::vector<std::string> binary_operator_names;
        binary_operator_names.push_back("UNION");
        binary_operator_names.push_back("INTERSECT");
        
        for(unsigned int i=0;i<binary_operator_names.size();++i){
          cout << "Train Algorithm " << binary_operator_names[i] << endl; 
          for(unsigned int j=10000;j<10*1000*1000;j+=10000){
              //two values in feature vectors
              Tuple t; t.push_back(j); t.push_back(j);
              OperatorSpecification op_spec(binary_operator_names[i],
                                            t,
                                            hype::PD_Memory_0, //input data is in CPU RAM
                                            hype::PD_Memory_0); //output data has to be stored in CPU RAM

              DeviceConstraint dev_constr;

              executeOperator(core::Scheduler::instance().getOptimalAlgorithm(op_spec,dev_constr));

          }
      }
    
        std::vector<std::string> copy_operator_names;
        copy_operator_names.push_back("COPY_CPU_CP");
        copy_operator_names.push_back("COPY_CP_CPU");
        copy_operator_names.push_back("COPY_CP_CP");
        
      for(unsigned int i=0;i<copy_operator_names.size();++i){
        cout << "Train Algorithm " << copy_operator_names[i] << endl; 
        for(unsigned int j=10000;j<10*1000*1000;j+=100000){

            Tuple t; t.push_back(j);
            OperatorSpecification op_spec(copy_operator_names[i],
                                          t,
                                          hype::PD_Memory_0, //input data is in CPU RAM
                                          hype::PD_Memory_1); //output data has to be stored in CPU RAM

            DeviceConstraint dev_constr;

            executeOperator(core::Scheduler::instance().getOptimalAlgorithm(op_spec,dev_constr));
            
        }
      }
    
}
                
int main(){

    
    initOperators();
    
    trainOperators();
//    
//    OperatorSequence op_seq;
//    
//    {
//    Tuple t; t.push_back(6*1000*1000);
//    OperatorSpecification op_spec("SELECTION",
//                                  t,
//                                  hype::PD_Memory_0, //input data is in CPU RAM
//                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM
//
//    DeviceConstraint dev_constr;
//
//    op_seq.push_back(make_pair(op_spec, dev_constr));
//    }
//
//    {
//    Tuple t; t.push_back(1000*1000);
//    OperatorSpecification op_spec("SORT",
//                                  t,
//                                  hype::PD_Memory_0, //input data is in CPU RAM
//                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM
//
//    DeviceConstraint dev_constr;
//
//    op_seq.push_back(make_pair(op_spec, dev_constr));
//    }
//    
//    {
//    Tuple t; t.push_back(1000*1000);  
//    OperatorSpecification op_spec("GROUPBY",
//                                  t,
//                                  hype::PD_Memory_0, //input data is in CPU RAM
//                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM
//
//    DeviceConstraint dev_constr;
//
//    op_seq.push_back(make_pair(op_spec, dev_constr));
//    }
//    
//    {
//    Tuple t; t.push_back(1000*1000);
//    OperatorSpecification op_spec("AGGREGATION",
//                                  t,
//                                  hype::PD_Memory_0, //input data is in CPU RAM
//                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM
//
//    DeviceConstraint dev_constr;
//
//    op_seq.push_back(make_pair(op_spec, dev_constr));
//    }
//    util::print(op_seq,cout);
    
    
    
    
    
    hype::query_optimization::QEP_Node* root; //(op_spec, dev_constr);
    
    {
    Tuple t; t.push_back(100*1000); t.push_back(100*1000);
    OperatorSpecification op_spec("UNION",
                                  t,
                                  hype::PD_Memory_0, //input data is in CPU RAM
                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM

    DeviceConstraint dev_constr;
    
    root = new hype::query_optimization::QEP_Node(op_spec, dev_constr);
    }

    hype::query_optimization::QEP_Node* childs[3];
    for(unsigned int j=0;j<2;++j){
        
    Tuple t; t.push_back(1*1000*1000); t.push_back(1*1000*1000);
    OperatorSpecification op_spec("INTERSECT",
                                  t,
                                  hype::PD_Memory_0, //input data is in CPU RAM
                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM

    DeviceConstraint dev_constr;
    
    childs[j] = new hype::query_optimization::QEP_Node(op_spec, dev_constr);
    
    hype::query_optimization::QEP_Node* sel_childs[2];
    for(unsigned int i=0;i<2;++i){
    Tuple t; t.push_back(6*1000*1000);
    OperatorSpecification op_spec("SELECTION",
                                  t,
                                  hype::PD_Memory_0, //input data is in CPU RAM
                                  hype::PD_Memory_0); //output data has to be stored in CPU RAM

    DeviceConstraint dev_constr;
    
    sel_childs[i] = new hype::query_optimization::QEP_Node(op_spec, dev_constr);
    }
    
    childs[j]->setChilds(sel_childs,2);
    }
    root->setChilds(childs,2);
    hype::query_optimization::QEP plan(root);
    
    cout << plan.toString() << endl;
    
    std::list<hype::query_optimization::QEP_Node*> order = plan.reverselevelorder_traversal(); //plan.levelorder_traversal();
    std::list<hype::query_optimization::QEP_Node*>::iterator it;
    for(it=order.begin();it!=order.end();++it){
        cout << (*it)->op_spec.getOperatorName() << "\t Nr. Featues: " << (*it)->op_spec.getFeatureVector().size() << endl;
    }

    hype::query_optimization::QEP new_plan(plan);
    std::cout << "New Plan: " << std::endl;
    std::cout << new_plan.toString() << std::endl;
    
    order = new_plan.reverselevelorder_traversal(); //plan.levelorder_traversal();
    for(it=order.begin();it!=order.end();++it){
        cout << (*it)->op_spec.getOperatorName() << "\t Nr. Featues: " << (*it)->op_spec.getFeatureVector().size() << endl;
    }
    
    hype::query_optimization::QEP plan_for_backtracking(plan);
    hype::query_optimization::QEP plan_for_greedy(plan);
    
    hype::query_optimization::optimizeQueryPlan(plan_for_backtracking,BACKTRACKING);
    
    hype::query_optimization::optimizeQueryPlan(plan_for_greedy,GREEDY_HEURISTIC);
    
    hype::query_optimization::QEP_Node* qep_root_new = plan_for_greedy.removeRoot();
    
    hype::query_optimization::QEP printout_plan(new hype::query_optimization::QEP_Node(*qep_root_new));
    delete qep_root_new;
    std::cout << printout_plan.toString() << std::endl;
    
    return 0;
}


