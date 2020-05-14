#include"Window.h"
#include"GUI.h"
using namespace Graph_lib;

stringstream ss;
stringstream yours;

class Token {
public:
	char kind;
	double num;
	Token(char ch) :kind(ch), num(0) {}
	Token(char ch, double val) :kind(ch), num(val) {}
};

class Token_stream {
private:
	Token buffer;//缓存区
	bool buffer_full;//判断是否存满
public:
	Token_stream() :buffer_full(false), buffer(0) {}
	Token get();
	void putback(Token t);
};

Token Token_stream::get() {
	if (buffer_full) {
		buffer_full = false;
		return buffer;
	}

	char ch;
	ss >> ch;

	switch (ch) {
	case ';':
	case '(':case ')':case '+':case '-':
	case '*':case '/':case '{':case '}':
		return Token(ch);
	case '.':
	case '0':case '1':case '2':case '3':case '4':
	case '5':case '6':case '7':case '8':case '9':
	{
		ss.putback(ch);
		double val;
		ss >> val;
		return Token('8', val);
	}
//	default:
//		cerr << "输入错误" << endl;
	}
}


double expression();
double term();
double primary();

Token_stream ts;

void Token_stream::putback(Token t) {
//	if (buffer_full)
//		cerr << "内存区已满";
	buffer = t;
	buffer_full = true;
}

double expression() {
	double left = term();//获得左边term的值
	Token t = ts.get();

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term() {
	double left = primary();
	Token t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double chushu = primary();
//			if (chushu == 0)//
//				cerr << "分母不能为零";
			left /= chushu;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double primary() {

	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double val = expression();
		t = ts.get();
//		if (t.kind != ')')
//			cerr << "你应该输入')'" << endl;
		return val;
	}
	case '8':
		return t.num;
	case '{':
	{
		double val = expression();
		t = ts.get();
//		if (t.kind != '}') {
//			cerr << "你应该输入'}'" << endl;
//		}
		return val;
	}
	default:
//		cerr << "输入格式有误";
		return 0;
	}
}

//------------------------------------------------------------------------------

class calculator :public Window {
private:

	Button calculate;
	Button quit_button;
	Button clear_button;

	Button Press_1;
	Button Press_2;
	Button Press_3;
	Button Press_4;
	Button Press_5;
	Button Press_6; 
	Button Press_7;
	Button Press_8;
	Button Press_9;
	Button Press_0;

	Button Press_plus;
	Button Press_subtract;
	Button Press_multiply;
	Button Press_divide;

	Button Press_left_bracket;
	Button Press_right_bracket;

	In_box input;
	Out_box output;

	static void cb_press_1(Address, Address);
	void press_1();
	static void cb_press_2(Address, Address);
	void press_2();
	static void cb_press_3(Address, Address);
	void press_3();
	static void cb_press_4(Address, Address);
	void press_4();
	static void cb_press_5(Address, Address);
	void press_5();
	static void cb_press_6(Address, Address);
	void press_6();
	static void cb_press_7(Address, Address);
	void press_7();
	static void cb_press_8(Address, Address);
	void press_8();
	static void cb_press_9(Address, Address);
	void press_9();
	static void cb_press_0(Address, Address);
	void press_0();

	static void cb_press_plus(Address, Address);
	void press_plus();
	static void cb_press_subtract(Address, Address);
	void press_subtract();
	static void cb_press_multiply(Address, Address);
	void press_multiply();
	static void cb_press_divide(Address, Address);
	void press_divide();

	static void cb_press_left_bracket(Address, Address);
	void press_left_bracket();
	static void cb_press_right_bracket(Address, Address);
	void press_right_bracket();

	static void cb_next(Address, Address);
	void next();
	static void cb_quit(Address, Address);
	void quit();
	static void cb_clear(Address, Address);
	void clear();

public:
	calculator(Point, int, int, const string&);
};

calculator::calculator(Point p, int w, int h, const string& title) :
	Window(p, w, h, title),
	input(Point(200, 0), 100, 20, "Please input your expression:"),
	output(Point(200, 100), 100, 20, "This is the answer:"),
	calculate(Point(300, 0), 70, 20, "Calculate", cb_next),
	quit_button(Point(300, 100), 70, 20, "Quit", cb_quit),
	clear_button(Point(300, 50), 70, 20, "Clear", cb_clear),

	Press_1(Point(200, 200), 50, 50, "1", cb_press_1),
	Press_2(Point(250, 200), 50, 50, "2", cb_press_2),
	Press_3(Point(300, 200), 50, 50, "3", cb_press_3),
	Press_4(Point(200, 250), 50, 50, "4", cb_press_4),
	Press_5(Point(250, 250), 50, 50, "5", cb_press_5),
	Press_6(Point(300, 250), 50, 50, "6", cb_press_6),
	Press_7(Point(200, 300), 50, 50, "7", cb_press_7),
	Press_8(Point(250, 300), 50, 50, "8", cb_press_8),
	Press_9(Point(300, 300), 50, 50, "9", cb_press_9),
	Press_0(Point(250, 350), 50, 50, "0", cb_press_0),

	Press_plus(Point(400, 200), 50, 50, "+", cb_press_plus),
	Press_subtract(Point(450, 200), 50, 50, "-", cb_press_subtract),
	Press_multiply(Point(400, 250), 50, 50, "*", cb_press_multiply),
	Press_divide(Point(450, 250), 50, 50, "/", cb_press_divide),

	Press_left_bracket(Point(400, 300), 50, 50, "(", cb_press_left_bracket),
	Press_right_bracket(Point(450, 300), 50, 50, ")", cb_press_right_bracket)

{
	attach(input);
	attach(output);
	attach(calculate);
	attach(quit_button);
	attach(clear_button);

	attach(Press_1);
	attach(Press_2);
	attach(Press_3);
	attach(Press_4);
	attach(Press_5);
	attach(Press_6);
	attach(Press_7);
	attach(Press_8);
	attach(Press_9);
	attach(Press_0);

	attach(Press_plus);
	attach(Press_subtract);
	attach(Press_multiply);
	attach(Press_divide);

	attach(Press_left_bracket);
	attach(Press_right_bracket);

	redraw();
}

void calculator::cb_press_1(Address, Address pw) {
	reference_to<calculator>(pw).press_1();
}

void calculator::press_1() {

	yours << 1;
	input.put(yours.str());

}

void calculator::cb_press_2(Address, Address pw) {
	reference_to<calculator>(pw).press_2();
}

void calculator::press_2() {

	yours << 2;
	input.put(yours.str());

}

void calculator::cb_press_3(Address, Address pw) {
	reference_to<calculator>(pw).press_3();
}

void calculator::press_3() {

	yours << 3;
	input.put(yours.str());

}

void calculator::cb_press_4(Address, Address pw) {
	reference_to<calculator>(pw).press_4();
}

void calculator::press_4() {

	yours << 4;
	input.put(yours.str());

}

void calculator::cb_press_5(Address, Address pw) {
	reference_to<calculator>(pw).press_5();
}

void calculator::press_5() {

	yours << 5;
	input.put(yours.str());

}

void calculator::cb_press_6(Address, Address pw) {
	reference_to<calculator>(pw).press_6();
}

void calculator::press_6() {

	yours << 6;
	input.put(yours.str());

}

void calculator::cb_press_7(Address, Address pw) {
	reference_to<calculator>(pw).press_7();
}

void calculator::press_7() {

	yours << 7;
	input.put(yours.str());

}

void calculator::cb_press_8(Address, Address pw) {
	reference_to<calculator>(pw).press_8();
}

void calculator::press_8() {

	yours << 8;
	input.put(yours.str());

}

void calculator::cb_press_9(Address, Address pw) {
	reference_to<calculator>(pw).press_9();
}

void calculator::press_9() {

	yours << 9;
	input.put(yours.str());

}

void calculator::cb_press_0(Address, Address pw) {
	reference_to<calculator>(pw).press_0();
}

void calculator::press_0() {

	yours << 0;
	input.put(yours.str());

}

void calculator::cb_press_plus(Address, Address pw) {
	reference_to<calculator>(pw).press_plus();
}

void calculator::press_plus() {

	yours << '+';
	input.put(yours.str());

}

void calculator::cb_press_subtract(Address, Address pw) {
	reference_to<calculator>(pw).press_subtract();
}

void calculator::press_subtract() {

	yours << '-';
	input.put(yours.str());

}

void calculator::cb_press_multiply(Address, Address pw) {
	reference_to<calculator>(pw).press_multiply();
}

void calculator::press_multiply() {

	yours << '*';
	input.put(yours.str());

}

void calculator::cb_press_divide(Address, Address pw) {
	reference_to<calculator>(pw).press_divide();
}

void calculator::press_divide() {

	yours << '/';
	input.put(yours.str());

}

void calculator::cb_press_left_bracket(Address, Address pw) {
	reference_to<calculator>(pw).press_left_bracket();
}

void calculator::press_left_bracket(){

	yours << "(";
	input.put(yours.str());

}

void calculator::cb_press_right_bracket(Address, Address pw) {
	reference_to<calculator>(pw).press_right_bracket();
}

void calculator::press_right_bracket() {

	yours << ")";
	input.put(yours.str());

}

void calculator::cb_next(Address, Address pw) {
	reference_to<calculator>(pw).next();
}

void calculator::next() {
	yours.str("");
	ss << input.get_string();
	char solve = ';';
	ss << solve;
	double val = 0;
	while (ss) {
		
		Token t = ts.get();
		if (t.kind == ';') {
			ss << val;
			break;
		}
		else {
			ts.putback(t);
			val = expression();
		}

	}
	ss.str("");
	stringstream _ss;
	_ss << val;
	output.put(_ss.str());
}

void calculator::cb_quit(Address, Address pw) {
	reference_to<calculator>(pw).quit();
}

void calculator::quit() {
	hide();
}

void calculator::cb_clear(Address, Address pw) {
	reference_to<calculator>(pw).clear();
}

void calculator::clear() {

	yours.str("");
	input.put(yours.str());

}

int main() {
	calculator cal(Point(100, 100), 600, 400, "calculator");
	return gui_main();
}