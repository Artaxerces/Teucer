#pragma once

#include <core/selection_expression.hpp>
#include <query_processing/column_processing/definitions.hpp>
#include <persistence/storage_manager.hpp>
#include <query_processing/operator_extensions.hpp>

namespace CoGaDB {
    namespace query_processing {
        namespace physical_operator {

            class CPU_column_convert_bitmap_to_positionlist : public hype::queryprocessing::UnaryOperator<ColumnPtr, ColumnPtr>, public PositionListOperator {
            public:
                typedef column_processing::cpu::TypedOperatorPtr TypedOperatorPtr;
                CPU_column_convert_bitmap_to_positionlist(const hype::SchedulingDecision& sched_dec, TypedOperatorPtr child);
                virtual bool execute();
                virtual ~CPU_column_convert_bitmap_to_positionlist();
            };
            
//            class GPU_column_convert_bitmap_to_positionlist : public hype::queryprocessing::UnaryOperator<ColumnPtr, ColumnPtr>, public PositionListOperator {
//            public:
//                typedef column_processing::cpu::TypedOperatorPtr TypedOperatorPtr;
//                GPU_column_convert_bitmap_to_positionlist(const hype::SchedulingDecision& sched_dec, TypedOperatorPtr child);
//                virtual bool execute();
//                virtual void releaseInputData();
//                virtual bool isInputDataCachedInGPU();
//                virtual ~GPU_column_convert_bitmap_to_positionlist();
//            };
            
                       

            column_processing::cpu::Physical_Operator_Map_Ptr map_init_function_column_convert_bitmap_to_positionlist();
            column_processing::cpu::TypedOperatorPtr create_CPU_column_convert_bitmap_to_positionlist(column_processing::cpu::TypedLogicalNode& logical_node, const hype::SchedulingDecision&, column_processing::cpu::TypedOperatorPtr left_child, column_processing::cpu::TypedOperatorPtr right_child);
//            column_processing::cpu::TypedOperatorPtr create_GPU_column_convert_bitmap_to_positionlist(column_processing::cpu::TypedLogicalNode& logical_node, const hype::SchedulingDecision&, column_processing::cpu::TypedOperatorPtr left_child, column_processing::cpu::TypedOperatorPtr right_child);
            
        }//end namespace physical_operator

        namespace logical_operator {

            class Logical_Column_Convert_Bitmap_To_PositionList : public hype::queryprocessing::TypedNode_Impl<ColumnPtr, physical_operator::map_init_function_column_convert_bitmap_to_positionlist> //init_function_column_convert_bitmap_to_positionlist> //init_function_column_convert_bitmap_to_positionlist>
            {
            public:
                Logical_Column_Convert_Bitmap_To_PositionList(hype::DeviceConstraint dev_constr = hype::DeviceConstraint());

                virtual unsigned int getOutputResultSize() const;

                virtual double getCalculatedSelectivity() const;

                virtual std::string getOperationName() const;

                std::string toString(bool verbose) const;

            };

        }//end namespace logical_operator

    }//end namespace query_processing

}; //end namespace CogaDB