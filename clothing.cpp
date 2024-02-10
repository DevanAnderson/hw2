#include "clothing.h"
#include <iomanip>

using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, 
            const string size, const string brand) : Product(category, name, price, qty) {
                size_ = size;
                brand_ = brand;
}

Clothing::~Clothing(){
    
}

string Clothing::displayString() const{
    stringstream s;
    s << name_ << '\n' << "Size: " << size_ << " Brand: " << brand_ << '\n' << fixed << setprecision(2) << price_ << ' ' << qty_ << " left.";
    string str = s.str();
    return str;
}

set<string> Clothing::keywords() const{
    ostringstream oss;
    oss << name_ << ' ' << brand_;
    string s = oss.str();
    s = convToLower(s);
    s+= ' ';
    set<string> key = parseStringToWords(s);
    return key;
}

void Clothing::dump(ostream& os) const{

    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;

    // Product::dump(os);
    // os << size_ << "\n" << brand_ << endl;
}