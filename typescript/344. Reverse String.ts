function reverseString(s: string[]) {
  for (let i = 0; i < Math.floor(s.length / 2); i++) {
    let t = s[i];
    s[i] = s[s.length - 1 - i];
    s[s.length - 1 - i] = t;
  }
}
