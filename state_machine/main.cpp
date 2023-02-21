#include "menu.cpp"

void get_string_from_console(std::string& destination) {
	destination.clear();

	while (true) {
		char x = std::cin.get();
		if (x == '\n') return;
		destination += x;
	}
}

int main() {
	Menu menu(machines);

	while (Machine* m = menu.select_object()) {
		std::cout << "Введите слово для проверки:\n";
		std::string input_string;
		get_string_from_console(input_string);

		try {
			m->run(input_string.c_str());
		}
		catch (exception& exc) {
			std::cout << exc.get_info() << std::endl;
		}
	}

	return 0;
}