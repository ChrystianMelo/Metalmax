#define BOOST_TEST_MODULE testAlgorithms

#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <set>


std::vector<std::string> splitLines(const std::string& text) {
	std::vector<std::string> lines;
	std::stringstream ss(text);
	std::string line;

	while (std::getline(ss, line)) {
		lines.push_back(line);
	}

	return lines;
}

/**
 * \brief L� o conte�do de um arquivo para uma string.
 *
 * Esta fun��o abre um arquivo no caminho fornecido, l� todo o seu conte�do e o retorna como uma string.
 * Lan�a uma exce��o se o arquivo n�o puder ser aberto.
 *
 * \param filePath Caminho para o arquivo a ser lido.
 * \return O conte�do do arquivo como uma string.
 *
 * \throws std::runtime_error Se o arquivo n�o puder ser aberto.
 */
std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		throw std::runtime_error("Erro ao abrir arquivo: " + filePath);
	}
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

/**
 * \brief Executa um programa externo com uma entrada fornecida e retorna a sa�da.
 *
 * Esta fun��o cria dois arquivos tempor�rios:
 * 1. `temp_input.txt` para armazenar a entrada.
 * 2. `temp_output.txt` para armazenar a sa�da gerada pelo programa externo.
 *
 * O programa execut�vel deve estar localizado em `./bin/run.out`. A entrada � redirecionada do arquivo tempor�rio
 * e a sa�da capturada no arquivo de sa�da. Ap�s a execu��o, os arquivos tempor�rios s�o removidos.
 *
 * \param input A string de entrada que ser� passada para o programa.
 * \return A sa�da gerada pelo programa como uma string.
 *
 * \throws std::runtime_error Se o programa n�o puder ser executado ou se ocorrer erro na manipula��o de arquivos.
 */
std::string runProgram(const std::string& input) {
	const std::string executable = "./bin/run.out";

	const std::string tempInput = "temp_input.txt";
	const std::string tempOutput = "temp_output.txt";

	std::ofstream inputFile(tempInput);
	inputFile << input;
	inputFile.close();

	const std::string command = executable + " < " + tempInput + " > " + tempOutput;
	int retCode = std::system(command.c_str());
	if (retCode != 0) {
		throw std::runtime_error("Erro ao executar o programa.");
	}

	std::string output = readFile(tempOutput);

	std::filesystem::remove(tempInput);
	std::filesystem::remove(tempOutput);

	return output;
}

// Roda os arquivos de teste.
BOOST_AUTO_TEST_CASE(IntegrationTest) {
	namespace fs = std::filesystem;
	const std::string inputsPath = "./tests/inputs";
	const std::string outputsPath = "./tests/outputs";

	for (const auto& inputFile : fs::directory_iterator(inputsPath)) {
		std::string inputFilePath = inputFile.path().string();
		std::string outputFilePath = outputsPath + "/" + inputFile.path().filename().string();

		std::string input = readFile(inputFilePath);
		std::string expectedOutput = readFile(outputFilePath);
		std::string actualOutput = runProgram(input);

		std::vector<std::string> expectedLines = splitLines(expectedOutput);
		std::vector<std::string> actualLines = splitLines(actualOutput);

		// Teste 1: Verifica se a primeira linha � igual
		BOOST_CHECK_MESSAGE(
			expectedLines[0] == actualLines[0],
			"Falha na primeira linha para arquivo: " + inputFilePath +
			"\nEsperado: " + expectedLines[0] +
			"\nGerado: " + actualLines[0]
		);

		// Teste 2: Verifica se a segunda linha � igual
		BOOST_CHECK_MESSAGE(
			expectedLines.size() > 1 && actualLines.size() > 1 && expectedLines[1] == actualLines[1],
			"Falha na segunda linha para arquivo: " + inputFilePath +
			"\nEsperado: " + (expectedLines.size() > 1 ? expectedLines[1] : "<ausente>") +
			"\nGerado: " + (actualLines.size() > 1 ? actualLines[1] : "<ausente>")
		);

		// Teste 3: Verifica se a terceira linha � igual
		BOOST_CHECK_MESSAGE(
			expectedLines.size() > 2 && actualLines.size() > 2 && expectedLines[2] == actualLines[2],
			"Falha na terceira linha para arquivo: " + inputFilePath +
			"\nEsperado: " + (expectedLines.size() > 2 ? expectedLines[2] : "<ausente>") +
			"\nGerado: " + (actualLines.size() > 2 ? actualLines[2] : "<ausente>")
		);

		// Verificar se a sa�da gerada tem pelo menos o n�mero de linhas esperado
		BOOST_REQUIRE_MESSAGE(
			expectedLines.size() <= actualLines.size(),
			"A sa�da gerada tem menos linhas que a sa�da esperada no arquivo: " + inputFilePath
		);

		// Teste 4: Verifica se todas as linhas a partir da quarta s�o iguais
		for (size_t i = 3; i < expectedLines.size(); ++i) {
			BOOST_CHECK_MESSAGE(
				expectedLines[i] == actualLines[i],
				"Falha na linha " + std::to_string(i + 1) + " para arquivo: " + inputFilePath +
				"\nEsperado: " + expectedLines[i] +
				"\nGerado: " + actualLines[i]
			);
		}
	}
}
