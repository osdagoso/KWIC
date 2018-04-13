#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

#include <functional>

/**
 * Order class hierarchy implemented following Template Method design pattern
 */

class Order {
    public:
        virtual void sortPhrases(vector<string> &listPhrases) = 0;
};

class OrderAsc : public Order {
    public:
        void sortPhrases(vector<string> &listPhrases) {
            sort(listPhrases.begin(), listPhrases.end());
        }
};

class OrderDesc : public Order {
    public:
        void sortPhrases(vector<string> &listPhrases) {
            sort(listPhrases.begin(), listPhrases.end(), greater<string>());
        }
};

#endif // ORDER_H_INCLUDED
