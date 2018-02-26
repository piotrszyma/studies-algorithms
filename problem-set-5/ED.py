class ED:
    def __init__(self):
        self.operations = 0

    def edit_distance(self, str1, str2):
        self.operations += 1

        def lev_ind(i, j):
            if str1[i - 1] == str2[j - 1]:
                return 0
            else:
                return 1

        def lev_ed(i, j):
            if min(i, j) == 0:
                return max(i, j)
            else:
                return min(
                    (lev_ed(i - 1, j) + 1),
                    (lev_ed(i, j - 1) + 1),
                    (lev_ed(i - 1, j - 1) + lev_ind(i, j))
                )

        return lev_ed(len(str1), len(str2))

    def clear_operations(self):
        self.operations = 0
