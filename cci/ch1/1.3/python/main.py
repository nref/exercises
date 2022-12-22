def urlify(url: str) -> bool:
   
    s = list(url)
    r_start : int = len(s) - 1;
    l_start : int = r_start;

    while (s[l_start - 1]) == ' ':
        l_start -= 1

    j : int = r_start;
    for i in range(l_start - 1, 0, -1):
        if s[i] == ' ':
            s[j] = '0'
            s[j-1] = '2'
            s[j-2] = '%'
            j -= 3
        else:
            s[j] = s[i]
            j -= 1
        print("'" + "".join(s) + "'")

    return "".join(s)


assert(urlify("Mr Doug Slater    ") == "Mr%20Doug%20Slater")
