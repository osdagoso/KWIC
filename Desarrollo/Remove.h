#ifndef REMOVE_H_INCLUDED
#define REMOVE_H_INCLUDED

/**
 * Remove class implemented as a Singleton
 */

 class Remove {
     private:
         static Remove *rInstance;
     public:
         void removePhrases(vector<int> indexPhrases, vector<string> &listPhrases) {
             //
         }
         void cleanIndexList(vector<int> &indexPhrases) {
             //
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
             cout << "Escribe los numeros de linea: " << endl;
             for (int i = 0; i < cantRemove; i++) {
                int index;
                cin >> index;
                while (index < 1 || index > listPhrases.size()) {
                    cout << index << " es un indice invalido. Intentalo de nuevo." << endl;
                    cin >> index;
                }
                indexPhrases.push_back(index);
             }
             cleanIndexList(indexPhrases);
             removePhrases(indexPhrases, listPhrases);
         }
         static Remove *instance() {
             if (!rInstance)
                rInstance = new Remove;
             return rInstance;
         }
 };

#endif // REMOVE_H_INCLUDED
