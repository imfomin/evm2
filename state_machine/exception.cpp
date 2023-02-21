#include <string>

class exception {
protected:
	std::string m_exception_info;
public:
	exception() { m_exception_info = "Неизвестное исключение"; }
	virtual const std::string& get_info() { return m_exception_info; }
};

class wrong_input : public exception {
public:
	wrong_input() { m_exception_info = "Ошибка: некорректное слово на входе"; }
};

class successful : public exception {
public:
	successful() { m_exception_info = "Автомат распознал слово"; }
};

// machine 1
class even_nulls : public exception {
public:
	even_nulls() { m_exception_info = "Ошибка: в слове чётное число нулей"; }
};

class odd_ones : public exception {
public:
	odd_ones() { m_exception_info = "Ошибка: в слове нечётное число единиц"; }
};

class ones_after_nulls : public exception {
public:
	ones_after_nulls() { m_exception_info = "Ошибка: обнаружена единица после нуля"; }
};

// machine 2
/*class no_second_one : public exception {
public:
	no_second_one() { m_exception_info = "Ошибка: не найдена пара для одной из единиц"; }
};*/

class odd_nulls : public exception {
public:
	odd_nulls() { m_exception_info = "Ошибка: в слове нечётное число нулей между двумя единицами"; }
};

// machine 3
class no_null_after_ones_pair : public exception {
public:
	no_null_after_ones_pair() { m_exception_info = "Ошибка: После пары единиц не найдено нуля"; }
};

// machine 3
class no_one_at_3 : public exception {
public:
	no_one_at_3() { m_exception_info = "Ошибка: На очередной третей позиции не обнаружено единицы"; }
};

// machine 4
class no_ones : public exception {
public:
	no_ones() { m_exception_info = "Ошибка: В слове не найдено ни одной единицы"; }
};