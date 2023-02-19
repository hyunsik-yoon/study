# 1207_Unique_Number_of_Occurrences

# https://leetcode.com/problems/unique-number-of-occurrences/description/

class Solution:
    def uniqueOccurrences(self, arr: List[int]) -> bool:

        m = {}

        for num in arr:
            if num in m:
                m[num] += 1
            else:
                m[num] = 0

        # REMEMBER python set()
        s = set()

        # REMEMBER dictionary values()
        # REMEMBER way to check existence
        for item in m.values():
            if item in s:
                return False
            else:
                s.add(item)

        """
        REMEMBER other way to iterate dictionary

        for item in m.items():
            key = item[0]
            val = item[0]
    	    print(key, val)

        # or

        for key in m.keys():
    	    print(key, m[key])

        # or

        for v in m.values():
    	    print(v)

        """

        return True
