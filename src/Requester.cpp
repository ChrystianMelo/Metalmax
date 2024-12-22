#include "Requester.h"

Requester::Requester() : m_receiver(nullptr), m_priority() {}

Requester::Requester(Receiver* receiver, std::queue<Receiver*> priority) :
	m_receiver(receiver), m_priority(priority) {}

void Requester::setReceiver(Receiver* newReceiver) {
	m_receiver = newReceiver;
}

Receiver* Requester::getReceiver() const {
	return m_receiver;
}

Receiver* Requester::getTopPriorityReceiver() const {
	return m_priority.front();
}

void Requester::popTopPriorityReceiver() {
	return m_priority.pop();
}

void Requester::match(Receiver* newReceiver) {
	m_receiver = newReceiver;
	newReceiver->setRequester(this);

	m_priority.pop();
}
