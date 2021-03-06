/******************************************************************************
 */

#ifndef _TIME_BASED_TRIGGER_EVENT_H_
#define _TIME_BASED_TRIGGER_EVENT_H_

#include "TimeBasedTrigger.h"
#include "boost/function.hpp"
#include <vector>
#include "StdOutputHandler.h"

namespace StochLib
{
 template<typename _populationVectorType>
 class TimeBasedTriggerEvent
 {
	
 public:
  typedef boost::function<void (double, _populationVectorType&)> EventAction;
  
  TimeBasedTriggerEvent(TimeBasedTrigger triggerFunctor,
			 std::vector<EventAction> actions): 
    triggerFunctor(triggerFunctor),
    actions(actions)
      {
      }
    
    TimeBasedTriggerEvent(TimeBasedTrigger triggerFunctor,
			  EventAction action): 
      triggerFunctor(triggerFunctor),
      actions(1,action)
	{
	}

    bool trigger(double time) {
      return triggerFunctor(time);
    }

    double getTriggerTime() const {
      return triggerFunctor.getTriggerTime();
    }

    void fire(double time, _populationVectorType& population) {
      #ifdef DEBUG
      COUT << "firing time-based trigger event at t="<<time<<"\n";
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

    friend inline bool operator<(const TimeBasedTriggerEvent<_populationVectorType>& lhs, const TimeBasedTriggerEvent<_populationVectorType>& rhs) {
      return lhs.getTriggerTime() < rhs.getTriggerTime();
    }

 private:
  TimeBasedTrigger triggerFunctor;
  std::vector<EventAction> actions;
 };
}

#endif
