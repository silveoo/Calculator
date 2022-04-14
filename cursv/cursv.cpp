#include <iostream>
#include <stack>

using namespace std;

const double pi = acos(-1);

struct reader
{
	char type; // type - тип чара. 0 - для чисел, + - для сложения и т.д.
	double value;
};

double normalSin(double x)
{
	return (round(sin(x) * 100000000) / 100000000); // Синус из С++ не выводит 0 если ввести в калькулятор sin(p)
}

double normalCos(double x)
{
	return (round(cos(x) * 100000000) / 100000000); // Косинус также не считает корректно некоторые значения
}

int Priority(char Ch)
{
	if (Ch == '+' || Ch == '-') return 1;
	if (Ch == '*' || Ch == '/') return 2;
	if (Ch == '^') return 3;
	if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'l' || Ch == 'q') return 4;
	else return 0; // Приоритет скобок - 0, т.к. в стеке операций операторы лежат НАД открывающейся скобкой
}

bool Maths(stack <reader>& SNum, stack <reader>& SOp, reader& item) {
	// В этой функции из стека с числами берется число, после чего удаляется из стека. Потом берется оператор из стека с операторами
	double a, b, c; // и свитч-кейсами выполняются операции. Далее получившееся число кладется обратно в стек с числами. Собственно, она
	a = SNum.top().value; // и проводит математические действия
	SNum.pop();
	switch (SOp.top().type)
	{
	case '+':
		b = SNum.top().value;
		SNum.pop();
		c = a + b;
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;

	case '-':
		b = SNum.top().value;
		SNum.pop();
		c = b - a;
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;

	case '*':
		b = SNum.top().value;
		SNum.pop();
		c = a * b;
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;

	case '/':
		b = SNum.top().value;
		if (a == 0) {
			cerr << "\nВы попытались разделить на нуль. Этого делать нельзя!\n";
			return false;
		}
		else
		{
			SNum.pop();
			c = (b / a);
			item.type = '0';
			item.value = c;
			SNum.push(item);
			SOp.pop();
			break;
		}
	case '^':
		b = SNum.top().value;
		SNum.pop();
		c = pow(b, a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	case 's':
		c = normalSin(a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	case 'c':
		c = normalCos(a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	case 't':
		if (normalCos(a) == 0) {
			cerr << "\nПри таком значении тангенс не определён\n";
			return false;
		}
		c = tan(a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	case 'l':
		if (a == 0)
		{
			cerr << "\nПри таком значении логарифм не определён\n";
			return false;
		}
		c = log(a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	case 'q':
		if (a < 0)
		{
			cerr << "\n Неверный аргумент для квадратного корня\n";
			return false;
		}
		c = sqrt(a);
		item.type = '0';
		item.value = c;
		SNum.push(item);
		SOp.pop();
		break;
	default:
		cerr << "\nОшибка!\n";
		return false;
		break;
	}
	return true;
}

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "Это калькулятор!\n\nПравила записи выражений:\nсинус - sin\nкосинус - cos\nтангенс - tan\nчисло ПИ - p\nквадратный корень - sqr\nвозведение в степень - ^\n" << endl;
	cout << "Введите любое математическое выражение: ";
	char Ch;
	double value;
	bool trigger = 1;
	stack <reader> SNum;
	stack <reader> SOp;
	reader item;
	while (1)
	{
		Ch = cin.peek();
		if (Ch == '\n')break;
		if ((Ch >= '0' && Ch <= '9') || (Ch == '-' && trigger == 1))
		{
			cin >> value;
			item.type = '0';
			item.value = value;
			SNum.push(item);
			trigger = 0;
			continue;
		}
		if (Ch == 's' || Ch == 'c' || Ch == 't' || Ch == 'l')
		{
			char alotsym[4];
			for (int i = 0; i < 3; i++)
			{
				Ch = cin.peek();
				alotsym[i] = Ch;
				cin.ignore();
			}
			if (alotsym[0] == 's' && alotsym[1] == 'i' && alotsym[2] == 'n')
			{
				item.type = 's';
				item.value = 0;
				SOp.push(item);
				continue;
			}
			if (alotsym[0] == 'c' && alotsym[1] == 'o' && alotsym[2] == 's')
			{
				item.type = 'c';
				item.value = 0;
				SOp.push(item);
				continue;
			}
			if (alotsym[0] == 't' && alotsym[1] == 'a' && alotsym[2] == 'n')
			{
				item.type = 't';
				item.value = 0;
				SOp.push(item);
				continue;
			}
			if (alotsym[0] == 'l' && alotsym[1] == 'o' && alotsym[2] == 'g')
			{
				item.type = 'l';
				item.value = 0;
				SOp.push(item);
				continue;
			}
			if (alotsym[0] == 's' && alotsym[1] == 'q' && alotsym[2] == 'r')
			{
				item.type = 'q';
				item.value = 0;
				SOp.push(item);
				continue;
			}
		}
		if (Ch == 'p')
		{
			item.type = '0';
			item.value = pi;
			SNum.push(item);
			trigger = 0;
			cin.ignore();
			continue;
		}
		if (Ch == '+' || Ch == '-' && trigger == 0 || Ch == '*' || Ch == '/' || Ch == '^')
		{
			if (SOp.size() == 0)
			{
				item.type = Ch;
				item.value = 0;
				SOp.push(item);
				cin.ignore();
				continue;
			}
			if (SOp.size() != 0 && Priority(Ch) > Priority(SOp.top().type))
			{
				item.type = Ch;
				item.value = 0;
				SOp.push(item);
				cin.ignore();
				continue;
			}
			if (SOp.size() != 0 && Priority(Ch) <= Priority(SOp.top().type))
			{
				if (Maths(SNum, SOp, item) == false)
				{
					system("pause");
					return 0;
				}
				continue;
			}
		}
		if (Ch == '(')
		{
			item.type = Ch;
			item.value = 0;
			SOp.push(item);
			cin.ignore();
			continue;
		}
		if (Ch == ')')
		{
			while (SOp.top().type != '(')
			{
				if (Maths(SNum, SOp, item) == false)
				{
					system("pause");
					return 0;
				}
				else continue;
			}
			SOp.pop();
			cin.ignore();
			continue;
		}
		else
		{
			cout << "\nНеправильный элемент!\n";
			system("pause");
			return 0;
		}
	}
	while (SOp.size() != 0)
	{
		if (Maths(SNum, SOp, item) == false) // Если в функции была ошибка - ставится на паузу система (для .exe) и выводится ошибка
		{
			system("pause");
			return 0;
		}
		else continue; // Если в функции не было ошибок - продолжаем работу
	}
	cout << endl;
	cout << endl;
	cout << " Ответ: " << SNum.top().value << endl;
	return 0;
}
