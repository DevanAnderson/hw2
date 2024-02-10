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

        void addToCart(std::string u, Product* p);
        void viewCart(std::string u);
        void checkout(std::string u);
    private:
        std::set<std::string> users_;
        std::set<Product*> products_;
        std::map<std::string, User*> userMap_;
        std::map<User*, std::vector<Product*>> cart_;
        std::map<std::string, std::set<Product*>> keywords_;
};

#endif