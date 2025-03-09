#pragma once
#include <vector>

template<class Tkey>
class comp {
public:
	bool operator()(const Tkey& elem1, const Tkey& elem2) {
		return elem1 <= elem2;
	}
};

template<class Tkey, class Tvalue>
class orderedTable {
	std::vector<std::pair<Tkey, Tvalue>> data;
public:
	orderedTable() {
		data = std::vector<std::pair<Tkey, Tvalue>>(0);
	}
	class iterator;
	void swap(iterator it1, iterator it2) {
		std::pair<Tkey, Tvalue> tmp = *it1;
		*it1 = *it2;
		*it2= tmp;
	}
	iterator insert(const Tkey & key, const Tvalue& value) {
		data.push_back(std::pair<Tkey, Tvalue>(key, value));
		iterator it=end()-1;
		comp<Tkey> cmp;
		while (it!=begin() && cmp((*it).first, (*(it - 1)).first)) {
			swap(it, it-1);
			it--;
		}
		return it;
	}
	iterator erase(const Tkey& key) {
		iterator it=this->begin();
		while (it < this->end() && ((*it).first != key)) {
			it++;
		}
		if ((*it).first == key) {
			swap(it, this->end()-1);
			data.pop_back();
			comp<Tkey> cmp;
			iterator result(it);
			while (it<this->end()-1 && !cmp((*it).first, (*(it + 1)).first)) {
				swap(it, it + 1);
				it++;
			}
			return result;
		}
		else {
			throw "key isn't found\n";
		}
	}
	iterator end() {
		return iterator(this->begin()+this->data.size());
	}
	iterator begin() {
		return iterator(data.data());
	}
	iterator binpoisk(std::vector<std::pair<Tkey, Tvalue>> & data_, const Tkey & x, int left, int right) {
		int might = (left + right) / 2;
		if ((data_.size() == 0)||((might == left) && (data_[might].first != x))) return end();
		if ((data_[might].first == x)) return iterator(&data_[might]);
		if (data_[might].first > x) return binpoisk(data_, x, left, might);

		return binpoisk(data_, x, might, right);
	}
	iterator find(const Tkey& key) {
		return binpoisk(data, key, 0, data.size()+1);
	}
	Tvalue& operator[](const Tkey& key) {

	}
	friend std::ostream& operator <<(std::ostream& ostr, orderedTable & table) {
		ostr << "|   KEY    |    VALUE   |\n";
		for (iterator it = table.begin(); it < table.end(); it++) ostr << "|       " << (*it).first << "       |       " << (*it).second << "      |\n";
		return ostr;
	}
	class iterator {
		std::pair<Tkey, Tvalue> * it;
	public:
		iterator(std::pair<Tkey, Tvalue> * it_) { // что делать, если сюда приходит const_iterator например из vector.begin()
			it=it_;
		}
		bool operator!=(const iterator& other) {
			return this->it != other.it;
		}
		bool operator<=(const iterator& other) {
			return this->it <= other.it;
		}
		bool operator<(const iterator& other) {
			return this->it < other.it;
		}
		iterator operator++(int) { // i++
			return it++;
			
		}
		iterator operator++() { // ++i
			return ++it;
		}
		iterator operator--() { // --i
			return --it;
		}
		iterator operator--(int) { // --i
			return it--;
		}
		iterator operator-(const int& i) {
			return iterator(it - i); //как контролировать, что мы не выходим за границы?
		}
		iterator operator+(const int& i) {
			return iterator(it + i); //как контролировать, что мы не выходим за границы?
		}
		std::pair<Tkey, Tvalue> & operator*() {
			return *it;
		}
		std::pair<Tkey, Tvalue> & operator->() {
			return *it;
		}

	};
	//class iterator {
	//public:
	//	typename std::vector<std::pair<Tkey, Tvalue>>::iterator it;
	//	iterator(consttypename std::vector<std::pair<Tkey, Tvalue>>::const_iterator & it_) { // что делать, если сюда приходит const_iterator например из vector.begin()
	//		it = static_cast<typename std::vector<std::pair<Tkey, Tvalue>>::iterator>(it_);
	//	}
	//	bool operator!=(const iterator& other) {
	//		return this->it != other.it;
	//	}
	//	iterator operator++(int) { // i++
	//		return it++;
	//	}
	//	iterator operator++() { // ++i
	//		return ++it;
	//	}
	//	iterator operator--() { // --i
	//		return --it;
	//	}
	//	iterator operator-(const int & i) {
	//		return iterator(it - i); //как контролировать, что мы не выходим за границы?
	//	}
	//	std::pair<Tkey, Tvalue> operator*() {
	//		return *it;
	//	}
	//	std::pair<Tkey, Tvalue> operator->() {
	//		return *it;
	//	}
	//};
};