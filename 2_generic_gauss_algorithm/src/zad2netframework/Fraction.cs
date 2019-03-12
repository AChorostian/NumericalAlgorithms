using System;
using System.Numerics;

namespace zad2netframework
{
    public class Fraction
    {
        private BigInteger numerator;
        private BigInteger denominator;

        public Fraction(BigInteger n, BigInteger d)
        {
            this.numerator = n;
            this.denominator = d;
        }
        public static Fraction operator +(Fraction a, Fraction b)
        {
            Fraction f = (a.denominator == b.denominator)
                ? new Fraction((a.numerator + b.numerator), a.denominator)
                : new Fraction((a.numerator * b.denominator) + (b.numerator * a.denominator), (a.denominator * b.denominator));
            return f.Fix();
        }
        public static Fraction operator -(Fraction a, Fraction b)
        {
            Fraction f = (a.denominator == b.denominator)
                ? new Fraction((a.numerator - b.numerator), a.denominator)
                : new Fraction((a.numerator * b.denominator) - (b.numerator * a.denominator), (a.denominator * b.denominator));
            return f.Fix();
        }
        public static Fraction operator *(Fraction a, Fraction b)
        {
            Fraction f = new Fraction((a.numerator * b.numerator), (a.denominator * b.denominator));
            return f.Fix();
        }
        public static Fraction operator /(Fraction a, Fraction b)
        {
            Fraction f = new Fraction((a.numerator * b.denominator), (a.denominator * b.numerator));
            return f.Fix();
        }
        public static bool operator <(Fraction a, Fraction b)
        {
            return a.denominator == b.denominator
                ? a.numerator < b.numerator ? true : false
                : (a.numerator * b.denominator) < (b.numerator * a.denominator) ? true : false;
        }
        public static bool operator >(Fraction a, Fraction b)
        {
            return a.denominator == b.denominator
                ? a.numerator > b.numerator ? true : false
                : (a.numerator * b.denominator) > (b.numerator * a.denominator) ? true : false;
        }
        public static bool operator ==(Fraction a, Fraction b)
        {
            a.Fix();
            b.Fix();
            return a.numerator == b.numerator ? true : false ;
        }
        public static bool operator !=(Fraction a, Fraction b)
        {
            return a.denominator == b.denominator
                ? a.numerator != b.numerator ? true : false
                : (a.numerator * b.denominator) != (b.numerator * a.denominator) ? true : false;
        }
        public override bool Equals(Object obj)
        {
            if (obj == null)
                return false;

            var second = obj as Fraction;

            return second != null && numerator == second.numerator;
        }

        public override int GetHashCode()
        {
            return 0;
        }
        public static implicit operator Fraction(float x)
        {
            Fraction f = new Fraction((BigInteger)(x * (float)(32768)), (BigInteger)(32768));
            return f.Fix();
        }
        public static implicit operator double(Fraction f)
        {
            double num = (double)f.numerator;
            double den = (double)f.denominator;
            return num/den;
        }
        public Fraction Fix()
        {
            // skracanie ułamka
            BigInteger a = this.numerator < 0 ? -this.numerator : this.numerator;
            BigInteger b = this.denominator < 0 ? -this.denominator : this.denominator;
            while (a != 0 && b != 0)
            {
                if (a > b)
                    a %= b;
                else
                    b %= a;
            }
            BigInteger d = (a == 0 ? b : a);
            // naprawa minusów
            if (d > 1)
            {
                this.numerator /= d;
                this.denominator /= d;
            }
            if (this.denominator < 0)
            {
                this.numerator *= -1;
                this.denominator *= -1;
            }
            return this;
        }
        public override string ToString()
        {
            return numerator.ToString() + "/" + denominator.ToString();
        }

    }
}
