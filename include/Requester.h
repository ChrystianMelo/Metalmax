#ifndef REQUESTER_H
#define REQUESTER_H

#include <iostream>
#include <queue>

#include "Receiver.h"

class Receiver;

/**
 * \class Requester
 *
 * \brief Representa o solicitante (proponente) no algoritmo de Gale-Shapley.
 *
 * \details A classe Requester representa os elementos que fazem as propostas no algoritmo de Gale-Shapley.
 * Cada Requester tem uma fila de prioridade que determina a ordem em que as propostas ser�o feitas.
 * Esta classe � abstrata, exigindo que as subclasses implementem o m�todo isEqual.
 */
class Requester {
public:
	/**
	 * \brief Construtor padr�o para a classe Requester.
	 *
	 * \details Inicializa o ponteiro para o receiver como nullptr e a fila de prioridade vazia.
	 */
	Requester();

	/**
	 * \brief 
	 */
	Requester(Receiver* receiver, std::queue<Receiver*> priority);

	/**
	 * \brief Define o receiver associado a este Requester.
	 *
	 * \param newReceiver Um ponteiro para o novo receiver que ser� associado ao Requester.
	 */
	void setReceiver(Receiver* newReceiver);

	/**
	 * \brief Obt�m o receiver atualmente associado a este Requester.
	 *
	 * \return Um ponteiro para o receiver associado.
	 */
	Receiver* getReceiver() const;

	/**
	 * \brief Obt�m o receiver de maior prioridade na fila.
	 *
	 * \details Retorna o pr�ximo receiver a quem o Requester far� uma proposta,
	 * com base na fila de prioridade.
	 *
	 * \return Um ponteiro para o receiver com a maior prioridade.
	 */
	Receiver* getTopPriorityReceiver() const;

	/**
	 * \brief Remove o receiver de maior prioridade da fila.
	 *
	 * \details Ap�s fazer uma proposta ao receiver de maior prioridade,
	 * ele � removido da fila de prioridades, permitindo que o pr�ximo
	 * receiver na fila seja considerado.
	 */
	void popTopPriorityReceiver();

	/**
	 * \brief Forma uma liga��o (match) entre o Requester atual e um novo Receiver.
	 *
	 * \details Este m�todo associa o Requester ao novo Receiver fornecido e vice-versa, estabelecendo
	 * uma conex�o entre eles. Al�m disso, remove o Receiver da fila de prioridade do Requester.
	 *
	 * \note Complexidade: O(1) � Todas as opera��es envolvidas (atribui��o de ponteiros e remo��o do topo da fila) s�o executadas em tempo constante.
	 *
	 * \param newReceiver Ponteiro para o Receiver que ser� associado a este Requester.
	 */
	void match(Receiver* newReceiver);

	/**
	 * \brief Verifica se o Requester atual � igual a outro Requester.
	 *
	 * \param other Outro objeto Requester a ser comparado.
	 *
	 * \return true se os Requesters forem considerados iguais, false caso contr�rio.
	 *
	 * \attention Este m�todo � abstrato e deve ser implementado nas subclasses para definir o crit�rio de igualdade.
	 */
	virtual bool isEqual(const Requester& other) const = 0;

	/**
	 * \brief Operador de igualdade necess�rio para o uso em std::unordered_map.
	 *
	 * \param other Outro objeto Requester a ser comparado.
	 *
	 * \return true se os Requesters forem iguais, false caso contr�rio.
	 */
	bool operator==(const Requester& other) const { return isEqual(other); };

private:
	/**
	 * \brief Ponteiro para o Receiver atualmente associado (casado) com este Requester.
	 */
	Receiver* m_receiver;

	/**
	 * \brief Fila de prioridade contendo os Receivers para os quais este Requester far� propostas.
	 */
	std::queue<Receiver*> m_priority;
};

#endif  // REQUESTER_H