#include "machine.cpp"

class Menu {
private:
	Machine** machines;
	size_t size;

	int select_item() {
		while (true) {
			int choice; std::cin >> choice; std::cin.get();
			if (choice < 0 || choice > size) {
				std::cout << "Неверное число...\n";
				continue;
			}
			return choice;
		}
	}
public:
	Menu() = delete;
	Menu(Machine** m_ptr) { machines = m_ptr; size = machines_count; }

	Machine* select_object() {
		std::cout << "\nВыберите условие для автомата:\n";
		for (int i = 0; i < size; ++i) {
			std::cout << i+1 << ". "; machines[i]->print_info();
		}
		std::cout << "0. Выход\n";

		int choice = select_item();

		if (choice == 0) return nullptr;
		else return machines[choice - 1];
	}
};