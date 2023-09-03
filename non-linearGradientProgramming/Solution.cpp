#include "Solution.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ConsoleInterface.h>

namespace KHAS {
	Solution::Solution(const std::string& title) noexcept
		: window_name_{ title }
		, app_{ window_name_ , WinWidth{ .width = 80 }, WinHeight{ .height = 100 } }
	{
		init();
	}

	void Solution::init() noexcept
	{
		using namespace std::string_literals;

		app_.addHeaderItem(window_name_);
		app_.addHeaderItem(app_.dividingLine(), IsFormated::Disable);
		app_.addHeaderItem("Лабораторная работа:"s, "№ 3"s, Aligment::JUSTIFIED);
		app_.addHeaderItem("Группа:"s, "ПБ-11"s, Aligment::JUSTIFIED);
		app_.addHeaderItem("Студент:"s, "Хакимов А.С."s, Aligment::JUSTIFIED);
		app_.addHeaderItem("метод решения:"s, "Эрроу-Гурвица."s, Aligment::JUSTIFIED);


	}

	bool Solution::checkValue(double x1, double x2) const noexcept
	{

		if (x1 < 0
			|| x2 < 0
			|| (5 * x1 + 6 * x2) > 60.
			|| (4 * x1 + 9 * x2) > 72.) return false;

		return true;
	}

	void Solution::start() noexcept
	{
		using namespace std::string_literals;
		/*
		auto x1{ generateRandom() };
		auto x2{ generateRandom() };

		while (!checkValue(x1, x2)) {
			x1 = generateRandom();
			x2 = generateRandom();
		}//*/
		double x1 { 7 };
		double x2 { 4 };
		auto fx{ funcF(x1, x2) };
		const auto lambda{ 0.001 };
		const auto coef_accuracy{ 0.0001 };

		printStartData(x1, x2, fx, lambda, coef_accuracy);
		printDerivatives();

		double alpha1{};
		double alpha2{};

		size_t iter{ 1 };

		for (double div_accuracy{ 1 }; div_accuracy > coef_accuracy; ++iter) {

			printNowIter(iter);

			/////////////////////////////////////////////////////////////
			/*       */
			alpha1 = getAlpha(funcG1(x1, x2), alpha1, lambda);
			alpha2 = getAlpha(funcG2(x1, x2), alpha2, lambda);

			printAlpha(alpha1, alpha2);

			//////////////////////////////////////////////////
			/*          */
			x1 += lambda * (funcF1(x1) + (-5 * alpha1) + (-6 * alpha2) );
			x1 = x1 < 0 ? 0 : x1;

			x2 += lambda * (funcF2(x2) + (-4 * alpha1) + (-9 * alpha2) );
			x2 = x2 < 0 ? 0 : x2;

			printVarX(x1, x2);

			/////////////////////////////////////////////////////
			/*                 */

			auto fg1{ funcG1(x1, x2) };
			auto fg2{ funcG2(x1, x2) };

			printFG(fg1, iter, "G1");
			printFG(fg2, iter, "G2");

			if (fg1 < 0 && fg2 < 0) continue;
			
			auto new_fx{ funcF(x1, x2) };
			div_accuracy = std::abs(new_fx - fx);
			fx = new_fx;

			printAccuracy(div_accuracy);

		}

		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
		app_.addDataItem("Необходимая точность достигнута");
		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
		app_.addDataItem(app_.createString("x1: "s, std::to_string(x1), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.createString("x2: "s, std::to_string(x2), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.createString("Количество итераций: "s, std::to_string(iter), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine('='), IsFormated::Disable);


		//window.addMenuItem("hi", [] { return std::vector<std::string>{ {"qwerty"} };  }, IsExit::True);
		//window.addMenuItem("fgfgfgfghfghf:", std::nullopt);
		//window.addMenuItem("Выход:", std::nullopt );
		app_.loop();
	}

	double Solution::generateRandom() const noexcept
	{
		return 1.0 * randFromRange<int32_t>(0, 10);
	}


	double Solution::funcF(double x1, double x2) const noexcept
	{
		auto xx1{ x1 - 9 };
		auto xx2{ x2 - 6 };
		return -1. * xx1 * xx1 - xx2 * xx2;
	}

	double Solution::funcG1(double x1, double x2) const noexcept
	{
		return 60 - 5 * x1 - 6 * x2;
	}

	double Solution::funcG2(double x1, double x2) const noexcept
	{
		return 72 - 4 * x1 - 9 * x2;
	}

	void Solution::printStartData(double x1, double x2, double fx, double lambda, double coef_accuracy) noexcept
	{
		using namespace std::string_literals;

		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
		app_.addDataItem("Исходные данные");
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem("f(x1,x2) = - (x1 - 9)^2 - (x2-6)^2 -> max"s);
		app_.addDataItem("5 * x1 + 6 * x2 <= 60");
		app_.addDataItem("4 * x1 + 9 * x2 <= 72");
		app_.addDataItem("x1; x2 >= 0");
		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
		app_.addDataItem("Возьмем любое допустимое решение системы ограничений");
		app_.addDataItem("в качественачального приближения");
		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);

		app_.addDataItem(app_.createString("x1: "s, std::to_string(x1), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("x2: "s, std::to_string(x2), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("lambda: "s, std::to_string(lambda), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("Точность: "s, std::to_string(coef_accuracy), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("alpha: "s, "0"s, Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("f(x1, x2): "s, std::to_string(fx), Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);

		app_.addDataItem(app_.createString("g1(x1, x2): "s, "60 - 5 * x1 - 6 * x2"s, Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);
		app_.addDataItem(app_.createString("g2(x1, x2): "s, "72 - 4 * x1 - 9 * x2"s, Aligment::JUSTIFIED), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine(), IsFormated::Disable);

		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);

	}


	void Solution::printDerivatives() noexcept
	{
		app_.addDataItem("Определим частные производные от функций f и g");
		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
		app_.addDataItem("fx1 = 18 - 2 * x1");
		app_.addDataItem("fx2 = 12 - 2 * x2");
		app_.addDataItem("g1x1 = -5");
		app_.addDataItem("g1x2 = -6");
		app_.addDataItem("g2x1 = -4");
		app_.addDataItem("g2x2 = -9");
		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
	}


	void Solution::printNowIter(size_t iter) noexcept
	{
		using namespace std::string_literals;
		app_.addDataItem(app_.dividingLine('-'), IsFormated::Disable);
		app_.addDataItem(app_.createString("Итерация №: "s, std::to_string(iter)), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
	}


	void Solution::printAlpha(double alpha1, double alpha2) noexcept
	{
		using namespace std::string_literals;

		app_.addDataItem(app_.createString("alpha1: "s, std::to_string(alpha1)), IsFormated::Disable);
		app_.addDataItem(app_.createString("alpha2: "s, std::to_string(alpha2)), IsFormated::Disable);

		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
	}


	void Solution::printVarX(double x1, double x2) noexcept
	{
		using namespace std::string_literals;
		app_.addDataItem(app_.createString("x1: "s, std::to_string(x1)), IsFormated::Disable);
		app_.addDataItem(app_.createString("x2: "s, std::to_string(x2)), IsFormated::Disable);

		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
	}

	void Solution::printAccuracy(double accuracy) noexcept
	{
		using namespace std::string_literals;

		app_.addDataItem(app_.createString("точность: "s, std::to_string(accuracy)), IsFormated::Disable);
		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
	}

	double Solution::getAlpha(double gfx, double last_alpha, double lambda) const noexcept
	{
		return gfx > 0 ? 0 : last_alpha - lambda * gfx;
	}

	double Solution::funcF1(double x) const noexcept
	{
		return 18 - 2 * x;
	}

	double Solution::funcF2(double x) const noexcept
	{
		return 12 - 2 * x;
	}

	void Solution::printFG(double x, size_t iter, const std::string& title) noexcept
	{
		app_.addDataItem(title+"(x"+std::to_string(iter)+") = "+std::to_string(x)+" > 0");
		std::string str{ "Найденая точка" };
		str += (x < 0 ? " не" : "");
		str += " принадлежит области допустимых решений";
		app_.addDataItem(std::move(str));
		app_.addDataItem(app_.dividingLine('.'), IsFormated::Disable);
	}
}