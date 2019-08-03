/*0-6对应周日-周六*/
int calc(int yy, int m, int d) {
    if (m < 3) m += 12, yy --;
    int c = yy / 100, y = yy % 100;
    int w = (c / 4 - c * 2 + y + y / 4 + (13 * (m + 1)) / 5 + d - 1) % 7;
    return (w + 7) % 7;
}