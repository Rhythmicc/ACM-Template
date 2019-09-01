template <class T>
inline bool Read(T &ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

void Out(int a){
    if(a < 0){
        putchar('-');
        a = -a;
    }
    if(a >= 10)Out(a / 10);
    putchar(a % 10 + '0');
}