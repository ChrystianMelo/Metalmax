#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <unordered_map>

#include "Requester.h"

class Requester;

/**
 * \class Receiver
 *
 * \brief Representa o receptor (destinat�rio) no algoritmo de Gale-Shapley.
 *
 * \details A classe Receiver representa os elementos que recebem propostas no algoritmo de Gale-Shapley.
 * Cada Receiver tem um mapa de prioridade que determina sua prefer�ncia sobre os diferentes Requesters.
 * Esta classe � abstrata, exigindo que as subclasses implementem o m�todo isEqual.
 */
class Receiver {
public:
	/**
	 * \brief Construtor padr�o da classe Receiver.
	 *
	 * \details Inicializa o ponteiro para o requester como nullptr e o mapa de prioridade vazio.
	 */
	Receiver();

	/**
	 * \brief
	 */
	Receiver(Requester* requester, std::unordered_map<Requester*, int> priority);

	/**
	 * \brief Define o requester associado a este Receiver.
	 *
	 * \details Associa um requester espec�fico a este Receiver. Isso reflete a proposta
	 * recebida do requester no algoritmo de Gale-Shapley.
	 *
	 * \param newRequester Um ponteiro para o requester que ser� associado a este Receiver.
	 */
	void setRequester(Requester* newRequester);

	/**
	 * \brief Obt�m o requester atualmente associado a este Receiver.
	 *
	 * \details Retorna o ponteiro para o requester que fez a proposta e foi aceito
	 * por este Receiver no algoritmo de Gale-Shapley.
	 *
	 * \return Um ponteiro para o requester associado.
	 */
	Requester* getRequester() const;

	/**
	 * \brief Verifica se um novo Requester � uma correspond�ncia melhor do que o atual.
	 *
	 * \details Este m�todo compara o Requester atual com um novo Requester, baseado nas prioridades armazenadas
	 * no mapa de prioridades da Receiver. Retorna true se o novo Requester tiver uma prioridade mais alta
	 * (valor num�rico menor) do que o atual Requester associado.
	 *
	 * \note Complexidade: O(1) � A busca em um std::unordered_map, como o utilizado para armazenar as prioridades,
	 * � realizada em tempo constante, assumindo uma boa fun��o de hash e distribui��o uniforme.
	 *
	 * \param newRequester Refer�ncia ao novo Requester que deseja fazer uma proposta.
	 * \return true se o novo Requester for uma correspond�ncia melhor (prioridade menor), false caso contr�rio.
	 */
	bool isBetterMatch(Requester& newRequester);

	/**
	 * \brief Verifica se o Receiver atual � igual a outro Receiver.
	 *
	 * \param other Outro objeto Receiver a ser comparado.
	 *
	 * \return true se os Receivers forem considerados iguais, false caso contr�rio.
	 *
	 * Este m�todo � abstrato e deve ser implementado nas subclasses para definir o crit�rio de igualdade.
	 */
	virtual bool isEqual(const Receiver& other) const = 0;

	/**
	 * \brief Operador de igualdade necess�rio para o uso em std::unordered_map.
	 * \param other Outro objeto Receiver a ser comparado.
	 * \return true se os Receivers forem iguais, false caso contr�rio.
	 */
	bool operator==(const Receiver& other) const { return isEqual(other); };

private:
	/**
	 * \brief Ponteiro para o Requester atualmente associado (casado) com este Receiver.
	 */
	Requester* m_requester;

	/**
	 * \brief Mapa de prioridade contendo a rela��o de Requesters e suas respectivas prioridades.
	 */
	std::unordered_map<Requester*, int> m_priority;

};

#endif // RECEIVER_H