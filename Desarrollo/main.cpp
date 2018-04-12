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

// global objects for holding the inputs and output strings.
vector<string> list_inputs;
vector<string> list_outputs;
vector<string> list_stop;
int thread_count;


// Structure used to pass the parameters to the thread function both in
// unix and in windows.
typedef struct thread_params {
    string sEntrada;
} thread_parameters;

// Takeks an array of words and returns a string separated by spaces
string string_from_vector(vector<string> sEntrada) {
    string salida = "";
    for(string sCadena : sEntrada) {
        salida += sCadena + " ";
    }

    salida.pop_back();
    return salida;
}

// From a string returns all the characters separated by an space.
vector<string> split_string(string sEntrada) {
    string sActual = "";
    vector<string> output;
    for(char character : sEntrada) {
        if(character != ' ') {
            sActual += character;
        } else {
            output.push_back(sActual);
            sActual = "";
        }
    }
    output.push_back(sActual);
    return output;
}


// This piuece of code will only be compiled if we are on a windows machine
#if defined(_WIN32)

#include <windows.h>

HANDLE semaphore_handle, integer_semaphore;


// Main function for the threads
DWORD WINAPI thread_windows(LPVOID lparams) {
 thread_parameters * params = (thread_parameters*) lparams;
 vector<string> words = split_string(params->sEntrada);

 for (int i = words.size(); i > 0; i--) {
    WaitForSingleObject(semaphore_handle, INFINITE);
    list_outputs.push_back(string_from_vector(words));
    ReleaseSemaphore(semaphore_handle, 1, NULL);
    rotate(words.begin(), words.begin() + 1, words.end());
 }

 // Decrease the count of the threads so we know when the processing of the
 // string has ended.
 WaitForSingleObject(integer_semaphore, INFINITE);
 thread_count--;
 ReleaseSemaphore(integer_semaphore, 1, NULL);
 delete params;
 return 0;
}

// Definition of permute_string in windows.
void permute_string(string sEntrada) {
    semaphore_handle = CreateSemaphore(
                        NULL,
                        1,
                        1,
                        NULL);
      integer_semaphore = CreateSemaphore(
                        NULL,
                        1,
                        1,
                        NULL);
     thread_parameters *param = new thread_parameters;
     param->sEntrada = sEntrada;

     CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread_windows, (void*) param, 0, NULL);
}




// Implementation of the functionality for linux.
#elif defined(__gnu_linux__)

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define Sleep(x) usleep(x*1000)

sem_t semaphore, integer_semaphore;

// Main threading function for linux.
void *thread_linux(void* sEntrada_params) {
    thread_params* params_ptr = (thread_params*) sEntrada_params;
    string sEntrada = params_ptr->sEntrada;
    vector<string> words = split_string(sEntrada);

    for (int i = words.size(); i > 0; i--) {
        sem_wait(&semaphore);
        list_outputs.push_back(string_from_vector(words));
        sem_post(&semaphore);
        rotate(words.begin(), words.begin() + 1, words.end());
    }
    sem_wait(&integer_semaphore);
    thread_count--;
    sem_post(&integer_semaphore);
    delete params_ptr;
}

// Implementation of the permute string for linux.
void permute_string(string sEntrada) {
    sem_init(&semaphore, 0, 1);
    sem_init(&integer_semaphore, 0, 1);
    thread_params* params = new thread_params;
    params->sEntrada = sEntrada;
    pthread_t thread1;
    pthread_create(&thread1, NULL, thread_linux, (void*) params);

}


#endif

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

    thread_count = list_inputs.size();

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
				for (auto i = list_inputs.begin(); i != list_inputs.end(); i++) {
					permute_string(*i);
				}

				while (thread_count > 0) {
					Sleep(100);
				}

				sort(list_outputs.begin(), list_outputs.end());

				for(string permutacion : list_outputs) {
					cout << permutacion << endl;
				}
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
