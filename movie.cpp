#include "movie.h"


using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, 
            const string genre, const string rating) : Product(category, name, price, qty) {
                genre_ = genre;
                rating_ = rating;
}

string Movie::displayString() const{
    string str = name_ + '\n' + "Genre: " + genre_ + " Rating: " + rating_ + '\n' + to_string(price_) + ' ' + to_string(qty_) + " left.";
    return str;
}

set<string> Movie::keywords() const{
    ostringstream oss;
    oss << name_;
    string s = oss.str();
    set<string> key = parseStringToWords(s);
    key.insert(genre_);
    return key;
}

void Movie::dump(std::ostream& os) const{
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}