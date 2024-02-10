#include "datastore.h"
#include <map>

class MyDataStore : public DataStore {
public:
  MyDataStore();
  ~MyDataStore();
  void addProduct(Product* p);
  void addUser(User* u);

  /**
  * Performs a search of products whose keywords match the given "terms"
  *  type 0 = AND search (intersection of results for each term) while
  *  type 1 = OR search (union of results for each term)
  */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);

  void addToCart(std::string user, int p, std::vector<Product *> &hits);
  void viewCart(std::string user);
  void buyCart(std::string user);
  void quit(std::string fileName);

private:
  std::set<Product*> items;
  std::set<User*> users;
  std::map<std::string, std::set<Product*>> productMap;
  std::map<std::string, std::vector<Product*>> userCart;
};