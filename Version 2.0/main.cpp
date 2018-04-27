#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>

/**
 * Rotate strings in a circular way.
 *
 * This codes compiles both in windows and in linux
 */

using namespace std;

#include "cleanWords.h"
#include "Order.h"
#include "Permute.h"
#include "Remove.h"

// Initializing Remove singleton
Remove* Remove::rInstance = nullptr;
Permute* Permute::pInstance = nullptr;
cleanWords* cleanWords::cInstance = nullptr;


// global objects for holding the inputs and output strings.
vector<string> list_inputs;
vector<string> list_outputs;
vector<string> list_stop;



// Load the strings from an input file.
void load_input() {
    ifstream file_input;
    string path;
    string line;

    cout << "Introduce el nombre del archivo con los enunciados a emplear: " << endl;
    cin >> path;
    file_input.open(path);
    cin.ignore();

    while (getline(file_input, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        line.erase(remove_if(line.begin(), line.end(), ::ispunct), line.end());
        list_inputs.push_back(line);
    }

    file_input.close();
}

void load_stop() {
    ifstream file_input;
    string path;
    string line;

    cout << "Introduce el nombre del archivo con la lista de stop words a considerar: " << endl;
    cin >> path;
    file_input.open(path);
    cin.ignore();

    while (getline(file_input, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        line.erase(remove_if(line.begin(), line.end(), ::ispunct), line.end());
        list_stop.push_back(line);
    }

    file_input.close();
}

int main() {
	char menuOption;
	bool isAsc = true;
	Order* orderModule;

    load_input();
    cout << endl;

	do {
		cout << "1. Ejecuta Key-Word-In-Context" << endl;
		if (list_stop.empty())
			cout << "2. Carga una lista de stop words" << endl;
		else
			cout << "2. Cambia la lista de stop words" << endl;
		if (isAsc)
			cout << "3. Cambia el tipo de ordenamiento (ASC seleccionado)" << endl;
		else
			cout << "3. Cambia el tipo de ordenamiento (DESC seleccionado)" << endl;
		cout << "4. Salir de la aplicacion" << endl;

		cout << endl << "Ingresa el numero de la accion que desees realizar: ";
		cin >> menuOption;
		cout << endl;

		switch (menuOption) {
			case '1':
			    // Based on the user's chosen setting, generate Order module
			    if (isAsc)
                    orderModule = new OrderAsc;
                else
                    orderModule = new OrderDesc;

                Remove::instance()->selectPhrasesToRemove(list_inputs);

                cleanWords::instance()->removeWords(list_inputs, list_stop);

				for (auto i = list_inputs.begin(); i != list_inputs.end(); i++) {
                    Permute::instance()->PermuteString(*i, list_outputs);
				}

				orderModule->sortPhrases(list_outputs);

				Remove::instance()->selectPhrasesToRemove(list_outputs);

				for(string permutacion : list_outputs) {
					cout << permutacion << endl;
				}

				delete orderModule;
				break;
			case '2':
			    load_stop();
			    cout << endl;
				break;
			case '3':
				isAsc = !isAsc;
				cout << endl;
				break;
			case '4':
				break;
			default:
				cout << "Instruccion invalida. Intentalo de nuevo." << endl;
				break;
		}
	} while (menuOption != '4' && menuOption != '1');

    return 0;
}
