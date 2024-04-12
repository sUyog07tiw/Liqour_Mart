#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// Encapsulation
class Product {
private:
    string name;
    double price;

public:
    Product(string n, double p) : name(n), price(p) {}

    // Getter
    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

// Inheritance
class Cart : public vector<Product> {
public:
    // Abstraction
    void displayAvailableLiquors(const vector<Product>& availableProducts) {
        cout << "---------------------------------------------" << endl;
        cout << "Available liquors" << endl;
        cout << "---------------------------------------------" << endl;
        for (size_t i = 0; i < availableProducts.size(); ++i) {
            cout << i + 1 << ". " << availableProducts[i].getName() << " - Rs." << availableProducts[i].getPrice() << endl;
        }
    }

    // Abstraction
    void displayCart() {
         cout << "---------------------------------------------" << endl;
         cout << "Shopping Cart" << endl;
         cout << "---------------------------------------------" << endl;
        double total = calculateTotal();
        for (const auto& item : *this) {
            cout << item.getName() << " - Rs." << item.getPrice() << endl;
        }
        cout << "\n---------------------------------------------" << endl;
        cout << "Billing" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "Sub-Total: Rs." << total << endl;
        double vat = calculateVAT(total);
        cout << "VAT(13%): Rs." << vat << endl;
        cout << "*********************************************" << endl;
        cout << "Total including VAT: Rs." << total + vat << endl;
        cout << "*********************************************" << endl;
    }

    // Polymorphism
    void addProduct(const vector<Product>& availableProducts, int index) {
        if (index >= 1 && index <= static_cast<int>(availableProducts.size())) {
            push_back(availableProducts[index - 1]);
            cout << "Added " << availableProducts[index - 1].getName() << " to the cart." << endl; // esma index ma bhako ra available product ma dekhako milauna lai index-1 gareko
        } else {
            cout << "Invalid liquor number. Please try again." << endl;
        }
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : *this) {
            total += item.getPrice();
        }
        return total;
    }
    
    // vat calcutate garera return garney -> total with vat
    double calculateVAT(double total) const {
        double vat_Rate = 0.13;
        return total * vat_Rate;
    }

    void checkout() {
        cout << "---------------------------------------------" << endl;
        cout << "Checkout completed. Thank you for shopping with us!" << endl;
        cout << "---------------------------------------------" << endl;
        clear();
    }
};

int main() {
    vector<Product> availableProducts = {
        Product("Barahsinghe Craft Yaktoberfest", 400),
        Product("Old Durbar 12yrs Blended Scotch", 5000),
        Product("Hibiki Suntory Harmony", 26000),
        Product("Uluvka Vodka", 12485),
        Product("Johnnie Walker Double Black", 8000),
        Product("Jameson Irish", 7500),
        Product("Jack Daniel's", 9000),
        Product("Ballantine's 21yrs", 24000),
        Product("The Macallan A Night On Earth", 19000),
        Product("Old Durbar Black Chimney", 4000)
    };

    Cart shoppingCart;

    
    shoppingCart.displayAvailableLiquors(availableProducts);
    cout << "\n---------------------------------------------" << endl;
    cout << "Adding items to the cart (type 'N' or 'n' to finish):" << endl;
    cout << "---------------------------------------------" << endl;

    string userInput;
    while(true){
        cout<<"Enter liquor number (1-"<< availableProducts.size() <<"):";
        getline(cin,userInput);

        if(userInput=="N"|| userInput=="n"){
            break;
        }
        try{
            int index =stoi(userInput);
            shoppingCart.addProduct(availableProducts,index);

         } catch(const invalid_argument& e){

            cout<<"Invalid Input.Please enter a valid number or 'N' or 'n' to finish."<<endl;
        }
    }

    shoppingCart.displayCart();

    shoppingCart.checkout();

    return 0;
}