#ifndef INTEGER_H
#define INTEGER_H

#include "../utils/List.cpp"

class Integer
{
    private:
        static const int DEFAULT_BASE = 100001;

        List<int> digitsInteger;
        int BASE;
        bool sign;

        static int max(int x, int y)
        {
            if(x < y) return y;
            return x;
        }
    public:

        Integer(int BASE)
        {
            this->BASE = BASE;
            sign = 1;
        }

        Integer(bool sign) : Integer(DEFAULT_BASE) {this->sign = sign;}

        Integer() : Integer(DEFAULT_BASE) {}

        Integer(int represent, int BASE) : Integer(BASE)
        {
            sign = (represent >= 0);
            represent = represent*sign;
            addDigit(represent);
        }

        Integer(long represent) : Integer(DEFAULT_BASE)
        {
            sign = (represent >= 0);
            represent = represent*sign;
            addDigit(represent);
        }

        Integer(long long represent) : Integer(DEFAULT_BASE)
        {
            sign = (represent >= 0);
            represent = represent*sign;
            addDigit(represent);
        }

        void addDigit(long long newDigit)
        {
            if(newDigit <= 0) return;

            while(0 < newDigit)
            {
                int res = newDigit%BASE;
                newDigit /= BASE;
                digitsInteger.add(res);
            }
        }

        int digitAt(int index)
        {
            try{
                return digitsInteger[index];
            }catch(const std::out_of_range& e)
            {
                return 0;
            }
        }

        int numberSize()
        {
            return digitsInteger.size();
        }

        int getBase()
        {
            return BASE;
        }

        friend Integer operator+(Integer first, Integer second)
        {
            // por el momento usamos esta linea, porque diferentes signos
            // implica que se hace una resta
            if(first.sign ^ second.sign) throw std::invalid_argument("Addition of Integers with different signs is not supported yet.");
            Integer sumOfIntegers(first.sign);
            int length = max(first.numberSize(), second.numberSize());
            int c = 0;
            long long expB = 1, expD = 1, res = 0;
            int B = first.getBase(), D = second.getBase();

            while(c < length || res != 0)
            {
                res += first.digitAt(c)*expB + second.digitAt(c)*expD;
                expB *= B;
                expD *= D;

                sumOfIntegers.addDigit(res%DEFAULT_BASE);
                res /= DEFAULT_BASE;
            }

            return sumOfIntegers;
        }

        friend std::ostream& operator<<(std::ostream& os, Integer& number)
        {
            //if(number.numberSize() == 0) return os << '0';

            if(!number.sign) os << "-";

            for(int i = number.numberSize() - 1; 0 <= i; i--)
            {
                os << number.digitsInteger[i];
            }  
            return os;
        }

        void operator=(long long number)
        {
            digitsInteger.clear();
            sign = number >= 0;
            this->addDigit((sign)? number: -number);
        }
};

#endif