#include "movie.h"
#include <iomanip>

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, 
            const string genre, const string rating) : Product(category, name, price, qty) {
                genre_ = genre;
                rating_ = rating;
}

Movie::~Movie(){
    
}

string Movie::displayString() const{
    stringstream s;
    s << name_ << '\n' << "Genre: " << genre_ << " Rating: " << rating_ << '\n' << fixed << setprecision(2) << price_ << ' ' << qty_ << " left.";
    string str = s.str();
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