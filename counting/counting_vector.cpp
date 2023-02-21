#include <iostream>
#include <fstream>
#include <vector>

void load(std::vector<std::string>& str_vec, const char* filename) {
	std::ifstream in(filename);

	if (!in) return;

	str_vec.clear();
	std::string input_buf;
	while (in) {
		char x;
		x = in.get();

		if (x == '\n') { str_vec.push_back(input_buf); input_buf.clear(); }
		else 		   { input_buf += x; }
	}

	in.close();
}

#define PRINT_VECTOR(vector) for (auto& el : vector) { std::cout << el << ' '; } std::cout << '\n';

std::vector<std::string> counting(std::vector<std::string>& people, uint32_t stride) {
	if (people.size() == 0) return std::vector<std::string>();

	std::vector<std::string> kicked_out;

	uint32_t index = (stride - 1) % people.size();
	while (people.size() > 1) {
		kicked_out.push_back(people[index]);
		people.erase(people.begin() + index);
		index = (index + stride - 1) % people.size();
	}

	return kicked_out;
}

int main(int argc, char* argv[]) {
	int stride;
	if (argc < 2) stride = 3;
	else stride = atoi(argv[1]);

	std::vector<std::string> people;

	load(people, "people.txt");

	std::cout << "Начальный набор людей: "; PRINT_VECTOR(people);
	std::cout << "-------------------------------------\n";

	std::vector<std::string> kicked_out = counting(people, stride);
	std::cout << "Порядок выбывания: "; PRINT_VECTOR(kicked_out);
	std::cout << "-------------------------------------\n";

	std::cout << "Победитель: "; PRINT_VECTOR(people);

	return 0;
}