#include <iostream>
#include "exception.cpp"

class Machine {
protected:
	enum Symbol { Null, One, End, Other };
#define SYMBOL_COUNT 4

	uint32_t state;
public:
	static Symbol transliterator(char ch) {
		switch (ch) {
		case '0':  return Null;
		case '1':  return One;
		case '\0': return End;
		default:   return Other;
		}
	}

	virtual void print_info() = 0;
	virtual void run(const char* input_string) = 0;
};

class Machine1 : public Machine {
private:
	enum State { A1, A2, A3, A4, EVEN_NULLS, ODD_ONES, ONES_AFTER_NULLS, WRONG_INPUT, Exit };
#define STATE_COUNT_1 4

	uint32_t program[STATE_COUNT_1][SYMBOL_COUNT];
public:
	Machine1() {
		state = A1;
		program[A1][Null] = A3;		  program[A1][One] = A2;				program[A1][End] = EVEN_NULLS;
		program[A2][Null] = ODD_ONES; program[A2][One] = A1;				program[A2][End] = ODD_ONES;
		program[A3][Null] = A4;		  program[A3][One] = ONES_AFTER_NULLS;	program[A3][End] = Exit;
		program[A4][Null] = A3;		  program[A4][One] = ONES_AFTER_NULLS;	program[A4][End] = EVEN_NULLS;

		for (int i = 0; i < STATE_COUNT_1; ++i) { program[i][Other] = WRONG_INPUT; }
	}
		
	void print_info() override {
		std::cout << "В слове сначала идёт чётное количество единиц, затем чётное количество нулей\n";
	}

	void run(const char* input_string) override {
		for (int i = 0; true; ++i) {
			state = program[state][transliterator(input_string[i])];
			
			if (state <= A4) continue;

			switch (state) {
			case EVEN_NULLS:       throw even_nulls();
			case ODD_ONES:         throw odd_ones();
			case ONES_AFTER_NULLS: throw ones_after_nulls();

			case WRONG_INPUT:      throw wrong_input();
			case Exit:             throw successful();
			default:               throw exception();
			}
		}
	}
};

class Machine2 : public Machine {
private:
	enum State { A1, A2, A3, /*NO_SECOND_ONE,*/ ODD_NULLS, WRONG_INPUT, Exit };
#define STATE_COUNT_2 3

	uint32_t program[STATE_COUNT_2][SYMBOL_COUNT];
public:
	Machine2() {
		state = A1;
		program[A1][Null] = A1; program[A1][One] = A2;		  program[A1][End] = Exit;
		program[A2][Null] = A3; program[A2][One] = A1;		  program[A2][End] = /*NO_SECOND_ONE*/Exit;
		program[A3][Null] = A2; program[A3][One] = ODD_NULLS; program[A3][End] = /*NO_SECOND_ONE*/Exit;

		for (int i = 0; i < STATE_COUNT_2; ++i) { program[i][Other] = WRONG_INPUT; }
	}
	
	void print_info() override {
		std::cout << "В слове между каждой парой единиц заключено чётное количество нулей\n";
	}

	void run(const char* input_string) override {
		for (int i = 0; true; ++i) {
			state = program[state][transliterator(input_string[i])];
			
			if (state <= A3) continue;

			switch (state) {
			//case NO_SECOND_ONE: throw no_second_one();
			case ODD_NULLS:     throw odd_nulls();

			case WRONG_INPUT:   throw wrong_input();
			case Exit:          throw successful();
			default:            throw exception();
			}
		}
	}
};

class Machine3 : public Machine {
private:
	enum State { A1, A2, A3, NO_NULL_AFTER_ONES_PAIR, WRONG_INPUT, Exit };
#define STATE_COUNT_3 3

	uint32_t program[STATE_COUNT_3][SYMBOL_COUNT];
public:
	Machine3() {
		state = A1;
		program[A1][Null] = A1; program[A1][One] = A2;		  program[A1][End] = Exit;
		program[A2][Null] = A1; program[A2][One] = A3;		                program[A2][End] = Exit;
		program[A3][Null] = A1; program[A3][One] = NO_NULL_AFTER_ONES_PAIR; program[A3][End] = NO_NULL_AFTER_ONES_PAIR;

		for (int i = 0; i < STATE_COUNT_3; ++i) { program[i][Other] = WRONG_INPUT; }
	}

	void print_info() override {
		std::cout << "В слове за каждой парой единиц идёт хотя бы один ноль\n";
	}

	void run(const char* input_string) override {
		for (int i = 0; true; ++i) {
			state = program[state][transliterator(input_string[i])];
			
			if (state <= A3) continue;

			switch (state) {
			case NO_NULL_AFTER_ONES_PAIR: throw no_null_after_ones_pair();

			case WRONG_INPUT:   		  throw wrong_input();
			case Exit:          		  throw successful();
			default:            		  throw exception();
			}
		}
	}
};

class Machine4 : public Machine {
private:
	enum State { A1, A2, A3, NO_ONE_AT_3, WRONG_INPUT, Exit };
#define STATE_COUNT_4 3

	uint32_t program[STATE_COUNT_4][SYMBOL_COUNT];
public:
	Machine4() {
		state = A1;
		program[A1][Null] = A2;          program[A1][One] = A2; program[A1][End] = Exit;
		program[A2][Null] = A3;          program[A2][One] = A3; program[A2][End] = Exit;
		program[A3][Null] = NO_ONE_AT_3; program[A3][One] = A1; program[A3][End] = Exit;

		for (int i = 0; i < STATE_COUNT_4; ++i) { program[i][Other] = WRONG_INPUT; }
	}

	void print_info() override {
		std::cout << "В слове каждый третий символ - единица\n";
	}

	void run(const char* input_string) override {
		for (int i = 0; true; ++i) {
			state = program[state][transliterator(input_string[i])];
			
			if (state <= A3) continue;

			switch (state) {
			case NO_ONE_AT_3: throw no_one_at_3();

			case WRONG_INPUT: throw wrong_input();
			case Exit:        throw successful();
			default:          throw exception();
			}
		}
	}
};

class Machine5 : public Machine {
private:
	enum State { A1, A2, NO_ONES, WRONG_INPUT, Exit };
#define STATE_COUNT_5 2

	uint32_t program[STATE_COUNT_5][SYMBOL_COUNT];
public:
	Machine5() {
		state = A1;
		program[A1][Null] = A1; program[A1][One] = A2; program[A1][End] = NO_ONES;
		program[A2][Null] = A2; program[A2][One] = A2; program[A2][End] = Exit;

		for (int i = 0; i < STATE_COUNT_5; ++i) { program[i][Other] = WRONG_INPUT; }
	}

	void print_info() override {
		std::cout << "В слове есть хотя бы одна единица\n";
	}

	void run(const char* input_string) override {
		for (int i = 0; true; ++i) {
			state = program[state][transliterator(input_string[i])];
			
			if (state <= A2) continue;

			switch (state) {
			case NO_ONES:     throw no_ones();

			case WRONG_INPUT: throw wrong_input();
			case Exit:        throw successful();
			default:          throw exception();
			}
		}
	}
};

Machine1 m1;
Machine2 m2;
Machine3 m3;
Machine4 m4;
Machine5 m5;

Machine* machines[] = { &m1, &m2, &m3, &m4, &m5 };
size_t machines_count = 5;