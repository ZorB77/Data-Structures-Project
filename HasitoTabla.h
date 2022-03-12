#ifndef HASITOTABLA_H
#define HASITOTABLA_H

#include <iostream>
template<typename T ,typename V>
class HashTable{


	class Node {

		public:
			T key;
			V value;
			Node(T key ,V value) : key(key) ,value(value) {}
	};

	int size;
	int capacity;
	Node** tabla;
	bool *torolt_e;
	
public:
	
	HashTable();						  //Default constructor
	HashTable(int);                       //Constructor with given size hashmap
	int HashFunction(T);                  //Preferred hash function
	int HashIndex(T, int);                //Finds an index in the hashmap, using quadratic probing 
	bool Insert(T ,V);					  //Inserts an element into hashmap
	V Search(T);						  //Searches a given element in the  hashmap
	bool Delete(T);						  //Removes a given element from the hashmap
	void Clear();                         //Clears everything
	void ReHash();						  //Contains resize, rehash
	bool prim_e(int, bool);				  //The size of the table will be transformed to prime on each resize
	bool SetKeyValue(T ,V);				  //Sets a given value to a key
	int sizeofTable() const;              //Returns the size of the table
	V begin();							  //Returns the first element of the map
	V end();							  //Returns the last element of the map
	bool containsKey(T);                  //Checks if the map contains a given key
	bool isEmpty() const;				  //Checks if the map is empty, if its empty returns true, otherwise false
	bool isFull() const;				  //Checks if the map is full
	void Print() const;					  //Prints a table and its size
	~HashTable();						  //Destructor	

};

template<typename T ,typename V>
HashTable<T ,V>::HashTable() {

	size = 0;
	capacity = 101;
	tabla = new Node* [capacity];
	torolt_e = new bool[capacity] {false};
	for (int i = 0; i < capacity; i++) {
		tabla[i] = new Node(NULL ,NULL);
	}
}
template<typename T, typename V>
HashTable<T, V>::HashTable(int capacity) {

	size = 0;
	this->capacity = capacity;
	tabla = new Node * [capacity];
	torolt_e = new bool[capacity] {false};
	for (int i = 0; i < capacity; i++) {
		tabla[i] = new Node(NULL, NULL);
	}
}
template<typename T ,typename V>
int HashTable<T ,V>::HashFunction(T key) {

	return (key % capacity);
}
template<typename T, typename V>
int HashTable<T, V>::HashIndex(T key, int i) {

	return (HashFunction(key) + (i * i)) % capacity;
}

template<typename T ,typename V>
bool HashTable<T ,V>::Insert(T key ,V value) {

	int j = 0;
	
	do {
		int i = HashIndex(key, j);
		if ((tabla[i]->key == NULL) && (!torolt_e[i])) {

			double loadFactor = (1.0 * size) / capacity;
			if (loadFactor > 0.75) {
				ReHash();
			}
			tabla[i]->key = key;
			tabla[i]->value = value;
			size++;
			return true;
		}
		j++;
	} while (j != capacity);
	//returns false if the table is full
	
	return false;
}
template<typename T, typename V>
V HashTable<T, V>::Search(T key) {

	int j = 0, i;

	do {
		i = HashIndex(key, j);
		if (tabla[i]->key == key) {
			return tabla[i]->value;
		}
		j++;
	} while ((tabla[i]->key != NULL) && (j != capacity));

	//returns NULL if the key wasn't found
	return NULL;
}
template<typename T, typename V>
bool HashTable<T, V>::Delete(T key) {


	int j = 0;
	bool torolt = false;
	do {
		int i = HashIndex(key, j);

		if (tabla[i]->key == key) {

			size--;
			tabla[i]->key = NULL;
			tabla[i]->value = NULL;
			torolt_e[i] = true;
			torolt = true;
		}
		j++;

	} while ((j != capacity));
	//returns NULL if the removal wasn't possible
	if (!torolt) {
		std::cout << "A tabla ures!\n";
		return false;
	}
	return true;
}
template<typename T, typename V>
void HashTable<T, V>::ReHash() {

	//I create a copy of my table and my vector torolt_e, which shows if an element is deleted or not
	Node** copy;
	bool* torolt_eCopy;
	torolt_eCopy = new bool[capacity] {false};
	copy = new Node * [capacity];

	
	for (int i = 0; i < capacity; i++) {
		copy[i] = new Node(tabla[i]->key, tabla[i]->value);
		torolt_eCopy[i] = torolt_e[i];
	}

	//I delete my tables, then i resize themm
	delete[] tabla;
	delete[] torolt_e;
	capacity *= 2;
	bool prim = false;
	while (!prim_e(capacity, prim)) {
		capacity++;
	}
	tabla = new Node * [capacity];
	torolt_e = new bool[capacity] {false};
	size = 0;
	for (int i = 0; i < capacity; i++) {
		tabla[i] = new Node(NULL, NULL);
	}

	for (int i = 0; i < capacity / 2; i++) {
		if (copy[i]->key != NULL) {
			Insert(copy[i]->key, copy[i]->value);
		}
	}


	for (int i = 0; i < capacity / 2; i++) {
		torolt_e[i] = torolt_eCopy[i];
	}

	delete[]torolt_eCopy;
	delete[] copy;

}
//test if the size of the table is prime
template<typename T, typename V>
bool HashTable<T ,V>::prim_e(int n  ,bool prim){


	if (n == 1) {
		prim = false;
	}
	else {
		if (n % 2 == 0) {
			prim = (n == 2);
		}
		else {
			if (n <= 5) {
				prim = true;
			}
			else {
				if ((((n - 1) % 6) != 0) && ((n + 1) % 6 != 0)) {
					prim = false;
				}
				else {
					prim = true;
					int j = 3;
					int gyok = sqrt(n);
					while ((j <= gyok) && prim) {
						if (n % j == 0) {
							prim = false;
						}
						else {
							j += 2;
						}
					}
				}
			}
		}
	}
	return prim;
}
template<typename T, typename V>
bool HashTable<T, V>::containsKey(T key) {

	 int j = 0, i;

    do {
		i = HashIndex(key, j);
		if (tabla[i]->key == key) {
				return true;
		}
		j++;
	} while ((tabla[i]->key != NULL) && (j != capacity));

    //returns NULL, if the key wasn't found
	return false;
}
template<typename T, typename V>
void HashTable<T, V>::Clear() {

	for (int i = 0; i < capacity; i++) {
		tabla[i]->key = NULL;
		tabla[i]->value = NULL;
	}
	capacity = size = 0;
}
template<typename T, typename V>
bool HashTable<T,V>::SetKeyValue(T key ,V value) {

	int j = 0, i;

	do {
		i = HashIndex(key, j);
		if (tabla[i]->key == key) {
			tabla[i]->value = value;
			//returns true if the set key value vas succesfully, otherwise false
			return true;
		}
		j++;
	} while ((tabla[i]->key != NULL) && (j != capacity));


	return false;

}
template<typename T, typename V>
V HashTable<T,V>::begin(){

	
	for (int i = 0; i < capacity; i++) {

		if (tabla[i]->key != NULL) {
			return tabla[i]->value;
		}
	}
	//if there was no element, returns null
	return NULL;
}
template<typename T, typename V>
V HashTable<T, V>::end() {

	
	for (int i = capacity - 1; i >= 0; i--) {
		if (tabla[i]->key != NULL) {
			return tabla[i]->value;
		}
	}
	//if there was no element, returns null
	return NULL;
}
template<typename T ,typename V>
int HashTable<T, V>::sizeofTable() const{

	return size;
}
template<typename T, typename V>
bool HashTable<T, V>::isFull() const {

	return size == capacity;
}
template<typename T, typename V>
bool HashTable<T, V>::isEmpty() const {

	return size == 0;
}
template<typename T, typename V>
void HashTable<T, V>::Print() const {

	std::cout <<"A tabla merete: " << size << std::endl;
	for (int i = 0; i < capacity; i++) {
		if (tabla[i]->key != NULL) {
			std::cout << tabla[i]->key << " " << tabla[i]->value << std::endl;
		}
	}
}
template<typename T ,typename V>
HashTable<T ,V>::~HashTable() {

	delete[] tabla;
	size = 0;
	capacity = 0;
}




#endif