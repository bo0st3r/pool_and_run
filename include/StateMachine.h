#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>

#include "State.h"

namespace pr
{
    typedef std::unique_ptr<State> StateRef;

    ////////////////////////////////////////////////////////////////
    /// \class Manages the states of the game. It is part of the "State" design pattern.
    ///
    /// We picked this pattern because our game has many differents states have different proccesses.
    /// It is using a Stack as states collection so the last in is the first out.
    ////////////////////////////////////////////////////////////////
    class StateMachine
    {
        public:
            StateMachine();
            virtual ~StateMachine();

            ////////////////////////////////////////////////////////////////
            /// \brief Adds a state to the stack and decides wether the last state should be removedor replaced.
            ////////////////////////////////////////////////////////////////
            void addState(StateRef newState, bool isReplacing = true);

            // Removes a state
            ////////////////////////////////////////////////////////////////
            /// \brief Removes the last state and resume the previous one.
            ////////////////////////////////////////////////////////////////
            void removeState();

            ////////////////////////////////////////////////////////////////
            /// \brief Processes the state changes : removing, adding, replacing.
            ////////////////////////////////////////////////////////////////
            void processStateChanges();

            ////////////////////////////////////////////////////////////////
            /// \brief Returns a reference to the active state.
            ////////////////////////////////////////////////////////////////
            StateRef& getActiveState();

        private:
            std::stack<StateRef> _states;
            StateRef _newState;

            bool _isRemoving;
            bool _isAdding;
            bool _isReplacing;
    };
}

#endif // STATEMACHINE_H
