#include <iostream>
#include <vector>

#define INITIAL_CAPACITY 8

template <typename T, typename Hasher>
class HashTable{
	private:
		
		std::vector<T*> table;
		std::vector<bool> deleted;
		int size;
		Hasher hasher1, hasher2;
		const float MAX_ALPHA;
		bool checkByHash(const size_t& hash1, const size_t& hash2, const T& key){
			int i;
			for ( i = hash1 % table.size();	( table[i] ) || deleted[i];	i = (i + ( 2 * hash2 + 1 )) % table.size() ){
				if ( table[i] )
					if (*table[i] == key) return true;
			}
			;
			if ( table[i] ) return true;
			else return false;
		};
		void expand(){

			std::vector<T*> newTable(table.size() * 2);
			for ( int i = 0; i < table.size(); ++i ){
				if ( table[i] ){
					size_t hash1 = hasher1(*table[i]);
					size_t hash2 = hasher2(*table[i]);

					int j;
					for ( j = hash1 % newTable.size(); newTable[j]; j = (j + ( 2 * hash2 + 1 )) % newTable.size() )
					;
					newTable[j] = table[i];
				}
			}

			table = newTable;
			deleted = std::vector<bool>(table.size() * 2);
		};
	public:
		HashTable(Hasher hasher1, Hasher hasher2, size_t _size = INITIAL_CAPACITY, float alpha = 0.75): 
			table(_size, NULL), 
			deleted(_size, false), 
			size(0), 
			MAX_ALPHA(alpha)
		{
		};
		HashTable(const HashTable<T, Hasher>& oldTable)
		{
			size = oldTable.size;
			deleted = oldTable.deleted;
			MAX_ALPHA = oldTable.MAX_ALPHA;
			hasher1 = oldTable.hasher1;
			hasher2 = oldTable.hasher2;

			table = std::vector<T*>(oldTable.table.size());
			for( int i = 0; i < oldTable.table.size(); ++i) {
				if(!oldTable.table[i]) table[i] = new T(*oldTable.table[i]);
			}
		};
		HashTable operator=(const HashTable<T, Hasher>& oldTable)
		{
			size = oldTable.size;
			deleted = oldTable.deleted;
			MAX_ALPHA = oldTable.MAX_ALPHA;
			hasher1 = oldTable.hasher1;
			hasher2 = oldTable.hasher2;

			table = std::vector<T*>(oldTable.table.size());
			for( int i = 0; i < oldTable.table.size(); ++i) {
				if(!oldTable.table[i]) table[i] = new T(*oldTable.table[i]);
			}
			return *this;
		};

		~HashTable(){
			int len = table.size();
			for ( int i = 0; i < len; ++i ){
				if ( !table[i] ) delete table[i];
			}
		};

		bool add(const T& key){

			if( ! ( size < table.size() * MAX_ALPHA) ) expand();

			size_t hash1 = hasher1(key);
			size_t hash2 = hasher2(key);
			if ( checkByHash(hash1, hash2, key) ) return false;

			int i;
			for ( i = hash1 % table.size(); table[i]; i = (i + ( 2 * hash2 + 1 )) % table.size() )
			;
			table[i] = new T(key);
			++size;
			return true;
		};

		bool deleteEl(const T& key){
			size_t hash1 = hasher1(key);
			size_t hash2 = hasher2(key);

			int i;
			for ( i = hash1 % table.size();	( table[i] ) || deleted[i];	i = (i + ( 2 * hash2 + 1 )) % table.size() ){
				if ( table[i] )	
					if (*table[i] == key) {
						delete table[i];
						table[i] = NULL;
						deleted[i] = true;
						return true;
					}
			}

			return false;
		};

		bool check(const T& elem){
			size_t hash1 = hasher1(elem);
			size_t hash2 = hasher2(elem);
			return checkByHash(hash1, hash2, elem);
		};

};

class StringHasher{
	public:
		StringHasher(unsigned int _prime = 69): prime(_prime){};
		size_t operator()(const std::string& str){
			size_t hash = 0;
			int len = str.length();
			for (int i = 0; i < len; ++i) hash = hash * prime + str[i];
			return hash;
		};
	private:
		const unsigned int prime;
};

void printResult(const bool& res){
	std::cout << ( res ? "OK" : "FAIL") << std::endl;
}

int main(){
	char c;
	std::string elem;
	HashTable<std::string, StringHasher> table(StringHasher(1), StringHasher(2));

	while ( std::cin >> c >> elem ) {
		switch (c)
		{
		case '?':
			printResult(table.check(elem));
			break;
		case '+':
			printResult(table.add(elem));
			break;
		case '-':
			printResult(table.deleteEl(elem));
			break;
		default:
			printResult(false);
			break;
		}
	}
	
}