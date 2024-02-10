#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore(){
}

MyDataStore::~MyDataStore(){
  // freeing up memory that was allocated for the item and user set
  for(set<Product*>::iterator it = items.begin(); it != items.end(); ++it)
  {
    delete *it;
  }

  for(set<User*>::iterator it = users.begin(); it != users.end(); ++it)
  {
    delete *it;
  }
  
}

void MyDataStore::addProduct(Product* p){
  // create a set of keys that contain the keywords of the product
  set<string> keys = (*p).keywords();
  items.insert(p);

  // iterate through the keys, see if they exist in product map
  set<string>::iterator itr;
  for(itr = keys.begin(); itr != keys.end(); ++itr)
  {
    // if they do exist, find the key where it's at and add it to the product set
    if(productMap.find(*itr) != productMap.end())
    {
      productMap[*itr].insert(p);
      // map<string, set<Product*>>::iterator addToKey = productMap.find(*itr);
      // addToKey->second.insert(p);
    }
    // if not, create a new pair of name and a set of products,
    //    and insert into the product map
    else if(productMap.find(*itr) == productMap.end())
    {
      set<Product*> newProducts;
      newProducts.insert(p);

      productMap.insert(make_pair(*itr, newProducts));
    }
  }
}
void MyDataStore::addUser(User* u){
  // if the user already exists, insert will not add the user
  // and if not, then new user is added
 
  vector<Product*> newCart;
  if(userCart.find(convToLower(u->getName())) == userCart.end())
  {
    userCart.insert(make_pair(convToLower(u->getName()), newCart));
  }
  users.insert(u);
}

vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
  set<Product*> setOfItems;
  vector<Product*> result;

  // if there is only one term (or less) return the only set list
  if(terms.size() < 2)
  {
    setOfItems = productMap.find(convToLower(terms[0]))->second;
    for(set<Product*>::iterator itr = setOfItems.begin(); itr != setOfItems.end(); ++itr)
    {
      result.push_back(*itr);
    }
    return result;
  }

  // This is the AND function (contains the intersection)
  if(type == 0)
  {
    // looping through the keyterms
    for(size_t i = 0; i < terms.size(); i++)
    {
      // making sure to be case insensitive, see if the term is in the map
      if(productMap.find(convToLower(terms[i])) != productMap.end())
      {
        // union all these sets into a big set
        setOfItems = setUnion(setOfItems, productMap.find(convToLower(terms[i]))->second);
      }
    }
    // loop through again, find the intersection and set the big set to only those
    for(size_t i = 0; i < terms.size(); i++)
    {
      if(productMap.find(convToLower(terms[i])) != productMap.end())
      {
        // setOfItems = setUnion(setOfItems, productMap.find(convToLower(terms[i]))->second);
        setOfItems = setIntersection(setOfItems, productMap.find(convToLower(terms[i]))->second);
      }
    }
  }

  // This is the OR function (contains everything)
  else
  {
    for(size_t i = 0; i < terms.size(); i++)
    {
      if(productMap.find(convToLower(terms[i])) != productMap.end())
      {
        setOfItems = setUnion(setOfItems, productMap.find(convToLower(terms[i]))->second);
      }
    }
  }

  // push all the set items into a vector list, and return
  for(set<Product*>::iterator itr = setOfItems.begin(); itr != setOfItems.end(); ++itr)
  {
    result.push_back(*itr);
  }
  return result;

}
void MyDataStore::dump(std::ostream& ofile){
  // dumping the product list using polymorphism
  ofile << "<products>" << endl;
  for(set<Product*>::iterator itr = items.begin(); itr != items.end(); ++itr)
  {
    (*itr)->dump(ofile);
  }
  ofile << "</products>" << endl;

  // dumping the user list using polymorphism
  ofile << "<users>" << endl;
  for(set<User*>::iterator itr = users.begin(); itr != users.end(); ++itr)
  {
    (*itr)->dump(ofile);
  }
  ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string user, int p, vector<Product *> &hits){
  vector<Product*> newCart;

  bool exist = false;
  set<User*>::iterator existingUser;

  // looping through the users, see if the user is an existing member
  for(existingUser = users.begin(); existingUser != users.end(); ++existingUser)
  {
    if(convToLower((*existingUser)->getName()) == convToLower(user))
    {
      exist = true;
    }
  }

  // if the user is not in the set, it is an invalid request (break the command)
  if(exist == false)
  {
    cout << "Invalid request" << endl;
    return;
  }

  // if the user is not in the userCart, then add them and an empty cart
  if((userCart.find(convToLower(user)) == userCart.end()))
  {
    userCart.insert(make_pair(convToLower(user), newCart));
  }

  map<std::string, std::vector<Product*>>::iterator itr = userCart.find(convToLower(user));

  // if out of bounds of the hits list, return
  if(p < 1 || p > hits.size())
  {
    cout << "Invalid request" << endl;
    return;
  }

  // if the user is found in the user cart, add the product to their cart
  if(itr != userCart.end())
  {
    (itr->second).push_back(hits[p - 1]);
  }
  else
  {
    cout << "Invalid request" << endl;
    return;
  }
}

void MyDataStore::viewCart(string user){
  map<string, vector<Product*>>::iterator findUserCart = userCart.find(convToLower(user));
  if(findUserCart == userCart.end())
  {
    cout << "Invalid username" << endl;
    return;
  }
  else
  {
    // looping through the cart, display them one by one
    int counter = 1;
    for(size_t i = 0; i < (findUserCart->second).size(); i++)
    {
      cout << "Item " << counter << endl;
      cout << (findUserCart->second[i])->displayString() << endl;
      counter++;
    }
  }
}

void MyDataStore::buyCart(string user){
  map<string, vector<Product*>>::iterator findUserCart = userCart.find(convToLower(user));

  double userBal = 0.0;
  set<User*>::iterator itr;

  // find the user in the users list and get their balance
  for(itr = users.begin(); itr != users.end(); ++itr)
  {
    if((*itr)->getName() == user)
    {
      userBal = (*itr)->getBalance();
      break;
    }
  }

  // if the user is not found in the user cart, then return
  if(findUserCart == userCart.end())
  {
    cout << "Invalid username" << endl;
    return;
  }
  else
  {
    vector<Product*> newList;

    // loop through their cart in sequential order,
    //  and check quantity, price, and balance to see if they can buy it
    for(size_t i = 0; i < (findUserCart->second).size(); i++)
    {
      if(userBal >= (findUserCart->second[i])->getPrice() && 
          (findUserCart->second[i])->getQty() >= 1)
      {
        (*itr)->deductAmount((findUserCart->second[i])->getPrice());
        userBal -= (findUserCart->second[i])->getPrice();
        (findUserCart->second[i])->subtractQty(1);
      }
      else
      {
        newList.push_back(findUserCart->second[i]);
      }
    }

    findUserCart->second.clear();
    findUserCart->second = newList;
  }
}