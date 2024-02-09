#include "mydatastore.h"

using namespace std;


MyDataStore::MyDataStore() {
}

void MyDataStore::addProduct(Product* p) {
    //insert product into steet of products
    products_.insert(p);

    //find the keywords in the product
    set<string> words = p->keywords();
    
    //go through the set of keywords
    for(set<string>::iterator it = words.begin(); it != words.end(); ++it){

        //see if the string is in the map
        map<string, set<Product*>>:: iterator it2 = keywords_.find(*it);

        //if the word is already in the map, add product to the set
        if(it2 != keywords_.end()){
            it2->second.insert(p);
        }
        else{
            //if word is not in the map, add it to the map
            set<Product*> prod;
            prod.insert(p);
            keywords_.insert({*it, prod});
        }
    }
}

void MyDataStore::addUser(User* u) {
    //insert the user into the set of all users and insert the user into the map of all users carts with an empty cart
    cart_.insert({u, {}});
    users_.insert(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> temp;
    set<Product*> temp2;
    vector<Product*> result;

    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        map<string, set<Product*>>::iterator it2 = keywords_.find(*it);
        if(it2 != keywords_.end()){
            temp2 = it2->second;
            break;
        }
    }

    //union
    if(type){
        for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
            map<string, set<Product*>>::iterator it2 = keywords_.find(*it);
            if(it2 != keywords_.end()){
                temp2 = it2->second;
                temp = setUnion(temp, temp2);
            }
        }
    }
    //intersection
    else{
        for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
            map<string, set<Product*>>::iterator it2 = keywords_.find(*it);
            if(it2 != keywords_.end()){
                temp2 = it2->second;
                temp = setIntersection(temp, temp2);
            }
        }
    }


    //put everything into a vector
    for(set<Product*>::iterator it = temp.begin(); it != temp.end(); ++it){
        result.push_back(*it);
    }

    return result;
}

void MyDataStore::addToCart(User* u, Product* p){
    if(u == nullptr || p == nullptr){
        cout << "Invalid request" << endl;
        return;
    }


    //find the user in the cart
    map<User* ,vector<Product*>>::iterator it = cart_.find(u);

    //if there was a user that was found, add the product to the cart
    if(it != cart_.end()){
        it->second.push_back(p);
    }
    else{
        cout << "Invalid request" << endl;
    }
}

void MyDataStore::viewCart(User* u){
    unsigned int i = 0;
    if(u == nullptr){
        cout << "Invalid username" << endl;
        return;
    }
    //find the user in the map;
    map<User*, vector<Product*>>::iterator it = cart_.find(u);

    if(it != cart_.end()){
        cout << it->first->getName() << "\'s cart:" << endl;
        //iterator through the products user has in the cart
        for(vector<Product*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            //display the products information
            cout << ++i << ": " << endl;
            (*it2)->displayString();
        }
    }
    else{
        cout << "Invalid username" << endl;
    }
}

void MyDataStore::checkout(User* u){
    map<User*, vector<Product*>>::iterator it = cart_.find(u);

    //checks for user
    if(it != cart_.end()){
        //user
        User* u = it->first;

        //loop through the products in users cart
        for(vector<Product*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            //product
            Product* p = *it2;
            //if the users balance is greater than the price and it is in stock, then checkout that product
            if(u->getBalance() > p->getPrice() && p->getQty() > 0){
                //deduct price from users balance
                u->deductAmount(p->getPrice());
                //reduce quantity by 1
                p->subtractQty(1);
            }
        }
    }
    else{
        cout << "Invalid username" << endl;
    }
}

void MyDataStore::dump(ostream& ofile) {
}
