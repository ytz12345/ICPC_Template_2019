static class Fraction { 
    public BigInteger x, y;
    public Fraction(BigInteger x, BigInteger y) {
        this.x = x; this.y = y; }
    public Fraction(int x, int y) {
        this.x = BigInteger.valueOf(x);
        this.y = BigInteger.valueOf(y); }
    public Fraction add(Fraction b) {
        return  new Fraction(x.multiply(b.y).add(y.multiply(b.x)), y.multiply(b.y)).normal(); }
    public Fraction sub(Fraction b) {
        return new Fraction(x.multiply(b.y).subtract(y.multiply(b.x)), y.multiply(b.y)).normal(); }
    public Fraction mul(Fraction b) {
        return new Fraction(x.multiply(b.x), y.multiply(b.y)).normal(); }
    public Fraction div(Fraction b) {
        return new Fraction(x.multiply(b.y), y.multiply(b.x)).normal(); }
    public boolean isZero() {
        return x.equals(BigInteger.ZERO); }
    public Fraction normal() {
        BigInteger gcd = x.gcd(y);
        return new Fraction(x.divide(gcd), y.divide(gcd)); }
}