"""
1249_Minimum_Remove_to_Make_Valid_Parentheses

https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/

이상한 괄호가 있으면 없애는 문제

e.g., "a)b(c)d(e" ==> "ab(c)de"

"""
class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:

        REMOVE = 'R'

        if str == "": return ""

        s = list(s)
        st = []

        for k in range(0, len(s)):
            if s[k].islower(): continue
            elif s[k] == '(':
                st.append(k)
            elif s[k] == ')':
                if len(st) == 0:
                    s[k] = REMOVE
                else:
                    st.pop()

        while len(st) > 0:
            k = st.pop()
            s[k] = REMOVE

        return "".join([c for c in s if c != REMOVE])
