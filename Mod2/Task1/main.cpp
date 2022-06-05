#include <iostream>
#include <vector>

#define INITIAL_CAPACITY 8

template <typename T, typename Hasher>
class HashTable{
	private:
		enum state{ empty, full, deleted };
		std::vector<T> table;
		std::vector<enum state> deletedTable;
		int size;
		Hasher hasher1, hasher2;
		const float MAX_ALPHA;
		bool checkByHash(const size_t& hash1, const size_t& hash2, const T& key){
			int i;
			for ( i = hash1 % table.size();	deletedTable[i] != empty;	i = (i + ( 2 * hash2 + 1 )) % table.size() ){
					if (deletedTable[i] != deleted && table[i] == key) return true;
			};
			return false;
		};
		void expand(){

			std::vector<T> newTable(table.size() * 2);
			std::vector<enum state> newDeleted(table.size() * 2, empty);
			for ( int i = 0; i < table.size(); ++i ){
				if(deletedTable[i] != full) continue;
				size_t hash1 = hasher1(table[i]);
				size_t hash2 = hasher2(table[i]);

				int j;
				for ( j = hash1 % newTable.size(); newDeleted[j] != empty; j = (j + ( 2 * hash2 + 1 )) % newTable.size() )
				;
				newTable[j] = table[i];
				newDeleted[j] = full;
			}

			table = newTable;
			deletedTable = newDeleted;
		};
	public:
		HashTable(Hasher hasher1, Hasher hasher2, size_t _size = INITIAL_CAPACITY, float alpha = 0.75): 
			table(_size), 
			deletedTable(_size, empty), 
			size(0), 
			MAX_ALPHA(alpha)
		{
		};
		HashTable(const HashTable<T, Hasher>& oldTable)
		{
			size = oldTable.size;
			deletedTable = oldTable.deletedTable;
			MAX_ALPHA = oldTable.MAX_ALPHA;
			hasher1 = oldTable.hasher1;
			hasher2 = oldTable.hasher2;

			table = oldTable.table;
		};
		HashTable operator=(const HashTable<T, Hasher>& oldTable)
		{
			size = oldTable.size;
			deletedTable = oldTable.deletedTable;
			MAX_ALPHA = oldTable.MAX_ALPHA;
			hasher1 = oldTable.hasher1;
			hasher2 = oldTable.hasher2;

			table = oldTable.table;
			return *this;
		};

		~HashTable(){
		};

		bool add(const T& key){

			if( ! ( size < table.size() * MAX_ALPHA) ) expand();

			size_t hash1 = hasher1(key);
			size_t hash2 = hasher2(key);

			int i;
			for ( i = hash1 % table.size(); deletedTable[i] != empty; i = (i + ( 2 * hash2 + 1 )) % table.size() )
				if(table[i] == key && deletedTable[i] == full) return false;
			
			table[i] = key;
			deletedTable[i] = full;
			++size;
			return true;
		};

		bool deleteEl(const T& key){
			size_t hash1 = hasher1(key);
			size_t hash2 = hasher2(key);

			int i;
			for ( i = hash1 % table.size();	deletedTable[i] != empty;	i = (i + ( 2 * hash2 + 1 )) % table.size() ){
				if (table[i] == key && deletedTable[i] == full) {
					deletedTable[i] = deleted;
					--size;
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