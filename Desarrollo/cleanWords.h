#ifndef CLEANWORDS_H_INCLUDED
#define CLEANWORDS_H_INCLUDED

#include <functional>
#include <set>
#include "Permute.h"

/**
 * Remove class implemented as a Singleton
 */

 class cleanWords {
     private:
         static cleanWords *cInstance;
     public:
         void removeWords(vector<string>& phrases, vector<string> words) {
             if(words.size() == 0) return;
            set<string> hash_words;
            for(string word : words) {
               hash_words.insert(word);
            }
            for(int i = 0; i < phrases.size(); i++) {
               vector<string> phrase_words = Permute::SplitString(phrases[i]);
               vector<string> temp;
               for(string s : phrase_words) {
                  if(hash_words.find(s) == hash_words.end()) {
                     temp.push_back(s);
                  }
               }
               phrases[i] = Permute::StringFromVector(temp);
            }
         }
         static cleanWords *instance() {
             if (!cInstance)
                cInstance = new cleanWords;
             return cInstance;
         }
 };

#endif // REMOVE_H_INCLUDED
