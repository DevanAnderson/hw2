#include "book.h"

using namespace std;

Book::Book(const string category, const string name, double price, int qty, 
            const string isbn, const string author) : Product(category, name, price, qty) {
                isbn_ = isbn;
                author_ = author;
}

string Book::displayString() const{
    string str = name_ + '\n' + "Author: " + author_ + " ISBN: " + isbn_ + '\n' + to_string(price_) + ' ' + to_string(qty_) + " left.";
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