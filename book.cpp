#include "book.h"
#include <iomanip>

using namespace std;

Book::Book(const string category, const string name, double price, int qty, 
            const string isbn, const string author) : Product(category, name, price, qty) {
                isbn_ = isbn;
                author_ = author;
}

Book::~Book(){
    
}

string Book::displayString() const{
    stringstream s;
    s << name_ << '\n' << "Author: " << author_ << " ISBN: " << isbn_ << '\n' << fixed << setprecision(2) << price_ << ' ' << qty_ << " left.";
    string str = s.str();
    return str;
}

set<string> Book::keywords() const{
    ostringstream oss;
    oss << name_ << ' ' << author_;
    string s = oss.str();
    set<string> key = parseStringToWords(s);
    key.insert(isbn_);
    return key;
}
    

void Book::dump(std::ostream& os) const{
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}