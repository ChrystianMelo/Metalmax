#include "Receiver.h"

Receiver::Receiver() : m_requester(nullptr), m_priority() {}

Receiver::Receiver(Requester* requester, std::unordered_map<Requester*, int> priority) :
	m_requester(requester), m_priority(priority) {}

void Receiver::setRequester(Requester* newRequester) {
	m_requester = newRequester;
}

Requester* Receiver::getRequester() const {
	return m_requester;
}

bool Receiver::isBetterMatch(Requester& newRequester) {
	return m_priority[&newRequester] < m_priority[m_requester];
}