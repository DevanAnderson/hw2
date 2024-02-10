#include "clothing.h"

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, 
            const string size, const string brand) : Product(category, name, price, qty) {
                size_ = size;
                brand_ = brand;
}

Clothing::~Clothing(){
    
}

string Clothing::displayString() const{
    string str = name_ + '\n' + "Size: " + size_ + " Brand: " + brand_ + '\n' + to_string(price_) + ' ' + to_string(qty_) + " left.";
    return str;
}

set<string> Clothing::keywords() const{
    ostringstream oss;
    oss << name_ << ' ' << brand_;
    string s = oss.str();
    set<string> key = parseStringToWords(s);
    return key;
}

void Clothing::dump(ostream& os) const{
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}