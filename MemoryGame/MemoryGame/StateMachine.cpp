#include "StateMachine.h"

// initial
State StateMachine::currentState = State::INIT_STATE;
bool StateMachine::updating = true;

void StateMachine::setCurrentState(State _newState, bool _isUpdating) {
	currentState = _newState;
	updating = _isUpdating;
}
State StateMachine::getCurrentState() {
	return StateMachine::currentState;
}
void StateMachine::setUpdate(bool _isUpdating) {
	updating = _isUpdating;
}
bool StateMachine::isUpdating() {
	return StateMachine::updating;
}