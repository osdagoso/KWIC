#ifndef PERMUTE_H_INCLUDED
#define PERMUTE_H_INCLUDED

#include <functional>

/**
 * Permute class implemented as a Singleton
 */

class Permute {
    private:
        static Permute *pInstance;
        // Takeks an array of words and returns a string separated by spaces

    public:
       static string StringFromVector(const vector<string>& sEntrada) {
            string salida = "";
            for(string sCadena : sEntrada) {
                salida += sCadena + " ";
            }

            salida.pop_back();
            return salida;
        }

        // From a string returns all the characters separated by an space.
        static vector<string> SplitString(string sEntrada) {
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
        void PermuteString(string sEntrada, vector<string>& list_outputs) {
            vector<string> words = SplitString(sEntrada);

            for (int i = words.size(); i > 0; i--) {
                list_outputs.push_back(StringFromVector(words));
                rotate(words.begin(), words.begin() + 1, words.end());
            }

        }
        static Permute *instance() {
            if (!pInstance)
                pInstance = new Permute;
            return pInstance;
        }
};

#endif // REMOVE_H_INCLUDED
