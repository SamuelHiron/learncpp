int main()
{ //No conversion needed, numeric promotion, numeric conversion, won’t compile due to narrowing conversion. Assume int and long are both 4 bytes.
    int a { 5 }; // 1a No conversion needed
    int b { 'a' }; // 1b numeric conversion => promotion
    int c { 5.4 }; // 1c narrowing conversion => won't compile
    int d { true }; // 1d numeric conversion => promotion
    int e { static_cast<int>(5.4) }; // 1e numeric conversion

    double f { 5.0f }; // 1f numerci promotion
    double g { 5 }; // 1g promo => conversion

    // Extra credit section
    long h { 5 }; // 1h promo => conversion

    float i { f }; // 1i (uses  previously defined variable f) narrowing conversion won't compile
    float j { 5.0 }; // 1j narrow  wont compile => allowed
}