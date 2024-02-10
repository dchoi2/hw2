#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand) : 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand) {

}

Clothing::~Clothing()
{

}

set<std::string> Clothing::keywords() const
{
  set<string> output = parseStringToWords(convToLower(getName()));
  set<string> brandKey = parseStringToWords(convToLower(brand_));
  for(set<string>::iterator it = brandKey.begin(); it != brandKey.end(); ++it)
  {
    output.insert(*it);
  }
  return output;
}

  /**
    * Allows for a more detailed search beyond simple keywords
    */
bool Clothing::isMatch(vector<string>& searchTerms) const
{

}

  /**
    * Returns a string to display the product info for hits of the search
    */
std::string Clothing::displayString() const
{
  string str = getName() + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" 
      + to_string(getPrice()) + " " + to_string(getQty()) + " left.\n";
  return str;
}

  /**
    * Outputs the product info in the database format
    */
void Clothing::dump(ostream& os) const
{
  os << "clothing" << endl;
  os << getName() << endl;
  os << getPrice() << endl;
  os << getQty() << endl;
  os << size_ << endl;
  os << brand_ << endl;
}
