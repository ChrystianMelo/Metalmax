#include <boost/test/unit_test.hpp>

#include "Algorithms.h"
#include "Requester.h"
#include "Receiver.h"

namespace {
	class Man : public Requester {
	public:
		std::string m_name;

		Man() : Requester(), m_name("") {}

		Man(std::string name, Receiver* receiver, std::queue<Receiver*> priority) :
			Requester(receiver, priority), m_name(name) {}

		bool isEqual(const Requester& other) const override {
			const Man* otherMan = dynamic_cast<const Man*>(&other);
			if (otherMan != nullptr) {
				return m_name == otherMan->m_name;
			}
			return false;
		}
	};

	class Woman : public Receiver {
	public:
		std::string m_name;

		Woman() : Receiver(), m_name("") {}

		Woman(std::string name, Requester* requester, std::unordered_map<Requester*, int> priority) :
			Receiver(requester, priority), m_name(name) {}

		bool isEqual(const Receiver& other) const override {
			const Woman* otherWoman = dynamic_cast<const Woman*>(&other);
			if (otherWoman != nullptr) {
				return m_name == otherWoman->m_name;
			}
			return false;
		}
	};
}

// Caso trivial - apenas um homem e uma mulher
BOOST_AUTO_TEST_CASE(GaleShapley_Trivial)
{
	std::queue<Receiver*> john_priority;
	Woman emma;
	john_priority.push(&emma);

	Man john("John", nullptr, john_priority);

	std::unordered_map<Requester*, int> emma_priority = { {&john, 1} };
	emma = Woman("Emma", nullptr, emma_priority);

	std::vector<Requester*> men = { &john };

	Algorithms::GaleShapley(men);

	BOOST_CHECK(john.getReceiver() == &emma);
	BOOST_CHECK(emma.getRequester() == &john);
}

// Preferências unilaterais
BOOST_AUTO_TEST_CASE(GaleShapley_SamePreferences)
{
	Woman emma;
	Woman olivia;
	Woman sophia;

	std::queue<Receiver*> john_priority;
	john_priority.push(&emma);
	john_priority.push(&olivia);
	john_priority.push(&sophia);
	Man john("John", nullptr, john_priority);

	std::queue<Receiver*> alex_priority;
	alex_priority.push(&emma);
	alex_priority.push(&olivia);
	alex_priority.push(&sophia);
	Man alex("Alex", nullptr, alex_priority);

	std::queue<Receiver*> tom_priority;
	tom_priority.push(&emma);
	tom_priority.push(&olivia);
	tom_priority.push(&sophia);
	Man tom("Tom", nullptr, tom_priority);

	std::unordered_map<Requester*, int> emma_priority = { {&john, 1}, {&alex, 2}, {&tom, 3} };
	std::unordered_map<Requester*, int> olivia_priority = { {&john, 1}, {&alex, 2}, {&tom, 3} };
	std::unordered_map<Requester*, int> sophia_priority = { {&john, 1}, {&alex, 2}, {&tom, 3} };

	emma = Woman("Emma", nullptr, emma_priority);
	olivia = Woman("Olivia", nullptr, olivia_priority);
	sophia = Woman("Sophia", nullptr, sophia_priority);

	std::vector<Requester*> men = { &john, &alex, &tom };

	Algorithms::GaleShapley(men);

	BOOST_CHECK(john.getReceiver() == &emma);
	BOOST_CHECK(alex.getReceiver() == &olivia);
	BOOST_CHECK(tom.getReceiver() == &sophia);
}

// Preferências opostas
BOOST_AUTO_TEST_CASE(GaleShapley_OppositePreferences)
{
	Woman emma;
	Woman olivia;
	Woman sophia;

	std::queue<Receiver*> john_priority;
	john_priority.push(&sophia);
	john_priority.push(&olivia);
	john_priority.push(&emma);
	Man john("John", nullptr, john_priority);

	std::queue<Receiver*> alex_priority;
	alex_priority.push(&sophia);
	alex_priority.push(&olivia);
	alex_priority.push(&emma);
	Man alex("Alex", nullptr, alex_priority);

	std::queue<Receiver*> tom_priority;
	tom_priority.push(&sophia);
	tom_priority.push(&olivia);
	tom_priority.push(&emma);
	Man tom("Tom", nullptr, tom_priority);

	std::unordered_map<Requester*, int> emma_priority = { {&tom, 1}, {&alex, 2}, {&john, 3} };
	std::unordered_map<Requester*, int> olivia_priority = { {&tom, 1}, {&alex, 2}, {&john, 3} };
	std::unordered_map<Requester*, int> sophia_priority = { {&tom, 1}, {&alex, 2}, {&john, 3} };

	emma = Woman("Emma", nullptr, emma_priority);
	olivia = Woman("Olivia", nullptr, olivia_priority);
	sophia = Woman("Sophia", nullptr, sophia_priority);

	std::vector<Requester*> men = { &john, &alex, &tom };

	Algorithms::GaleShapley(men);

	BOOST_CHECK(john.getReceiver() == &emma);
	BOOST_CHECK(alex.getReceiver() == &olivia);
	BOOST_CHECK(tom.getReceiver() == &sophia);
}
