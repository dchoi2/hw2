#include "movie.h"
#include "util.h"

using namespace std;


Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating) {

}
Movie::~Movie()
{

}

/**
  * Returns the appropriate keywords that this product should be associated with
  */
std::set<std::string> Movie::keywords() const
{
  set<string> output = parseStringToWords(convToLower(getName()));
  output.insert(convToLower(genre_));
  return output;
}

/**
  * Allows for a more detailed search beyond simple keywords
  */
bool Movie::isMatch(vector<string>& searchTerms) const
{

}

/**
  * Returns a string to display the product info for hits of the search
  */
string Movie::displayString() const
{
  string str = getName() + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" 
      + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n";
  return str;
}

/**
  * Outputs the product info in the database format
  */
void Movie::dump(std::ostream& os) const
{
  os << "movie" << endl;
  os << getName() << endl;
  os << getPrice() << endl;
  os << getQty() << endl;
  os << genre_ << endl;
  os << rating_ << endl;
}