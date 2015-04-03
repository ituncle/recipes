#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <time.h>

//#include <Windows.h>

namespace Combination
{
	int combination() 
	{
		std::cout << "hello world!" << std::endl;
		int values[] = { 1, 2, 3, 4, 5, 6, 7, };
		int elements[] = { 1, 1, 1, 0, 0, 0, 0 };
		const size_t N = sizeof(elements) / sizeof(elements[0]);
		assert(N == sizeof(values) / sizeof(values[0]));
		std::vector<int> selectors(elements, elements + N);
		int count = 0;
		do {
			std::cout << ++count << ": ";
			for (size_t i = 0; i < selectors.size(); i++){
				if (selectors[i]){
					std::cout << values[i] << ", ";
				}
			}
			std::cout << std::endl;
		} while (prev_permutation(selectors.begin(), selectors.end()));
		return 0;
	}
}

namespace MergeN{
	typedef int Record;
	typedef std::vector<Record> File;

	struct Input
	{
		Record value;
		size_t index;
		const File* file;

		explicit Input(const File* f)
			: value(-1),index(0),file(f) {};

		bool next()
		{
			if (index < file->size()) {
				value = (*file)[index];
				++index;
				return true;
			} else {
				return false;
			}
		}

		bool operator<(const Input& rhs) const
		{
			return value > rhs.value;
		}
	};

	File mergeN(const std::vector<File>& files)
	{
		File output;
		std::vector<Input> inputs;
		
		for (size_t i = 0; i < files.size(); ++i) {
			Input input(&files[i]);
			if (input.next()){
				inputs.push_back(input);
			}
		}
		std::make_heap(inputs.begin(), inputs.end());
		while (!inputs.empty()) {
			std::pop_heap(inputs.begin(), inputs.end());
			output.push_back(inputs.back().value);

			if (inputs.back().next()){
				std::push_heap(inputs.begin(), inputs.end());
			}
			else {
				inputs.pop_back();
			}
		}
		return output;
	}
	void mergeN_test()
	{
		const int kFiles = 32;
		std::vector<File> files(kFiles);
		for (int i = 0; i < kFiles; ++i){
			File file(rand() % 10);
			std::generate(file.begin(), file.end(), &rand);
			std::sort(file.begin(), file.end());
			files[i].swap(file);
		}

		File output = mergeN(files);
		std::copy(output.begin(), output.end(), std::ostream_iterator
			<Record>(std::cout, "\n"));
	}
}//namespace

namespace Partition
{
	bool isOdd(int x)
	{
		return x % 2 != 0;
	}

	void moveOddsBeforeEvens()
	{
		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::partition(oddeven, oddeven + 6, &isOdd);
		std::copy(oddeven, oddeven + 6, std::ostream_iterator<int>(std::cout, ", "));
		std::cout << std::endl;
	}

	void partition()
	{
		moveOddsBeforeEvens();
		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::stable_partition(oddeven, oddeven + 6, &isOdd);
		std::copy(oddeven, oddeven + 6, std::ostream_iterator<int>(std::cout, ", "));
		std::cout << std::endl;
	}
}//namespace

namespace Permutation
{
	void permutation()
	{
		int elements[] = { 1, 2, 3, 4 };
		const size_t N = sizeof(elements) / sizeof(elements[0]);
		std::vector<int> vec(elements, elements + N);

		int count = 0;
		do{
			std::cout << ++count << ": ";
			std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, ", "));
			std::cout << std::endl;
		} while (next_permutation(vec.begin(), vec.end()));
	}
}

namespace Permutation2
{
	void permutation()
	{
		char elements[] = { 'a', 'a', 'b', 'b','b' };
		const size_t N = sizeof(elements) / sizeof(elements[0]);
		std::vector<char> vec(elements, elements + N);
		
		int count = 0;
		do {
			std::cout << ++count << ": ";
			std::copy(vec.begin(), vec.end(), std::ostream_iterator<char>(std::cout, ", "));
			std::cout << std::endl;
		} while (next_permutation(vec.begin(), vec.end()));
	}
}

namespace Unique
{
	struct AreBothSpaces
	{
		bool operator()(char x, char y) const
		{
			return x == ' ' && y == ' ';
		}
	};

	void removeContinuousSpaces(std::string& str)
	{
		std::string::iterator last = std::unique(str.begin(), str.end(), AreBothSpaces());
		str.erase(last, str.end());
	}

	void unique_test()
	{
		std::string inout;

		inout = "";
		removeContinuousSpaces(inout);
		assert(inout == "");

		inout = "a";
		removeContinuousSpaces(inout);
		assert(inout == "a");

		inout = " a";
		removeContinuousSpaces(inout);
		assert(inout == " a");

		inout = "  a";
		removeContinuousSpaces(inout);
		assert(inout == " a");

		inout = "a ";
		removeContinuousSpaces(inout);
		assert(inout == "a ");

		inout = "a  ";
		removeContinuousSpaces(inout);
		assert(inout == "a ");

		inout = "aaa    bbb";
		removeContinuousSpaces(inout);
		assert(inout == "aaa bbb");

		inout = "aaa    bbb       ccc";
		removeContinuousSpaces(inout);
		assert(inout == "aaa bbb ccc");

		inout = " a b   c d ";
		removeContinuousSpaces(inout);
		assert(inout == " a b c d ");

		inout = "        ";
		removeContinuousSpaces(inout);
		assert(inout == " ");
	}
}

namespace Select
{
	using namespace std;
	vector<int> selectBySorting(const vector<int>& input, int k1, int k2)
	{
		assert(0 <= k1 && k1 < input.size());
		assert(0 <= k2 && k2 < input.size());
		assert(k1 <= k2);
		vector<int> temp(input);
		sort(temp.begin(), temp.end());
		return vector<int>(temp.begin() + k1, temp.begin() + k2 + 1);
	}

	vector<int> selectByNthElement(const vector<int>& input, int k1, int k2)
	{
		assert(0 <= k1 && k1 < input.size());
		assert(0 <= k2 && k2 < input.size());
		assert(k1 <= k2);

		vector<int> temp(input);
		nth_element(temp.begin(), temp.begin() + k2 + 1, temp.end());
		nth_element(temp.begin(), temp.begin() + k1, temp.begin() + k2 + 1);
		sort(temp.begin() + k1, temp.begin() + k2 + 1);
		return vector<int>(temp.begin() + k1, temp.begin() + k2 + 1);
	}
	vector<int> selectByPartialSort(const vector<int>& input, int k1, int k2)
	{
		assert(0 <= k1 && k1 < input.size());
		assert(0 <= k2 && k2 < input.size());
		assert(k1 <= k2);

		vector<int> temp(input);
		nth_element(temp.begin(), temp.begin() + k1, temp.end());
		partial_sort(temp.begin() + k1, temp.begin() + k2 + 1, temp.end());
		return vector<int>(temp.begin() + k1, temp.begin() + k2 + 1);
	}
	void print(const vector<int>& vec)
	{
		copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
	}
	static decltype(clock()) _beg;

	template<typename F>
	void PTT(F dut)
	{
		auto beg = clock();
		dut();
		cout << "Cost Tick: " << clock() - beg << endl;
	}

	inline void beg()
	{
		_beg = clock();
	}
	inline void end()
	{
		cout << "Cost Tick: " << clock() - _beg << endl;
		beg();
	}
	void select()
	{
		vector<int> input;
		for (int i = 0; i < 1000000; ++i){
			input.push_back(i);
		}
		random_shuffle(input.begin(), input.end());

		PTT([&](){selectBySorting(input, 100000, 500000); });
		PTT([&](){selectByNthElement(input, 100000, 500000); });
		PTT([&](){selectByPartialSort(input, 100000, 500000); });
	}
}

int main(void) {
	//Combination::combination();
	//MergeN::mergeN_test();
	//Partition::partition();
	//Permutation2::permutation();
	//Unique::unique_test();
	
	Select::select();
	//system("PAUSE");
	return 0;
}