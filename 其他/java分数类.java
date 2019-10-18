public static class Fraction {//偷懒写法，中间不约分
    public BigInteger x, y;
    public Fraction(BigInteger x, BigInteger y) {
        this.x = x; this.y = y; }
    public static Fraction add(Fraction a, Fraction b) {
        return new Fraction(a.x.multiply(b.y).add(a.y.multiply(b.x)), a.y.multiply(b.y)); }
    public static Fraction sub(Fraction a, Fraction b) {
        return new Fraction(a.x.multiply(b.y).subtract(a.y.multiply(b.x)), a.y.multiply(b.y)); }
    public static Fraction neg(Fraction a) {
        return new Fraction(a.x.negate(), a.y); }
    public static Fraction mul(Fraction a, Fraction b) {
        return new Fraction(a.x.multiply(b.x), a.y.multiply(b.y)); }
    public static Fraction div(Fraction a, Fraction b) {
        return new Fraction(a.x.multiply(b.y), a.y.multiply(b.x)); }
    public static boolean isZero(Fraction a) {
        return a.x.equals(BigInteger.ZERO); }
    public static Fraction normal(Fraction a) {
        BigInteger gcd = a.x.gcd(a.y);
        return new Fraction(a.x.divide(gcd), a.y.divide(gcd)); }
    public static void print(Fraction a) {
        a = Fraction.normal(a);
        System.out.println(a.x + "/" + a.y); }
}