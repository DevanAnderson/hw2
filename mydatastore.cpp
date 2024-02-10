#include "mydatastore.h"

using namespace std;


MyDataStore::MyDataStore() {
}

MyDataStore::~MyDataStore() {
}

void MyDataStore::addProduct(Product* p) {
    //insert product into steet of products
    products_.insert(p);

    //find the keywords in the product
    set<string> words = p->keywords();
    
    //go through the set of keywords
    for(set<string>::iterator it = words.begin(); it != words.end(); ++it){

        //see if the string is in the map
        map<string, set<Product*>>:: iterator it2 = keywords_.find(convToLower(*it));

        //if the word is already in the map, add product to the set
        if(it2 != keywords_.end()){
            it2->second.insert(p);
        }
        else{
            //if word is not in the map, add it to the map
            set<Product*> prod;
            prod.insert(p);
            keywords_.insert({convToLower(*it), prod});
        }
    }
}

void MyDataStore::addUser(User* u) {
    //insert the user into the set of all users and insert the user into the map of all users carts with an empty cart
    cart_.insert({u, {}});
    users_.insert(convToLower(u->getName()));
    userMap_.insert({convToLower(u->getName()), u});
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    set<Product*> temp;
    set<Product*> temp2;
    vector<Product*> result;

    for(vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        map<string, set<Product*>>::iterator it2 = keywords_.find(*it);
        if(it2 != keywords_.end()){
            temp = it2->second;
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
            cout << *it << ' ';
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

void MyDataStore::addToCart(string u, Product* p){
    map<string, User*>::iterator it2 = userMap_.find(u);
    
    if(it2 == userMap_.end() || p == nullptr){
        cout << "Invalid request" << endl;
        return;
    }


    //find the user in the cart
    map<User* ,vector<Product*>>::iterator it = cart_.find(it2->second);

    //if there was a user that was found, add the product to the cart
    if(it != cart_.end()){
        it->second.push_back(p);
    }
    else{
        cout << "Invalid request" << endl;
    }
}

void MyDataStore::viewCart(string u){
    //find the user
    map<string, User*>::iterator it2 = userMap_.find(u);
    if(it2 == userMap_.end()){
        cout << "Invalid username" << endl;
        return;
    }
    //used to print out numbered lines
    unsigned int i = 0;

    //find the users cart;
    map<User*, vector<Product*>>::iterator it = cart_.find(it2->second);

    //make sure there is a cart
    if(it != cart_.end()){
        cout << it->first->getName() << "\'s cart:" << endl;
        //iterator through the products user has in the cart
        for(vector<Product*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            //display the products information
            cout << ++i << ": " << endl;
            cout << (*it2)->displayString() << endl;
        }
    }
}

void MyDataStore::checkout(string u){
    //find the user
    map<string, User*>::iterator it = userMap_.find(convToLower(u));
    if(it == userMap_.end()){
        cout << "Invalid input" << endl;
        return;
    }

    User* user = it->second;

    //find the users cart
    map<User*, vector<Product*>>::iterator it2 = cart_.find(user);

    vector<Product*>& cart = it2->second;

    //checkout each product if possible
    for(vector<Product*>::iterator it3 = cart.begin(); it3 != cart.end();){
        Product* prod = *it3;
        if(user->getBalance() > prod->getPrice() && prod->getQty() > 0){
            user->deductAmount(prod->getPrice());
            prod->subtractQty(1);
            //erase the product from the cart
            it3 = cart.erase(it3);
        }
        else{
            ++it3;
        }
    }
}

void MyDataStore::dump(ostream& ofile) {
    //dump the products
    ofile << "<products\n";
    //iterate through the products
    for(set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile);
        //once dumped, delete the product
        delete *it;
    }
    ofile << "</products>\n";

    //dump the users
    ofile << "<users>\n";
    //iteratre through the users
    for(set<string>::iterator it = users_.begin(); it != users_.end(); ++it){
        //find the user in the map and dump it into the file
        map<string, User*>::iterator it2 = userMap_.find(*it);
        it2->second->dump(ofile);
        //delete user
        delete it2->second;
    }
    ofile << "</users>\n";
}
