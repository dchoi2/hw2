#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, string isbn, string auth) : 
    Product(category, name, price, qty), 
    isbnNum_(isbn),
    author_(auth) {

}

Book::~Book()
{
  
}

std::set<std::string> Book::keywords() const
{
  set<string> output = parseStringToWords(convToLower(author_));
  set<string> nameKey = parseStringToWords(convToLower(getName()));
  for(set<string>::iterator it = nameKey.begin(); it != nameKey.end(); ++it)
  {
    output.insert(*it);
  }
  output.insert(isbnNum_);

  return output;
}

  /**
    * Allows for a more detailed search beyond simple keywords
    */
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{

}

  /**
    * Returns a string to display the product info for hits of the search
    */
std::string Book::displayString() const
{
  string str = getName() + "\n" + "Author: " + author_ + " ISBN: " + isbnNum_ + "\n" 
      + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n";
  return str;
}

  /**
    * Outputs the product info in the database format
    */
void Book::dump(std::ostream& os) const
{
  os << "book" << endl;
  os << getName() << endl;
  os << getPrice() << endl;
  os << getQty() << endl;
  os << isbnNum_ << endl;
  os << author_ << endl;
}
