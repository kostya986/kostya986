#include <iostream>
#include <vector>
#include <list>
#include <iterator>

template<class T>
class VectorList
{
private:
    using VectT  = std::vector<T>;
    using ListT = std::list<VectT>;

public:
    using value_type = T;

    VectorList() = default;
    VectorList(VectorList const &) = default;
    VectorList(VectorList &&) = default;

    VectorList & operator=(VectorList &&)     = default;
    VectorList & operator=(VectorList const &) = default;

    // метод, который будет использоваться для заполнения VectorList
    // гарантирует, что в списке не будет пустых массивов
    template<class It>
    void append(It p, It q) // определена снаружи
  {
        if (p != q)
            data_.push_back(VectT(p,q));
    }


    bool empty() const { return size() == 0; }

    // определите метод size
    size_t size() const
    {
        size_t result = 0;
        for (auto &now : data_) {
            result += now.size();
        }
        return result;
    }

    // определите const_iterator
    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, const T, int, const T*, const T&> {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = int;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

        friend class VectorList<T>;

        const_iterator() = default;
        const_iterator(const const_iterator &) = default;
        const_iterator(ListT const *data, typename ListT::const_iterator it, typename VectT::const_iterator i)
            : date(data), itl(it), itv(i)
            {
                if (date->size() == 0) {
                    date = data;
                    itl = --date->end();
                    itv = (--date->end())->end();
                }
            }

        const_iterator operator++(int) {
            if (itv != (--date->end())->end()) {
                const_iterator tmp(*this);
                ++itv;
                if (itv == itl->end() && itl != --date->end()) {
                    ++itl;
                    itv = itl->begin();
                }
                return tmp;
            }
            return *this;
        }

        const_iterator& operator++() {
            if (itv != (--date->end())->end()) {
                ++itv;
                if (itv == itl->end() && itl != --date->end()) {
                    ++itl;
                    itv = itl->begin();
                }
            }
            return *this;
        }

        const_iterator operator--(int) {
            if (itv != --(date->begin()->begin())) {
                const_iterator tmp(*this);
                --itv;
                if (itv == --itl->begin() && itl != date->begin()) {
                    --itl;
                    itv = --itl->end();
                }
                return tmp;
            }
            return *this;
        }

        const_iterator& operator--() {
            if (itv != --(date->begin()->begin())) {
                --itv;
                if (itv == --itl->begin() && itl != date->begin()) {
                    --itl;
                    itv = --itl->end();
                }
            }
            return *this;
        }

        bool operator == (const const_iterator &it) const {
            return itv == it.itv;
        }

        bool operator != (const const_iterator &it) const {
            return itv != it.itv;
        }

        reference operator *() const {
            return *itv;
        }

        pointer operator ->() const {
            return &*itv;
        }

        ListT const *date = &data_;
        typename ListT::const_iterator itl;
        typename VectT::const_iterator itv;
    };

    // определите методы begin / end
    const_iterator begin() const { return const_iterator(&data_, data_.cbegin(), data_.cbegin()->cbegin()) ; }
    const_iterator end()   const { return const_iterator(&data_, --data_.cend(), (--data_.cend())->cend()) ; }

    // определите const_reverse_iterator
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // определите методы rbegin / rend
    const_reverse_iterator rbegin() const { return std::reverse_iterator<const_iterator>(end()) ;   }
    const_reverse_iterator rend()   const { return std::reverse_iterator<const_iterator>(begin()) ; }

private:
    ListT data_;
};

int main() {
	VectorList<int> vl;
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6};
	vl.append(v1.begin(), v1.end());
	vl.append(v2.begin(), v2.end());
	for(auto it = vl.begin(); it != vl.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	for (auto it = vl.begin(); it != vl.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	VectorList<int> VL;
	if (VL.begin() == VL.end())
		std::cout << "Ohh yeee \n";


	std::cout << "\n";


	for (auto it = --vl.end(); it != --vl.begin(); --it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;

	for (auto it = --vl.end(); it != --vl.begin(); --it) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;

	std::cout << *vl.rbegin() << std::endl;

	std::cout << vl.begin().operator ->() << std::endl;
	std::cout << &*vl.begin() << std::endl;

	std::cout << VL.size() << "\n";
	std::cout << vl.size() << std::endl;

	return 0;
}
