#pragma once
#include "ConsoleInterface.h"
#include <vector>
#include <string>
#include <optional>
#include <random>
#include <type_traits>

namespace KHAS {

	class Solution final
	{
	private:
		const std::string window_name_;
		ConsoleInterface app_;
	public:
		explicit Solution(const std::string& title) noexcept;

		void start() noexcept;

	private:
		void init() noexcept;
		double generateRandom() const noexcept;

		bool checkValue(double x1, double x2) const noexcept;

		double funcF(double x1, double x2) const noexcept;
		double funcF1(double x) const noexcept;
		double funcF2(double x) const noexcept;

		double funcG1(double x1, double x2) const noexcept;
		double funcG2(double x1, double x2) const noexcept;


		void printStartData(double x1, double x2, double fx, double lambda, double coef_accuracy) noexcept;


		void printDerivatives() noexcept;
		void printNowIter(size_t iter) noexcept;

		void printAlpha(double alpha1, double alpha2) noexcept;

		void printVarX(double x1, double x2) noexcept;

		void printAccuracy(double accuracy) noexcept;

		void printFG(double x, size_t iter, const std::string& title, bool is_belongs) noexcept;

		void findingOptimalAccuracy(double x1, double x2, double fx, double lambda, double coef_accuracy) noexcept;
		double getAlpha(double gfx, double last_alpha, double lambda) const noexcept;
	private:	


		template <typename T>
			requires std::is_arithmetic_v<T>
		T randFromRange(T lhs, T rhs) const noexcept;

	};

	template <typename T>
		requires std::is_arithmetic_v<T>
	T Solution::randFromRange(T lhs, T rhs) const noexcept
	{
		std::mt19937 gen{ std::random_device{}() };

		if constexpr (std::is_floating_point_v<T>) {
			std::uniform_real_distribution<> dist(lhs, rhs);
			return dist(gen);
		}
		else
		{
			std::uniform_int_distribution<> dist(lhs, rhs);
			return dist(gen);
		}
	}
}



