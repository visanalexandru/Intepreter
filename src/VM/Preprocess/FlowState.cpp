//
// Created by gvisan on 18.08.2020.
//

#include "FlowState.h"

namespace VM{

   FlowState::FlowState():inLoop(false),inFunction(false) {

   }

   void FlowState::enterLoop() {
       inLoop=true;
   }

   void FlowState::exitLoop() {
        inLoop=false;
   }

   void FlowState::enterFunction() {
       inFunction=true;
   }

   void FlowState::exitFunction() {
       inFunction=false;
   }

   bool FlowState::isInFunction() const {
       return inFunction;
   }

   bool FlowState::isInLoop() const {
       return inLoop;
   }


}