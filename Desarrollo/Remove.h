#ifndef REMOVE_H_INCLUDED
#define REMOVE_H_INCLUDED

#include <functional>

/**
 * Remove class implemented as a Singleton
 */

 class Remove {
     private:
         static Remove *rInstance;
     public:
         void removePhrases(vector<int> indexPhrases, vector<string> &listPhrases) {
             for(int index : indexPhrases) {
                listPhrases.erase(listPhrases.begin() + index - 1);
             }
         }
         void cleanIndexList(vector<int> &indexPhrases) {
             sort(indexPhrases.begin(), indexPhrases.end(), greater<int>());
             indexPhrases.erase(unique(indexPhrases.begin(), indexPhrases.end()), indexPhrases.end());
         }
         void selectPhrasesToRemove(vector<string> &listPhrases) {
             int cont = 0;
             int cantRemove;
             vector<int> indexPhrases;

             for(string phrase : listPhrases) {
					cout << ++cont << ". " << phrase << endl;
				}
             cout << endl << "Introduce la cantidad de lineas que desees eliminar: ";
             cin >> cantRemove;

             if (cantRemove > 0) {
                 cout << "Escribe los numeros de linea: " << endl;
                 for (int i = 0; i < cantRemove; i++) {
                    int index;
                    cin >> index;
                    while (index < 1 || (size_t)index > listPhrases.size()) {
                        cout << index << " es un indice invalido. Intentalo de nuevo." << endl;
                        cin >> index;
                    }
                    indexPhrases.push_back(index);
                 }
                 cleanIndexList(indexPhrases);
                 removePhrases(indexPhrases, listPhrases);
             }
             cout << endl;
         }
         static Remove *instance() {
             if (!rInstance)
                rInstance = new Remove;
             return rInstance;
         }
 };

#endif // REMOVE_H_INCLUDED
