#include "StateMachine.h"
#include <iostream>


namespace pr{
    StateMachine::StateMachine(){}

    StateMachine::~StateMachine(){}

    void StateMachine::addState(StateRef newState, bool isReplacing)
    {
        _isAdding = true;
        _isReplacing = isReplacing;

        // Moves the give unique_ptr to _newState
        _newState = std::move(newState);
    }

    void StateMachine::removeState()
    {
        _isRemoving = true;
        processStateChanges();
    }

    void StateMachine::processStateChanges()
    {
        // When removing and the states are not empty
        // Pops the last state and if not empty resumes the last one
        if(_isRemoving && !_states.empty())
        {
            _states.pop();

            if(!_states.empty())
            {
                _states.top()->resume();
            }
        }

        // When adding a new state
        if(_isAdding)
        {
            // If the states are not empty
            // Pops a state if isReplacing or pause the last state instead
            if(!_states.empty())
            {
                if(_isReplacing)
                {
                    _states.pop();
                }
                else
                {
                    _states.top()->pause();
                }
            }

            // Adds and inits the new state
            // Set isAdding to false

            _states.push(std::move(_newState));
            _states.top()->init();
            _isAdding = false;
        }
    }

    // Returns the reference of the state at the top of the _states Stack
    StateRef& StateMachine::getActiveState()
    {
        return _states.top();
    }
}
