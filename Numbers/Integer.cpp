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

        static void cleanDigits(Integer& num)
        {
            int length = num.numberSize();
            while(num.digitAt(length-1) == 0)
                length--;
            List<int> clean(length);
            for(int i = 0; i < length; i++)
                clean.add(num.digitAt(i));

            num.digitsInteger = clean;
        }

        static int karatsuba(Integer& num1, Integer& num2, int start, int end)
        {
            if(start == end) return num1.digitAt(start)*num2.digitAt(start);

        }

    public:
        Integer(): Integer(0) {}
        Integer(long long x)
        {
            sign = x >= 0;
            addDigit(sign? x: -x);
        }
        Integer(const Integer& toC) : digitsInteger(toC.digitsInteger), sign(toC.sign), BASE(toC.BASE) {}
        //~Integer() {}

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

        int numberSize() const
        {
            return digitsInteger.size();
        }

        int getBase()
        {
            return BASE;
        }

        // operaciones entre numeros
        friend Integer operator-(const Integer& num)
        {
            Integer toR(num);
            toR.sign = !toR.sign;
            return toR;
        }

        friend Integer operator+(Integer first, Integer second)
        {
            if (first.sign ^ second.sign) 
            {
                if(first.sign == true)
                    return first - (-second);
                return second - (-first);
            }
                

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
            sumOfIntegers.sign = first.sign;
            Integer::cleanDigits(sumOfIntegers);
            return sumOfIntegers;
        }

        friend Integer operator-(const Integer& num1, const Integer& num2)
        {
            if (num1.BASE != num2.BASE) 
                throw std::invalid_argument("Not defined difference of integers in different Bases yet");

            if(num1 < num2)
                return -(num2 - num1);

            bool carry = 0;
            int maxSize = Integer::max(num1.numberSize(), num2.numberSize());
            Integer tR;
            tR.BASE = num1.BASE;

            for(int i = 0; i < maxSize; i++)
            {
                int kResult = num1.digitAt(i) - num2.digitAt(i) - carry;
                if(kResult < 0)
                {
                    carry = 1;
                    kResult += num1.BASE;
                }
                else carry = 0;
                tR.forceAdd(kResult);
            }

            Integer::cleanDigits(tR);
            return tR;
        }

        /*friend Integer operator*(const Integer& num1, const Integer& num2)
        {

            return std::nullptr;
        }*/

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

        // operadora de asignacion
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

        // operadores de comparacion
        friend bool operator<(const Integer& num1, const Integer& num2)
        {
            if(num2.sign == 0 && num1.sign == 1) return false;
            else if(num2.sign == 1 && num1.sign == 0) return true;
            else if(num2.sign == 1 && num1.sign == 1)
            {
                int length = Integer::max(num2.numberSize(), num1.numberSize());
                for(int i = length - 1; 0 <= i; i--)
                {
                    if(num1.digitAt(i) < num2.digitAt(i))
                        return true;
                    else if(num2.digitAt(i) < num1.digitAt(i))
                        return false;
                }

                return false;
            }

            return -num2 < -num1;
        }  

        friend bool operator==(Integer& num1, Integer& num2)
        {
            return num1.digitsInteger == num2.digitsInteger;
        }

        friend bool operator<=(Integer& num1, Integer& num2)
        {
            return num1 < num2 || num1 == num2;
        }

        friend bool operator>(Integer& num1, Integer& num2)
        {
            return  num2 < num1;
        }

        friend bool operator>=(Integer& num1, Integer& num2)
        {
            return num1 > num2 || num1 == num2;
        }

        List<int> getList()
        {
            return List(digitsInteger);
        }
};

#endif