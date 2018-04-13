#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED

class Order {
    private:
        virtual bool definedOrder(int i, int j) = 0;
    public:
        void sortPhrases(vector<string> &listPhrases) {
            sort(listPhrases.begin(), listPhrases.end(), definedOrder);
        }
};

class OrderAsc : public Order {
    private:
        bool definedOrder(int i, int j) {
            return (i < j);
        }
};

class OrderDesc : public Order {
    private:
        bool definedOrder(int i, int j) {
            return (j < i);
        }
};

#endif // ORDER_H_INCLUDED
