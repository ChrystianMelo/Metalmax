#ifndef RECEIVER_H
#define RECEIVER_H

#include <iostream>
#include <unordered_map>

#include "Requester.h"

class Requester;

/**
 * \class Receiver
 *
 * \brief Representa o receptor (destinatário) no algoritmo de Gale-Shapley.
 *
 * \details A classe Receiver representa os elementos que recebem propostas no algoritmo de Gale-Shapley.
 * Cada Receiver tem um mapa de prioridade que determina sua preferência sobre os diferentes Requesters.
 * Esta classe é abstrata, exigindo que as subclasses implementem o método isEqual.
 */
class Receiver {
public:
	/**
	 * \brief Construtor padrão da classe Receiver.
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
	 * \details Associa um requester específico a este Receiver. Isso reflete a proposta
	 * recebida do requester no algoritmo de Gale-Shapley.
	 *
	 * \param newRequester Um ponteiro para o requester que será associado a este Receiver.
	 */
	void setRequester(Requester* newRequester);

	/**
	 * \brief Obtém o requester atualmente associado a este Receiver.
	 *
	 * \details Retorna o ponteiro para o requester que fez a proposta e foi aceito
	 * por este Receiver no algoritmo de Gale-Shapley.
	 *
	 * \return Um ponteiro para o requester associado.
	 */
	Requester* getRequester() const;

	/**
	 * \brief Verifica se um novo Requester é uma correspondência melhor do que o atual.
	 *
	 * \details Este método compara o Requester atual com um novo Requester, baseado nas prioridades armazenadas
	 * no mapa de prioridades da Receiver. Retorna true se o novo Requester tiver uma prioridade mais alta
	 * (valor numérico menor) do que o atual Requester associado.
	 *
	 * \note Complexidade: O(1) – A busca em um std::unordered_map, como o utilizado para armazenar as prioridades,
	 * é realizada em tempo constante, assumindo uma boa função de hash e distribuição uniforme.
	 *
	 * \param newRequester Referência ao novo Requester que deseja fazer uma proposta.
	 * \return true se o novo Requester for uma correspondência melhor (prioridade menor), false caso contrário.
	 */
	bool isBetterMatch(Requester& newRequester);

	/**
	 * \brief Verifica se o Receiver atual é igual a outro Receiver.
	 *
	 * \param other Outro objeto Receiver a ser comparado.
	 *
	 * \return true se os Receivers forem considerados iguais, false caso contrário.
	 *
	 * Este método é abstrato e deve ser implementado nas subclasses para definir o critério de igualdade.
	 */
	virtual bool isEqual(const Receiver& other) const = 0;

	/**
	 * \brief Operador de igualdade necessário para o uso em std::unordered_map.
	 * \param other Outro objeto Receiver a ser comparado.
	 * \return true se os Receivers forem iguais, false caso contrário.
	 */
	bool operator==(const Receiver& other) const { return isEqual(other); };

private:
	/**
	 * \brief Ponteiro para o Requester atualmente associado (casado) com este Receiver.
	 */
	Requester* m_requester;

	/**
	 * \brief Mapa de prioridade contendo a relação de Requesters e suas respectivas prioridades.
	 */
	std::unordered_map<Requester*, int> m_priority;

};

#endif // RECEIVER_H