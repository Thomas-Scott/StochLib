/******************************************************************************
 */

#ifndef _STATE_BASED_TRIGGER_EVENT_H_
#define _STATE_BASED_TRIGGER_EVENT_H_

#include "StdOutputHandler.h"
#include "CustomStateBasedTrigger.h"
#include "boost/function.hpp"
#include <vector>

namespace StochLib
{
 template<typename _populationVectorType>
 class StateBasedTriggerEvent
 {
	
 public:
  typedef boost::function<void (double, _populationVectorType&)> EventAction;

  StateBasedTriggerEvent(CustomStateBasedTrigger<_populationVectorType> triggerFunctor,
			 EventAction action):
    triggerFunctor(triggerFunctor),
    actions(1,action)
      {
      }

  StateBasedTriggerEvent(CustomStateBasedTrigger<_populationVectorType> triggerFunctor,
			 std::vector<EventAction> actions):
    triggerFunctor(triggerFunctor),
    actions(actions)
      {
      }
    

    bool trigger(double time, _populationVectorType& population) {
      return triggerFunctor(time, population);
    }

    void fire(double time, _populationVectorType& population) {
      #ifdef DEBUG
      COUT << "firing state-based trigger event at t="<<time<<"\n";
      COUT << "population before firing:\n";
      for (std::size_t i=0; i!=population.size(); ++i) {
	COUT << "population["<<i<<"]="<<population[i]<<"\n";
      }
      COUT << "firing "<<actions.size()<<" actions...\n";
      #endif

      for (std::size_t i=0; i<actions.size(); ++i) {
	actions[i](time,population);
      }

      #ifdef DEBUG
      COUT << "population after firing:\n";
      for (std::size_t i=0; i!=population.size(); ++i) {
	COUT << "population["<<i<<"]="<<population[i]<<"\n";
      }
      #endif
    }

    void reset() {
      triggerFunctor.reset();
    }

 private:
  CustomStateBasedTrigger<_populationVectorType> triggerFunctor;
  std::vector<EventAction> actions;

 };
}

#endif
