#ifndef PSANDS_CISP430_OPERAND_H
#define PSANDS_CISP430_OPERAND_H

namespace psands_cisp430_a3
{
	class Operand
	{
	private:
		double _value;
	public:
		Operand();
		Operand(double value);
		~Operand();
		double getValue();
		void setValue(double value);
	};
}

#endif // PSANDS_CISP430_OPERAND_H