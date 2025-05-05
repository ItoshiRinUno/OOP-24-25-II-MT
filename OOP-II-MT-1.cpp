/*
*Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци), насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број). Класата за опишување на книгите е апстрактна (5 поени).

За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) и дали ја има на залиха (логичка променлива). (5 поени)

За секој објект од двете изведени класи треба да бидат на располагање следниве методи:

Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)

За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB

За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg

Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)

Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:

void mostExpensiveBook (Book** books, int n)

во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)

Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)
EX. INPUT:
4
3
1
0-312-31677-1
The Moscow Vector
Robert Ludlum
7
www.finki-education/olinebooks/book1.pdf
1
2
007-6092006565
Thinking in C++
Bruce Eckel
52
1.2
1
1
978-0672326974
C++ Primer Plus
Stephen Prata
20
www.finki-education/olinebooks/book2.pdf
30
XO OUTPUT:
====== Testing method mostExpensiveBook() ======
FINKI-Education
Total number of online books: 2
Total number of print books: 1
The most expensive book is:
007-6092006565: Thinking in C++, Bruce Eckel 59.8
EX. INPUT:
3
2
007-6092006565
Thinking in C++
Bruce Eckel
52
1.2
1
978-1118823774
C++ for Dummies
Stephen R. Davis
21
2.2
10
XO OUTPUT:
====== Testing PrintBook class ======
CONSTRUCTOR
OPERATOR <<
007-6092006565: Thinking in C++, Bruce Eckel 59.8
CONSTRUCTOR
OPERATOR <<
978-1118823774: C++ for Dummies, Stephen R. Davis 24.15
OPERATOR >
Rezultat od sporedbata e:
007-6092006565: Thinking in C++, Bruce Eckel 59.8
 */
//STAR OF YOUR CODE
#include <iostream>
#include <cstring>
using namespace std;
class Book { //abstract class
protected:
    char ISBN[21];
    char *title;
    char author[31];
    double price;
    void copy(const Book &b) {
        strcpy(ISBN, b.ISBN);
        this->title = new char[strlen(b.title)+1];
        strcpy(this->title, b.title);
        strcpy(this->author, b.author);
        this->price = b.price;
    }
public:
	void setISBN(const char *ISBN) {
		strcpy(this->ISBN, ISBN);
	}
    Book(const char *ISBN="", const char *title="", const char *author="", double price=0) {
        strcpy(this->ISBN, ISBN);
        this->title = new char[strlen(title)+1];
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price = price;
    }
    Book(const Book &b) {
        copy(b);
    }
    Book &operator=(const Book &b) {
        if (this!=&b) {
            delete [] title;
            copy(b);
        }
        return *this;
    }
    virtual ~Book(){delete [] title;}
	virtual double bookPrice() const = 0;
	bool operator>(const Book &other) const{
		return this->bookPrice() > other.bookPrice();
	}
	friend ostream &operator<<(ostream &os, const Book &b) {
		b.print(os);
		return os;
	}
	virtual void print(ostream &out) const {
		cout<<ISBN<<": "<<title<<", "<<author<<" ";
	}
};
class OnlineBook : public Book {
private:
    char *url;
    int size; //in MBs
	void copy(const OnlineBook &ob) {
		this->url = new char[strlen(ob.url)+1];
		strcpy(this->url, ob.url);
		this->size = ob.size;
	}
public:
    OnlineBook(const char *ISBN="", const char *title="", const char *author="", double price=0, const char *url="", int size=0) : Book(ISBN,title,author,price) {
	    this->url = new char[strlen(url)+1];
    	strcpy(this->url, url);
    	this->size = size;
    }
	OnlineBook(const OnlineBook &ob) : Book(ob) {
    	copy(ob);
    }
	OnlineBook &operator=(const OnlineBook &ob) {
	    if (this!=&ob) {
		    delete [] url;
	    	Book::operator=(ob);
	    	copy(ob);
	    }
    	return *this;
    }
	~OnlineBook() override{delete [] url;}
	double bookPrice() const override{
	    return (size > 20 ? price*1.20 : price);
    }
	void print(ostream &out) const override {
	    Book::print(out);
    	out<<bookPrice()<<endl;
    }
};
class PrintBook : public Book {
private:
	double mass; //in kgs
	bool available;
	void copy(const PrintBook &ob) {
		this->mass = ob.mass;
		this->available = ob.available;
	}
public:
	PrintBook(const char *ISBN="", const char *title="", const char *author="", double price=0, double mass=0.0, bool available=false) : Book(ISBN,title,author,price) {
		this->mass = mass;
		this->available = available;
	}
	PrintBook(const PrintBook &ob) : Book(ob) {
		copy(ob);
	}
	PrintBook &operator=(const PrintBook &pb){
		if (this!=&pb) {
			Book::operator=(pb);
			copy(pb);
		}
		return *this;
	}
	~PrintBook() override{};
	double bookPrice() const override{
		return (mass > 0.7 ? price*1.15 : price);
	}
	void print(ostream &out) const override {
		Book::print(out);
		out<<bookPrice()<<endl;
	}
};
void mostExpensiveBook(Book** books, int n) {
	int onlineCount = 0, printCount = 0;
	int maxIdx = 0;
	float maxPrice = books[0]->bookPrice();

	for (int i = 0; i < n; ++i) {
		if (dynamic_cast<OnlineBook*>(books[i]))
			onlineCount++;
		else if (dynamic_cast<PrintBook*>(books[i]))
			printCount++;

		if (books[i]->bookPrice() > maxPrice) {
			maxPrice = books[i]->bookPrice();
			maxIdx = i;
		}
	}
	cout << "FINKI-Education " << endl;
	cout << "Total number of online books: " << onlineCount << endl;
	cout << "Total number of print books: " << printCount << endl;
	cout << "The most expensive book is:" << endl;
	cout << *books[maxIdx];
}
//END OF YOUR CODE
//GIVEN MAIN:
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
