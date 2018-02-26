def ed_lcs(str1, str2):
    list1 = list(str1)
    list2 = list(str2)

    matrix = [[0 for x in range(len(str2) + 1)] for y in range(len(str1) + 1)]

    lcs_operations = 0

    for i in range(len(str1) + 1):
        for j in range(len(str2) + 1):
            matrix[i][j] = 0

    for i in range(1, len(str1) + 1):
        matrix[i][0] = i

    for j in range(1, len(str2) + 1):
        matrix[0][j] = j

    # for i in range(len(str2) + 1):
    #     matrix[0][i] = 0

    for i in range(1, len(str1) + 1):
        for j in range(1, len(str2) + 1):
            lcs_operations += 1
            if list1[i - 1] == list2[j - 1]:
                matrix[i][j] = matrix[i - 1][j - 1] + 1
            else:
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1])

    lcs = ""

    # for i in range(len(str1) + 1):
    #     for j in range(len(str2) + 1):
    #         print(matrix[i][j], end='')
    #         print(" ", end='')
    #     print("")

    c_x = len(str1)
    c_y = len(str2)

    while c_x != 0 and c_y != 0:
        if matrix[c_x][c_y] == matrix[c_x][c_y - 1]:
            c_y -= 1
        elif matrix[c_x][c_y] == matrix[c_x - 1][c_y]:
            c_x -= 1
        else:
            lcs += list1[c_x - 1]
            c_x -= 1
            c_y -= 1

    return lcs[::-1]
    # return lcs_operations
