#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "product_parser.h"
#include <string>

class MyDataStore : public DataStore{
    public:
        MyDataStore();
        ~MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        virtual void dump(std::ostream& ofile);

        void addToCart(User* u, Product* p);
        void viewCart(User* u);
        void checkout(User* u);
    private:
        std::set<User*> users_;
        std::set<Product*> products_;
        std::map<User*, std::vector<Product*>> cart_;
        std::map<std::string, set<Product*>> keywords_;
};

#endif