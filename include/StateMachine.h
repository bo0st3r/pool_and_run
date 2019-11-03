#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>

#include "State.h"

namespace pr
{
    typedef std::unique_ptr<State> StateRef;

    ////////////////////////////////////////////////////////////////
    /// \class StateMachine is part of the State design pattern and manages the differents possible states.
    ////////////////////////////////////////////////////////////////
    // The StateMachine is used to manage all the states.
    // This cliss will be adding/removing states, process the state changes, ...
    // It is using a Stack as states collection so the last in is the first out.
    class StateMachine
    {
        public:
            StateMachine();
            virtual ~StateMachine();

            // Adds a new state.
            // Decide wether the last state should be removed (isReplacing, default value) or paused (!isReplacing)
            void addState(StateRef newState, bool isReplaceing = true);
            // Removes a state
            void removeState();
            void processStateChanges();

            StateRef& GetActiveState();

        private:
            std::stack<StateRef> _states;
            StateRef _newState;

            bool _isRemoving;
            bool _isAdding;
            bool _isReplacing;
    };
}

#endif // STATEMACHINE_H
