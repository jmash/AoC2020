#include<iterator>
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>
#include<sstream>
#include<unordered_set>
#include<numeric>
#include<utility>
#include<tuple>
#include<optional>

static int64_t mod_inv(int64_t a, int64_t n)
{
	int64_t t = 0, newt = 1, r = n, newr = a;
	while (newr != 0)
	{
		int64_t q = r / newr;
		int64_t nt = newt; newt = t - q * newt; t = nt;
		int64_t nr = newr; newr = r - q * newr; r = nr;
	}
	if (r > 1) return -1;
	if (t < 0) t += n;
	return t;
}
/*

t % 7 = (7-0) % 7 = 0
t % 13 = (13-1)
t % 59 = (59-4)
t % 31 = (


t=0 mod 7
*/
struct BusSchedule
{
public:
	std::unordered_map<int64_t,int64_t> all_busses;
	int64_t solve_busstop() const
	{
		std::vector<int64_t> ids;
		std::vector<int64_t> equalval;

		for (auto p : all_busses)
		{
			int64_t b = p.first;
			int64_t o = p.second;
			ids.push_back(b);
			equalval.push_back((b - o) % b);
		}
		//chinese remainder theorem
		int64_t N=std::reduce(ids.begin(), ids.end(), (int64_t)1,std::multiplies<int64_t>());
		int64_t x = 0;
		for (size_t i = 0; i < ids.size(); i++)
		{
			int64_t p = N / ids[i];
			x += equalval[i] * mod_inv(p, ids[i]) * p;
		}
		return x % N;
	}
};

std::istream& operator>>(std::istream& inp, BusSchedule& bs)
{
	while (std::isspace(inp.peek()))
	{
		inp.ignore();
	}
	std::string wholething;
	getline(inp, wholething);
	std::istringstream iss(wholething);
	std::string item;
	int64_t offset = 0;
	while (getline(iss, item,','))
	{
		if (item != "x")
		{
			bs.all_busses[atoll(item.c_str())]=offset;
		}
		offset++;
	}
	return inp;
}


int main(int argc, char** argv)
{
	std::ifstream inp("./input.txt");
	BusSchedule bs;
	int64_t timestamp;
	inp >> timestamp >> bs;

	std::cout << "The timestamp is: " << bs.solve_busstop() << std::endl;

	return 0;
}
