#include "StateMachine.h"

namespace pr
{
StateMachine::StateMachine()
{
    //ctor
}

StateMachine::~StateMachine()
{
    //dtor
}

void StateMachine::addState(StateRef newState, bool isReplaceing)
{
    this->_isAdding = true;
    this->_isReplacing = isReplaceing;

    // Nullify the given StateRef and fills _newState with it.
    this->_newState = std::move(newState);
}

void StateMachine::removeState()
{
    this->_isRemoving = true;
}

void StateMachine::processStateChanges()
{
    // When removing and the states are not empty
    // Pops the last state and if not empty resumes the last one
    if(this->_isRemoving && !this->_states.empty())
    {
        this->_states.pop();

        if(!this->_states.empty())
        {
            this->_states.top()->resume();
        }
    }

    // When adding a new state
    if(this ->_isAdding)
    {
        // If the states are not empty
        // Pops a state if isReplacing or pause the last state instead
        if(!this->_states.empty())
        {
            if(this->_isReplacing)
            {
                this->_states.pop();
            }
            else
            {
                this->_states.top()->pause();
            }
        }

        // Adds and inits the new state
        // Set isAdding to false
        this->_states.push(std::move(this->_newState));
        this->_states.top()->init();
        this->_isAdding = false;
    }
}


// Returns the reference of the state at the top of the _states Stack
StateRef& StateMachine::GetActiveState()
{
    return this->_states.top();
}

}
