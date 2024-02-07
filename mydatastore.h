#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "product_parser.h"
#include <string>

class MyDataStore : public DataStore{
    public:
        MyDataStore();
        void addProduct(Product* p);
        void addUser(User* u);
        std::vector<Product*> search(std::vector<std::string>& terms, int type);
        virtual void dump(std::ostream& ofile);
};

#endif