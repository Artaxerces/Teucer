/* 
 * File:   CigarFSM.cpp
 * Author: John Sarrazin
 * 
 * Created on 25. Juni 2015, 11:20
 */

#include "util/genomics_extension/CigarFSM.hpp"
#include <boost/lexical_cast.hpp>

CigarFSM::CigarFSM()
        :currentState(START),
         insertCount(0),
         matchCount(0),
         deleteCount(9),
         cigar("")
        {}

//// Use default copy constructor.
//CigarFSM::CigarFSM(const CigarFSM& orig) {
//}

 //Use default destructor
CigarFSM::~CigarFSM() {}

//
//void CigarFSM::handleInput(const char input){
//            switch (input)
//            {
//                case 'i':
//                case 'I':
//                    handleInsert();
//                    break;
//                case 'd':
//                case 'D':
//                    handleDelete();
//                    break;
//                case 'm':
//                case 'M':
//                    handleMatch();
//                    break;
//                //TODO add error handling
//                default:
//                    return;
//            }
//        }

void CigarFSM::reset(){
            currentState=START;
            insertCount=0;
            deleteCount=0;
            matchCount=0;
            cigar="";
        }

const std::string CigarFSM::getCigar(){
            //Use copy to not change state of the FSM. 
            std::string finalCigar = cigar;
            
            switch (currentState)
            {
                case DELETE:
                    finalCigar+=boost::lexical_cast<std::string>(deleteCount)+"D";
                    break;
                case INSERT:
                    finalCigar+=boost::lexical_cast<std::string>(insertCount)+"I";
                    break;
                case MATCH:
                    finalCigar+=boost::lexical_cast<std::string>(matchCount)+"M";
                    break;
            }
            return finalCigar;
        }

void CigarFSM::handleInsert(){
            switch (currentState)
            {
                case MATCH:
                    cigar+=boost::lexical_cast<std::string>(matchCount)+"M";
                    matchCount=0;
                    break;
                case DELETE:
                    cigar+=boost::lexical_cast<std::string>(deleteCount)+"D";
                    deleteCount=0;
                    break;
            }
            insertCount++;
            currentState = INSERT;
        }

void CigarFSM::handleDelete(){
            switch (currentState)
            {
                case MATCH:
                    cigar+=boost::lexical_cast<std::string>(matchCount)+"M";
                    matchCount=0;
                    break;
                case INSERT:
                    cigar+=boost::lexical_cast<std::string>(insertCount)+"I";
                    insertCount=0;
                    break;
            }
            deleteCount++;
            currentState = DELETE;
        }

void CigarFSM::handleMatch(){
            switch (currentState)
            {
                case DELETE:
                    cigar+=boost::lexical_cast<std::string>(deleteCount)+"D";
                    deleteCount=0;
                    break;
                case INSERT:
                    cigar+=boost::lexical_cast<std::string>(insertCount)+"I";
                    insertCount=0;
                    break;
            }
            matchCount++;
            currentState = MATCH;
        }

//FIXME use char instead of string
void CigarFSM::handleDatabaseInput(const std::string baseValue,const int insertOffset){
    if(baseValue == "X")
        handleDelete();
    else if(insertOffset > 0)
        handleInsert();
    else
        handleMatch();
}
