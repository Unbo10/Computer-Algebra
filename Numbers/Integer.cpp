#ifndef INTEGER_H
#define INTEGER_H

#include "../utils/List.cpp"

class Integer
{
    private:
        static const int DEFAULT_BASE = 100000;
        static const int digitsByBlock = 5;

        List<int> digitsInteger;
        int BASE = DEFAULT_BASE;
        bool sign;

        static int max(int x, int y)
        {
            if(x < y) return y;
            return x;
        }

        void forceAdd(long long newDigit)
        {
            if(newDigit == 0) digitsInteger.add(0);
            while(0 < newDigit)
            {
                int res = newDigit%BASE;
                newDigit /= BASE;
                digitsInteger.add(res);
            }
        }

        // O(log_10 (n))
        static int digits(int x)
        {
            int c = 0;
            while(x != 0)
            {
                x /= 10;
                c++;
            }
            return c;
        }
    public:
        Integer(): Integer(0) {}
        Integer(long long x)
        {
            sign = x >= 0;
            addDigit(sign? x: -x);
        }

        void addDigit(long long newDigit)
        {
            if(newDigit <= 0) return;
            forceAdd(newDigit);
        }

        int digitAt(int index) const
        {
            try{
                return digitsInteger[index];
            }catch(const std::invalid_argument& e)
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
            if (first.sign ^ second.sign) 
                throw std::invalid_argument("Addition of Integers with different signs is not supported yet.");

            if (first.BASE != second.BASE) 
                throw std::invalid_argument("Not defined sum of integers in different Bases yet");

            Integer sumOfIntegers;
            int length = max(first.numberSize(), second.numberSize());
            int c = 0;
            long long res = 0;

            while (c < length || res != 0)
            {
                res += first.digitAt(c) + second.digitAt(c);
                sumOfIntegers.addDigit(res % first.BASE);
                res /= first.BASE;
                c++;
            }

            return sumOfIntegers;
        }


        friend std::ostream& operator<<(std::ostream& os, const Integer& number)
        {
            if(number.digitsInteger.size() == 0) return os << '0';

            if(!number.sign) os << "-";
            
            os << number.digitAt(number.digitsInteger.size() - 1);
            for(int i = number.digitsInteger.size() - 2; i >= 0; i--)
            {
                for(int j = 0; j < Integer::digitsByBlock- digits(number.digitAt(i)); j++)
                    os << '0';
                os << number.digitAt(i);
            }  
            return os << " (based-)" << number.BASE;
        }

        void operator+=(const Integer& other)
        {
            *this = *this + other;
        }

        Integer& operator=(long long number)
        {
            digitsInteger.clear();
            sign = number >= 0;
            this->addDigit((sign)? number : -number);
            return *this;
        }

        List<int> getList()
        {
            return digitsInteger;
        }
};

#endif